string=""
read String

if [ "$(echo $String | rev)" = "$String" ]
     then
          echo "\"$String\" is a palindrome"
     else
          echo "\"$String\" is not a palindrome"
fi

