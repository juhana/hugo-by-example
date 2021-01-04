---
title: Addcontext
permalink: /guts/addcontext/
categories: 
  - Hugo Guts
---

Unless a game is currently in a [pause](/input-output/pause/), in most
official Hugo interpreters, right-clicking on the screen will bring up
whatever context menu has been defined for the game (possible in v3 or
later games).

![Future Boy!](/assets/images/Context.jpg)

In Future Boy!, Kent Tessman coded
an adaptive context menu system that updated itself depending on the
player object, the location, and the objects and characters nearby (this
system is available as a library contribution
[here](/contributions/context-menu.h/)). In Necrotic Drift, Robb Sherwin had
a context menu that mirrored the options shown graphically to best
approximate the menus used in Magnetic Scrolls games like Guild of
Thieves and Jinxter. Conceivably, there are other novel uses yet to be
discovered!

To do these context menus, one has to use the
barely-mentioned-in-the-Hugo-Book command `addcontext`. Luckily, we are
here to shed some light on its mysteriousness.

| calling form            | what it does                                                                           |
|-------------------------|----------------------------------------------------------------------------------------|
| addcontext 0            | Clears all context menu choices                                                        |
| addcontext "COMMAND"    | Sends "COMMAND" to the command line with carriage return                               |
| addcontext "COMMAND..." | Sends "COMMAND " text to the command and waits for more input                          |
| addcontext "-"          | Puts a separator in the context menu between commands and the next command to be added |

align="top"\|*ways to call addcontext*

Let's show some examples:


    addcontext "Look"   ! When this option is clicked in the context menu,
                        ! the command "Look" is executed
    addcontext "Examine..."  ! When this is clicked, "Examine " is sent
                             ! to the command line and waits for more text to be typed

    ! addcontext is always used with a dictionary entry so you can't feed it a routine
    ! here is an example that WOULD NOT work
    addcontext { print "HELLO "; char.name }
