# Minimal

This is a very simple game engine for personal projects

---

Execution order:

Main thread:
* Entity management [Parallel]
* Main custom loop update [Sequential]
* Script components [Sequential]
* Physics components [Parallel]

Graphics thread:
* Graphical components [Parallel]
