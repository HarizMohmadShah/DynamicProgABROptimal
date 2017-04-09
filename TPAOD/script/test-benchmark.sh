#!/bin/sh

# Author : Bin Mohmad Shah Hariz
# Version : 1.0
# date : 09/4/2017

# This file run computeABROpt in /bin directory with
# parameter n: the total element in the dictionary which obtained in 
#              file benchmark_countX.in in /benchmark directory             
# parameter file: the benchmarkX.in in /benchmark directory
# (with X the benchmark number)
#
# this file create the output .c in /benchmark directory
# for each benchmark and compare it with .out correspond
#
# All file .c will be deleted at the end of this file execution
#
# To run this test: execute test-benchmark.sh in script directory

# move to parent directory
cd ..

# create temporary file
touch TMP

# loop for each benchmark.in file
for test in $(ls ./benchmark/*.in)
do

    echo "Test file $test..."
    base =$(basename $test .in)

    #execution of computeABROpt
    ./bin/computeABR 
    

    
 
