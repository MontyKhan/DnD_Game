cmake_minimum_required(VERSION 3.16)  # CMake version check
project(DnD_Game LANGUAGES CXX)               	# Create project "DnD_Game"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

# Add main.cpp file of project root directory as source file
set (SOURCE_FILES
combatant.cpp 
csv_reader.cpp 
tools.cpp 
load_file.cpp 
weapon_type.cpp 
roll.cpp 
pathfinding.cpp 
player.cpp 
tile.cpp 
object.cpp 
display.cpp 
main.cpp
)

set( LIBS libs/rapidxml libs/sfml )

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(dnd_game ${SOURCE_FILES})
target_include_directories(dnd_game PRIVATE libs/include include/)

TARGET_LINK_LIBRARIES(dnd_game ${LIBS} )