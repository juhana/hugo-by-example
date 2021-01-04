---
title: type
permalink: /properties/type/
categories: 
  - Properties
---

The **type** [property](properties/) is defined by the [standard library](library/).

## type (object [property](properties/))

The `type` property is used to mark [objects](basics/objects/) as a
certain kind. It is most often used by [classes](basics/object_classes/).

An example:

    class playingcard
    {
         type playingcard
    }

    playingcard JoS "Jack of Spades"
    {
         long_desc
               "It is a Jack of Spades."
    }

    container deck "deck of cards"
    {
          before
                {
                xobject DoPutIn
                      {
                       if object.type ~= playingcard
                            {
                            "Only cards should be put in the deck."
                            return true
                            }
                       return false
                      }
                }
    }

In the above example, we show how someone may check the type of
something before allowing an action.
