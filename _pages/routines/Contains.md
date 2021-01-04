---
title: Contains
permalink: /routines/contains/
categories: 
  - Object Tree
  - Routines
---

| calling form                                      | description                                                                                                                                  |
|---------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------|
| `Contains(parent or grandparent, possible child)` | Returns the child if the specified object is present as a possession of the specified parent, even as a grandchild, otherwise returns false. |

## The routine

    !----------------------------------------------------------------------------
    ! Contains(object 1, object 2)
    ! returns <object2> if <object 1> contains <object 2> (even as a grandchild)

    routine Contains(obj, possible_child)
    {
        local nextobj

        for (nextobj=parent(possible_child); nextobj; nextobj=parent(nextobj))
        {
            if nextobj = obj
                return possible_child
        }
    }

As you can see, `Contains` has a loop that keeps it going until it has
found the child's highest parent, so besides grandparents, it'll work
for great-grandparents and so forth (as seldom as that comes up).

## Examples of usage

"HugoZork" uses it when checking the player's inventory to see if he is
holding the sword, as "if sword in player" would be fooled if the sword
were in some container.

"The Vault of Hugo" uses it to check if an exploding bomb is in the same
location as the player, with the line "Contains(location,bomb)".

Mike Snyder's Distress code uses it in a custom routine made to check
whether a player is holding something or a component of something:

    !----------------------------------------------------------------------------
    !This is basically to check and see if the player can refer to something as
    !held -- mainly used in "DoPoint" because we need to check the part_of too.
    !
    routine PlayerHas(obj)
    {
        if Contains(player,obj) { return true }
        if Contains(player,obj.part_of) { return true }
    !  this next line is redundant since part_of aliases to found_in
    !    if Contains(player,obj.found_in) { return true }
        return false

    }
