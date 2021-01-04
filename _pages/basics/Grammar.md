---
title: Grammar
permalink: /basics/grammar/
categories: 
  - Basics
---

Your new game will almost always require the creation of new verbs that
are specific to your world. These new verbs need to be defined with a
grammar definition. This is very easy in Hugo.

The syntax for grammar definition is

```
[x]verb "<verb1>" [, "<verb2", "<verb3>", ...]
* <syntax specification 1>           <VerbRoutine1>
* <syntax specification 2>           <VerbRoutine2>
...
```

Where "&lt;verb*X*&gt;" is the verb you're defining. Multiple verbs can
be defined for one grammar rule. These are synonyms for each other (so
you can have 'attack', 'hit', 'punch' all do the same thing.)

Here are a couple of examples from the verblib.g grammar file included
in the standard hugo library.

```
verb "get"
    *                   DoVague
    * "up"/"out"/"off"          DoExit
    * "outof"/"offof"/"off" object      DoExit
    * "in"/"on" object          DoEnter
    * multinotheld "from"/"off" parent  DoGet
    * multinotheld "offof"/"outof" parent   DoGet
    * multinotheld              DoGet
```

Line by line:

1.  This line is telling the compiler that we are defining a new, normal
    verb called **get**
2.  The **\*** is a place holder for the verb(s) defined in line one,
    this line is saying that we need to call the routine **DoVague** if
    the line contains only *get*
3.  This line we are defining what to do when the player types *get up*
    (or *get out* or *get off*)
4.  This line shows what to do when the player types *get out of
    **object***. The hugo parser will concatenate *out of*, or *off of*
    to *outof* or *offof* for easier parsing.
5.  What to do if the player types *get in* or *get on* some **object**.
    (Call the **DoEnter** routine)
6.  **multinotheld** means multiple things that are *not* held by the
    player. (ie. *get apple, peach and pie from the table*)
7.  What to do when the player types *get &lt;objects&gt; off of **object**.*
8.  What to do if the player just types something like *get apple and
    banana*



```
xverb "save"
    *       DoSave
    * "game"    DoSave
```

This defines what to do when the player types either *save* or *save
game*. This is an xverb. An xverb is a verb that does not call the Main
routine when it successfully completes it action. This means that the
turn counter will not be incremented. xverbs are generally used for 'out
of world' actions, actions that are for non-action, housekeeping-type
verbs (such as saving, quitting and restarting)

## verb some_object?

The *Grammar & Parsing* section of the Hugo Book has a section on
directing a verb definition to an object's `noun` property. If it worked
as described, one could have a somewhat dynamic verb which changed as
the game progressed. It doesn't currently work, though, so in the
meantime (while it is looked into), don't waste your time with it!

## See also:

Be sure to also check out the [grammar tokens](basics/grammar-tokens/) page.
