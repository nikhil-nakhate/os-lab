#!/bin/bash

dir=`pwd`
a=`find $dir -type f -atime +365` 
if [ "$a" != "" ]; 
then
	cp -r $dir /home/nikhil/backup/
fi

