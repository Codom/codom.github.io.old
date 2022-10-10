#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2022 Christopher Odom <christopher.r.odom@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

"""
Builds a webpage, depends on python-markdown

Module wraps the markdown parser to add custom styling to
vanilla markdown

TODO list:
[ ] Build resume
"""

import markdown
import subprocess
import os

def main():
    process_resume()
    process_markdown("index")
    process_markdown("blog")
    process_markdown("static_wobsite")

# This is ugly lmao
header = """
<!DOCTYPE html>
<html>

<header>
<a href="https://github.com/Codom/Codom.github.io" class="github-corner" aria-label="View source on GitHub"><svg width="80" height="80" viewBox="0 0 250 250" style="fill:#151513; color:#fff; position: absolute; top: 0; border: 0; right: 0;" aria-hidden="true"><path d="M0,0 L115,115 L130,115 L142,142 L250,250 L250,0 Z"></path><path d="M128.3,109.0 C113.8,99.7 119.0,89.6 119.0,89.6 C122.0,82.7 120.5,78.6 120.5,78.6 C119.2,72.0 123.4,76.3 123.4,76.3 C127.3,80.9 125.5,87.3 125.5,87.3 C122.9,97.6 130.6,101.9 134.4,103.2" fill="currentColor" style="transform-origin: 130px 106px;" class="octo-arm"></path><path d="M115.0,115.0 C114.9,115.1 118.7,116.5 119.8,115.4 L133.7,101.6 C136.9,99.2 139.9,98.4 142.2,98.6 C133.8,88.0 127.5,74.4 143.8,58.0 C148.5,53.4 154.0,51.2 159.7,51.0 C160.3,49.4 163.2,43.6 171.4,40.1 C171.4,40.1 176.1,42.5 178.8,56.2 C183.1,58.6 187.2,61.8 190.9,65.4 C194.5,69.0 197.7,73.2 200.1,77.6 C213.8,80.2 216.3,84.9 216.3,84.9 C212.7,93.1 206.9,96.0 205.4,96.6 C205.1,102.4 203.0,107.8 198.3,112.5 C181.9,128.9 168.3,122.5 157.7,114.1 C157.9,116.9 156.7,120.9 152.7,124.9 L141.0,136.5 C139.8,137.7 141.6,141.9 141.8,141.8 Z" fill="currentColor" class="octo-body"></path></svg></a><style>.github-corner:hover .octo-arm{animation:octocat-wave 560ms ease-in-out}@keyframes octocat-wave{0%,100%{transform:rotate(0)}20%,60%{transform:rotate(-25deg)}40%,80%{transform:rotate(10deg)}}@media (max-width:500px){.github-corner:hover .octo-arm{animation:none}.github-corner .octo-arm{animation:octocat-wave 560ms ease-in-out}}</style>

<body>
<div id="topbar">
    <h1 id="title"><a href="index.html">Christopher Odom</a></h1>
    <h2 id="subtitle"><a href="https://github.com/Codom">Github</a> <a href="https://gitlab.com/Codom">Gitlab</a> <a href="./resume.pdf">R&egrave;sum&egrave;</a> <a href="./blog.html">Blog</a></h2>
</div>
</header>
"""

# Footer is way cleaner, contains all of the stuff for the bg animation
footer = """
    <div id = "animContainer"></div>
    <script src="js/three.js"></script>
    <script src="animation.js"></script>
    <link rel="stylesheet" type="text/css" href="style.css">

</body>
</html>
"""

def process_markdown(page: str):
    with open(f"src/{page}.md", "r", encoding="utf-8") as in_file:
        text = in_file.read()

    html = "".join([header, "\n", markdown.markdown(text, extensions=['markdown.extensions.fenced_code']), "\n", footer])

    print(f"outputting to docs/{page}.html")
    with open(f"docs/{page}.html", "w", encoding="utf-8") as out_file:
        out_file.write(html)

def process_resume():
    latex_env = os.environ | {"TEXINPUTS": ".:./src:"}
    print(latex_env)
    print("Compiling resume...")
    subprocess.run(["pdflatex", "src/resume.tex"], env=latex_env)
    subprocess.run(["mv", "resume.pdf", "docs/"])
    subprocess.run(["rm", "resume.aux", "resume.log", "resume.out"])
    print("done")

if __name__ == "__main__":
    main()
