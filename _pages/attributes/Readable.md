---
title: readable
permalink: /attributes/readable/
categories: 
  - Attributes
---

The `readable` [attribute](attribute) signifies that an
object can be used with the verbs "read" and "peruse." Even still, the
[Standard Library](Standard_Library) will just direct the
action to [DoLook](DoLook), so without replacing [verb
grammar](verb_grammar) or creating a `DoRead` routine, to
offer a different response, one could do something like this:

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
