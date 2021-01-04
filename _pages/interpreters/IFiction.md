---
title: iFiction
permalink: /interpreters/ifiction/
categories: 
  - Interpreters
---

"iFiction" files are metadata tags used by multi-interpreters like Zoom
for the Mac, helping to create an iTunes-like frontend to playing IF
games. While not officially supported by Hugo (there isn't a way to
automatically generate them like TADS or Inform can), one can manually
write .ifiction files, which should then be distributed with your game
(the name of the .ifiction file should be the same as the game file).

### .ifiction example

Here is an example .ifiction file for the game "Party Arty- Man of La
Mancha":

        <?xml version="1.0" encoding="UTF-8"?>
        <ifindex version="1.0" ns="http://babel.ifarchive.org/protocol/iFiction/">
            <story>
            <identification>
                <ifid>DEEA7FA5-0AF8-45D2-8741-D1CD69E02E9E</ifid>
                <format>hugo</format>
            </identification>
        <bibliographic>
            <title>Party Arty, Man of La Munchies</title>
            <author>Roody Yogurt</author>
            <language>en-US</language>
            <headline>An Interactive Example</headline>
            <firstpublished>2011</firstpublished>
            <genre>Comedy</genre>
            <group>Hugo</group>
            <forgiveness>Merciful</forgiveness>
            <description>A story told at the crossroads of levity and destiny!</description>
        </bibliographic>
        </story>
        </ifindex>

*(This would be in a file called **party.ifiction**, distributed with
the game)*