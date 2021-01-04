---
title: lockable
permalink: /attributes/lockable/
categories: 
  - Attributes
---

`lockable` is given to objects that can be locked (and therefore,
unlocked). As such, it is often used with the
[locked](locked) attribute. An object needs the `lockable`
attribute just to get any sort of response from **UNLOCK** or **LOCK**
commands.

    object deadbolt "deadbolt lock"
    {
       article "the"
       adjective "deadbolt"
       noun "lock"
       is lockable locked
    }
