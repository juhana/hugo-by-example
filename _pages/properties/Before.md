---
title: before
permalink: /properties/before/
categories: 
  - Properties
---

`before` and its partner [object](globals/object/)
[property](properties/), [after](properties/after/), are two of
the more complicated object properties. The information contained
therein determines what code should be run before normal actions (with
their standard responses) are allowed (and whether normal code execution
is allowed at all). 

### Defined by the compiler

`before` is one of six properties defined by the compiler (and not by
the [standard library](library/)). If we could see
its definition, it'd look something like this:

    property before $additive $complex

Let's take a look at those two extra parameters:

-   **$additive** tells the compiler that a `before` routine "defined in
    an inherited class or object is not overwritten by a new property
    routine in the new object." What I (Roody Yogurt) believe this means
    is that **this** is allowed:

<!-- -->

    class rock "rock"
    {
        noun "rock"
        before {
               object DoListen
                  {
                  "It sounds like a rock."
                  }
               }
    }

    rock big_rock "big rock"
    {
        adjective "big"
        before  {
                object DoGet
                   {
                   "It is much too big."
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
    [location](globals/location/), parent(player) (the last one only
    called by [DoGo](verb-routines/dogo/)*- When the routine
    [BeforeRoutines](guts/beforeroutines/) calls things like
    `player.before`, `location.before`, and `object.before`, the
    `before` property of the object set to the applicable
    [global variable](basics/global/) is called. If the usage is true for
    the current object, it goes on to check the verb routine and so
    forth.
-   **verbroutine**- This is obviously the verb routines we are trying
    to catch, either because we want to prevent the action or just
    change its outcome. If there is *no* verb routine, the block code
    will be applied to *all* verbs. In some cases- like when the usage
    parameter is the [location](globals/location/) global variable-
    this will also apply to xverbs. To get around this, use
    [AnyVerb](guts/anyverb).
-   **the block code**- This is where you put the text you want to print
    instead or the code that just alters some global value or something
    before letting routines go on as normal. Unless the block code
    *explicitly* returns false, the action-processing will stop right
    there. If you want the action to go on, return false!

### `before` order

The order of `before` properties is explained on things like the
[Game Loop page](loops/game-loop/), but you can also get it straight from
the horse's mouth by taking a look at
[hugolib.h](library/hugolib.h/)'s
[BeforeRoutines](guts/beforeroutines/) routine.
