---
title: Properties
permalink: /properties/
categories: 
  - Properties
  - Basics
  - Declarations
---

Properties are similar to attributes, but considerably more powerful.
They are more than simple yes/no flags, they are sets of valid data
associated with an object. The values may represent almost anything,
including objects, number, dictionary addresses, and sections of
executable code. While every object carries every attribute, not every
object may have every property; it must be specified in the object
definition at the time the object is created. 

## Predefined properties

#### Basic Properties

Here is a list of properties predefined by the compiler or defined in
the [standard library](library/), in alphabetical
order. The "order defined" field shows the order properties are defined
by the compiler or in [hugolib.h](library/hugolib.h/). With the
exception of the predefined properties (that have values that are set by
the compiler), the property values are determined by the order defined,
unless [aliased](basics/alias/) to another property. Note that you
can sort the table on any column by clicking on the symbol in that
column:

| Property name | Property value | Order defined | Used for | Notes |
| --- | --- | --- | --- | --- |
| [adjective](properties/adjective) | 04 | 05 | adjective(s) for describing object | pre-defined in compiler, aliased by adjectives |
| adjectives | 04 | 08 | Alias of [adjective](properties/adjective) |  |
| [after](properties/after) | 02 | 03 | post-verb routines | pre-defined in compiler |
| [article](properties/article) | 05 | 06 | "a", "an", "some", etc... | pre-defined in compiler |
| [before](properties/before) | 01 | 02 | per-verb routines | pre-defined in compiler |
| [capacity](properties/capacity) | 16 | 21 | Used for holding/inventory purposes. |  |
| [door_to](properties/door_to) | 23 | 28 | Used for handling 'Enter object'. |  |
| [exclude_from_all](properties/exclude_from_all) | 22 | 27 | Exclude object from multi-object verbs (ie. Get all) |  |
| [found_in](scope/found_in) | 13 | 18 | Used to put one object in multiple locations. |  |
| [holding](properties/holding) | 17 | 22 | Used for holding/inventory purposes. |  |
| [in_scope](properties/in_scope) | 20 | 25 | Actor(s) which can access an object |  |
| initial_desc | 11 | 16 | Used when an object is not moved (or not visited) |  |
| [list_contents](properties/list_contents) | 19 | 24 | Used for overriding the normal listing routine. |  |
| long_desc | 12 | 17 | Detailed description of object. |  |
| [name](properties/name) | 00 | 01 | Property 0: Basic object name | pre-defined in compiler |
| [noun](properties/noun) | 03 | 04 | noun(s) for referring to the object | pre-defined in compiler, aliased by nouns |
| nouns | 03 | 07 | Alias of [noun](properties/noun) |  |
| [parse_rank](properties/parse_rank) | 21 | 26 | Used for matching similarly named objects. |  |
| prep | 06 | 10 | Alias of [preposition](properties/preposition) |  |
| [preposition](properties/preposition) | 06 | 09 | "in", "inside", "outside of", etc... | aliased by prep |
| [pronoun](properties/pronoun) "it" | 07 | 11 | "he", "him", "her", etc... | returns 'it' by default, aliased by pronouns |
| pronouns | 07 | 12 | Aliased to [pronoun](properties/pronoun) |  |
| [reach](properties/reach) | 18 | 23 | Used for limiting accessible objects |  |
| [react_after](properties/react_after) | 09 | 14 | Allows an object to react when it's not directly involved. |  |
| [react_before](properties/react_before) | 08 | 13 | Allows an object to react when it's not directly involved. |  |
| short_desc | 10 | 15 | Basic 'X is here' description |  |
| [size](properties/size) 10 | 15 | 20 | Used for holding/inventory purposes. | Defaults to 10 |
| [type](properties/type) | 14 | 19 | Used to identify the type of object. |  |


#### Directional Properties

[Directions](classes/direction/) out of rooms are also properties.
They can hold the [object](globals/object/) that is north/south/etc
from the current room. When used as is, these properties are only used
by the [room](basics/rooms/) object, but they are often
[aliased](basics/alias/) to other properties when used with other
objects. The last two in the list really aren't used for directions, but
are still only used in rooms.

| Property name | Property value | Order defined | Direction | Notes |
| --- | --- | --- | --- | --- |
| [n_to](directions/n_to) | 24 | 29 | North | aliased by statusline_height |
| [ne_to](directions/ne_to) | 25 | 30 | North east | aliased by [key_object](properties/key_object) |
| [e_to](directions/e_to) | 26 | 31 | East | aliased by when_open |
| [se_to](directions/se_to) | 27 | 32 | South east | aliased by when_closed |
| [s_to](directions/s_to) | 28 | 33 | South | aliased by [ignore_response](properties/ignore_response) |
| [sw_to](directions/sw_to) | 29 | 34 | South west | aliased by [order_response](properties/order_response) |
| [w_to](directions/w_to) | 30 | 35 | West | aliased by [contains_desc](properties/contains_desc) |
| [nw_to](directions/nw_to) | 31 | 36 | North west | aliased by [inv_desc](properties/inv_desc) |
| [u_to](directions/u_to) | 32 | 37 | Up | aliased by [desc_detail](properties/desc_detail) |
| [d_to](directions/d_to) | 33 | 38 | Down |  |
| [in_to](directions/in_to) | 34 | 39 | In |  |
| [out_to](directions/out_to) | 35 | 40 | Out |  |
| [cant_go](properties/cant_go) | 36 | 41 | Message | "You can't go that way" |


#### Other Room Properties

| Property name | Property value | Order defined | Used for | Notes |
| --- | --- | --- | --- | --- |
| [extra_scenery](properties/extra_scenery) | 37 | 43 | Used in room objects to list words/objects in the description that are not important to the game. | |


#### Non-Room Properties

Finally, these properties are never used in rooms, so they are aliased
to previously defined properties (to save space).

| Property name | Property value | Order defined | Alias of | Used for |
| --- | --- | --- | --- | --- |
| [key_object](properties/key_object) | 25 | 45 | [ne_to](directions/ne_to) | Used to denote what key unlocks the object. |
| when_open | 26 | 46 | [e_to](directions/e_to) | Used to hold an openable object's description when it is open. |
| when_closed | 27 | 47 | [se_to](directions/se_to) | Used to hold an openable object's description when it is closed. |
| [ignore_response](properties/ignore_response) | 28 | 48 | [s_to](directions/s_to) | Used to hold an unfriendly character's response. |
| order_response | 29 | 49 | [sw_to](directions/sw_to) | Used for giving orders to characters. |
| [contains_desc](properties/contains_desc) | 30 | 50 | [w_to](directions/w_to) | Used to override the standard "X Contains" descriptions. |
| [inv_desc](properties/inv_desc) | 31 | 51 | [nw_to](directions/nw_to) | Used for inventory listing only. |
| [desc_detail](properties/desc_detail) | 32 | 52 | [u_to](directions/u_to) | Used for parenthetical details in inventory listings |
| [misc](properties/misc) | 39 | 53 | not aliased | For miscellaneous use. (determined by the author) |

Using this table, by subtracting the predefined and library defined
properties, you have a total of about 200 available properties that you
can define for any object, character or scenery. Note that unlike
attributes, you can increase the number of allowed properties from the
default of 254 by using the statement

    $MAXPROPERTIES=600

Or whatever number you want if you want a different number than 600.

## Defining your own properties

While the Hugo standard library offers a large number of predefined
properties, there will be many times that you need to define your own.

| Usage                 |
|-----------------------|
| property **&lt;property name&gt;** |

Defining a property is very similar to an [alias](basics/alias/):

    property <property name> <default value>

The default value can be either a [constant](basics/constants/) or a
[dictionary word](definitions/dictionary-words/). If an object does not
have either a default value assigned, or defined in the object and you
try find that property of an object, it will return 0 (or "" or the
"nothing" object depending on context).

## Interacting with properties

| Usage                 |
|-----------------------|
| &lt;object&gt;.&lt;property&gt; |

To read the value of a property (or to execute its code, in some cases),
use the form:

| Usage                 |
|-----------------------|
| &lt;object&gt;.#&lt;property&gt; |

The number of elements reserved can be found with:

| Usage                 |
|-----------------------|
| &lt;object&gt;.&lt;property&gt; #&lt;element number&gt; |

And a single element can be found via:

    object diamond "diamond"
    {
        noun "diamond"
        adjective "shiny" "expensive"
    }

In the above code, `diamond.adjective #2` would equal "expensive".

## Examples

Let's take a look at a couple of examples:

    ! [code]
    ! Defining new properties

    ! First, a simple property, used to hold the 'xyzzyness' of an object

    property xyzzyness 0

    ! second, a properties that holds five values, how much it's affected
    ! different classes of magic (earth, fire, water, air and spirit)

    property magic_effect 0 0 0 0 0 0 ! we use 6 zeros as place holders.

    ! now to put them into action

    object suitcase "suitcase"
    {
        nouns "suitcase", "case"
        adjectives "brown", "sampson"
        article "the"

        long_desc
        {
           "Your trusty traveling companion, the Sampson suitcase has seen many
           adventures with you. It's brown exterior is beaten, but not broken
           through."
        }

        xyzzyness 10
        magic_effect 1 10 5 0 4
    }

    ! [some more code

    routine CheckXyzzyness(obj)
    {
        select obj.xyzzyness
        {
            case 1,2,3
            {
               print CArt(obj); " "; obj.name; " is only slightly xyzzy."
            }
            case 4,5,6
            {
                print CArt(obj); " "; obj.name; " is pretty xyzzy."
            }
            case 7,8,9
            {
                print CArt(obj); " "; obj.name; " is very xyzzy."
            }
        }
    }

    ! routine to return how effective a particular magic is

    routine MagicEffective(obj, magic_class)
    {
        local x
        select magic_class
        {
            case 1: return obj.magic_effect        ! earth magic
            case 2: return obj.magic_effect #2     ! fire magic
            case 3: return obj.magic_effect #3     ! water magic
            case 4: return obj.magic_effect #4     ! air magic
            case 5: return obj.magic_effect #5     ! spirit magic
        }
    }

## Other uses for properties

I think it's important to remind people that properties don't only need
to be used for keeping track of quantities (even when you set them to
numerical values). They are very useful for keeping track of states
(especially when used with [constants](basics/constants/)). For
example, you could have a "swimming" property, returning either 1 (true)
or 0 (false), making it act like an attribute. If you have dice, you can
use a property to determine which side is face-up. As the manual points
out (and you'll see all the time), properties can even have routines in
them. There are many possibilities.

## The difference between object.&lt;property&gt; and &amp;object.&lt;property&gt;

The & is used as a "reference" to the property in question. It is used
to test whether the property exists. It returns a value of true if the
property exists, and false if it does not. It can be used to determine
whether to do something based on whether or not the property is present
in the object.

When reading Hugo code, it's not always apparent what these two things
do. In the first example (the code without the ampersand), assuming that
object.property exists, `if object.property` executes `object.property`
then goes on to execute the next bit of code. `if &object.property`, on
the other hand, just executes the next bit of code. Let's show it with
code:

    object dog "dog"
    {
        noun "dog"
        in STARTLOCATION
        bark {
             "Bark."
             }
    }

    routine DoAmp
    {
        if &dog.bark
        "Amp!"
    }

    routine DoNoAmp
    {
        if dog.bark
        "No Amp!"
    }

This gives us:

>&gt;amp  
>Amp!
>
>&gt;noamp  
>Bark.  
>No Amp!

And that's that!
