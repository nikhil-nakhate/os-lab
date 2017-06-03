if [ $# -eq 3 ]; then
	if [ -e $3 ]; then
    	    tail -n +$1 $3 | head -n`expr $2 - $1 + 1`
        fi   
else
        echo "Missing arguments!"	
fi


