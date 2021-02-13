---
title: FindObject
permalink: /scope/findobject/
categories: 
  - Scope
  - Object Tree
  - Routines
---

| calling form | description |
| --- | --- |
| `FindObject(object,location)` | Returns true (1) if the specified object is available in the specified location, or false (0) if it is not. Returns 2 if the object is visible but not physically accessible. The location argument is 0 during object disambiguation performed by the engine. Also calls: [`ObjectisKnown`](routines/objectisknown), [`ExcludeFromAll`](routines/exludefromall) |
