---
title: Attributes
permalink: /attributes/
categories: 
  - Attributes
  - Basics
---

You can think of an attribute as something that an object has, or
doesn't have. It represents a simple YES/NO definition. Is the object
open, can the object be locked, etc... 

### Predefined attributes

Unlike some properties, there are no predefined attributes created by
the compiler, although there are some which are predefined by the
[standard libraries](/library/). You can define a
maximum of 128 attributes, including those defined by the standard
libraries. This is one of the [Hugo Compiler](/basics/compiler/)'s 
*hard limits* (it can't be
changed). Using the [alias](/basics/alias/) command, you can get
around this limitation. There are several attributes defined in the Hugo
standard library (in the order shown under *order defined*) in the
following table.

<table style="width:98%;">
<colgroup>
<col style="width: 6%" />
<col style="width: 32%" />
<col style="width: 32%" />
<col style="width: 13%" />
<col style="width: 13%" />
</colgroup>
<thead>
<tr class="header">
<th><p>Attribute name</p></th>
<th><p>Attribute<br />
value</p></th>
<th><p>Order<br />
defined</p></th>
<th><p>Used for</p></th>
<th><p>Notes</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><a href="active">active</a></p></td>
<td><p>14</p></td>
<td><p>17</p></td>
<td><p>Set if an object is active</p></td>
<td><p>(alias for <strong>switchedon</strong>)</p></td>
</tr>
<tr class="even">
<td><p><a href="already_listed">already_listed</a></p></td>
<td><p>23</p></td>
<td><p>28</p></td>
<td><p><em>For library use.</em></p></td>
<td><p>(alias for <strong>workflag</strong>)</p></td>
</tr>
<tr class="odd">
<td><p><a href="clothing">clothing</a></p></td>
<td><p>15</p></td>
<td><p>18</p></td>
<td><p>Set if an object can be worn</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="container">container</a></p></td>
<td><p>18</p></td>
<td><p>22</p></td>
<td><p>Set if an object can contain things (have something <em>put in</em> them).</p></td>
<td><p>Conflicts with <strong>platform</strong> (see below)</p></td>
</tr>
<tr class="odd">
<td><p><a href="enterable">enterable</a></p></td>
<td><p>17</p></td>
<td><p>21</p></td>
<td><p>Set an object may be entered</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="female">female</a></p></td>
<td><p>05</p></td>
<td><p>07</p></td>
<td><p>Set if a character is female (default is male)</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="hidden">hidden</a></p></td>
<td><p>20</p></td>
<td><p>24</p></td>
<td><p>Set if an object is not listed</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="known">known</a></p></td>
<td><p>00</p></td>
<td><p>01</p></td>
<td><p>Set when an object is known by the player</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="light">light</a></p></td>
<td><p>11</p></td>
<td><p>13</p></td>
<td><p>Set if an object is/provides light</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="living">living</a></p></td>
<td><p>04</p></td>
<td><p>06</p></td>
<td><p>Set if an object is a character</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="lockable">lockable</a></p></td>
<td><p>08</p></td>
<td><p>10</p></td>
<td><p>Set if an object can be locked</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="locked">locked</a></p></td>
<td><p>09</p></td>
<td><p>11</p></td>
<td><p>Set if an object is locked</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="mobile">mobile</a></p></td>
<td><p>16</p></td>
<td><p>20</p></td>
<td><p>Set if an object may be moved around.</p></td>
<td><p>(alias for <strong>worn</strong>)</p></td>
</tr>
<tr class="even">
<td><p><a href="moved">moved</a></p></td>
<td><p>01</p></td>
<td><p>02</p></td>
<td><p>Set when an object has been moved</p></td>
<td><p>aliased by <em>visited</em></p></td>
</tr>
<tr class="odd">
<td><p><a href="open">open</a></p></td>
<td><p>07</p></td>
<td><p>09</p></td>
<td><p>Set if an object is open</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="openable">openable</a></p></td>
<td><p>06</p></td>
<td><p>08</p></td>
<td><p>Set if an object can be opened</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="platform">platform</a></p></td>
<td><p>19</p></td>
<td><p>23</p></td>
<td><p>Set if an object can contain things (have something <em>put on</em> them).</p></td>
<td><p>Conflicts with <strong>container</strong> (see below)</p></td>
</tr>
<tr class="even">
<td><p><a href="plural">plural</a></p></td>
<td><p>03</p></td>
<td><p>05</p></td>
<td><p>Set for plural objects</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="quiet">quiet</a></p></td>
<td><p>21</p></td>
<td><p>25</p></td>
<td><p>Set if a container/platform is quiet (contents not initially listed).</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="readable">readable</a></p></td>
<td><p>12</p></td>
<td><p>14</p></td>
<td><p>Set if an object can be read</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="special">special</a></p></td>
<td><p>24</p></td>
<td><p>29</p></td>
<td><p>For miscellaneous use.</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="static">static</a></p></td>
<td><p>02</p></td>
<td><p>04</p></td>
<td><p>Set for an object that cannot be taken</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="switchable">switchable</a></p></td>
<td><p>13</p></td>
<td><p>15</p></td>
<td><p>Set if an object can be switched on/off</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="switchedon">switchedon</a></p></td>
<td><p>14</p></td>
<td><p>16</p></td>
<td><p>Set if an object is switched on</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="transparent">transparent</a></p></td>
<td><p>22</p></td>
<td><p>26</p></td>
<td><p>Set if an object is not opaque. (It can be seen through)</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="unfriendly">unfriendly</a></p></td>
<td><p>10</p></td>
<td><p>12</p></td>
<td><p>Set if a character is an opponent</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="visited">visited</a></p></td>
<td><p>01</p></td>
<td><p>03</p></td>
<td><p>Set when a room has been visited</p></td>
<td><p>(alias for <strong>moved</strong>)</p></td>
</tr>
<tr class="even">
<td><p><a href="workflag">workflag</a></p></td>
<td><p>23</p></td>
<td><p>27</p></td>
<td><p><em>For library use.</em></p></td>
<td><p>aliased by <em>already_listed</em></p></td>
</tr>
<tr class="odd">
<td><p><a href="worn">worn</a></p></td>
<td><p>16</p></td>
<td><p>19</p></td>
<td><p>Set if an object is being worn.</p></td>
<td><p>aliased by <em>mobile</em></p></td>
</tr>
</tbody>
</table>

After the attributes mentioned in the above table, you have a total of
104 available (non-aliased) attributes left that you can define for your
game.

### New attribute definition

To define an attribute, use the attribute command `attribute `<name>.
For example, if an object in your game can be magic or not, you may
create an attribute like so:


    attribute magic

    object lantern "Magic lantern"
    {
        nouns "lantern", "light"
        adjectives "magic", "small"

        long_desc
        {
            "A small, magic lantern is sitting here."
        }

        is magic, light
    }

### Importance of proper object attribution

Several verb [grammar tokens](/basics/grammar/) rely on attributes
being set correctly. This means that even when you want your game to
deny a specific command, the proper attribute needs to be set for it to
work correctly. Imagine, if you will, a television set with the
following `before` code:

    Object TV "television"
    {
        is static   !  Can't be moved
        before {
               object DoSwitchOff
                      {
                      "You'd turn off the tv, but you're pretty sure \"Wheel of Misfortune\" is on next."
                      return true
                      }
               }
    }

Without the `switchable` attribute, &gt;TURN OFF TV will get the
response "You can't do that with the television." and all of your
players will be left to wonder when- *if ever*- "Wheel of Misfortune"
will air. Don't do that to them. In this example, the second line of the
definition should be changed to:

            is static, switchable   !  Can't be moved, can be turned on

### Aliases


*Main Article: [alias](/basics/alias/)*

If you need to define a lot of attributes and might run out of them,
what you can do is define some attribute as an alias of another
attribute. If there are two conditions that are mutually exclusive, or
that they don't apply to different classes of objects, then you can
alias an existing attribute to something else. For example, let's say
you have an attribute called 'broken' to indicate the player broke
something. This is only going to be used by an object that can be
broken, so if you have a scenery object - like a radioactive boulder -
that can't be broken but has to glow, you could do the following:

    attribute broken
    attribute glow alias broken

Then the attributes 'broken' and 'glow' are the same attribute, and you
can use them interchangeably.
