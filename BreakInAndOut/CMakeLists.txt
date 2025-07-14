# CMakeList.txt : CMake project for BreakInAndOut, include source and define
# project specific logic here.
#

include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG        v3.13.0
)
FetchContent_MakeAvailable(entt)
# Add source to this project's executable.

set(SOURCES "src/main.cpp" "src/Scene.cpp" "src/Entity/Ball.cpp" "src/System/intergrate.cpp" "src/utils/math.cpp" "src/System/Draw.cpp" "src/utils/collisionDetection.cpp" "src/System/collision.cpp" "src/Entity/Block.cpp" "src/Entity/Paddle.cpp" "src/System/paddleMovement.cpp"   "src/System/switchLayer.cpp"  "src/Entity/ui/Button.cpp" "src/Entity/ui/Text.cpp" "src/Entity/ui/Panel.cpp" "src/Entity/ui/TextButton.cpp" "src/System/handleMouseClick.cpp" "src/UI/mainMenu.cpp"  "src/System/edit.cpp" "src/utils/Editor.cpp" "src/utils/Level.cpp" "src/System/watch.cpp" "src/UI/editPanel.cpp" "src/UI/levelPanel.cpp" "src/System/lunchBall.cpp" "src/System/damagePaddle.cpp"  "src/UI/selectCustomLevel.cpp" "src/System/pageTransition.cpp" "src/System/music.cpp" "src/System/checkWin.cpp")
add_executable (BreakInAndOut ${SOURCES})
target_include_directories(BreakInAndOut PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(BreakInAndOut PRIVATE raylib)
target_link_libraries(BreakInAndOut PRIVATE EnTT::EnTT)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(BreakInAndOut copy_assets)

add_custom_target(copy_levels
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/levels ${CMAKE_CURRENT_BINARY_DIR}/levels
)
add_dependencies(BreakInAndOut copy_levels)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BreakInAndOut PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
