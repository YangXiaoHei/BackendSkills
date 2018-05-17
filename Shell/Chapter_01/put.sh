#! /bin/bash 

count=10
i=0

while true
do
    if [ $i -lt $count ]
    then
        sleep 1
        let i++
        echo -n '#'
    else echo; exit 0
    fi
done
