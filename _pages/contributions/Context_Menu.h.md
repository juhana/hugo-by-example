---
title: Context Menu.h
permalink: /contributions/context-menu.h/
categories: 
  - Library Contributions
---

Kent Tessman's Future Boy! has an adaptive context menu system. This
library contribution is *that* menu system, slightly adapted for general
usage. As such, it follows the
[Future Boy Selected Source license](misc/future-boy-license/).
You can download it [here](https://raw.githubusercontent.com/hugoif/library-contributions/main/context_menu.h).

## Usage

Besides including this file with your game, you'll want to add
`BuildContextMenu` to the `main` routine and define locations and
objects like this:

    room jetplane "On A Jetplane"
    {
         build_menu
              AddtoMenu("Jump out")
    }

    object newspaper "newspaper"
    {
         build_menu
              AddtoMenu("Read newspaper")
    }

## Special Notes

The character code in the extension relies on [dict](strings/dict/) to
add "talk to &lt;character name&gt;" to the dictionary table so it can be
added to the context menu. Because of that, you'll also need to add the
following to your source before anything is defined or included:

    $MAXDICTEXTEND = 512
