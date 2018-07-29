#pragma once

#include <string>
#include <memory>

class GameOfLifeImpl;

/**
 * \brief The GameOfLife main entity.
 *
 * This is a popular game.
 */
class GameOfLife
{
public:
    /**
     Constructor.
     @param grid_width the width of grid
     @param grid_height the height of grid
     */
    GameOfLife( const size_t grid_width = 30, const size_t grid_height = 20 );

    /**
     Destructor.
     */
    ~GameOfLife( );

    /**
     Initialization of grid.
     @param init_file_path the path to file. If it is an empty string then initialization will be random.
     If the file format is incorrect - undefined behaviour!
     @return true if success, otherwise - false
     */
    bool init( const std::string& init_file_path = "" );

    /**
     Calculates new generation.
     @param num_of_threads the count of threads.
     */
    void iterate( const size_t num_of_threads = 2 );

    /**
     Prints current generation.
     @param file_path the output file path for printing.
     If empty - prints to console.
     @param append_to_file if true - append to file, otherwise - rewrite.
     */
    void print( const std::string& file_path = "", const bool append_to_file = true ) const;

private:
    std::unique_ptr<GameOfLifeImpl> m_p_impl;
};
