---
title: vehicle
permalink: /classes/vehicle/
categories: 
  - Classes
---

Occasionally, you may need to have a vehicle in your game. Be it a car
(in a city), a horse (in a western) or a flying saucer. You're in luck,
as [objlib.h](Objlib) defines a basic vehicle class!


### First Things First

If you're going to use a vehicle in your game, you'll need to set the
**USE_VEHICLES** flag near the top of your code.

    #set USE_VEHICLES

### "Driving" Verbs

You will also need to define the verb(s) used to "drive" your vehicle
(or fly, or ride, etc...)

    verb "drive"
        *        DoMoveinVehicle
        * object DoMoveinVehicle

### Defining the Vehicle

Here's a simple example of a car definition:

    vehicle rollsroyce "Rolls Royce"
    {
      article "my"
      adjectives "silver", "expensive", "rolls"
      nouns "car", "rolls", "royce", "wraith"

      vehicle_verb "drive"
      long_desc
      {
        ! your description would go here
      }

      ! can't drive the car if it's out of gas
      vehicle_move
      {
        if self is not filled ! Assuming we've defined a 'filled' attribute
        {
          "The fuel gauge is sitting on empty, this beautiful car isn't going
           anywhere at the moment."
          return false   ! returning false here stops the MoveinVehicle action
        }
        else
        {
          return true
        }
    }

### The Vehicle Path

The Hugo Library assumes that vehicles cannot be moved in any location
by default (you probable wouldn't want a car to be able to be driven in
your kitchen) so you have to define a [property](properties)
for each room where a vehicle *can* be driven, and also, which vehicles
are allowed where. (for example, you may not want to allow a tricycle on
a freeway)

    ! a couple of simple rooms where the rollsroyce defined above can be driven
    room mainStreet "Main street"
    {
      long_desc
      {
        "A really nifty description of Main Street would go here"
      }
      e_to myHouse
      s_to bentonStreet
      n_to thirdStreet
      vehicle_path rollsroyce
    }

    room bentonStreet "Benton Street"
    {
      ! descriptions and exits definitions here
      vehicle_path rollsroyce
    }

    room myHouse "My House"
    {
      long_desc
      {
        "123 Main Street, the house I grew up in"
      }
      w_to mainStreet
      e_to entryHall
      ! and so on and so forth
      ! notice, there is no vehicle_path defined in this room, because
      ! driving a car here would be kind of silly
    }

## Determining whether player is in the vehicle

To determine if the player is in the vehicle, compare the parent to the
vehicle:

       if (parent(player)=rollsroyce) {
         ! code if they're in the car
       } else {
         ! if they're not
       }

# Things not to do

If you are using a test on a place, and the test succeeded, **do not**
use MovePlayer, because the player would be pulled out of the vehicle:


    ! We presume two other vehicles called Taxicab and PoliceCar were defined elsewhere

    room Airport2 "Chase International Airport"
    {
       vehicle_path Taxicab, PoliceCar, rollsroyce
       long_desc
       {
         "A sign out front says
           'Chase International Airport
        Welcomes you to the City of Panus
        Established 1700, Incorporated 1830.

        Chevy Chase County
        Established 1750
        Incorporated 1910
        Welcomes you to the Home of East-Coast University.'

            The main pick up/departure roadway continues north and south, while
            to the west is a driveway with a sign reading 'Authorized Vehicles Only'"
       }
       n_to Airport1
       s_to Airport3
       w_to
       {
         if (parent(player)=Taxicab or parent(player)=policecar)
         {
           print "The police waive you through."
           Moveplayer(Airport4)  ! NO! THIS IS WRONG!  THIS WILL PULL THE PLAYER OUT OF THE VEHICLE!
         } else {
           if (parent(player)=rollsroyce)
             "Your vehicle is not authorized."
           else:
             "Pedestrians are not permitted past this point."
         }
       }
    }

Instead, you need to cover the two conditions, when the user is in a
vehicle and when they are not, in the before event:

    room Airport2 "Chase International Airport"
    {
       vehicle_path Taxicab, PoliceCar, rollsroyce
       long_desc
       {
         "A sign out front says
           'Chase International Airport
        Welcomes you to the City of Panus
        Established 1700, Incorporated 1830.

        Chevy Chase County
        Established 1750
        Incorporated 1910
        Welcomes you to the Home of East-Coast University.'

            The main pick up/departure roadway continues north and south, while
            to the west is a driveway with a sign reading 'Authorized Vehicles Only'"
       }

       before
        {
        location    DoMoveinVehicle
        {
    ! if you have multiple exits, specify each with  or  between them, e.g. if ((object=e_obj) or (object=nw_obj)) etc
                 if ((object=w_obj) )
                   {
                    if (parent(player) = PoliceCar or parent(player)=Taxicab)
                      {
                         print "The Police waive you through "
                         return false  ! This permits the move to go through
                      } else
                         "Your vehicle is not authorized."
                      }
                   }
            }
            location    DoGo
        {
                   if ((object=w_obj))
                     {
                       "Pedestrians are not permitted past this point. "
                       return true   ! This is optional, it happens automatically
             }
            }
       ! If neither of these were the case or they weren't traveling west, the go or drive command
       ! proceeds as if this code was not here
       }

       n_to Airport1
       s_to Airport3
       w_to Airport4  ! this will be overridden by the 'before' event
    }

In the above example, a police car or taxi can be driven west, but you
can't walk there or drive the Rolls.

# Lurking Forklifts

In the Infocom game *The Lurking Horror*, there is a forklift that
allows you to drive it with regular navigation commands (**GO EAST. N.
WEST.**) as long as the forklift is turned on. The following code does
its best approximation of the Lurking Horror behavior. The most
challenging aspect was that `DoMoveInVehicle` requires the [word
array](Word_Array) to have one of the `vehicle_verb` words in
it, so we had to use [InsertWord](InsertWord) to make room
for it if the player had typed a one-word command like "**NORTH**."

    room basement "Basement"
    {
        e_to tempbase
        u_to compcenter
        vehicle_path forklift
        before
            {
            location    DoMoveinVehicle
                {
                if object = u_obj
                    "The forklift won't fit into the stairwell."
                else
                    return false
                }
            }
    }

    room compcenter "Computer Center"
    {
        d_to basement
    }

    vehicle forklift "forklift"
    {
        article "the"
        noun "forklift"
        in basement
        prep "on", "off"
        short_desc
            "There is a forklift here."
        long_desc
            "It is a rusty and wheezing old forklift. It looks like you could control it fairly easy, though."
        vehicle_verb "go" "drive" "ride" ! "go" is first so it still says "You can't go that way."
        vehicle_move
            {
            if self is not switchedon
                {
                "You can't go anywhere in a forklift that isn't running."
                return false
                }
            else
                return true
            }
        before
            {
            object DoSwitchOn, DoSwitchoff
                {
                if parent(player) ~= self
                    "You'll have to get in it first."
                else
                    return false
                }
            }
        react_before  {
            if verbroutine = &DoGo and parent(player) = self
                    {
                    if object = d_obj, out_obj  ! let's interpret >OUT and >DOWN
                        {                        ! as getting out of the forklift
                        words = 0                ! stop SetupDirectionObjects from
                        verbroutine = 0          ! resetting the object (it's called by
                        object = out_obj               ! Perform)
                        return false
                        }
                    if self is switchedon
                        {
                        if words > 1
                            word[1] = "drive"
                        else
                            {
                            InsertWord(1)
                            word[1] = "drive"
                            }
                        Perform(&DoMoveInVehicle, object)
                        return true
                        }
                    else
                        {
                        "You can't go anywhere in a forklift that isn't running."
                        return true
                        }
                    }
            return false
            }
        after
            {
            object DoSwitchOn
                {
                "The forklift sputters to life."
                }
            object DoSwitchOff
                {
                "The forklift coughs ones, and dies."
                }
            object DoListen
                {
                "At the moment, the forklift is quiet as a graveyard."
                }
            object DoExit
                {
                "You are now on your feet."
                }
            }
        is switchable
    }

    room tempbase "Temporary Basement"
    {
        w_to basement
        e_to deadstorage
        vehicle_path forklift
        before
            {
            location    DoMoveinVehicle
                {
                if object = u_obj
                    "The forklift won't fit into the stairwell."
                else
                    return false
                }
            }
    }

    room deadstorage "Dead Storage"
    {
        w_to tempbase
        vehicle_path forklift
        is not light
    }

    replace NewVMessages(r, num, a, b)
    {

            select r

        case &DoSwitchOn
        {
            select num
            case 1: {
                if object = forklift
                    "It's wheezing away already."
                else
                    print CThe(object); IsorAre(object); " already turned on."
                }
            case 2: return false
        }

        case &DoSwitchOff
        {
            select num
            case 1:  {
                if object = forklift
                    "It's already off."
                else
                    print CThe(object); IsorAre(object); " already turned off."
                }
            case 2:  return false
        }

            case else : return false

        return true ! this line is only reached if we replaced something
    }

    replace DarkWarning
    {
        "It is pitch black."
    }

### Shenanigans

In the above example, we had to do several things in the
[react_before](react_before) property so that "down" would
an acceptable direction for leaving the forklift:

1.  We changed the object from `d_obj` to `out_obj` so that
    [DoGo](DoGo) doesn't automatically print a "You'll have
    to get off" message.
2.  We cleared the [words](words) global so that when
    [SetupDirectionObjects](SetupDirectionObjects) is called
    by [Perform](Perform), it doesn't reset the [object
    global](object_(Global)) back to `d_obj`
3.  We clear the [verbroutine](verbroutine) global so that
    `DoGo` can't call the vehicle class's `before` property.
