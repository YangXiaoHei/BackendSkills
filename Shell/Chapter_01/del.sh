#! /bin/bash

#array to store command line arguments expcept the first one
declare -a args

# iterator controller
i=0

# for loop to assign variable
for arg in $@
do
    [ $i -ne 0 ] && args[$i]=$arg
    let i++ # make i increment
done

input_file_name=$1
output_file_name=`egrep "$[^.]+"`


