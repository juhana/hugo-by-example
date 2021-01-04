---
title: reach
permalink: /properties/reach/
categories: 
  - Properties
---

`reach` is an [object](/globals/object/)
[property](/properties/) given to
[enterable](/attributes/enterable/) [containers](/basics/containers-and-platforms/),
[platforms](/basics/containers-and-platforms/), and [vehicles](/classes/vehicle/).
If a `reach` property exists for the object the
[player](/globals/player/) is in, only objects *also* in the same
object or listed in the object's `reach` property will successfully work
for any verb routine that calls [CheckReach](/routines/checkreach/). If
not, the player will get a, "You can't reach &lt;the object&gt; from
&lt;the parent object&gt;." message.

### Example

*For a full example, see [CheckReach](/routines/checkreach/)*

    object couch "couch"
    {
        article "the"
        nearby tv
        noun "couch"
        reach table remote
        is enterable, platform, static
    }
