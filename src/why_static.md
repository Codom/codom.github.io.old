<!--
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
-->

# Why Static?

## January 8th, 2021

Static websites are really cool. They load fast,
they can look good with real minimal design, it's
dead simple to scale the elements in a static page
with minimal css programming, and the webpage
doesn't take 200 mb of memory in order to load.
(shout out to [motherfuckingwebsite.com](https://motherfuckingwebsite.com/))
Moreover, countless tools exist to convert formats
that writers are used to (markdown namely) into static
html with a simple command, and can
be used to dynamically generate articles that can
be added to a massive website seamlessly.

So why are they so rarely used, even for simple news sites?

Well, I really don't know.
It likely has to do with personalization, tracking, and advertising
requiring dynamic loading of content using complex client
server models with user authentication and whatnot,
but the point of this post is to justify my decision
not other people's.

The main draw of static webpages to me is simple:
it's free through github pages.
It's also *extremely* simple to setup an ad-hoc
hack build system that auto generates my html from
markdown, which I find really fun and insightful to maintain.
And if you don't want to do that there
is no shortage of other better designed systems
to generate beautiful looking html (Jekyll to name one).

It's really funny to me that a few lines of
make and some text files can not only make a fully
featured website with blogging capabilities, it also
vastly outperforms most other 'simple' website solutions
that target non-programmers while looking not too much
worse.
(although running make is definitely too arcane for
the average non-nerd).

That's not to say that this is inherently better
than using a more complicated react based solution
with an inbuilt editor, user auth, 
rss feed manager, etc.
however for my purposes this static website is perfect.
I can even automatically manage an rss feed using git
hooks or Github webhooks (which I plan on doing soon).
