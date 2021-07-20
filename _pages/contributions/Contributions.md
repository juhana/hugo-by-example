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

| Name | Description | Additional Notes | On Archive? |
|------|-------------|------------------|-------------|
| [Beta](contributions/beta.h) | Modified version of the [Comments in Transcripts](tips/comments-in-transcripts) code.<br>Allows testers to type: **&gt;\* [tester's comments]**. | | [yes](https://www.ifarchive.org/if-archive/programming/hugo/library/contributions/beta.h) |
| [Books](contributions/books.hug) | Kent Tessman's Future Boy! book class that allows commands like **&gt;CONSULT BOOK ABOUT FUTURE BOY!** | | [no](https://raw.githubusercontent.com/hugoif/library-contributions/main/books.hug) |
| [CanGo](contributions/cango) | A routine that provides exit descriptions for rooms | | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/cango.h) |
| [Container](contributions/contain.h) | SuperContainer class by Kent Tessman (with tweak by Robb Sherwin). Used for objects that are both platforms and containers (like a desk). | | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/container.zip) |
| [Context_Menu.h](contributions/context-menu.h) | Kent Tessman's Future Boy! adaptive context menu system | | [no](https://raw.githubusercontent.com/hugoif/library-contributions/main/context_menu.hug) |
| Converse | Chris Tate's conversation system based on "Pytho's Mask" | | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/converse.zip) |
| [Footnotes](contributions/footnotes) | New footnote system by Roody Yogurt | | [no](https://github.com/hugoif/library-contributions/tree/main/footnotes) | 
| [MapGen](contributions/mapgen) | Routines for making games with rooms with randomly-generated connections | | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/mapgen.h)
| [Multikey](contributions/multikey.h) | A replacement for DoLock/DoUnLock that allows doors to have multiple key objects | | [no](https://github.com/hugoif/library-contributions/blob/main/Multikey.h)
| [NewMenu](contributions/newmenu) | Menu update by Roody Yogurt | | [yes](https://www.ifarchive.org/if-archive/programming/hugo/library/contributions/newmenu.h)
| Phone | A telephone class | | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/phone.txt) |
| [Plumbing](contributions/plumbing) | A library contribution that provides nearly <em>nothing but the kitchen sink</em> | | [no](https://github.com/hugoif/library-contributions/tree/main/plumbing) |
| Printf | A routine to print a formatted string, similar to C's printf() | | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/printf.hug) |
| Ptalk | Robb Sherwin's port of Adam Cadre's "Phototalk" | Variations of this used in most of Sherwin's games | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/ptalk.zip) |
| [RandMove](contributions/randmove) | Code for random NPC movement scripting | Works with slight change; [this page](contributions/randmove) also suggests a replacement | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/randmove.txt) |
| [Simpletalk](contributions/simpletalk.h) | Simplified version of Robb Sherwin's "Phototalk" extension port, modified to be #include-able | | [yes](https://www.ifarchive.org/if-archive/programming/hugo/library/contributions/simpletalk.zip) |
| [Sort](contributions/sort.h) | Configurable extension for sorting arrays in several ways | | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/sort.zip) |
| [Spellsys](contributions/spellsys) | Library for doing Spellcaster-type spells | Won't compile as-is, but its page has information on how to fix | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/spellsys.zip) |
| Strfnc | A set of additional string functions | | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/strfnc.h) |
| [Time](contributions/time.h) | Future Boy! routines for measuring the passage of real time by Kent Tessman | | [no](https://github.com/hugoif/library-contributions/tree/main/time) |
| Useverbs | Allows players to play game in "USE NOUN TO DO SOMETHING" form (if using involves hitting, burning, locking, tying, digging, or cutting) | | [yes](https://ifarchive.org/if-archive/programming/hugo/library/contributions/useverbs.zip) |
| [Version](contributions/version.h) | Provides a form for quick-and-easy "VERSION" responses to non-Roodylib games | | [no](https://raw.githubusercontent.com/hugoif/library-contributions/main/version.hug) |


### Library Contributions In Progress

These are contributions that are currently being updated.

| Name | Description | Latest Version | Status | On Archive? |
|------|-------------|----------------|--------|-------------|
| [Follow](contributions/follow) | Future Boy! routines for better NPC following by Kent Tessman | 2.0 | Works great | [no](https://github.com/hugoif/library-contributions/tree/main/follow) | 
| [NewAutomap](contributions/newautomap) | Glk-compliant version of [Automap](contributions/automap) | 1.2 | See notes | [no](https://github.com/hugoif/library-contributions/tree/main/newautomap) |
| [NewBoxdraw](contributions/newboxdraw.h) | Updated version of the [Boxdraw.h](contributions/boxdraw.h) to work better with glk interpreters | 1.4 | Works fine | [no](https://github.com/hugoif/library-contributions/tree/main/newboxdraw) |
| NewConverse | An update to Chris Tate's conversation system based on "Pytho's Mask" | 2.0 | Works great. | [no](https://github.com/hugoif/library-contributions/tree/main/newconverse) | 
| [Opportune](contributions/opportune.h) | Small extension for quick 1-turn WINDOWS OF OPPORTUNITY (or questions) | 1.3 | Works fine | [no](https://github.com/hugoif/library-contributions/blob/main/opportune.h) |
| [PastTense](contributions/pasttense.h) | Extension for changing verblib and various messages to past tense | 1.2 | Not really tested | [no](https://github.com/hugoif/library-contributions/blob/main/pasttense.h) |
| [Timesasked](contributions/timesasked.h) | Keeps track of number of times characters are asked and told about things | 1.1 | Works fine | [no](https://github.com/hugoif/library-contributions/tree/main/timesasked) |


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
