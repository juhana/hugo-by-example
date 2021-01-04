---
title: preposition
permalink: /properties/preposition/
categories: 
  - Properties
---

`preposition` is an [object](/globals/object/)
[property](/properties/) for
[containers](/basics/containers-and-platforms/) and
[platforms](/basics/containers-and-platforms/). Usually, the `preposition` property
is called if the object is [enterable](/attributes/enterable/) (such as
the case with [vehicles](/classes/vehicle/)), but
[WhatsIn](/routines/whatsin/) also checks for it, so it can also affect
regular containers and platforms (and even
[characters](/characters/)), too.

### Things to keep in mind

-   In [DescribePlace](/guts/describeplace/), it helps connote the
    player's relation to the object. So, an `enterable` "water" object
    with preposition "under" in a [location](/globals/location/) called
    "The Ocean" would result in "The Ocean, under the water".
-   Leaving [vehicles](/classes/vehicle/) and enterable objects
    actually checks for a second `preposition` element, used in
    statements like:

<!-- -->

             print CThe(player); " will have to get ";
             if parent(player).prep #2
                print parent(player).prep #2; " ";
             else
                print "out ";
             print "of "; The(parent(player)); " first."

-   In the case of non-enterable objects that have contents listed in
    room descriptions or such, a defined preposition property can
    replace the following:

<!-- -->

             if a.prep
                print capital a.prep; " ";
             elseif a is platform
                print "Sitting on ";
             else
                print "Inside ";

In the case of characters, it can replace this:

             if FORMAT & USECHARNAMES_F
                CThe(a)
             else
                print capital a.pronoun;
             if list_count < b
                print " also";
             print MatchPlural(a, "has", "have");
