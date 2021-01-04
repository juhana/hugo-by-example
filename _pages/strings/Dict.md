---
title: Dict
permalink: /strings/dict/
categories: 
  - Strings
---

For the most part, the dictionary table is set in stone after compiling.
Sometimes, we want to reserve some space for new dictionary entries like
when there are objects that can be named in-game (like in Beyond Zork).
To add new dictionary words to the game, one needs to use the `dict`
function.

#### Games That Use This

- The `DoName` routine in The Vault of Hugo uses `dict` to allow
players to name an "unnamed object."
- Future Boy! uses it to write dictionary entries to be used with the
[addcontext](/guts/addcontext/) function (which only accepts
dictionary entries).

<table>
<thead>
<tr class="header">
<th><p>calling form</p></th>
<th><p>WHAT IT ALL MEANS</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><code>x = dict(</code><array><code>, </code><maxlen><code>)</code><br />
<code>or</code><br />
<code>x = dict(parse$, </code><maxlen><code>)</code></p></td>
<td><p><array> or <code>&lt;parse$&gt;</code> is the string being written to the dictionary table<br />
<maxlen> is the maximum number of digits we'll take from the string<br />
<code>x</code> will be set to the address of the new dictionary entry</p></td>
</tr>
</tbody>
</table>
