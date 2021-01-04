---
title: Gargoyle
permalink: /interpreters/gargoyle/
categories: 
  - Interpreters
---

Gargoyle is a multi-platform, multi-if-system interpreter for
Interactive Fiction. It focuses on good typography in games. Because it
uses a [Glk](definitions/glk/) API library, it does not support any
additional windows besides the status line. That said, there is support
for both sound and graphics.

## Media in Gargoyle

Music and graphics (that are displayed in the main window) will be heard
and seen just fine. As the resource files are accessed, the individual
song or graphic file is dumped into the game's directory. This is not
ideal from a Hugo author's perspective, but there are two ways to get
around this.

### Glk.h

The more forceful approach is to use a library contribution like
Glk.h to determine if your game is being played on a
[Glk](definitions/glk/)-based interpreter. If it is, you can choose to not
play the music file or display the graphic, giving Gargoyle nothing to
rip out of the resource file.

![Gargoyle](assets/images/GB Gargoyle.jpg)

### Include a configuration file

Gargoyle only tries to play resource files if the configuration file
tells it so. You'll notice that Gargoyle is distributed with a file
called `garglk.ini`. Make a copy of that file and rename it to share the
same name as your game. Edit it and change the graphics and sound
settings to the following:

    graphics      0               # enable graphics
    sound         0               # enable sound

If that file is in the same directory as your game, Gargoyle will not
play the media. Of course, this is easily changed, but your intentions
will be clear.

## Sample configuration files

As mentioned in the previous section, it is possible to write a Gargoyle
configuration file so you have some control over how your game looks.
Here are several Gargoyle configuration files written to emulate the
color schemes of their original versions.

| Gargoyle configuration file                                            | Hugo game                                                                    |
|------------------------------------------------------------------------|------------------------------------------------------------------------------|
| [pirate.ini](http://roody.gerynarsabode.org/gargoyle/pirate.ini)       | [Pirate Adventure](http://ifarchive.org/if-archive/games/hugo/pirate.hex)    |
| [pmime.ini](http://roody.gerynarsabode.org/gargoyle/pmime.ini)         | [Pantomime](http://ifarchive.org/if-archive/games/hugo/pmime.hex)            |
| [scourgdos.ini](http://roody.gerynarsabode.org/gargoyle/scourgdos.ini) | [A Crimson Spring](http://ifarchive.org/if-archive/games/hugo/scourgdos.hex) |

Also, both
[Cryptozookeeper](http://www.joltcountry.com/index.php/robbsherwin_videogame/cryptozookeeper)
and [Tales of the Traveling Swordsman](http://ifarchive.org/indexes/if-archiveXgamesXcompetition2006XhugoXtales_ts.html)
were distributed with Gargoyle configuration files included.
