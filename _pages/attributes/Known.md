---
title: known
permalink: /attributes/known/
categories: 
  - Attributes
---

`known` is an [attribute](attributes/) for keeping track of
whether a player has seen something yet. Unlike the
[moved](attributes/moved/) attribute, it requires no direct interaction.
For objects not originally defined with the `known` attribute, objects
are given it by routines like [FindObject](scope/findobject/),
[DescribePlace](guts/describeplace/),
[ShortDescribe](routines/shortdescribe/),
AddSpecialDesc,
[ListObjects](routines/listobjects/), and
[RunScripts](routines/runscripts/) as you happen upon them.

## Using `known` to fake knowledge

Sometimes you'll have to code fake objects just to make your game seem
smarter. Part of this process is giving the hypothetical object the
`known` attribute so the player doesn't get a "You don't know about
that." type response. Take, for instance, this fake object to allow a
specialized responsed to &gt;GO HOME.

    object home_object "home"
    {
       noun "home"
       in_scope you
       is known
       before
          {
          object
             {
             if verbroutine = &DoGo
                "Good plan, but how?"
             else
                "That doesn't make any sense."
             }
          xobject
             {
             "That doesn't make any sense."
             }
          }
    }
