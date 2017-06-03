echo "Enter File: \c"
              read f1
              if [ -f $f1 ]
          then
               echo "Converting Lower Case to Upper Case "
                 tr "[a-z]" "[A-Z]" <$f1
                             
              else
                     echo "$f1 does not exist"
              fi

