cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 17)

project(seqpp)

add_library(
  ${PROJECT_NAME} SHARED
  src/commands.cpp
  src/instrument.cpp
  src/instrument.h
  src/music.cpp
  src/music.h
)

add_subdirectory(external/rtmidi)

target_include_directories(
  ${PROJECT_NAME} 
  PRIVATE external/rtmidi/
)

target_link_directories(
  ${PROJECT_NAME}
  PRIVATE external/rtmidi/
)

target_link_libraries(
  ${PROJECT_NAME}
  LINK_PRIVATE rtmidi
)
