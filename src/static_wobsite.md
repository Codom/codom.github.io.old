# Easy way to make your own static website generator

My personal website started out as a kind of joke. I learned how
to use gnu make in university as a minimal build system to compile
some notes I had into html. I showed this off to my roommate and then
he showed me how to actually host this stuff on github pages with
a custom domain. This make script comprised of patsubst macros that
automatically generated the rules based off of the md files in my src/
directory and fed them all into the `markdown` program.

```make
PAGES := $(patsubst src/%.md,  docs/%.html, $(wildcard src/*.md))
MARKC := markdown
all: $(PAGES)

docs/%.html : src/%.md
	touch $@ && $(MARKC) $< > $@ && cat src/global >> $@
```

In addition to the above rule, I also threw in some rules to build my
resume and some wasm modules just for fun:

```make
TEX   := $(patsubst src/%.tex, docs/%.pdf, $(wildcard src/*.tex))
TEXC  := pdflatex

CC      := emcc
CFLAGS  := -Wall -Isrc/wasm-canvas/include


docs/%.pdf : src/%.tex
	TEXINPUTS=".:./src:" $(TEXC) $<
	mv *.pdf docs/

docs/page.wasm : src/wasm_main.c
	$(CC) $(CFLAGS) --shell-file template.html src/wasm_main.c -o docs/wasm.html
```

As good as the make
system was, it wasn't particularly great when it comes to generating
a full navigable site with a standard global html elements. This *could* be
(and was) achieved using some file concatenation, but it ended up being
kind of a hack.

Now the static site generation is embedded in a python script that wraps
around the markdown module. Not only can I easily have all of the
html post-processing in one place, but the python-markdown module provides
an extension system in order to extend the syntax in useful ways. The best part?
It's so easy to get started. Below is all of the python needed to manually build
a couple of webpages in order to get started.

```python
import markdown
header = """
<DOCTYPE html>
<-- etc -->
"""
footer = "<-- etc -->"

def main():
    process_markdown("index")
    process_markdown("blog")
    # etc.

def process_markdown(page: str):
    with open(f"src/{page}.md", "r", encoding="utf-8") as in_file:
        text = in_file.read()

    html = "".join([header, "\n", markdown.markdown(text, extensions=['']), "\n", footer])

    print(f"outputting to docs/{page}.html")
    with open(f"docs/{page}.html", "w", encoding="utf-8") as out_file:
        out_file.write(html)

if __name__ == "__main__":
    main()
```

Of particular note is the header and footer concatenation. This makes it possible
to embed a global header into all of your pages, but also to embed script tags
and stylesheet links. I use this in order to apply my stylesheet and to setup
some js to run a Mandelbrot zoom frag shader in the background of my pages.

```python
header = """
<link rel="stylesheet" type="text/css" href="style.css">
"""

footer = """
<script src="js/three.js"></script>
<script src="animation.js"></script>
"""
```

And voila! Your very own static site generator.

However, that's not quite the extent of what can actually be done. This is
simply wrapping the output of the compiler. The python-markdown module provides
a way to extend the actual markdown syntax. I haven't explored what is possible
with that, but I do have some ideas for the future of this website, particularly
when it comes to more elegant page transitions by overriding how markdown `[]()` links
are handled. Perhaps more on that later :^)

I will likely port the rest of the makefile's functionality into the build.py script
for my personal website using some process spawning hacks since I'm not really using
the dependency graph features of make anyway. This will make the latex stuff a bit
more complicated, but it's worth it just to get rid of the make dependency. Other
than that, I am very happy with how this latest overhaul turned out.
