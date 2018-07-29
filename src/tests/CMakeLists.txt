project(unit_tests)

include(CMTestUtils)

# declare tests
cm_add_test(simple_test simple_test.cpp)
cm_add_test(file_test file_test.cpp)
