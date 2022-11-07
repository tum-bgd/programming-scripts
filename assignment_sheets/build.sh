#!/bin/bash

newestFile() {
  local latest file
  for file; do
    [[ $file && $file -nt $latest ]] || latest=$file
  done
}

directoryHasNewerFilesThan() {
  [[ "$(newestFile "$1"/*)" -nt "$(newestFile "$2" "$2"/*)" ]]
}

function die()
{
    echo "ONE COMPILATION FAILED. STOPPING. $@"
    exit -1
}


if [ -f focus ]; then
FILES=$(cat focus)
else
FILES=*.tex
fi

# the following variable overrides latex behaviour to build the PDF
# document ID. It overrides the file time. In this way, the PDF-ID does
# not change and PDF.js viewers should not jump to the beginning of the
# file on reload. 

export SOURCE_DATE_EPOCH=1 
for f in $FILES; do
    # check if tasks are updated (TODO should be only local tasks)
    pdflatex "$f" || die "Unable to build $f";
    if [ "$HOSTNAME" == "werner" ]; then
	echo "on werner"
	cp $(basename $f .tex).pdf /var/www/html # for inspection
    fi
done

echo "Build complete."
if [ -f focus ]; then
echo "THIS WAS A FOCUS BUILD. DELETE or UPDATE focus"
else
echo "THIS WAS A FULL BUILD. USE echo <filename> > focus TO ALWAYS BUILD ONLY ONE FILE"
fi

    
   # TODO check whether we need to
	
