#!/bin/bash

#https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/
set -euo pipefail

#show debug info
#set -x

#move to script dir
cd "$(dirname "${0}")"

#save root dir
ROOT=$(pwd)

function CheckNeeded {
  NEEDED=$(which ${1})
  if [ ! -f "${NEEDED}" ]; then
    echo "You need ${1} to run this script!"
    exit 0
  fi
}
function MKDIR {
  if [ ! -d "${1}" ]; then
    mkdir ${1}
  fi
}
function RMDIR {
  if [ -d "${1}" ]; then
    rm -rf ${1}
  fi
}
function CleanUp {
  echo "Remove temp files..."
  RMDIR build
  RMDIR dict
}
function UnTarDict {
  if [ ! -d "dict" ]; then
    echo "creating dict dir with dictionaries"
    tar -xzf dict.tar.gz
  fi
}
function BuildProgram {
  if [ ! -d "build" ]; then
    MKDIR build
  fi
  cd build
  cmake -DCMAKE_BUILD_TYPE=$1 ..
  make
  cd ..
}
#check for options
if [ ${#} -ne 0 ]; then
  if [ "${1}" == "clean" ]; then
    CleanUp
    exit 1
  fi
    if [ "${1}" == "fix" ]; then
    ./fixFormat.bash
  fi
fi
#check if dependencies are ok
CheckNeeded cmake || exit 1
CheckNeeded g++ || exit 1

UnTarDict

#set build variables
BUILD_TYPE=Release

#don't search for words of size 2 or less
export IGNORE_LESS=1

#use AVX
export ENABLE_SIMD=1
export CXXFLAGS="-O2 -Wall -std=c++11 -mavx2"

#build!
BuildProgram $BUILD_TYPE

DICTIONARY=./dict/pt-Br_dictionary.txt

#run!
echo "running simd version."
echo "anagram_SIMD pt-Br_dictionary.txt gabrielfarinas"
time ./build/anagram_SIMD ${DICTIONARY} gabrielfarinas > ./build/gabrielfarinas.txt
count=$(wc -l ./build/gabrielfarinas.txt)
echo "total anagrams generated: ${count}"
echo "_______________________________________________________________________________"

echo "anagram_SIMD pt-Br_dictionary.txt gabrielwernersbachfarinas"
time ./build/anagram_SIMD ${DICTIONARY} gabrielwernersbachfarinas > ./build/gabrielwernersbachfarinas.txt
count=$(wc -l ./build/gabrielwernersbachfarinas.txt)
echo "total anagrams generated: ${count}"
echo "_______________________________________________________________________________"

################################################################################
#use non simd version:
unset ENABLE_SIMD
unset CXXFLAGS

#build!
BuildProgram $BUILD_TYPE

#run!
echo "running cpp version."
echo "anagram pt-Br_dictionary.txt gabrielfarinas"
time ./build/anagram ${DICTIONARY} gabrielfarinas > ./build/gabrielfarinas.txt
count=$(wc -l ./build/gabrielfarinas.txt)
echo "total anagrams generated: ${count}"
echo "_______________________________________________________________________________"

echo "anagram pt-Br_dictionary.txt gabrielwernersbachfarinas"
time ./build/anagram ${DICTIONARY} gabrielwernersbachfarinas > ./build/gabrielwernersbachfarinas.txt
count=$(wc -l ./build/gabrielwernersbachfarinas.txt)
echo "total anagrams generated: ${count}"
echo "_______________________________________________________________________________"

################################################################################
#include 1 and 2 letter words
unset IGNORE_LESS

#build again to search Tom Marvolo Riddle - now it will not ignore the word `i`
BuildProgram $BUILD_TYPE
DICTIONARY=./dict/minimal.txt
echo "running cpp version."
echo "anagram minimal.txt tommarvoloriddle"
time ./build/anagram ${DICTIONARY} tommarvoloriddle > ./build/voldemort.txt

echo "famous anagram(words are sorted):"
cat ./build/voldemort.txt
