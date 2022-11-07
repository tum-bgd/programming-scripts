#!/bin/bash

function include_tabitem_from_file()
{
    SYNTAX="$1"
    shift
    TABNAME="$1";
    shift
    SOURCE="$1"
    echo -n '````{tab-item} '
    echo "$TABNAME"
    echo '```'$SYNTAX
    cat "cpp/$SOURCE"
    echo '```' 
    echo '````'
    

    
}
#    00_helloworld.cpp
#  -rw-r--r-- 1 martin martin    45 Sep 26 13:03 00_helloworld.makeout
#  -rw-r--r-- 1 martin martin    75 Sep 26 13:00 00_helloworld.mk
#  -rw-r--r-- 1 martin martin    29 Sep 26 13:03 00_helloworld.runout

function render_tabset(){
    echo '`````{tab-set}'
    include_tabitem_from_file "cpp" "Source" "$1.cpp"
    include_tabitem_from_file "" "Makefile" "$1.mk"
    include_tabitem_from_file "" "Build Output" "$1.makeout"
    include_tabitem_from_file "" "Run Output" "$1.runout"
    
    
    echo '````` '
}
function render_include(){
    echo '`````{tab-set}'
    include_tabitem_from_file "" "$1" "$2"
    echo '````` '
}


cat "$1" | while read LINE; do
    
    if [[ $LINE == @cppgroup* ]]; then
	render_tabset $(echo $LINE |cut -d" " -f2)
    elif [[ $LINE == @include* ]]; then
	render_include $(echo $LINE |cut -d" " -f2) $(echo $LINE |cut -d" " -f3)
    else
	echo $LINE
    fi
      
done

