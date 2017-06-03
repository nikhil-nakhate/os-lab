#!/bin/bash

echo -n "enter the number of fibonacci numbers to be displayed :"
read num
a=0
b=1
 if [ $num -eq 1 ];
   then echo -n "0 "
 else
    echo -n -e "\n $a "
    echo -n "$b "
    i=$num
    while [ $i -gt 2 ];
      do
       c=$(( $a + $b ))
       a=$b
       b=$c
       let i=i-1
       echo -n "$c "
     done
  fi
echo -n -e "\n\n(press 'Enter' to exit)\n"
read num

