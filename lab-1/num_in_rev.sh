#!/bin/bash

echo "Enter a Number"
read num
num2=0

while [ $num -gt 0 ]
do
num2=`expr $num % 10 + $num2 \* 10`
num=`expr $num / 10`
done

echo $num2 
