---
title: cant_go
permalink: /properties/cant_go/
categories: 
  - Properties
---

`cant_go` is property for [room](Rooms) objects. Its code
will replace the standard "You can't go that way." message. Here is an
example of its usage:

    room ocean "Middle of the Ocean"
    {
          long_desc
               "Who thought jumping off the ocean liner in the middle of the ocean was a good idea?"
          cant_go
               "There is no land in that direction."
    }

## Advanced Usage

Besides that obvious case, you can also tweak `cant_go` to replace
single-direction "can't go" messages. It can be beneficial to keep
location directional properties (n_to, e_to, etc.) clear of printed
code so that exit-checking routines and extensions work properly. So,
instead of:

    room cave "Cave"
    {
          w_to
               "That direction is blocked by a cave-in."
          e_to treasure_vault
    }

You can have:

    room cave "Cave"
    {
          e_to treasure_vault
          cant_go
                {
                if object = w_obj
                     "That direction is blocked by a cave-in."
                else
                     return false
                }
    }

This way, going west will still get the special message but the other
unsuccessful directions will get the default.
