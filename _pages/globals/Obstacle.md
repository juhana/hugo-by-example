---
title: obstacle
permalink: /globals/obstacle/
categories: 
  - Global Variables
---

If the `obstacle` 
[global variable](/basics/global/) is set to *anything*,
any command to leave the room results in "&lt;`obstacle` object&gt;
stops you from leaving."

| Usage                          |
|--------------------------------|
| `obstacle` = &lt;obstacle object&gt; |
| `obstacle` = 0                 |

This is used in games like Spur or Guilty Bastards when characters speak
to the player over several turns (like, mini-cut scenes). Of course, it
could be used for other things, too, but those games show how it
*especially* works for character "infodumps" in games with
[ASK/TELL](/verb-routines/doask/) conversation systems (it is somewhat
believable that a character might answer side questions mid-oration).
The point is, you don't want the player leaving the room and ruining
everything.

## What it looks like

Here is a sample transcript of the above concept in action:

>Ballroom Floor  
>The ballroom is full of mingling party guests. Your only escape is the
large set of doors to the south.  
>
>A sharply dressed man approaches you. Without missing a beat, he
introduces himself. "Good evening, I'm Charles Edwards. I'm an emergency
room surgeon. Have you ever been in an emergency room on Saturday
night?"
>
>&gt;GO SOUTH  
>Charles stops you from going anywhere.
>
>Charles continues. "Now that I have this conversation started, I will
let it follow its natural course."
>
>&gt;

## Default response

[Messages](/basics/messages/)'s `obstacle` response code is such:

        case &DoGo
        {
            select num
            case 1:  print CThe(obstacle); " stop"; \
                MatchSubject(obstacle); " you from going anywhere."

If you want a different message, you'll need to
[change](/basics/messages/) it.
