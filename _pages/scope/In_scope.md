---
title: in_scope
permalink: /properties/in_scope/
categories: 
  - Scope
  - Properties
---

The `in_scope` [property](properties/) is defined by the
[standard library](library/). It puts an
[object](globals/object/) in the scope of an actor. It is like
[found_in](scope/found_in/) except it works off of characters, not
locations. It allows much cleaner code when used in conjuction with the
[PutInScope]({{page.url}}#putinscope) and
[RemoveFromScope]({{page.url}}#removefromscope) routines.

## in_scope (object [property](properties/))

    in_scope you

is a more-eloquent alternative to:

    found_in {return location}

As is the case with [found_in](scope/found_in/), although in the
actor's scope, the object is not technically in the same room according
to the object tree.

## PutInScope and RemoveFromScope

If `in_scope` properties change within the course of the game, it is
recommended that you use [PutInScope]({{page.url}}#putinscope)
and [RemoveFromScope]({{page.url}}#removefromscope) to do so.

### PutInScope

| calling form             | what it does                                                                                                                                                                                                                                 |
|--------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| PutInScope(object,actor) | Makes the given object accessible to the specified actor, regardless of their respective locations, and providing that the in_scope property of the object has at least one empty slot—i.e., one that equals 0. Returns true if successful. |

Example:

    player_character you "you"
    {
          in_scope 0 0 ! this hypothetical game has a max of 2 objects being moved to the player's scope
    }

    female_character old_granny "kindly grandmother"
    {
          noun "grandmother"
          adjective "kindly"
          before
                {
                object DoPush
                     {
                     if self is not special
                          {
                          "It's not often that you just happen to be at the
                           top of a staircase next to an old person. You weigh your options."
                          PutInScope(angel_on_shoulder, you)
                          PutInScope(devil_on_shoulder, you)
                          self is special
                          }
                     else
                          "Talk to the little guys on your shoulders!"
                     }
                }
    }

### RemoveFromScope

| calling form                  | what it does                                                                                                                                                      |
|-------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| RemoveFromScope(object,actor) | Removes the given object from the scope of the specified actor. Returns true if successful, or false if the object was never in scope of the actor to begin with. |

Example:

            "You refrain from pushing the old woman. The angel on your shoulder smiles triumphantly.
             The devil says something unkind about your haircut. Both pop out of existence."
             RemoveFromScope(angel_on_shoulder, you)
             RemoveFromScope(devil_on_shoulder, you)
