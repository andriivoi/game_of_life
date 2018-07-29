#pragma once

#include "grid_impl.h"

class GameOfLifeImpl
{
public:
    GameOfLifeImpl( const size_t grid_width, const size_t grid_height );

    bool init( const std::string& init_file_path );

    void iterate( const size_t num_of_threads );

    void print( const std::string& file_path, const bool append_to_file ) const;

    GridImpl m_current_generation;
    GridImpl m_next_generation;
};
