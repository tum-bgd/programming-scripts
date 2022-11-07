all:
	./in2md.sh book/cppintro.md.in > book/cppintro.md
	./in2md.sh book/libraries_happly.md.in > book/libraries_happly.md
	./in2md.sh book/libraries_happly_boostgeometry.md.in > book/libraries_happly_boostgeometry.md
	jb build book
	jb build --builder pdflatex book
	cp book/_build/html/* /var/www/html/programming -R
	cp book/_build/latex/book.pdf /var/www/html/programming/programming.pdf

upload:
	rsync  --no-perms --no-owner --no-group -avz --delete-after  book/_build/html/* di67nav@webdev02-tum.lrz.de:~/webserver/htdocs/en/teaching/oer/programming
	rsync book/_build/latex/book.pdf di67nav@webdev02-tum.lrz.de:~/webserver/htdocs/en/teaching/oer/programming/programming.pdf 
