for x in `ls`
   do
     if [ -e $x ]; 
     then
     lc=`echo $x  | tr '[A-Z]' '[a-z]'`
     fi
     if [ $lc != $x ]; then
        mv $x $lc
     fi
   done
