# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Create library.
add_library(litegui_lib STATIC litegui.cpp litegui.h types.h context.h event.h)
target_link_libraries(litegui_lib PUBLIC SDL3::SDL3)
target_include_directories(litegui_lib PUBLIC ${EXT_DIRECTORY}/sdl/include)

# Create executable.
add_executable(litegui main.cpp)
target_link_libraries(litegui PRIVATE litegui_lib)

# We need to copy SDL3 libs.
add_custom_command(TARGET litegui_lib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3-shared>
        $<TARGET_FILE_DIR:litegui_lib>
)
add_custom_command(TARGET litegui POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3-shared>
        $<TARGET_FILE_DIR:litegui>
)

# Configure included contexts.
option(CTX_SDL3 "Includes SDL3 context into the build." ON)
if (CTX_SDL3)
    add_subdirectory(contexts/sdl3)
    target_link_libraries(litegui_lib PUBLIC ctx_sdl3)
endif()