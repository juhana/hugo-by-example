---
title: size
permalink: /properties/size/
categories: 
  - Properties
---

`size` is a [property](/properties/) given to all objects (the
default value is 10). Routines like [Acquire](/guts/acquire)
(called by DoGet and DoPutIn) check object sizes to see if there is
"room" within a container or platform by comparing it to the latter's
[capacity](/properties/capacity/) property.

You can give an object a different value by specifying something else:

    object boulder "boulder"
    {
        article "a"
        noun "boulder"
        size 1000
    }
