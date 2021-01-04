---
title: NewAutomap
permalink: /contributions/newautomap/
categories: 
  - Library Contributions
---

`NewAutomap`, an update to [Automap](Automap), is a library
extension that adds several mapping possible mapping functions to your
game. One use is to show a quick map that will last one turn, and
another option will turn on an automapper that stays on. Lastly, there
is an option to do a full map that shows as many rooms as possible.
Unlike the original, this version will work on glk interpreters. It can
be downloaded [here](http://roody.gerynarsabode.org/hbe/newautomap.zip).

## How To Add to Your Game

Besides including the library extenstion file, you'll want to add the
following to the grammar and the main routine in your main source file:

    ! grammar
    xverb "map", "m"
            *                                       DoMap
            * "on"                                  DoMapOn
            * "off"                                 DoMapOff
            * "from" object                         DoMap
            * "game"                                DoFullMap
            * "game" "from" object                  DoFullMap


    ! to be added to main{}, after PrintStatusLine

            MapSet

## How to Code Your Mappable Rooms

Here is everything a mappable room needs:

    room room5 "room 5"
    {
          ! only rooms with the visited attribute are shown. of course, you don't need to set this as rooms will be set visited when
          ! they are, um, visited
          is visited

          e_to room3  ! your average direction definition

          s_to   {                            ! exits with doors or other special code
                 if object = s_obj            ! need to check if the object is set to the direction object
                   return a_door.door_to  ! before executing proper direction code. otherwise, we'll just
             else                         ! return with the final destination so as not to confuse the
               return room4           ! mapper
                 }

          map_list #13 ! all rooms need 13 open map_list property slots if the game uses the full map function
    }

## Differences Between Glk and Non-Glk Performance

In glk interpreters, all mapping is drawn in the status window since
[locate](locate) doesn't work in the main window. In a
regular interpreter, the automapper is in a floating window beneath the
status line.
