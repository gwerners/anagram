cmake_minimum_required(VERSION 3.10.2)

#set( CMAKE_VERBOSE_MAKEFILE on )

if(DEFINED ENV{ENABLE_SIMD})
  add_definitions(-DUSE_SIMD)
endif()

set(CMAKE_CXX_FLAGS $ENV{CXXFLAGS})
set(CMAKE_CXX_FLAGS_RELEASE $ENV{CXXFLAGS})
message("CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE}")
message("CXXFLAGS $ENV{CXXFLAGS}")

if(DEFINED ENV{IGNORE_LESS})
  #add_compile_definitions(IGNORE_WORDS_WITH_LESS_LETTERS)
  add_definitions(-DIGNORE_WORDS_WITH_LESS_LETTERS)
endif()

if(DEFINED ENV{ENABLE_SIMD})
  project (anagram_SIMD)
  add_executable(anagram_SIMD main.cpp anagram_simd.cpp)
else()
  project (anagram)
  add_executable(anagram main.cpp anagram.cpp)
endif()
