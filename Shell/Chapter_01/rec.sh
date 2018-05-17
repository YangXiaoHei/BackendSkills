#! /bin/bash

fun()
{
   
   sleep 1 
   echo $1
   fun hello
}

fun hi
