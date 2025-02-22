cmake_minimum_required(VERSION 3.8)

project("Game")
add_executable(${PROJECT_NAME} "src/main.c" "src/game.c" "src/game.h")
add_compile_definitions(ASSETS_DIRECTORY="../../../../assets")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/raylib/include")
target_link_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/raylib/lib")
target_link_libraries(${PROJECT_NAME} PUBLIC "raylib.lib"
                                             "winmm.lib")