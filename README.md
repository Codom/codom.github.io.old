# Codom.github.io
This project uses a make-based static website generator/resume typesetter,
and depends on markdown and latex.

Simply cd into `src` and run `make`, and all markdown files in `src` will
produce a corresponding `html` file in the root directory, and will have
`src/style.css` linked in and whatever in `src/global` appended to the end
of each html file.
