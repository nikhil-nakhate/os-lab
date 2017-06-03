#!/bin/bash

Columns=$(tput cols)
Startpoint=$(($Columns-12))
Color1=`tput setab 4`
Normal=`tput sgr0`
while :
do
  Time=`date +%r`
  tput sc
  tput cup 0 $Startpoint
  echo -n "$Color1$Time $Normal"
  tput rc
  sleep 1
done
