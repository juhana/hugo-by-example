---
title: Containers and Platforms
permalink: /basics/containers-and-platforms/
categories: 
  - Basics
---

In their strictest definition, containers and platforms are just objects
that have the `container` or `platform`
[attribute](attribute), respectively. This allows the
verblib-grammar-token-defined parser to accept commands like **&gt;PUT
THING ON PLATFORM** or **&gt;PUT THING IN CONTAINER** (even if all you
want is a different not-successful message than "You can't do that.").

-   If it's a *working* container/platform (objects can actually be
    placed in/on it), it should also have [holding](holding)
    and [capacity](capacity)
    [properties](properties) (these are used by
    [Acquire](Acquire) to verify the container/platform has
    room for more objects).

-   If the object's contents shouldn't show up in a room listing (or
    when you look at it), it should also have the
    [quiet](quiet) attribute.
-   Containers may also have [open](open),
    [openable](openable), [locked](locked),
    [transparent](transparent), or
    [lockable](lockable) attributes, depending.
-   If you want the object's contents to *only* show up when the player
    looks in it, use [list_contents](list_contents).
-   If a container object can *also* have objects placed on top of it
    (like a desk), check out the [supercontainer
    class](supercontainer).
