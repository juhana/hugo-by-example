---
title: inv_desc
permalink: /properties/inv_desc/
categories: 
  - Properties
---

Sometimes one wants to split up the &gt;INVENTORY response somehow. The
inv_desc object property is a built-in option for doing that
(DoInventory calls WhatsIn(player), which calls
[SpecialDesc(obj)](/routines/specialdesc/), which checks for the
inv_desc property).

Let's say you are writing a game where you can wield one weapon at a
time and want to reflect that in your inventory response:

    object mace "mace"
    {
    noun "mace"
    article "the"
    equipped 0
    inv_desc {
             if equipped = true
                {
                 "You are wielding the mace."
                  return true
                }
             else
                return false
             }
    }

That would give us this:

<div class="output">

&gt;i
You are wielding the mace.
You are also carrying a shield.

</div>

Of course, in this example, our DoEquip routine would have to make sure
that only one object was equipped at a time. If the game needs to check
for more than one object, we'll have to replace SpecialDesc(obj). In the
following example, the protagonist is a juggler, and &gt;INVENTORY
checks to see how many balls the PC is juggling.

    object smoothball "smooth ball"
    {
    in emptyroom
    noun "ball"
    article "a"
    adjective "smooth"
    juggling 0
    inv_desc {
             if self.juggling = 1
                return true
             else
                return false
             }
    }

    object lumpyball "lumpy ball"
    {
    in emptyroom
    noun "ball"
    article "a"
    adjective "lumpy"
    juggling 0
    inv_desc {
             if self.juggling = 1
                return true
             else
                return false
             }
    }

    replace SpecialDesc(obj)
    {
        local a, c, flag, printed_blankline
        local t

        if FORMAT & LIST_F
            return
        t=0
        list_count = 0
        for a in obj
        {
            if a is not hidden
                {
                c++
                flag = true
                }
            else
                flag = false

            if FORMAT & INVENTORY_F and obj = player and flag
            {
                if &a.inv_desc
                    Indent
                if a.inv_desc
                    {
                    if FORMAT & LIST_F:  print newline
                    AddSpecialDesc(a)
                    t = 1
                    }
            }
    ! This next section is used in room descriptions
            elseif a is not moved and flag
            {
                if &a.initial_desc
                {
                    print newline
                    override_indent = false
                    if FORMAT & INVENTORY_F and FORMAT & NOINDENT_F and not printed_blankline
                        print ""
                    printed_blankline = true
                    Indent
                }
                if a.initial_desc
                    AddSpecialDesc(a)
            }
        }
    ! if t=1, it means something at least one inv_desc property has returned true.
    ! This is where the MAGIC HAPPENS!!
            if t=1
            {
            print "You are juggling "; number list_count;
            if list_count > 1
            print " balls."
            else
            print " ball."
            }
        list_count = c - list_count
    }

Which would give us:

<div class="output">

&gt;i
You are juggling 2 balls.
You are also carrying a broken unicycle.

</div>

(Assuming you set up a DoJuggle to set the balls' juggling property to
1)

You can also modify SpecialDesc(obj) so the first part is a proper list
that names all of the individual items.
