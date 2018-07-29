#pragma once

#define PRINT_TEST_RESULT(success)\
    std::cout << __FUNCTION__ << " : " << ((success) ? "SUCESS" : "FAIL") << std::endl;\
    assert(success)
