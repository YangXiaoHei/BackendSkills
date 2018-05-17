#! /bin/bash

[ -z $1 ] && echo "no num to convert" || echo "obase=16; $1" | bc
