---
title: PastTense.h
permalink: /contributions/pasttense.h/
categories: 
  - Contributions
---

`PastTense` is a library contribution for games that are told in the
past tense- either in part or their entirety. You can get it
[here](https://github.com/hugoif/library-contributions/blob/main/pasttense.h).

It inelegantly provides game messages in past tense by replacing 'NewVMessages' and 'NMessages' so be aware of that if your game also replaces those.  If using Roodylib, 'PastTense' may not be up to date in terms of messages replaced.

'PastTense' was used in [Storm Over London](https://ifdb.org/viewgame?id=bwm5l6dqe3inefds) by Juhana Leinonen.

### Usage

Just include "pasttense.h" after "verblib.h"/"verbstub.h" and set the
[global variable](basics/global/) `pasttense` to
*true* when you want the game to be past tense.
