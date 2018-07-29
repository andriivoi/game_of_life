#include <chrono>

#include "game_of_life_impl.h"

GameOfLifeImpl::GameOfLifeImpl( const size_t grid_width, const size_t grid_height )
    : m_current_generation(grid_width, grid_height)
    , m_next_generation(grid_width, grid_height)
{
    std::srand( static_cast<unsigned int>(time(nullptr)) );
}

bool GameOfLifeImpl::init( const std::string& init_file_path )
{
    if ( !init_file_path.empty( ) )
        return m_current_generation.initialize_from_file( init_file_path );
    else
        return m_current_generation.initialize_random( );
}

void GameOfLifeImpl::iterate( const size_t num_of_threads )
{
    m_next_generation.recalculate( m_current_generation, num_of_threads );

    std::swap( m_next_generation, m_current_generation );
}

void GameOfLifeImpl::print( const std::string& file_path, const bool append_to_file ) const
{
    m_current_generation.print( file_path, append_to_file );
}
