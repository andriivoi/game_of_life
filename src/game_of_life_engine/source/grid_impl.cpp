#include <cstdio>
#include <iostream>
#include <fstream>
#include <thread>

#include "grid_impl.h"

enum CellCondition : char
{
    ALIVE = 1,
    DEAD = 0
};

GridImpl::GridImpl( const size_t size_x, const size_t size_y )
    : m_grid( size_x, std::vector<char>(size_y, CellCondition::DEAD) )
{
}

char GridImpl::get_cell( const size_t x, const size_t y ) const
{
    return m_grid[x][y];
}

int GridImpl::get_live_neighbors_count( const size_t cell_x, const size_t cell_y ) const
{
    size_t grid_size_x(0), grid_size_y(0);
    if( !get_grid_size( grid_size_x, grid_size_y ) )
        return 0;

    size_t upper = cell_y == 0 ? grid_size_y : cell_y - 1;

    size_t lower = cell_y + 1;
    if (lower >= grid_size_y)
        lower = 0;

    size_t left = cell_x == 0 ? grid_size_x : cell_x - 1;

    size_t right = cell_x + 1;
    if (right >= grid_size_x)
        right = 0;

    int count = 0;
    for (size_t x = left; x <= right; x++)
    {
        for (size_t y = upper; y <= lower; y++)
        {
            if ( cell_x == x && cell_y == y )
                continue;

            count += m_grid[x][y];
        }
    }
    return count;
}

char GridImpl::calc_cell( const char cur_state, const int num_live_neighbors ) const
{
    if ( CellCondition::ALIVE == cur_state )
    {
        if ( num_live_neighbors < 2 || num_live_neighbors > 3 )
            return CellCondition::DEAD;
    }
    else
    {
        if ( 3 == num_live_neighbors )
            return CellCondition::ALIVE;
    }

    return cur_state;
}

void GridImpl::recalculate( const GridImpl& previous_generation, const size_t num_of_threads )
{
    size_t grid_size_x(0), grid_size_y(0);
    if( !get_grid_size( grid_size_x, grid_size_y ) )
        return;

    if ( num_of_threads > 1 )
        split_on_threads( previous_generation, num_of_threads );
    else
        calc_generation_in_range( previous_generation, 0, grid_size_x );
}

void GridImpl::calc_generation_in_range( const GridImpl& previous_generation, const size_t x_begin, const size_t x_end )
{
    size_t grid_size_x(0), grid_size_y(0);
    if( !get_grid_size( grid_size_x, grid_size_y ) )
        return;

    for (size_t x = x_begin; x < x_end; x++)
    {
        for (size_t y = 0; y < grid_size_y; y++)
        {
            m_grid[x][y] = calc_cell(previous_generation.get_cell(x, y), previous_generation.get_live_neighbors_count(x, y));
        }
    }
}

void GridImpl::split_on_threads( const GridImpl& previous_generation, const size_t num_of_threads )
{
    size_t grid_size_x(0), grid_size_y(0);
    if( !get_grid_size( grid_size_x, grid_size_y ) )
        return;

    std::vector<std::thread> threads;
    size_t prev_begin = 0;
    for (size_t i = 0; i < num_of_threads; i++)
    {
        const size_t cnt = grid_size_x / num_of_threads + (0 == i ? grid_size_x % num_of_threads : 0);
        const size_t end = prev_begin + cnt;
        threads.push_back(std::thread(&GridImpl::calc_generation_in_range, this, previous_generation, prev_begin, end));
        prev_begin = end;
    }

    for ( auto& thread : threads )
    {
        if( thread.joinable( ) )
            thread.join();
    }
}

bool GridImpl::initialize_random( )
{
    size_t grid_size_x(0), grid_size_y(0);
    if( !get_grid_size( grid_size_x, grid_size_y ) )
        return false;

    for (size_t y = 0; y < grid_size_y; y++)
    {
        for (size_t x = 0; x < grid_size_x; x++)
        {
            m_grid[x][y] = std::rand() % 2 == CellCondition::DEAD;
        }
    }

    return true;
}

inline bool check_for_valid_string( const std::string& inp_str )
{
    return !inp_str.empty( ) && ('|' == inp_str[0]);
}

bool GridImpl::initialize_from_file( const std::string& file_path )
{
    bool ret_val = false;

    std::ifstream file_inp( file_path );
    if ( file_inp.good() )
    {
        size_t cur_row = 0;
        std::string line_tmp;
        while( getline(file_inp, line_tmp) )
        {
            if(!check_for_valid_string(line_tmp))
                continue;

            for( size_t cur_col = 1; cur_col < line_tmp.length( ) - 1; cur_col++ ) // because '|' in the start and '|' in the end of every string
            {
                m_grid[cur_col - 1][cur_row] = '*' == line_tmp[cur_col]; // ? CellCondition::ALIVE : CellCondition::DEAD;
            }
            cur_row++;
        }
        ret_val = true;
    }
    else
    {
        std::cerr << "File not found!!!";
    }

    return ret_val;
}

inline void print_line( const size_t columns, std::ostream& out_stream )
{
    out_stream << ' ' << std::string( columns, '-' ) << std::endl;
}

void GridImpl::print( const std::string& file_path, const bool append_to_file ) const
{
    size_t grid_size_x(0), grid_size_y(0);
    if( !get_grid_size( grid_size_x, grid_size_y ) )
        return;

    // prepare stream
    std::ofstream ofs;
    const bool output_to_file = !file_path.empty( );
    if ( output_to_file )
        ofs.open( file_path, append_to_file ? std::ios_base::app : std::ios_base::trunc );

    std::ostream& out_stream  = output_to_file ? ofs : std::cout;

    // ouput to stream
    print_line(grid_size_x, out_stream);
    for (size_t y = 0; y < grid_size_y; y++)
    {
        out_stream << '|';
        for (size_t x = 0; x < grid_size_x; x++)
        {
            if ( CellCondition::ALIVE == m_grid[x][y])
                out_stream << '*';
            else
                out_stream << ' ';
        }
        out_stream << '|' << std::endl;
    }
    print_line(grid_size_x, out_stream);
    out_stream << std::endl;
}

bool GridImpl::get_grid_size( size_t& x, size_t& y ) const
{
    if( m_grid.empty( ) )
        return false;

    x = m_grid.size( );
    y = m_grid[0].size( );
    return true;
}
