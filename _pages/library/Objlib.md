---
title: objlib.h
permalink: /library/objlib.h/
categories: 
  - Hugo Library
---

The Hugo Object Library defines some of the base
[classes](basics/object_classes/) used in many games. It is
automatically included by the [hugolib.h](library/hugolib.h/) file
(The main file of the Hugo Standard Library)

<table>
<thead>
<tr class="header">
<th><p>Object</p></th>
<th><p>Description</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><a href="Rooms"><code>room</code></a></p></td>
<td><p>Defines the basic room object, gives it light and makes it static so that it cannot be picked up and taken.</p></td>
</tr>
<tr class="even">
<td><p><code>character</code></p></td>
<td><p>Basis for a male NPC (Non-Player Character)</p></td>
</tr>
<tr class="odd">
<td><p><code>female_character</code></p></td>
<td><p>Basis for a female NPC.</p></td>
</tr>
<tr class="even">
<td><p><code>player_class</code></p></td>
<td><p>Defines the Player Character (the character that is controlled by the gamer).</p></td>
</tr>
<tr class="odd">
<td><p><a href="Doors"><code>door</code></a></p></td>
<td><p>Defines a door which also handles knowing which side the player character is on when he/she goes through.</p></td>
</tr>
<tr class="even">
<td><p><a href="direction"><code>direction</code></a></p></td>
<td><p>The base class used to hold the compass directions used in the game. It also handles the direction objects (n_to, e_to, etc...)</p></td>
</tr>
<tr class="odd">
<td><p><a href="scenery"><code>scenery</code></a></p></td>
<td><p>Defines a scenery object, it does not get listed in the room contents because the library assumes that it was mentioned in the room description.</p></td>
</tr>
<tr class="even">
<td><p><a href="Components"><code>component</code></a></p></td>
<td><p>A component class is an object that is <code>part_of</code> another object. (such as adding a lever to a machine)</p></td>
</tr>
<tr class="odd">
<td><p><a href="vehicle"><code>vehicle</code></a></p></td>
<td><p>The basic vehicle class defines ridable objects such as cars, trucks, airplanes, horses, etc...<br />
<strong>NOTE:</strong> If you are going to use this object, be sure to set the <strong>USE_VEHICLES</strong> flag.</p></td>
</tr>
<tr class="even">
<td><p><a href="Plurals"><code>plural_class</code></a></p></td>
<td><p>Defines a plural name for objects so the player can give commands such as <code>Take the toys.</code> and have the game understand that the ball, airplane and rubber duckie are all to be taken together (because they are all part of the toy class that the author defines.<br />
<strong>NOTE:</strong> If you are going to use this object, be sure to set the <strong>USE_PLURALS</strong> flag.</p></td>
</tr>
<tr class="odd">
<td><p><a href="Plurals#identical_class"><code>identical_class</code></a></p></td>
<td><p>Similar to the <code>plural_class</code> but for items that are considered identical (such as coins, or sporks, or whatever)<br />
<strong>NOTE:</strong> If you are going to use this object, be sure to set the <strong>USE_PLURALS</strong> flag.</p></td>
</tr>
<tr class="even">
<td><p><code>attachable</code></p></td>
<td><p>Defines an object that can be attached to other objects.<br />
<strong>NOTE:</strong> If you are going to use this object, be sure to set the <strong>USE_ATTACHABLES</strong> flag.</p></td>
</tr>
</tbody>
</table>

