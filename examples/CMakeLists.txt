function(create_sdl3_example NAME SOURCES)
    if (INCLUDE_SDL3)
        add_executable(${NAME} ${SOURCES})
        target_link_libraries(${NAME} PRIVATE litegui)
        target_include_directories(basic PRIVATE ${CMAKE_SOURCE_DIR}/src)
        target_include_directories(basic PRIVATE ${EXT_DIRECTORY}/sdl/include)

        # We need to copy SDL3 libs.
        add_custom_command(TARGET basic POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3::SDL3-shared>
            $<TARGET_FILE_DIR:${NAME}>
        )
    endif()
endfunction()

add_subdirectory(sdl3_basic)