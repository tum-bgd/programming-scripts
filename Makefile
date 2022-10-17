all:
	./in2md.sh book/cppintro.md.in > book/cppintro.md
	./in2md.sh book/libraries_happly.md.in > book/libraries_happly.md
	jb build book
	cp book/_build/html/* /var/www/html/programming -R
	rsync  --no-perms --no-owner --no-group -avz --delete-after  book/_build/html/* di67nav@webdev02-tum.lrz.de:~/webserver/htdocs/en/teaching/oer/programming

