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

set(SOURCES "src/main.cpp" "src/Scene.cpp" "src/Entity/Ball.cpp" "src/System/intergrate.cpp" "src/utils/math.cpp")
add_executable (BreakInAndOut ${SOURCES})
target_include_directories(BreakInAndOut PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(BreakInAndOut PRIVATE raylib)
target_link_libraries(BreakInAndOut PRIVATE EnTT::EnTT)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BreakInAndOut PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
