---
title: reach
permalink: /properties/reach/
categories: 
  - Properties
---

`reach` is an [object](object)
[property](property) given to
[enterable](enterable) [containers](containers),
[platforms](platforms), and [vehicles](vehicles).
If a `reach` property exists for the object the
[player](player) is in, only objects *also* in the same
object or listed in the object's `reach` property will successfully work
for any verb routine that calls [CheckReach](CheckReach). If
not, the player will get a, "You can't reach &lt;the object&gt; from
&lt;the parent object&gt;." message.

### Example

*For a full example, see [CheckReach](CheckReach)*

    object couch "couch"
    {
        article "the"
        nearby tv
        noun "couch"
        reach table remote
        is enterable, platform, static
    }
