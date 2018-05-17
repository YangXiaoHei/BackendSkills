#! /bin/bash

declare -A map
map[name]=yanghan
map[age]=24
map[address]=wanghu

echo "echo map[name]=${map[name]}"
echo "echo map size is ${#map[@]}"
echo "echo map all keys : ${!map[@]}"
echo "echo map all values : ${map[@]}"
