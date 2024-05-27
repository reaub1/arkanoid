cmake_minimum_required(VERSION 3.7)

project(Arkanoid LANGUAGES C)

# Add the directory where FindSDL2_ttf.cmake is located
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Include the path to SDL2_ttf
include_directories(/usr/include/SDL2)

# Find SDL2_ttf library
find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf HINTS /usr/lib/x86_64-linux-gnu)

if (SDL2_TTF_LIBRARY)
    message(STATUS "Found SDL2_ttf: ${SDL2_TTF_LIBRARY}")
else ()
    message(FATAL_ERROR "SDL2_ttf library not found")
endif ()

add_executable(${PROJECT_NAME} main.c init.c draw.c update.c menu.c game.c block.c)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARY})

# Copy resource files to the binary directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sprites.bmp
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Arkanoid_sprites.bmp
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Arkanoid_ascii.bmp
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/level/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/level/)
