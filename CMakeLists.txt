cmake_minimum_required(VERSION 3.16)  # CMake version check
project(DnD_Game LANGUAGES CXX)       # Create project "DnD_Game"
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
battlemap.cpp
main.cpp
)

link_directories(${CMAKE_SOURCE_DIR}/lib)

if (WIN32)
  message("Platform identified as Windows")
  set(LIBS_PATH ${CMAKE_SOURCE_DIR}/libs/windows/)
  
  set(LIBS_DEBUG 
  sfml-graphics-d
  sfml-window-d
  sfml-system-d
  )
  set(LIBS_RELEASE 
  sfml-graphics
  sfml-window
  sfml-system
  )
endif (WIN32)

if (UNIX)
  message("Platform identified as Unix")
  set(LIBS_PATH ${CMAKE_SOURCE_DIR}/libs/linux/)
  
  set(LIBS_DEBUG 
  sfml-graphics
  sfml-window
  sfml-system
  )
  set(LIBS_RELEASE 
  sfml-graphics
  sfml-window
  sfml-system
  )
endif (UNIX)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(dnd_game ${CMAKE_SOURCE_DIR}/${SOURCE_FILES})
target_include_directories(dnd_game PRIVATE ${LIBS_PATH}include ${CMAKE_SOURCE_DIR}/include/)

if (CMAKE_BUILD_TYPE STREQUAL "RELEASE")
  message("Release build")
  set(LIBS ${LIBS_RELEASE})
  set(OUTPUT_DIRECTORY "build/release")
else ()
  message("Debug build")
  set(LIBS ${LIBS_DEBUG})
  set(OUTPUT_DIRECTORY "build/debug")
endif ()

foreach(LIB ${LIBS})
  find_library(FOUND_LIB_${LIB} ${LIB}
               HINTS ${LIBS_PATH}
              )
  message("Lib: ${LIB}")
  if (FOUND_LIB_${LIB})
    message("Found lib: ${FOUND_LIB_${LIB}}")
    set(FOUND_LIBS ${FOUND_LIBS} ${FOUND_LIB_${LIB}})
  else ()
    message("Lib not found!")
  endif ()
  
endforeach(LIB)

target_link_libraries(dnd_game ${FOUND_LIBS})

set_target_properties(dnd_game 
                      PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Debug/"
                                 RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}
                     )
