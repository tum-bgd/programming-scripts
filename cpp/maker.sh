#!/bin/bash
set -e

# conditional_make <makefile> builds and runs a job if and only if required
function conditional_make()
{
    
    NAME="$1"
    if [ -f "$NAME".runout ]; then echo "Skipping $NAME";
    else
	echo "Compiling and running $NAME"
    make -f "$NAME".mk 2>&1 > $NAME.makeout 
    if [ $? -ne 0 ]; then
	echo "ERROR occured in build";
	cat "$NAME".makeout;
	exit
    fi
    make -f "$NAME".mk run > "$NAME".runout 2>&1   
    if [ $? -ne 0 ]; then
	echo "ERROR occured in run";
	cat "$NAME".runout;
	exit
    fi
    fi;
    }


for f in *.mk; do
    echo "Considering $f"
    conditional_make `basename "$f" .mk`
done


	 
