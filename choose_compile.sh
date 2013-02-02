#!/bin/sh 

if [ "$#" -lt 2 ]
then
  echo "Usage: $0 [file] [choice] [optinal output name]"
  echo "Options:\n\t1\tVanilla g++"
  echo "\t2\tWith Boost and OpenCV"
  echo "\t3\tOnly OpenCV"
  echo "\t4\tOnly Boost"
  exit 1
fi

OUT=""

if ! [ -e "$1" ]
then
   echo "Nope. File doesn't exist.\n"
   exit 1
fi

#set output save location one is provided
if [ -n "$3" ] #if $3 is not empty
then
  OUT=$3
else
  OUT="a.out"
fi

if [ $2 = "1" ]; then 
  g++ $1 -o $OUT
  echo $?
fi
if [ $2 = "2" ]; then 
  g++ -g $1 `pkg-config --cflags opencv` `pkg-config --libs opencv` -lboost_system -lboost_filesystem -o $OUT
  echo $?
fi
if [ $2 = "3" ]; then 
  g++ -g $1 -o $OUT `pkg-config --cflags opencv` `pkg-config --libs opencv`
  echo $?
fi
if [ $2 = "4" ]; then 
  g++ -g $1 -I /home/dan/boost_1_51_0 -o $OUT -lboost_system -lboost_filesystem
  echo $?
fi

echo "Wrote: $OUT"

exit 0
