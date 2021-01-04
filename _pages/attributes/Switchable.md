---
title: switchable
permalink: /attributes/switchable/
categories: 
  - Attributes
---

**switchable** is a predefined [attribute](attributes/) set to
indicate that an [object](globals/object/) can be turned on and off.
As such, it is often used in conjunction with
[switchedon](attributes/switchedon/).

Example:

    object tableLamp "Table lamp"
    {
        nouns "lamp", "light"
        adjectives "table", "small", "ugly"

        is switchable,  not switchedon

        long_desc
        {
            "It's the ugly table lamp your mother bought you for Christmas."
            if self is switchedon
                "Currently it is turned on and glowing with a soft white glow."
            else
                "It sits on the table, turned off."
        }
    }
