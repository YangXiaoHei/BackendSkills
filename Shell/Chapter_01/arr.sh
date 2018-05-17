#! /bin/bash

arr=(1 2 3 4 5)
echo ${arr[@]}
echo ${arr[0]}
echo ${arr[1]}
echo ${arr[2]}

declare -A map
map=([name]='yanghan' [address]='wanghu')
echo ${!map[@]}
echo ${map[@]}
echo ${map[age]}
echo ${map[name]}
