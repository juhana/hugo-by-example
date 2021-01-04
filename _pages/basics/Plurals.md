---
title: Plurals
permalink: /basics/plurals/
categories: 
  - Basics
  - Classes
---

There may come a time where you will want the player to be able to act
upon a group of objects together. Say for example, you want them to be
able to type something like *`get letters`* instead of typing
*`get the rejection letter. Get the yellow letter. Get the love letter.`*

The Hugo standard library offers two classes to handle plural objects,
**`plural_class`** and **`identical_class`**. 

## Before starting

Before using the plural_class or identical_class in your code, you
will need to set the USE_PLURAL_OBJECTS flag and call
`InitPluralObjects` (usually in your `init` routine)

    #set USE_PLURAL_OBJECTS

    routine init
    {
        ...
    #ifset USE_PLURAL_OBJECTS
        InitPluralObjects
    #endif
    }

## plural_class

The `plural_class` object is used to group two or more similar objects
together, such as letters, sundaes, cars, etc.

    ! first, we need to enable plurals in the library, so we
    ! set the USE_PLURAL_OBJECTS flag somewhere at the beginning
    ! of our code
    #set USE_PLURAL_OBJECTS
    ...

    ! we will need to also initialize the plural object system,
    ! somewhere inside the init routine
    routine init
    {
       ! other init code here
       ...
       InitPluralObjects
       ...
    }

    ! defining plural objects now
    ! first, define the plural_class
    plural_class cars "cars"
    {
        ! the plural_of lists all the objects that are included
        ! in this particular grouping of objects
        plural_of red_car, blue_car, police_car
        noun "cars"
        single_noun "car"
    }

    ! next, we're gonna define a generic toy_car class object to reduce typing when
    ! defining multiple toy cars
    object toy_car_class "toy car"
    {
        noun "car"
        plural_is cars
    }

    ! now to the cars themselves

    toy_car_class red_car "red car"
    {
        noun "car"
        adjectives "toy", "red"
        ...
        ! we've inherited the 'plural_is' from toy_car_class
    }

    toy_car_class blue_car "blue car"
    {
        noun "car"
        adjectives "toy", "blue"
        ...
    }

    toy_car_class police_car "police car"
    {
        noun "car"
        adjectives "toy", "police", "cop"
        ...
    }

Sample output (assuming we've actually added long_desc to the cars, and
did other thing right)

>There are a red car, blue car and a police car here  
>&gt; get cars
>
>red car: Taken.  
>blue car: Taken.  
>police car: Taken.

## identical_class

The `identical_class` is used in a similar way to the `plural_class`
above, but it is used to represent groupings of identical objects, such
as pencils, pens, pineapples.

    ! first, we need to enable plurals in the library, so we
    ! set the USE_PLURAL_OBJECTS flag somewhere at the beginning
    ! of our code
    #set USE_PLURAL_OBJECTS
    ...

    ! we will need to also initialize the plural object system,
    ! somewhere inside the init routine
    routine init
    {
       ! other init code here
       ...
       InitPluralObjects
       ...
    }

    ! defining identical plural objects now

    ! first, define the identical class object

    identical_class pineapples "pineapples"
    {
        plural_of pineapple1, pineapple2, pineapple3, pineapple4
        noun "pineapples"
        single_noun "pineapple"
    }

    ! now, on to the fruit
    object pineapple1 "pineapple"
    {
        noun "pineapple"
        identical_to pineapples
    }

    ! here, we cleverly used the first pineapple object to define
    ! the following so we can cut down on typing
    pineapple1 pineapple2
    {}

    pineapple1 pineapple3
    {}

    pineapple1 pineapple4
    {}

>There are four pineapples here.  
>&gt;Get three pineapples
>
>pineapple: Taken.  
>pineapple: Taken.  
>pineapple: Taken.
>
>&gt;Inventory
>
>You are carrying three pineapples.
>
>&gt;Look
>
>There is one pineapple here.

## plural_verbs

| From objlib.h  |
|-------------------------------------------------------------------------------------------------------------------------------------|
| The plural_verbs property should return true if the current verbroutine is in the list of valid actions for the class in question. |

The plural class object's `plural_verbs` property dictates whether the
command should be applied to all of the intended objects or if the
player should be given the response, "You'll have to do that one at a
time."

The default `plural_verb` property looks like this:

        plural_verbs
        {
    #ifclear NO_VERBS
            if verbroutine = &DoLook, &DoGet, &DoDrop, &DoPutin
                return true
    #ifset USE_CHECKHELD
            elseif verbroutine = &DoDrop_CheckHeld, &DoPutin_CheckHeld
                return true
    #endif
            else
    #endif
                return false
        }

As you can see, DoLook, DoGet, DoDrop, and DoPutIn will work with most
plural objects. In your own game, you may want to limit or expand this
functionality.
