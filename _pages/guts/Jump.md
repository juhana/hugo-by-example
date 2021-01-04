---
title: Jump
permalink: /guts/jump/
categories: 
  - Hugo Guts
---

The `jump` command is the "GOTO" of the Hugo language. Since Hugo
doesn't use line numbers, `jump` works off of labels. These labels are
denoted with a colon symbol (":").

### A nonsensical jump example

    print "Marty McGnat sez,\"Doc, I need to get back to 198\I3\i.\""
    jump 1983Label
    print "Marty McGnat sez,\"Oh no, I'm stuck in 195\I3\i!\""
    :1983Label
    print "Marty McGnat sez,\"Yay, I'm back home!\""

### Why jumps can be no fun

There technically isn't any reason to avoid using `jump` , and it can be
a nice shortcut when you don't want to use giant `if-then` blocks or
plan out a [`while`](loops/while/) loop. Still, when you
[replace](guts/replace/) a [routine](routines/) that has
jumps in it, the jumps are *not* replaced, so you'll have to rename all
of the jumps and labels. Because of this alone, you may want to avoid
jumps if you think the routine might be replaced at some point.
