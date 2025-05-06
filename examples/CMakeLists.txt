function(create_example_executable NAME SOURCES)
    add_executable(${NAME} ${SOURCES})
    target_link_libraries(${NAME} PRIVATE litegui)
    target_include_directories(basic PRIVATE ${CMAKE_SOURCE_DIR}/src)

    # We need to copy SDL3 libs.
    add_custom_command(TARGET basic POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3-shared>
        $<TARGET_FILE_DIR:${NAME}>
    )
endfunction()

add_subdirectory(basic)