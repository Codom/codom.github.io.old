PAGES = $(patsubst %.md, %.html, $(wildcard *.md))
CC = markdown

all : $(PAGES)
	mv $(PAGES) ..

%.html : %.md
	$(CC) $< > $@

.phony clean :
	rm ../$(PAGES)
