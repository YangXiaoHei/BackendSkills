#! /bin/bash

function fname() 
{
    echo $1, $2
    echo $@
    echo $*
    return 99;
}

fname 1 2 3 4 5
echo $0
