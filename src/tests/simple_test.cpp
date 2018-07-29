#include <iostream>
#include <cassert>
#include "../source/include_impl/grid_impl.h"
#include "test_utils.h"

void run_test_1( )
{
    GridImpl test_grid( 20, 30 );

    int ret_val = 0;
    for( int i = 0; i < 10; i++ )
    {
        ret_val = test_grid.calc_cell(0, i);

        if ( 3 == i)
        {
            PRINT_TEST_RESULT(1 == ret_val);
        }
        else
        {
            PRINT_TEST_RESULT(0 == ret_val);
        }
    }
}

void run_test_2( )
{
    GridImpl test_grid( 20, 30 );

    int ret_val = test_grid.calc_cell(1, 3);
    PRINT_TEST_RESULT(1 == ret_val);

    ret_val = test_grid.calc_cell(1, 2);
    PRINT_TEST_RESULT(1 == ret_val);

    ret_val = test_grid.calc_cell(1, 1);
    PRINT_TEST_RESULT(0 == ret_val);

    ret_val = test_grid.calc_cell(1, 4);
    PRINT_TEST_RESULT(0 == ret_val);
}

int main()
{
    run_test_1( );
    run_test_2( );

    return 0;
}
