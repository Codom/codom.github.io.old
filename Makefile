PAGES := $(patsubst src/%.md,  docs/%.html, $(wildcard src/*.md))
TEX   := $(patsubst src/%.tex, docs/%.pdf, $(wildcard src/*.tex))
MARKC := markdown
TEXC  := pdflatex
OUTDIR := docs/

CC      := emcc
CFLAGS  := -Wall -Isrc/wasm-canvas/include

all : $(TEX) docs/page.wasm $(PAGES)

deploy: all
	cd docs && emrun index.html

docs/%.html : src/%.md
	touch $@ && $(MARKC) $< > $@ && cat src/global >> $@

docs/%.pdf : src/%.tex
	TEXINPUTS=".:./src:" $(TEXC) $<
	mv *.pdf docs/

docs/page.wasm : src/wasm_main.c
	$(CC) $(CFLAGS) --shell-file template.html src/wasm_main.c src/wasm-canvas/src/canvas.c src/wasm-canvas/src/window.c -o docs/wasm.html



.phony clean :
	rm docs/*html docs/*pdf docs/*js docs/*wasm resume.*
