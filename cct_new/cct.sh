#!/bin/bash

build="build"

if [ ! -d "$build" ]; then
  mkdir "$build"
fi

cd  build 
cmake ../
make 

if [ $? = 0 ]                 
then  
 	./main
else  
    echo "compiled error"
fi  

