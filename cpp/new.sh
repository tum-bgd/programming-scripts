#!/bin/bash

function die()
{
    echo "FATAL: $@"
    exit -1
}


echo -n "Which name shall it have? "; read NAME
test -f "$NAME.cpp" && die "This is already in use. Be careful!"
cp 00_helloworld.cpp $NAME.cpp
cat 00_helloworld.mk | sed -e "s/00_helloworld/$NAME/g" > $NAME.mk
