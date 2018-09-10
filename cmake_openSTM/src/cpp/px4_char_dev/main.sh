#!/bin/bash 
make

if [ $? = 0 ]                 
then  
   ./main
else  
    echo "compiled error"
fi  

