---
title: platform
permalink: /attributes/platform/
categories: 
  - Attributes
---

`platform` is an [attribute](attributes/) given to objects for
which commands such as **&gt;LOOK ON &lt;object&gt;** or **&gt;PUT THING ON
&lt;object&gt;** work. Without the `platform` attribute, these commands would
get a "You can't do that." response.

Other things to keep in mind:

-   If it's a *working* platform (objects can actually be placed on it),
    it should also have [holding](properties/holding/) and
    [capacity](properties/capacity/) [properties](properties/)
    (these are used by [Acquire](guts/acquire) to verify the
    platform has room for more objects).
-   If the object's contents shouldn't show up in a room listing (or
    when you look at it), it should also have the
    [quiet](attributes/quiet/) attribute.
-   If you want the object's contents to *only* show up when the player
    looks on it, use [list_contents](properties/list_contents/).
-   If the container object can *also* have objects placed inside it
    (like a desk), check out the [supercontainer class](contributions/contain.h/).
