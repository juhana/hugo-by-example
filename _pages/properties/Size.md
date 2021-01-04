---
title: size
permalink: /properties/size/
categories: 
  - Properties
---

`size` is a [property](Properties) given to all objects (the
default value is 10). Routines like [Acquire](Acquire)
(called by DoGet and DoPutIn) check object sizes to see if there is
"room" within a container or platform by comparing it to the latter's
[capacity](capacity) property.

You can give an object a different value by specifying something else:

    object boulder "boulder"
    {
        article "a"
        noun "boulder"
        size 1000
    }
