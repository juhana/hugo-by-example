---
title: Reading
permalink: /tips/reading/
categories: 
  - Tips
---

*For help on making "consult"-able books, check out the
[Books](/contributions/books.hug/) page...*

There are multiple "schools of thought" when it comes to reading in IF.
Some authors feel that it is okay if **&gt;READ** redirects to
**&gt;EXAMINE**; others feel it should get its own distinct response. In
both cases, as far as the Hugo
[Standard Library](/library/) is concerned, you'll have to give
the object that can be **&gt;READ** the [readable](/attributes/readable/)
attribute.

One way to give a distinct answer to **&gt;READ** would be to replace
the verblib.g [grammar](/basics/grammar/) with something that
redirects to a `DoRead` routine that checks that the object is
`readable` and looks for a `writing` [property](/properties/) or
something like that.

On the other hand, a much easier way to handle it (that'll save you the
trouble of replacing grammar or writing new routines or making new
properties) is to just check what verb word the player used in our
[long_desc](/properties/descriptions/) response:

    object chainsaw "chainsaw"
    {
        article "a"
        noun "chainsaw"
        is readable
        long_desc
            {
            if (word[1] = "read", "peruse")
                {
                "\"Black & Decker.\""
                }
            else
                "Scary looking thing."
            }
        in bill
    }

In the above example, **&gt;READ CHAINSAW** and **&gt;EXAMINE CHAINSAW**
will get two different replies!
