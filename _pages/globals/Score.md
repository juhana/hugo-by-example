---
title: score
permalink: /globals/score/
categories: 
  - Global Variables
---

*See also: [Scoring](/tips/scoring/)*

`score` is a [global variable](/basics/global/) used to store the
points awarded so far in a score-tracking game; A non-score-tracking
game that has [STATUSTYPE](/globals/statustype/) set to 0 will ignore
`score` altogether. Games with `STATUSTYPE` set to 1 will show the
current score and turn [counter](/globals/counter/) in the status line.

### adding to the score

Since you want to add points to the total, score-increasing code will
look like this:

    score = score + 10 ! where we want to add 10 points
