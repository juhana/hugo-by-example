---
title: preposition
permalink: /properties/preposition/
categories: 
  - Properties
---

`preposition` is an [object](object)
[property](properties) for
[containers](containers) and
[platforms](platforms). Usually, the `preposition` property
is called if the object is [enterable](enterable) (such as
the case with [vehicles](vehicles)), but
[WhatsIn](WhatsIn) also checks for it, so it can also affect
regular containers and platforms (and even
[characters](characters)), too.

### Things to keep in mind

-   In [DescribePlace](DescribePlace), it helps connote the
    player's relation to the object. So, an `enterable` "water" object
    with preposition "under" in a [location](location) called
    "The Ocean" would result in "The Ocean, under the water".
-   Leaving [vehicles](vehicles) and enterable objects
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
