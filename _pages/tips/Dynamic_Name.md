---
title: Dynamic Name
permalink: /tips/dynamic-name/
categories: 
  - Tips
---

This is left in for examples, but there is an easier way to get a
dynamic name for a room or object, which will be shown at the bottom of
this article. The method below may be useful for some cases, so it's
left here as an exercise.

## The Original Suggestion

This allows the name of a room to be created dynamically. I had to do it
because making the name dynamic by using a routine in the **name**
property made the run-time system think I had overflowed the page and
ask for a unnecessary **\[MORE\]** keypress.

1\. Insert the following at the start of your code:

    property dynname                     ! Room generates its own name dynamically

2\. in routine **Describeplace** in file **hugolib.h** replace the line

      print "\n"; capital place.name;

with

    !!! Dynamic Names

        if place.dynname
        {

        }
        else {
            print "\n"; capital place.name;
        }

What this does is call the dynname property if it exists, otherwise the
name property is used.

3\. To use dynname, add it as a property

Explanations are given with !! in front of them. Let's say I want to
call an area east or west depending on a flag, and have it assigned a
number:

    room Corner "Corner"   !! This name is what is shown in the room display
    {
        dynname
        {
           if street_number < 1
               print "East ";
           else: print "West ";
           print number abs(street_number); ordinal( street_number ) ;"St. "
        }
     !!! ... more properties
    }

(The [ordinal](ordinal) routine mentioned above generates the
st, rd, th extension on a number.)

## A simpler method

To provide a dynamic name, do not define it in the object (or room's)
header, define it as the **name** [property](property) and
create code for it.

The following example is for a gas meter, that if you hit it with a
sledge hammer, it now reports it's leaking. But before it's hit, it's
just a gas meter. The code for a hit sets the special attribute leaking.
So here is how we can change the name:

        name
        {
            if self is leaking
               {
                sound repeat "air leak.wav"
                return "gas meter - WARNING: The gas meter is leaking"
               } else {
               return "gas meter"
               }

        }

So if there are other meters there, you get this

>&gt;e
>
>You are in the Meter Room of the control center  
>  You are in the meter room of the control center.  Nailed to a table is a yardstick. Oh. Excuse me,
>it's 39 inches long.  It's a meter stick.  Of course, how stupid of me! You can go OUT to return
>to the control center.  
>A gas meter, an electric meter, and a water meter are here.
>
>&gt;hit gas meter with sledge  
>You've smashed the meter.  It is now leaking.  Be careful or you won't be here long.
>
>&gt;look  
>You are in the Meter Room of the control center  
>  You are in the meter room of the control center.  Nailed to a table is a yardstick. Oh. Excuse me,
>it's 39 inches long.  It's a meter stick.  Of course, how stupid of me! You can go OUT to return
>to the control center.  
>  A gas meter - WARNING: The gas meter is leaking, an electric meter, and a water meter are here.

------------------------------------------------------------------------
