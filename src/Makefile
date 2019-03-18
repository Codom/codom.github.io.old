PAGES = $(patsubst %.md, %.html, $(wildcard *.md))
CC = markdown

all : $(PAGES)
	mv $(PAGES) ..

%.html : %.md
	touch $@ && $(CC) $< >> $@ && cat global >> $@

.phony clean :
	rm ../$(PAGES)
