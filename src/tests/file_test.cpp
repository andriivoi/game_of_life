#include <iostream>
#include <cassert>
#include <fstream>

#include "test_utils.h"
#include "game_of_life.h"

static constexpr auto OUT_FILE_TEST = "out_file_test.txt";

static constexpr auto INIT_FILE_COMPLEX = "init_file_complex.txt";
static constexpr auto BENCHMARK_COMPLEX = "benchmarks/benchmark_complex.txt";

static constexpr auto INIT_FILE_SIMPLE = "init_file_simple.txt";
static constexpr auto BENCHMARK_SIMPLE = "benchmarks/benchmark_simple.txt";

bool compare_files(const std::string& file_path_1, const std::string& file_path_2)
{
  std::ifstream f1(file_path_1, std::ifstream::binary|std::ifstream::ate);
  std::ifstream f2(file_path_2, std::ifstream::binary|std::ifstream::ate);

  if (f1.fail() || f2.fail())
  {
    return false; //file problem
  }

  if (f1.tellg() != f2.tellg())
  {
    return false; //size mismatch
  }

  //seek back to beginning and use std::equal to compare contents
  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
}

void run_test_1( )
{
    GameOfLife test_game( 25, 25 );

    assert( test_game.init( INIT_FILE_COMPLEX ) );
    test_game.print( OUT_FILE_TEST );

    const bool success = compare_files( INIT_FILE_COMPLEX, OUT_FILE_TEST );

    std::remove( OUT_FILE_TEST );
    PRINT_TEST_RESULT( success );
}

void run_test_2( )
{
    GameOfLife test_game( 25, 25 );

    assert( test_game.init( INIT_FILE_SIMPLE ) );
    test_game.print( OUT_FILE_TEST );
    for(int i = 0; i < 50; i++)
    {
        test_game.iterate( 1 );
        test_game.print( OUT_FILE_TEST );
    }

    const bool success = compare_files( OUT_FILE_TEST, BENCHMARK_SIMPLE );

    std::remove( OUT_FILE_TEST );
    PRINT_TEST_RESULT( success );
}

void run_test_3( )
{
    GameOfLife test_game( 25, 25 );

    assert( test_game.init( INIT_FILE_COMPLEX ) );
    test_game.print( OUT_FILE_TEST );
    for(int i = 0; i < 200; i++)
    {
        test_game.iterate( 4 );
        test_game.print( OUT_FILE_TEST );
    }

    const bool success = compare_files( OUT_FILE_TEST, BENCHMARK_COMPLEX );

    std::remove( OUT_FILE_TEST );
    PRINT_TEST_RESULT( success );
}

int main()
{
    run_test_1( );
    run_test_2( );
    run_test_3( );

    return 0;
}
