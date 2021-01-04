---
title: Glk
permalink: /definitions/glk/
categories: 
  - Definitions
---

From [The Interactive Fiction Wiki](http://www.ifwiki.org)

>An Application Programming Interface (API) for programs with textual user interfaces, created by Andrew Plotkin. Glk is not itself a programming language, nor is it a virtual machine; it merely defines an abstract mechanism to handle input and output. A full description of Glk is available at [the author's website](http://eblong.com/zarf/glk/).
>
>Glulx is a virtual machine that uses Glk and is designed for use in writing interactive fiction. Tor Andersson has adapted many interpreters to use Glk API as part of the [Gargoyle](interpreters/gargoyle/) project.

Basically, there's this standard called "Glk." All major IF languages
(and several minor ones) have interpreters available that abide by its
rules. This includes Hugo. When playing games in a glk-based
interpreter, though, some of Hugo's functionality may be hindered or
altogether broken.

Broken things include:

-   ability to have more than two windows (the two windows being the
    main window and status window)
-   ability for the Hugo game to detect
    [display.windowlines](guts/display-object/) accurately in the
    main window; [locate](input-output/locate/) is also broken in the main
    window
-   some [media](basics/resources/) capabilities will work
    differently, if at all. For instance,
    resource.h's `LoadPicture` will work with
    [Gargoyle](interpreters/gargoyle/), but `PictureInText` will cause the
    interpreter to crash.

### "glk-detecting" code

If you run the `glkcheck` while the cursor is currently in the main
window, you can detect whether a game is being played on a glk-based
interpreter:

    global glk

    routine glkcheck
    {
        if display.windowlines > (display.screenheight + 100)
            glk = true
            else : glk = false
            return glk
    }

Then, you could check for `glk` or execute `glkcheck` every time you
want to do something fancy with windows, [locate](input-output/locate/), or
[resources](basics/resources/).
