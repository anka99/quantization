#!/bin/bash

if [[ $# -ne 2 ]]; then
  echo "Illegal number of arguments."
  exit 1
fi

PROGRAM="${1}"
DIRECTORY="${2}"

if [[ ! -e "${PROGRAM}" ]]; then
  echo "Invalid path to file."
  exit 2
elif [[ ! -x "${PROGRAM}" ]]; then
  echo "File is not acceptable."
  exit 3
elif [[ ! -d "${DIRECTORY}" ]]; then
  echo "Invalid directory."
  exit 4
fi

for f in "${DIRECTORY}"/*.in
do
   echo "${f}"
   valgrind -q --leak-check=full --track-origins=yes ./"${PROGRAM}" <"${f}" >temp.out 2>temp.err
   diff -q temp.out "${f::-3}".out
   diff -q temp.err "${f::-3}".err
 done
 
 rm temp.out
 rm temp.err
