# University of Leeds 2023-24
# COMP 5823M Assignment 1 Flight Simulator
# Satvik Tiwari
# 201791342

================================================

LINUX :

To compile on the University Linux machines, you will need to do the following:

[userid@machine A1_handout]$ module add legacy-eng
[userid@machine A1_handout]$ module add qt/5.15.2
[userid@machine A1_handout]$ qmake -project QT+=opengl LIBS+=-lGLU
[userid@machine A1_handout]$ qmake
[userid@machine A1_handout]$ make

To execute the programe:

[userid@machine A1_handout]$ ./A1_handout 

========================================================

A : Pitch up
S : Pitch Down

W : Yaw left
D : Yaw right

Q : Roll left
R : Roll right

Q : Quit

0-9 : Set speed from 0 to 9 m/s depending on which key use press from '0' to '9'
+ : Increse speed by 1 m/s
- : Decrease speed by 1 m/s

==================================================================

