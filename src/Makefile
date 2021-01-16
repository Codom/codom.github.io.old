PAGES = $(patsubst %.md, %.html, $(wildcard *.md))
TEX = $(patsubst %.tex, %.pdf, $(wildcard *.tex))
CC = markdown
CCT = pdflatex

all : $(PAGES) $(TEX)
	mv $(BLOGS) $(PAGES) $(TEX) ..

%.html : %.md
	touch $@ && $(CC) $< >> $@ && cat global >> $@
%.pdf : %.tex
	$(CCT) $<

.phony clean :
	rm ../$(PAGES)
