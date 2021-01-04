---
title: IFID
permalink: /definitions/ifid/
categories: 
  - Definitions
---

"IFID" stands for "interactive fiction identification." Just as the ISBN
system does for books, the IFID system attempts to do for works of
interactive fiction. Game IFID's should abide by the description
provided by the [Treaty of Babel](http://ifwiki.org/index.php/Treaty_of_Babel).

## New Hugo Game IFIDs

Eventually, Hugo might join the ranks of [TADS 3](http://tads.org) and
[Inform 7](http://inform7.com/) in having a game's IFID being an UUID
(universallly unique identifier) determined by the compiler (if one
isn't already declared). In the meantime, Hugo authors should go to the
[IFID Generator](http://tads.org/ifidgen/ifidgen) site and get one from
the web applet.

### Put it in your game

To include that number in your game, declare it as a constant first.

    constant IFID "<your IFID number>"

Then, when you print in the title of your game (or have a &gt;VERSION or
&gt;ABOUT response), have something like:

            Font(BOLD_ON)
            "Game Title"
            Font(BOLD_OFF)
            "Game Blurb"
            print BANNER
            print "IFID: "; IFID

## "Legacy" Hugo Games

If a game was released to the public before one of those long UUID-style
IFIDs was declared in it, there are some rules established to determine
an IFID.

1.  **Use the Babel software suite to determine the IFID.**
    Using the babel program (in Windows, the proper shell command is
    "babel -ifid <game file>") will produce an IFID in the format,
    "HUGO-VV-$$-$$-SN-SN-SN". Let's break it into parts:
    1.  **VV** - Hugo version number (examples: "25" means Hugo 2.5 and
        "31" means Hugo 3.1)
    2.  **$$-$$** - ID string (random value produced by the compiler)
    3.  **SN-SN-SN** - serial number (compilation date in the format
        MM-DD-YY)
2.  **In the rare cases the babel program doesn't work, the IFID for a
    legacy ".hex" Hugo story file is the prefix "HUGO-" followed by its
    MD5 hash, with hexadecimal characters a to f written in upper case,
    A to F.**
    As even Version 1 games like East of Eastwood and Sceptre Quest work
    with the babel program, it's unlikely anyone would ever have to use
    the MD5 method. Still, in that unlikely event, that is what you do.

## Don't Touch that IFID!

Another thing that is often unclear is whether new revisions maintain
the same IFID. Luckily, the Treaty is very clear about this. Updates *do
not* get a new IFID. The only time a new IFID should be issued is if the
game is ported to another language.

<table>
<thead>
<tr class="header">
<th><p>From <em>The Treaty of Babel</em></p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>As with published books, where an ISBN remains the same even if the book is reprinted with corrections, the IFID should be associated with a project, _not_ a specific story file compiled from it. A re-release with bug fixes should have the same IFID.<br />
<br />
If a game is ported from one system to another (other than simply being moved from one version of a system to the next, e.g., by being moved from TADS 2 to TADS 3), the port receives a new IFID. Again, this is analogous to books: a different-format reissue of a book, such as a paperback of what was previously hardback, gets a new ISBN.</p></td>
</tr>
</tbody>
</table>

## "What else should I do?"

If you want to be all saintly about it, go make an
[iFiction](interpreters/ifiction/) file, too.
