BOOKS = principles-of-programming computational-foundations-1

all: build deploy

build: build_jupyter_books build_pdflatex build_merge_html

build_preprocess:
	./in2md.sh files/cppintro.md.in > files/cppintro.md
	./in2md.sh files/libraries_happly.md.in > files/libraries_happly.md
	./in2md.sh files/libraries_happly_boostgeometry.md.in > files/libraries_happly_boostgeometry.md
	cd cpp && ./maker.sh && cd ..

build_jupyter_books:
	for book in $(BOOKS) ; do \
		jb build --path-output _build/$${book} --config $${book}_config.yml --toc $${book}_toc.yml . ; \
	done

build_pdflatex:
	for book in $(BOOKS) ; do \
		jb build --config $${book}_config.yml --toc $${book}_toc.yml --builder pdflatex . ; \
		cp _build/latex/$${book}.pdf _build/$${book}/_build/html/$${book}.pdf ; \
	done

build_merge_html:
	rm -rf _html && mkdir -p _html
	for book in $(BOOKS) ; do \
		cp -a _build/$${book}/_build/html/. _html/$${book}/ ; \
	done

deploy:
	rsync -a --delete _html/ /var/www/html/programming

upload:
	rsync --no-perms --no-owner --no-group -avz --delete-after  _html/* di67nav@webdev02-tum.lrz.de:~/webserver/htdocs/en/teaching/oer/programming
