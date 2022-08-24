PAGES := $(patsubst src/%.md, %.html, $(wildcard src/*.md))
TEX   := $(patsubst src/%.tex, %.pdf, $(wildcard src/*.tex))
MARKC := markdown
TEXC  := pdflatex

CC      := emcc
CFLAGS  := -Wall -Isrc/wasm-canvas/include
# LFLAGS += `pkg-config sdl2 --libs`

all : $(TEX) page.wasm $(PAGES)

deploy: all
	emrun hello.html

%.html : src/%.md
	touch $@ && $(MARKC) $< > $@ && cat src/global >> $@

%.pdf : src/%.tex
	$(TEXC) $<

page.wasm : src/wasm_main.c
	$(CC) $(CFLAGS) --shell-file template.html src/wasm_main.c src/wasm-canvas/src/canvas.c src/wasm-canvas/src/window.c -o wasm.html



.phony clean :
	rm $(PAGES) $(TEX)
