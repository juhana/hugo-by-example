---
title: Rooms
permalink: /basics/rooms/
categories: 
  - Basics
  - Classes
---

Most interactive fiction games take place in multiple locations. These
locations are represented by rooms in the code. A room does not have to
be an actual room, it can be used to represent someplace outdoors, a
hall, or even a spaceship.

In Hugo, a room is represented by an [object](objects) that
is defined in the standard library. The basic definition of a room gives
its internal name, a display name, the room description and exits to
other locations.

Here is a short example of a simple room with two exits

```
room passenger_car "Passenger car"
{
   long_desc
      "The passenger car of the IF Express has been decorated in the style
       of an old-fashioned, American train from the Old West. To either side
       of the center aisle are padded seats. In one corner is an old stove
       for heat in the winter months. To the north is a door to the baggage
       car, and to the south is a door to the caboose."

   n_to baggage_car
   s_to caboose
}
```

Line by line:

-   **Line 1** Create a room object, with the internal name of
    **passenger_car** and displays **"Passenger car"** as the room name
    on the display.
-   **Line 3** [long_desc](Descriptions#long_desc) is the
    main description of the room, shown when first entered, or when the
    player types *look*
-   **Lines 4-8** The actual description text.
-   **Line 10** what room to go to when the player wishes to go north.
-   **Line 11** what room to go to when the player wishes to go south.

## "Regions"

[Inform 7](http://inform7.com/) has a concept of "regions", where groups
of rooms can have different behaviors. Hugo doesn't have built-in
support, but it's easy enough to set-up a system for your own game to
work off of.

1.  Create a `region` property.
        property region
2.  Create an [object class](object_Classes) for each of your
    regions.
        room library
        {
            region library
        }
3.  Write rooms for your regions.
        library reference_desk "Reference Desk"
        {
            n_to fiction_aisle
            w_to magazines_aisle
            e_to computer_center
        }
4.  Write region-checking code.
        player_character you "you"
        {
        before
            {
             actor DoYell
                {
                 if location.region = library
                    "Not in a library, you don't!"
                else
                    return false
                }
            }
        }
