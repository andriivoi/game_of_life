#include "game_of_life.h"

#include "game_of_life_impl.h"

GameOfLife::GameOfLife( const size_t grid_width, const size_t grid_height )
    : m_p_impl( std::make_unique<GameOfLifeImpl>(grid_width, grid_height) )
{
}

GameOfLife::~GameOfLife( ) = default;

bool GameOfLife::init( const std::string& init_file_path )
{
    if( !m_p_impl )
        return false;

    return m_p_impl->init( init_file_path );
}

void GameOfLife::iterate( const size_t num_of_threads )
{
    if( m_p_impl )
        m_p_impl->iterate( num_of_threads );
}

void GameOfLife::print( const std::string& file_path, const bool append_to_file ) const
{
    if( m_p_impl )
        m_p_impl->print( file_path, append_to_file );
}
