---
title: Library Contributions
permalink: /contributions/
classes: wide
categories: 
  - Library Contributions
---

This page explores library contributions, including but
not limited to those found at the IF Archive.

### Stable Library Contributions

These contributions are largely unchanged since their release.

| Name | Description | Hugo Version | Status | On Archive? |
|------|-------------|--------------|--------|-------------|
| [Beta](contributions/beta.h) | Modified version of the [Comments in Transcripts](tips/comments-in-transcripts) code.<br>Allows testers to type: **&gt;\* [tester's comments]**. | 2.8 | Works fine | [yes](https://www.ifarchive.org/if-archive/programming/hugo/library/contributions/beta.h) |
| [Books](contributions/books.hug) | Kent Tessman's Future Boy! book class that allows commands like **&gt;CONSULT BOOK ABOUT FUTURE BOY!** | 3.1 | Works fine | [no](https://raw.githubusercontent.com/hugoif/library-contributions/main/books.hug) |
| [CanGo](contributions/cango) | A routine that provides exit descriptions for rooms | 2.5+ | Works fine | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/cango.h) |
| [Container](contributions/contain.h) | SuperContainer class by Kent Tessman (with tweak by Robb Sherwin). Used for objects that are both platforms and containers (like a desk). | 3.1 | Works great | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/container.zip) |
| [Context_Menu.h](contributions/context-menu.h) | Kent Tessman's Future Boy! adaptive context menu system | 3.1 | Works fine | [no](https://raw.githubusercontent.com/hugoif/library-contributions/main/context_menu.h) |
| Converse | Chris Tate's conversation system based on "Pytho's Mask" | 2.5 | Works great | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/converse.zip) |
| [Footnotes](contributions/footnotes) | New footnote system by Roody Yogurt | 1.4 | Works great | [no](https://github.com/hugoif/library-contributions/tree/main/footnotes) | 
| [MapGen](contributions/mapgen) | Routines for making games with rooms with randomly-generated connections | 2.5+ | Works fine | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/mapgen.h)
| [Multikey](contributions/multikey.h) | A replacement for DoLock/DoUnLock that allows doors to have multiple key objects | 3.1 | Works great | [no](http://hugo.gerynarsabode.org/images/a/a6/Multikey.h)
| [NewMenu](contributions/newmenu) | Menu update by Roody Yogurt | 3.4 | Works fine | [no](https://www.ifarchive.org/if-archive/programming/hugo/library/contributions/newmenu.h)
| Phone | A telephone class | 2.2 | Not tested | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/phone.txt) |
| [Plumbing](contributions/plumbing) | A library contribution that provides nearly <em>nothing but the kitchen sink</em> | 3.1 | Barely tested | [no](http://roody.gerynarsabode.org/hbe/plumbing.zip) |
| Printf | A routine to print a formatted string, similar to C's printf() | 3.1.03 | Should work fine | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/printf.hug) |
| Ptalk | Robb Sherwin's port of Adam Cadre's "Phototalk" | 2.5 | Variations of this used in most of Sherwin's games | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/ptalk.zip) |
| [RandMove](contributions/randmove) | Code for random NPC movement scripting | 2.1 | Works with slight change; [this page](contributions/randmove) also suggests a replacement | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/randmove.txt) |
| [Simpletalk](contributions/simpletalk.h) | Simplified version of Robb Sherwin's "Phototalk" extension port, modified to be #include-able | 2.4 | Works fine | [yes](https://www.ifarchive.org/if-archive/programming/hugo/library/contributions/simpletalk.zip) |
| [Sort](contributions/sort.h) | Configurable extension for sorting arrays in several ways | 2.5 | Works great | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/sort.zip) |
| [Spellsys](contributions/spellsys) | Library for doing Spellcaster-type spells | 2.2 | Won't compile as-is, but its page has information on how to fix | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/spellsys.zip) |
| Strfnc | A set of additional string functions | 2.4 | Not tested | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/strfnc.h) |
| [Time](contributions/time.h) | Future Boy! routines for measuring the passage of real time by Kent Tessman | 3.1 | Works great | [no](http://roody.gerynarsabode.org/hbe/time.h) |
| Useverbs | Allows players to play game in "USE NOUN TO DO SOMETHING" form (if using involves hitting, burning, locking, tying, digging, or cutting) | 2.4 | Not tested | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/useverbs.zip) |


### Library Contributions In Progress

These are contributions that are currently being updated.

| Name | Description | Latest Version | Status | On Archive? |
|------|-------------|----------------|--------|-------------|
| [Follow](contributions/follow) | Future Boy! routines for better NPC following by Kent Tessman | 1.7 | Works great | [no](http://roody.gerynarsabode.org/hbe/follow.h) | 
| [NewAutomap](contributions/newautomap) | Glk-compliant version of [Automap](contributions/automap) | 1.2 | See notes | [no](http://roody.gerynarsabode.org/hbe/newautomap.zip) |
| [NewBoxdraw](contributions/newboxdraw.h) | Updated version of the [Boxdraw.h](contributions/boxdraw.h) to work better with glk interpreters | 1.4 | Works fine | [no](http://roody.gerynarsabode.org/hbe/newboxdrawglk.h) |
| NewConverse | An update to Chris Tate's conversation system based on "Pytho's Mask" | 2.0 | Works great. | [no](http://roody.gerynarsabode.org/hbe/newconverse.zip) | 
| [Opportune](contributions/opportune.h) | Small extension for quick 1-turn WINDOWS OF OPPORTUNITY (or questions) | 1.3 | Works fine | [no](http://roody.gerynarsabode.org/hbe/opportune.h) |
| [PastTense](contributions/pasttense.h) | Extension for changing verblib and various messages to past tense | 1.2 | Not really tested | [no](http://roody.gerynarsabode.org/hbe/pasttense.h) |
| [Timesasked](contributions/timesasked.h) | Keeps track of number of times characters are asked and told about things | 1.1 | Works fine | [no](http://roody.gerynarsabode.org/hbe/timesasked.zip) |
| [Version](contributions/version.h) | Provides a form for quick-and-easy "VERSION" responses to games | 1.5 | Works fine | [no](https://raw.githubusercontent.com/hugoif/library-contributions/main/version.h) |


### Outdated Library Contributions

Some contributions are a little outdated or unnecessary:

| Name | Description | Hugo Version | Reason | On Archive? |
|------|-------------|--------------|--------|-------------|
| [Automap](contributions/automap/) | Provides Beyond Zork-like map capabilities to games. | 2.5 | Touched up and made glk-compatible as NewAutomap but this is the original. | [Yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/automap.zip) |
| [Boxdraw](contributions/boxdraw.h) | Draws quote boxes either in main window or floating above text. | 2.4 | Updated and turned into [NewBoxdraw](contributions/newboxdraw.h/). | [Yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/boxdraw.h) |
| Extra | A routine for parsing extraneous words in room descriptions | 2.4 | Made unnecessary by [extra_scenery](properties/) property. | [Yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/extra.txt) |
| Menu | Menu replacement | 2.1 | This has since been made obsolete by the latest version of Hugo's official Menu routine. | [Yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/menu.txt) |
| Newlib01 | A collection of new library routines for the Hugo system | 2.4 | Not tested. It's a mishmash of stuff, so something may be useful but it's unlikely one would use most of it. | [Yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/newlib01.hug) |
| Smrtdesk | A desk object designed to deal intelligently with user interaction between a desk and its drawers. | 2.4d | Not tested. Probably made irrelevant by the SuperContainer ([Container](contributions/contain.h)) contribution. | [Yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/Smrtdesk.h) |
