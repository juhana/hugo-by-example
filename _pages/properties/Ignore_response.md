---
title: ignore_response
permalink: /properties/ignore_response/
categories: 
  - Properties
  - Characters
---

`ignore_response` is an object [property](properties/)
([aliased](basics/alias/) to [s_to](directions/s_to/)) specifically
used for [characters](characters/). It is called by
[SpeakTo](parsing/speakto/) if the character being talked to is
[unfriendly](attributes/unfriendly/) or if an order was given and no
[order_response](property/order_response/) has been set. It is called
by [DoTalk](verb-routines/dotalk/), [DoAsk](verb-routines/doask/), and
[DoTell](verb-routines/dotell/) if the character is unfriendly.

## Example

    character jimmy "Jimmy"
    {
        noun "jimmy"
        long_desc
            "Jimmy is a little brat!"
        ignore_response
            "Jimmy ignores you and sticks his tongue out at you! The nerve!"
    }
