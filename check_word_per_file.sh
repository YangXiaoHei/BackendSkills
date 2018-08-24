#! /bin/bash

path_arr_file=$1
content_arr_file=$2

while read path
do
    while read word
    do
        if grep -q "$word" $path
        then
            echo "$path contains word $word"
        fi
    done < $content_arr_file
done < $path_arr_file
