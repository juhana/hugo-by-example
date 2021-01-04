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
<th><p>Property name</p></th>
<th><p>Property<br />
value</p></th>
<th><p>Order<br />
defined</p></th>
<th><p>Used for</p></th>
<th><p>Notes</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><a href="adjective">adjective</a></p></td>
<td><p>04</p></td>
<td><p>05</p></td>
<td><p>adjective(s) for describing object</p></td>
<td><p><strong>pre-defined in compiler</strong>, aliased by <em>adjectives</em></p></td>
</tr>
<tr class="even">
<td><p><a href="adjectives">adjectives</a></p></td>
<td><p>04</p></td>
<td><p>08</p></td>
<td><p>Alias of <strong>adjective</strong></p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="after">after</a></p></td>
<td><p>02</p></td>
<td><p>03</p></td>
<td><p>post-verb routines</p></td>
<td><p><strong>pre-defined in compiler</strong></p></td>
</tr>
<tr class="even">
<td><p><a href="article">article</a></p></td>
<td><p>05</p></td>
<td><p>06</p></td>
<td><p>"a", "an", "some", etc...</p></td>
<td><p><strong>pre-defined in compiler</strong></p></td>
</tr>
<tr class="odd">
<td><p><a href="before">before</a></p></td>
<td><p>01</p></td>
<td><p>02</p></td>
<td><p>per-verb routines</p></td>
<td><p><strong>pre-defined in compiler</strong></p></td>
</tr>
<tr class="even">
<td><p><a href="capacity">capacity</a></p></td>
<td><p>16</p></td>
<td><p>21</p></td>
<td><p>Used for holding/inventory purposes.</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="door_to">door_to</a></p></td>
<td><p>23</p></td>
<td><p>28</p></td>
<td><p>Used for handling 'Enter &lt;object'.</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="exclude_from_all">exclude_from_all</a></p></td>
<td><p>22</p></td>
<td><p>27</p></td>
<td><p>Exclude object from multi-object verbs (ie. Get all)</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="Found_in">found_in</a></p></td>
<td><p>13</p></td>
<td><p>18</p></td>
<td><p>Used to put one object in multiple locations.</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="holding">holding</a></p></td>
<td><p>17</p></td>
<td><p>22</p></td>
<td><p>Used for holding/inventory purposes.</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="In_scope">in_scope</a></p></td>
<td><p>20</p></td>
<td><p>25</p></td>
<td><p>Actor(s) which can access an object</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="Descriptions#initial_desc">initial_desc</a></p></td>
<td><p>11</p></td>
<td><p>16</p></td>
<td><p>Used when an object is not moved (or not visited)</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="list_contents">list_contents</a></p></td>
<td><p>19</p></td>
<td><p>24</p></td>
<td><p>Used for overriding the normal listing routine.</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="Descriptions#long_desc">long_desc</a></p></td>
<td><p>12</p></td>
<td><p>17</p></td>
<td><p>Detailed description of object.</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="Name">name</a></p></td>
<td><p>00</p></td>
<td><p>01</p></td>
<td><p>Property 0: Basic object name</p></td>
<td><p><strong>pre-defined in compiler</strong></p></td>
</tr>
<tr class="even">
<td><p><a href="noun">noun</a></p></td>
<td><p>03</p></td>
<td><p>04</p></td>
<td><p>noun(s) for referring to the object</p></td>
<td><p><strong>pre-defined in compiler</strong>, aliased by <em>nouns</em></p></td>
</tr>
<tr class="odd">
<td><p><a href="nouns">nouns</a></p></td>
<td><p>03</p></td>
<td><p>07</p></td>
<td><p>Alias of <strong>noun</strong></p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="parse_rank">parse_rank</a></p></td>
<td><p>21</p></td>
<td><p>26</p></td>
<td><p>Used for matching similarly named objects.</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="prep">prep</a></p></td>
<td><p>06</p></td>
<td><p>10</p></td>
<td><p>Alias of <strong>preposition</strong></p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="preposition">preposition</a></p></td>
<td><p>06</p></td>
<td><p>09</p></td>
<td><p>"in", "inside", "outside of", etc...</p></td>
<td><p>aliased by <em>prep</em></p></td>
</tr>
<tr class="odd">
<td><p><a href="pronoun">pronoun</a> "it"</p></td>
<td><p>07</p></td>
<td><p>11</p></td>
<td><p>"he", "him", "her", etc...</p></td>
<td><p><strong>returns 'it' by default</strong>, aliased by <em>pronouns</em></p></td>
</tr>
<tr class="even">
<td><p><a href="pronouns">pronouns</a></p></td>
<td><p>07</p></td>
<td><p>12</p></td>
<td><p>Aliased to <strong>pronoun</strong></p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="reach">reach</a></p></td>
<td><p>18</p></td>
<td><p>23</p></td>
<td><p>Used for limiting accessible objects</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="React_after">react_after</a></p></td>
<td><p>09</p></td>
<td><p>14</p></td>
<td><p>Allows an object to react when it's not directly involved.</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="React_before">react_before</a></p></td>
<td><p>08</p></td>
<td><p>13</p></td>
<td><p>Allows an object to react when it's not directly involved.</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="Descriptions#short_desc">short_desc</a></p></td>
<td><p>10</p></td>
<td><p>15</p></td>
<td><p>Basic 'X is here' description</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="size">size</a> 10</p></td>
<td><p>15</p></td>
<td><p>20</p></td>
<td><p>Used for holding/inventory purposes.</p></td>
<td><p><em>Defaults to 10</em></p></td>
</tr>
<tr class="even">
<td><p><a href="Type">type</a></p></td>
<td><p>14</p></td>
<td><p>19</p></td>
<td><p>Used to identify the type of object.</p></td>
<td></td>
</tr>
</tbody>
</table>

#### Directional Properties

[Directions](classes/direction/) out of rooms are also properties.
They can hold the [object](globals/object/) that is north/south/etc
from the current room. When used as is, these properties are only used
by the [room](basics/rooms/) object, but they are often
[aliased](basics/alias/) to other properties when used with other
objects. The last two in the list really aren't used for directions, but
are still only used in rooms.

<table style="width:91%;">
<colgroup>
<col style="width: 6%" />
<col style="width: 32%" />
<col style="width: 32%" />
<col style="width: 6%" />
<col style="width: 13%" />
</colgroup>
<thead>
<tr class="header">
<th><p>Property name</p></th>
<th><p>Property<br />
value</p></th>
<th><p>Order<br />
defined</p></th>
<th><p>Direction</p></th>
<th><p>Notes</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><a href="n_to">n_to</a></p></td>
<td><p>24</p></td>
<td><p>29</p></td>
<td><p>North</p></td>
<td><p>aliased by <em>statusline_height</em></p></td>
</tr>
<tr class="even">
<td><p><a href="ne_to">ne_to</a></p></td>
<td><p>25</p></td>
<td><p>30</p></td>
<td><p>North east</p></td>
<td><p>aliased by <em>key_object</em></p></td>
</tr>
<tr class="odd">
<td><p><a href="e_to">e_to</a></p></td>
<td><p>26</p></td>
<td><p>31</p></td>
<td><p>East</p></td>
<td><p>aliased by <em>when_open</em></p></td>
</tr>
<tr class="even">
<td><p><a href="se_to">se_to</a></p></td>
<td><p>27</p></td>
<td><p>32</p></td>
<td><p>South east</p></td>
<td><p>aliased by <em>when_closed</em></p></td>
</tr>
<tr class="odd">
<td><p><a href="s_to">s_to</a></p></td>
<td><p>28</p></td>
<td><p>33</p></td>
<td><p>South</p></td>
<td><p>aliased by <em>ignore_response</em></p></td>
</tr>
<tr class="even">
<td><p><a href="sw_to">sw_to</a></p></td>
<td><p>29</p></td>
<td><p>34</p></td>
<td><p>South west</p></td>
<td><p>aliased by <em>order_response</em></p></td>
</tr>
<tr class="odd">
<td><p><a href="w_to">w_to</a></p></td>
<td><p>30</p></td>
<td><p>35</p></td>
<td><p>West</p></td>
<td><p>aliased by <em>contains_desc</em></p></td>
</tr>
<tr class="even">
<td><p><a href="nw_to">nw_to</a></p></td>
<td><p>31</p></td>
<td><p>36</p></td>
<td><p>North west</p></td>
<td><p>aliased by <em>inv_desc</em></p></td>
</tr>
<tr class="odd">
<td><p><a href="u_to">u_to</a></p></td>
<td><p>32</p></td>
<td><p>37</p></td>
<td><p>Up</p></td>
<td><p>aliased by <em>desc_detail</em></p></td>
</tr>
<tr class="even">
<td><p><a href="d_to">d_to</a></p></td>
<td><p>33</p></td>
<td><p>38</p></td>
<td><p>Down</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="in_to">in_to</a></p></td>
<td><p>34</p></td>
<td><p>39</p></td>
<td><p>In</p></td>
<td></td>
</tr>
<tr class="even">
<td><p><a href="out_to">out_to</a></p></td>
<td><p>35</p></td>
<td><p>40</p></td>
<td><p>Out</p></td>
<td></td>
</tr>
<tr class="odd">
<td><p><a href="Cant_go">cant_go</a></p></td>
<td><p>36</p></td>
<td><p>41</p></td>
<td><p>Message</p></td>
<td><p>"You can't go that way"</p></td>
</tr>
</tbody>
</table>

#### Other Room Properties

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
<th><p>Property name</p></th>
<th><p>Property<br />
value</p></th>
<th><p>Order<br />
defined</p></th>
<th><p>Used for</p></th>
<th><p>Notes</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><a href="extra_scenery">extra_scenery</a></p></td>
<td><p>37</p></td>
<td><p>43</p></td>
<td><p>Used in room objects to list words/objects in the description that are not important to the game.</p></td>
<td><p>|+</p></td>
</tr>
</tbody>
</table>

#### Non-Room Properties

Finally, these properties are never used in rooms, so they are aliased
to previously defined properties (to save space).

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
<th><p>Property name</p></th>
<th><p>Property<br />
value</p></th>
<th><p>Order<br />
defined</p></th>
<th><p>Alias of</p></th>
<th><p>Used for</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><a href="key_object">key_object</a></p></td>
<td><p>25</p></td>
<td><p>45</p></td>
<td><p>ne_to</p></td>
<td><p>Used to denote what key unlocks the object.</p></td>
</tr>
<tr class="even">
<td><p><a href="when_open">when_open</a></p></td>
<td><p>26</p></td>
<td><p>46</p></td>
<td><p>e_to</p></td>
<td><p>Used to hold an openable object's description when it is open.</p></td>
</tr>
<tr class="odd">
<td><p><a href="when_closed">when_closed</a></p></td>
<td><p>27</p></td>
<td><p>47</p></td>
<td><p>se_to</p></td>
<td><p>Used to hold an openable object's description when it is closed.</p></td>
</tr>
<tr class="even">
<td><p><a href="ignore_response">ignore_response</a></p></td>
<td><p>28</p></td>
<td><p>48</p></td>
<td><p>s_to</p></td>
<td><p>Used to hold an unfriendly <a href="Characters">character</a>'s response.</p></td>
</tr>
<tr class="odd">
<td><p><a href="Order_response">order_response</a></p></td>
<td><p>29</p></td>
<td><p>49</p></td>
<td><p>sw_to</p></td>
<td><p>Used for giving orders to characters.</p></td>
</tr>
<tr class="even">
<td><p><a href="contains_desc">contains_desc</a></p></td>
<td><p>30</p></td>
<td><p>50</p></td>
<td><p>w_to</p></td>
<td><p>Used to override the standard "X Contains" descriptions.</p></td>
</tr>
<tr class="odd">
<td><p><a href="inv_desc">inv_desc</a></p></td>
<td><p>31</p></td>
<td><p>51</p></td>
<td><p>nw_to</p></td>
<td><p>Used for inventory listing only.</p></td>
</tr>
<tr class="even">
<td><p><a href="desc_detail">desc_detail</a></p></td>
<td><p>32</p></td>
<td><p>52</p></td>
<td><p>u_to</p></td>
<td><p>Used for parenthetical details in inventory listings</p></td>
</tr>
<tr class="odd">
<td><p><a href="misc">misc</a></p></td>
<td><p>39</p></td>
<td><p>53</p></td>
<td><p><em>not aliased</em></p></td>
<td><p>For miscellaneous use. (determined by the author)</p></td>
</tr>
</tbody>
</table>

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

| Usage                          |
|--------------------------------|
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

| Usage                  |
|------------------------|
| &lt;object&gt;.#&lt;property&gt; |

The number of elements reserved can be found with:

| Usage                                     |
|-------------------------------------------|
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
