---
title: locked
permalink: /attributes/locked/
categories: 
  - Attributes
---

`locked` is given to objects that are locked. As such, it is often used
with the [lockable](attributes/lockable/) attribute.

    object deadbolt "deadbolt lock"
    {
       article "the"
       adjective "deadbolt"
       noun "lock"
       is lockable locked
    }
