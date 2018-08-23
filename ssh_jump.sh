#! /bin/bash

target_file=./target_list
public_key=/home/leyi/amazon_cn.pem

if [ ! -f $target_file ]
then
    echo "[ERROR] $target_file not exist or not a file!"
    exit 1
fi

if [ ! -e $public_key ]
then
    echo "[ERROR] $public_key is not exist!"
    exit 1
fi 

sed '/^$/d; s/ *//g' -i $target_file

exec 6<&0
exec 0< $target_file

declare -A target_map

index=1
while read host
do
    target_map[$index]=`echo -n $host | sed 's/\[.*\]//g'`
    (( index++ ))
done

echo
echo "/------------------------  Display all support host ---------------------------/"
echo "${target_map[*]}" | sed 's/ /\n/g;' | cat -n
echo "/------------------------------------------------------------------------------/"
echo

exec 0<&6

read -n1 -p "Enter the index of host you want to jump  "  anwser


if [ -z "${target_map[$anwser]}" ]
then
    echo -e "\n[ERROR] Input index invalid  $anwser"
    exit 1
fi

echo
echo "******************************************"
echo "Remote host connecting \"${target_map[$anwser]}\" ,  Please waiting..."
echo "******************************************"
echo
ssh -o TCPKeepAlive=yes -o ServerAliveInterval=300 -i /home/leyi/amazon_cn.pem ${target_map[$anwser]}
