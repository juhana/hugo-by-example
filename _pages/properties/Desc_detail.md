---
title: desc_detail
permalink: /properties/desc_detail/
categories: 
  - Properties
---

`desc_detail` is an [object](globals/object/)
[property](properties/) meant to be filled with routines that
print messages such as " **(providing light**" or "*' (currently
dark)*'", any of those things that might follow an object in an
inventory or room listing (under the right circumstances). Two things to
remember:

1.  The space before the parenthesis is important.
2.  The printed text should have a semicolon (and therefore won't print
    a newline).

### Tales of the Traveling Swordsman

    object sword "broadsword"
    {

        inherits game_object !Description handling, etc.

        !MISC #1 = is the sword in its sheath? True=yes, False=no
        misc true

        nouns "sword", "blade", "broadsword", "weapon"
        adjectives "broad", "my"
        article "your"
        in swordsman
        is sharp, always_held
        size 25

        exclude_from_all { return true }

        desc_detail {
            if (self.misc #1) {
                " (sheathed)";
            } else {
                " (unsheathed)";
            }
        }

        ! more object code ...
    }

And:

    object beam "heavy wooden beam"
    {
        inherits game_object !Description handling, etc.

        !MISC #1 = has the player picked up the beam at least once?
        misc false

        nouns "beam", "crossbar", "bar", "wood"
        adjectives "wooden", "wood", "long", "large", "big", "heavy", "bulky"
        article "a"
        size 75 !Huge Size
        in loft !Because that's where it starts out at.
        exclude_from_all { return true }

        desc_detail {
            if Contains(player,self) {
                " (held across both arms)";
            } else {
                return false !No desc detail.
            }
        }
    ! more object code
    }
