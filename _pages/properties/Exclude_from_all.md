---
title: exclude_from_all
permalink: /properties/exclude_from_all/
categories: 
  - Properties
---

`exclude_from_all`, when true, restricts an item from being included in
multiple-object verbs like [DoGet](verb-routines/doget/) (&gt;GET ALL) or
[DoDrop](verb-routines/dodrop/) (&gt;DROP ALL). The
[`scenery`](basics/scenery/) class is defined like this:

    class scenery
    {
        type scenery
        exclude_from_all
        {
    #ifclear NO_VERBS
            if verbroutine = &DoGet
                return true
            else
    #endif
                return false
        }
        is static, hidden
    }

It won't show up for &gt;GET ALL, but it will for other verbs that use
the [multi grammar token](basics/grammar-tokens/).

### Printing the failure

If `exclude_from_all` returns true, the item is completely skipped. We
can make it seem like the object was "considered", though, by having
something like this:

    object jelly "jelly"
    {
       noun "jelly"
       exclude_from_all
          {
          if verbroutine = &DoGet
            {
            print self.name ; ":_ ";
            "You can't get the jelly while picking up other items."
            return true
            }
          else
            return false
          }
       in sandwich_shop
    }

Giving:

>&gt;get all  
>jelly: You can't get the jelly while picking up other items.  
>book: Taken.  
>jar: Taken.

### Parents and 'exclude_from_all'

If an object is a parent to other objects and has a false `exclude_from_all` property (allowing it to be used in "all" commands), its children will be skipped.   If the parent has a true `exclude_from_all` property, the command will get applied to its children instead (unless further rules prevent it in the [ExcludeFromAll](routines/excludefromall/) routine).
