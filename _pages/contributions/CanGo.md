---
title: CanGo
permalink: /contributions/cango/
categories: 
  - Library Contributions
---

**CanGo** is a library contribution written by Cardinal Teulbachs and
uploaded to the IF Archive in 2000. It is a nice array/routine combo
that allows for automatic exit-listing in games. You can get it
[here](http://ifarchive.smallwhitehouse.org/if-archive/programming/hugo/library/contributions/cango.h).
It should work for you fine as long as you follow these rules:

1.  Keep direction property code clean, as described
    [here](Direction#Direction_properties_that_play_nice_with_others).
2.  Give rooms names that will easily fit into the format, "You can go
    east to \[preposition\] \[room name\]."
3.  Add a space to the preposition property for rooms that require
    prepositions (example: `prep " a"`
4.  Call the routine `YouCanGo()` from each room's `long_desc` property
    (assuming you want exits listed in every room description).

## `CanGo` in practice

Let's put CanGo to the test!

    room STARTLOCATION "porch"
    {
    prep " the"
    long_desc
        {
        "You are standing on an ornate porch."
        YouCanGo
        }
    in_to livingroom
    s_to street
    }

    room livingroom "living room"
    {
    prep {
          if self is visited
            return " the"
            else
            return " a"
            }
    long_desc
        {
        "This living room is quite comfortable."
        YouCango
        }
        out_to STARTLOCATION
    }

    room street "street"
    {
        prep " the"
        long_desc
            {
            "This quiet lane extends a ways in each direction."
            YouCanGo
            }
        n_to STARTLOCATION
        e_to eastend
        w_to westend
    }

    room eastend "east end"
    {
        prep " the"
        long_desc
            {
            "The street abruptly ends with a brick wall."
            YouCanGo
            }
        w_to street
    }

    room westend "west end"
    {
        prep " the"
        long_desc
            {
            "The street ends in a giant puddle."
            YouCango
            }
        e_to street
    }

    array go_dirs[13]

    routine YouCanGo
    {
        local n, p, cnt, the_dir, list_ref , total

       go_dirs[1] = location.n_to
       go_dirs[2] = location.s_to
       go_dirs[3] = location.e_to
       go_dirs[4] = location.w_to
       go_dirs[5] = location.ne_to
       go_dirs[6] = location.nw_to
       go_dirs[7] = location.se_to
       go_dirs[8] = location.sw_to
       go_dirs[9] = location.in_to
       go_dirs[10] = location.out_to
       go_dirs[11] = location.u_to
       go_dirs[12] = location.d_to

       for(n = 1; n <= 12; n++)
       {
            if go_dirs[n]
                {
                total++
                }
       }

        go_dirs[0] = total

       if go_dirs[0] = 0                             ! if nowhere to go
            {
            ""
            Indent
            "There are no obvious exits from here."
            return true                                ! bail out
            }

        ""
        Indent
       "You can go ";

       for (n=1; n<=12; n++)                ! begin Exits loop
       {
         if go_dirs[n] ~= 0                 ! skip empty array elements
         {
           if go_dirs[n].type = door
           {
             local x
             for (x=1; x<=2; x++)
             {
               if go_dirs[n].between#x ~= location
                 the_dir = go_dirs[n].between#x
             }
           }
           else
             the_dir = go_dirs[n]

           if go_dirs[n] = location.n_to : print "north to"; the_dir.prep; " "; the_dir.name;
           elseif go_dirs[n] = location.s_to : print "south to"; the_dir.prep; " "; the_dir.name;
           elseif go_dirs[n] = location.e_to : print "east to"; the_dir.prep; " "; the_dir.name;
           elseif go_dirs[n] = location.w_to : print "west to"; the_dir.prep; " "; the_dir.name;
           elseif go_dirs[n] = location.ne_to : print "northeast to"; the_dir.prep; " "; the_dir.name;
           elseif go_dirs[n] = location.nw_to : print "northwest to"; the_dir.prep; " "; the_dir.name;
           elseif go_dirs[n] = location.se_to : print "southeast to"; the_dir.prep; " "; the_dir.name;
           elseif go_dirs[n] = location.sw_to : print "southwest to"; the_dir.prep; " "; the_dir.name;
           elseif go_dirs[n] = location.in_to : print "in to"; the_dir.prep; " "; the_dir.name;
           elseif go_dirs[n] = location.out_to : print "out to"; the_dir.prep; " "; the_dir.name;
           elseif go_dirs[n] = location.u_to : print "up to"; the_dir.prep; " "; the_dir.name;
           elseif go_dirs[n] = location.d_to : print "down to"; the_dir.prep; " "; the_dir.name;

           cnt = 0
           for (p=n; p<=12; p=p+1)         ! determine whether list end
           {
             if go_dirs[p] ~= 0
               cnt++
           }

           if cnt = 2
                {
                if total = 2  ! choose appropriate punct.
                    " or ";
                else
                    ", or ";
                }
           elseif cnt >= 3 : ", ";
           elseif cnt = 1 : { "." : break }        ! and break if end

           cnt = 0                                  ! reset counter for next pass
           list_ref = 0
         }
       }
       local m
       for (m=0; m<=12; m++)                        ! flush array
          go_dirs[m] = 0
       return true                                  ! return true to advance turn
    }

The above code would have the following output:

>Porch  
>You are standing on an old porch.
>
>You can go south to the street or in to a living room.
>
>&gt;in
>
>Living room  
>This living room is quite comfortable.
>
>You can go out to the porch.
>
>&gt;out
>
>Porch  
>You are standing on an old porch.
>
>You can go south to the street or in to the living room.
>
>&gt;s
>
>Street  
>This quiet lane extends a ways in each direction.
>
>You can go north to the porch, east to the east end, or west to the west
end.
>
>&gt;w
>
>West end  
>The street ends in a giant puddle.
>
>You can go east to the street.
