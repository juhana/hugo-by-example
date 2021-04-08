---
title: container
permalink: /attributes/container/
categories: 
  - Attributes
---

`container` is an [attribute](attributes/) given to objects for
which commands such as **&gt;LOOK INSIDE &lt;object&gt;** or 
**&gt;PUT THING IN &lt;object&gt;** work. Without the `container` attribute,
these commands would get a "You can't do that." response.

Other things to keep in mind:

-   If it's a *working* container (objects can actually be placed in
    it), it should also have [holding](properties/holding/) and
    [capacity](properties/capacity/) [properties](properties/)
    (these are used by [Acquire](guts/acquire) to verify the
    container has room for more objects).
-   Containers may also have [open](attributes/open/),
    [openable](attributes/openable/), [locked](attributes/locked/),
    [transparent](attributes/transparent/), or
    [lockable](attributes/lockable/) attributes, depending.
-   If the object's contents shouldn't show up in a room listing (or
    when you look at it), it should also have the
    [quiet](attributes/quiet/) attribute.
-   If you want the object's contents to *only* show up when the player
    looks in it, use [list_contents](properties/list_contents/).
-   If the container object can *also* have objects placed on top of it
    (like a desk), check out the [supercontainer class](contributions/contain.h/).

## Hugo Homework

People occasionally run into problems while coding windows (the
part-of-a-building kind), as they don't give the window object the
`container` attribute and then wonder why **&gt;LOOK IN WINDOW** doesn't
work. Of course, this can be dealt with by added new
[grammar](basics/grammar/), but for our purposes, code a
`container`-attribute-having window object that has adequate responses
to "traditional" container commands like **&gt;PUT THING IN WINDOW**.
