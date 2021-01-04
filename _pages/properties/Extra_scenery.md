---
title: extra_scenery
permalink: /properties/extra_scenery/
categories: 
  - Properties
---

`extra_scenery` is a room property that holds dictionary words, like
`nouns` or `adjectives`. Unlike those other examples, though, when
players type `extra_scenery` words, they get a "You don't need to refer
to that." message. Basically, it's a heads-up to the player that the
object is not implemented (and therefore, not worth any attention).

### example

    room attic "dusty attic"
    {
        long_desc
            "Between the feeble amount of light dripping from your flashlight
        and the insane amount of junk,  it is difficult to see anything up here.
        What \Bcan\b be seen consists mostly of unmarked boxes and bric-a-brac."
        extra_scenery "dust" "bric-a-brac"
        d_to upstairshallway
    }

Now, referring to "dust" or "bric-a-brac" will result in "You don't need
to refer to that."

### changing the default message

The `extra_scenery` response is handled by the
[Message](Messages) routine with this code:

        case &Parse
        {
            select num
            case 1:  print CThe(player); \
                    MatchPlural(player, "doesn't", "don't"); \
                    " need to refer to that."
                    ! ... goes on to list other cases

So keep that in mind if you'd like to
[change](Messages#Custom_or_New_Routine_Responses) it.
