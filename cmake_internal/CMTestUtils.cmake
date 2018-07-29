function(cm_add_test test_name test_source)
    add_executable(${test_name} ${test_source})

    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${UNIT_TEST_BIN_OUTPUT_DIR})

    target_link_libraries(${test_name}
                           PRIVATE
                               GameOfLifeEngine
    )

    set_target_properties(${test_name}
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${UNIT_TEST_BIN_OUTPUT_DIR}
    )
endfunction()
