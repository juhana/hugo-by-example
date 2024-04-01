---
title: objlib.h
permalink: /library/objlib.h/
classes: wide
categories: 
  - Hugo Library
---

The Hugo Object Library defines some of the base
[classes](basics/object_classes/) used in many games. It is
automatically included by the [hugolib.h](library/hugolib.h/) file
(The main file of the Hugo Standard Library.)

| Object | Description | Notes |
| --- | --- | --- |
| [room](basics/rooms) | Defines the basic room object, gives it light and makes it static so that it cannot be picked up and taken. |
| [character](classes/character-classes) | Basis for a male NPC (Non-Player Character) |
| [female_character](classes/character-classes) | Basis for a female NPC. |
| player_class | Defines the Player Character (the character that is controlled by the gamer). |
| [door](classes/doors) | Defines a door which also handles knowing which side the player character is on when he/she goes through. |
| [direction](classes/direction) | The base class used to hold the compass directions used in the game. It also handles the direction objects (n_to, e_to, etc...) |
| [scenery](basics/scenery) | Defines a scenery object, it does not get listed in the room contents because the library assumes that it was mentioned in the room description. |
| [component](classes/components) | A component class is an object that is part_of another object. (such as adding a lever to a machine) |
| [vehicle](classes/vehicle) | The basic vehicle class defines ridable objects such as cars, trucks, airplanes, horses, etc... | If you are going to use this object, be sure to set the USE_VEHICLES flag. |
| [plural_class](basics/plurals) | Defines a plural name for objects so the player can give commands such as Take the toys. and have the game understand that the ball, airplane and rubber duckie are all to be taken together (because they are all part of the toy class that the author defines. | If you are going to use this object, be sure to set the USE_PLURALS flag. |
| identical_class | Similar to the plural_class but for items that are considered identical (such as coins, or sporks, or whatever) | If you are going to use this object, be sure to set the USE_PLURALS flag. |
| attachable | Defines an object that can be attached to other objects. | If you are going to use this object, be sure to set the USE_ATTACHABLES flag. |

objlib.h also defines the [last_library_object](library/Last_library_object)
