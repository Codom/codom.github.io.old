PAGES := $(patsubst src/%.md, %.html, $(wildcard src/*.md))
TEX   := $(patsubst src/%.tex, %.pdf, $(wildcard src/*.tex))
MARKC := markdown
TEXC  := pdflatex

CC      := emcc
CFLAGS  := -Wall -Werror -pedantic -s WASM=1 -os
CFLAGS  += `pkg-config sdl2 --cflags`
LFLAGS := -s USE_SDL=2
# LFLAGS += `pkg-config sdl2 --libs`

all : $(PAGES) $(TEX) test.wasm

deploy: all
	emrun hello.html

%.html : src/%.md
	touch $@ && $(MARKC) $< > $@ && cat src/global >> $@

%.pdf : src/%.tex
	$(TEXC) $<

# Note this is a unity build, and if you ever make this not a unity build
# I will time travel to the future and slap you.
test.wasm : src/wasm_main.c
	$(CC) $(CFLAGS) $(LFLAGS) src/wasm_main.c -o hello.js

.phony clean :
	rm $(PAGES) $(TEX)
