---
title: after
permalink: /properties/after/
categories: 
  - Properties
---

`after` and its partner [object](globals/object/)
[property](properties/), [before](properties/before/), are two of
the more complicated object properties. Logically, `after` property
routines are for running code *after* an action, but it is even a tad
more schizophrenic than `before` as it is often used solely to provide
an alternate response to the standard response of a successful action.



### Defined by the compiler

`after` is one of six properties defined by the compiler (and not by the
[standard library](library/)). If we could see its
definition, it'd look something like this:

    property after $additive $complex

Let's take a look at those two extra parameters:

-   **$additive** tells the compiler that a `after` routine "defined in
    an inherited class or object is not overwritten by a new property
    routine in the new object." What I (Roody Yogurt) believe this means
    is that **this** is allowed:

<!-- -->

    class rock "rock"
    {
        noun "rock"
        after {
               object DoListen
                  {
                  "It sounds like a rock."
                  }
               }
    }

    rock big_rock "big rock"
    {
        adjective "big"
        after  {
                object DoGet
                   {
                   "You heave the big rock up onto your shoulders."
                   }
                }
    }

The `big_rock` object will [inherit](guts/inherits/) the `rock`
object's `DoListen` response. As far as I (Roody Yogurt) can understand,
this is the extent of `$additive`'s functionality.

-   **$complex** just tells the compiler to expect the routine to be in
    the before/after layout, which would not work as a standard routine.

</ul>

### Usage

The parts:

-   **usage** *Possible entries: [actor](globals/actor/),
    [object](globals/object/), [xobject](globals/xobject/),
    [location](globals/location/)*- When the routine
    [BeforeRoutines](guts/beforeroutines/) calls things like
    `player.after`, `location.after`, and `object.after`, the `after`
    property of the object set to the applicable
    [global variable](basics/global/) is called. If the usage is true for
    the current object, it goes on to check the verb routine and so
    forth.
-   **verbroutine**- This is obviously the verb routines we are trying
    to catch. If there is *no* verb routine, the block code will be
    applied to *all* verbs. This would only *possibly* work with
    [actor](globals/actor/) or [location](globals/location/) as the
    usage parameter.
-   **the block code**- For a normal verb routine, the block code here
    would just have the alternate text for a successful action (instead
    of the standard response). A DoGive or DoShow response might also
    move the object in question to its new parent. In *some* uncommon
    cases, there might be some unrelated code to whatever just happened.

### Calling `after`

Looking at [AfterRoutines](guts/afterroutines/), you'll notice that
it does not call `object.after` or `xobject.after`. These things are
called by the verb routines themselves, as a way of offering easily
configurable success messages. This is a nice thing to keep in mind when
one is writing new verbs to add to his or her own "standard library".
Still, you can take a look at `AfterRoutines` to see the order in which
the other usages are called.
