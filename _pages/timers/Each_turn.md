---
title: each_turn
permalink: /timers/each_turn/
categories: 
  - Timers
  - Properties
---

The **each_turn** property is defined by the [standard
library](standard_library), and is used by room
[objects](objects). A [room's](Rooms) `each_turn`
[property](Properties) is executed every turn that the player
is in the relevant room.

    routine main
    {
            counter = counter + 1
            PrintStatusLine
            run location.each_turn
            runevents
            RunScripts
            if speaking not in location
                    speaking = 0
    }

As you can see, it is called after PrintStatusLine but before timers,
fuses, or other events and scripts are called. In any case, `each_turn`
is very useful.

## Using each_turn as a timer

    room burningroom "Burning Room"
    {
         long_desc
              "The room is on fire! Better get out soon!"
         misc 0
         out_to saferoom
         each_turn
              {
              self.misc++
              if self.misc = 3
                   {
                   "You have burned to death! Drat."
                    endflag = 2
                   }
              }
    }

## Using each_turn to check conditions

    room chemlab "Chem Lab"
    {
          long_desc
               "You are in a lab. Hooray for science!"
          each_turn
               {
               if Contains(jar,matter) and Contains (jar,antimatter)
                    {
                    "You have 'sploded to death! Drat."
                     endflag = 2
                    }
               }
    }

Sometimes, you'll even use `each_flag` in instances where the player
*won't* die! It's true!
