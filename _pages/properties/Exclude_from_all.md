---
title: exclude_from_all
permalink: /properties/exclude_from_all/
categories: 
  - Properties
---

`exclude_from_all`, when true, restricts an item from being included in
multiple-object verbs like [DoGet](DoGet) (&gt;GET ALL) or
[DoDrop](DoDrop) (&gt;DROP ALL). The
[`scenery`](scenery) class is defined like this:

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
the [multi grammar token](Grammar_Tokens).

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
