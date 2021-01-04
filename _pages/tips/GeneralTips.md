---
title: General Tips
permalink: /tips/general/
categories: 
  - Tips
---

Here are some general Hugo tips to keep in mind (in no particular
order):

### Compartmentalize Your Code

While browsing the example Hugo code out there, you'll notice that
several authors take advantage of Hugo's `#include` flag to split up
source code into several files. As your game gets larger and more
unruly, you might find that following suit helps you compartmentalize
your game design, letting you switch between objects, verb routines, and
routine replacements with more ease.

### Comment Your Code

>Any code of your own that you haven’t looked at for six or more
months
>might as well have been written by someone else.
>
>(Eagleson’s Law)

Commenting your code can save you headaches later on when your going
over what it's supposed to do. (versus what it's actually doing
sometimes)

### Hugo Manual Bookmarks and Comments

Adobe Reader lets you add your own "stickies" to and highlight text in
Adobe Acrobat files. Using that with the .pdf of the Hugo manual is a
great way to bookmark important sections (like lists of attributes or
grammar tokens), making them a lot faster to pull up.

### Look At The Library

When troubleshooting problems, you'll want to look at any relevant code
in the Hugo library files. It'll help a lot when you have an idea how
this or that routine works.

### Return True For A Turn To Ensue

When it comes to verb routines, sometimes it is easy to forget that
returning false means [`main`](main) is not called after the
turn is over (so the turn counter doesn't go up, the status line isn't
redrawn, events aren't run, etc.). When adding your own verbs, remember
to return true when you want a turn to "count".

### Where Capitalization Works (And Where It Doesn't)

Hugo accepts capitalized words in the naming of objects and their name
properties, but since all text that a player enters is changed to
lowercase, capitalized `noun` and `adjective`
[properties](Properties) will never be recognized. Keep this
in mind when you are doing string-matching to parser input, too.

### Correct String Property Formats

It can be frustrating when the following doesn't compile:

    long_desc "You are a fine specimen, if I do say so myself."

Since that doesn't seem all that different from other properties that
list just one thing. Unfortunately, you'll find very quickly that it
doesn't work. As mentioned in the manual, you'll have to do one of the
following instead.

    ! Either enclose the string in brackets
    long_desc {"You are a fine specimen, if I do say so myself."}

    ! Or move the string to the next line
    long_desc
         "You are a fine specimen, if I do say so myself."

    ! Or do the colon trick
    long_desc : "You are a fine specimen, if I do say so myself."

Speaking of which,

### The Colon Is Connected To The...

You can put multiple lines of code on one line using the ":" character.

    if red_door is open : print "The red door is open!"

### To Be Continued

When you run out of space while typing one line's worth of commands, you
can continue on the next line if you use the "\\" character.

    nouns "plant", "flower", "marigold", \
    "fauna", "greenery"

### One Print String Per Paragraph

Get in the habit of limiting your print strings to one paragraph. For
example:

    print "This is your first paragraph."
    print "\nThis is your second paragraph."

is preferable over

    print "This is your first paragraph.\n
          \nThis is your second paragraph."

The first version allows for easy inclusion of
[Indents](Indent) if your code needs formatting. This is one
of those things where you'll thank yourself later.

### Helpful ShORtcut

**Or** statements can be shortened from:

    if thing = something1 or thing = something2

to

    if thing = something1,something2

### Keeping Track of Library Versions

Even as old as most Hugo libraries are, it's still possible to find
yourself using an outdated library (or library contribution) without
realizing it. Add the following to your `hugolib.h` file right after the
constants are declared:

    #ifset VERSIONS
    #message ""
    #message "Hugo Library v3.1.03.1 by Kent Tessman"
    #endif

Now, if you `#set VERSIONS` in your source file, when you compile your
game, the compiler will print that message, reminding you what library
you are using. Similar code has been added to the library contributions
hosted on *Hugo By Example*, but go ahead and add it to every library
you'd like to keep track of.

### Checking Room Exits By Value

The [MovePlayer](MovePlayer) routine has this interesting
code that checks to see if a direction from a room is valid:

        if loc.type = direction
        {
            local k
            k = location.(loc.dir_to)
            if k > 1                ! since a message always returns 1
                loc = k
            else
                return
        }

So, according to this code, all "You can't go that way." messages we
might give our game will numerically equal 1. This should be a useful
way of identifying valid exits.

### Bananas

Hugo's author encourages the implementation of bananas in any game. More
bananas mean more monkeys, and monkeys are always fun.

### Blocking Contents Listing

If you want to keep non-hidden, non-quiet containers from listing their
descriptions in room descriptions, check out the page 
"[Blocking Contents Listing](Blocking_Contents_Listing)."
