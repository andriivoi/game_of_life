#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>
#include "game_of_life.h"

int main()
{
    GameOfLife game;

    assert( game.init( ) );
    //assert( game.init( "init_file.txt" ) );

    game.print( ); // prints init state

    while (true) // You should terminate the program
    {
        game.iterate( );

        game.print( );
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // delay
    }

    return 0;
}
