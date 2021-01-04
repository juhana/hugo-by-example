---
title: ignore_response
permalink: /properties/ignore_response/
categories: 
  - Properties
  - Characters
---

`ignore_response` is an object [property](Properties)
([aliased](alias) to [s_to](s_to)) specifically
used for [characters](characters). It is called by
[SpeakTo](SpeakTo) if the character being talked to is
[unfriendly](unfriendly) or if an order was given and no
[order_response](order_response) has been set. It is called
by [DoTalk](DoTalk), [DoAsk](DoAsk), and
[DoTell](DoTell) if the character is unfriendly.

## Example

    character jimmy "Jimmy"
    {
        noun "jimmy"
        long_desc
            "Jimmy is a little brat!"
        ignore_response
            "Jimmy ignores you and sticks his tongue out at you! The nerve!"
    }
