include_directories(${EXT_DIRECTORY}/doctest)
include_directories(${SRC_DIRECTORY})

# Creates a test and adds it to CTest.
function(create_test TEST_NAME TEST_SOURCE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE litegui)
    add_test(NAME "${TEST_NAME}" COMMAND ${TEST_NAME})
endfunction()

# Test list:
create_test(test_event test_event.cpp)