PAGES = $(patsubst %.md, %.html, $(wildcard *.md))
CC = markdown

all : $(PAGES)
	mv $(PAGES) ..

%.html : %.md
	touch $@ && cat global >> $@ && $(CC) $< >> $@

.phony clean :
	rm ../$(PAGES)
