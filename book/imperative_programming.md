# Imperative Programming
Programming is the principles procedure of telling a computer what it is supposed to do and there are various programming styles that can be used to program computers. 
However, the most widely used and most basic style of thinking of computers is the paradigm of imperative programming.

Imperative programming matches very well the nature of computers being rather dumb and simple machines. In imperative programming, the programmer takes the role of an imperator and provides instructions to the computer in a very precise ordered form. These instructions come from a comparably small set of instructions which the computer must support.

## A Robot Model of Intrinsic Instructions
A very basic model of a computer can be imagined as a small robot that has two functions: turn right by an angle of $\pi/2$ and go one step into the direction currently looking at. When building such a machine, one immediately also designs a programming language which has two operations (we call them intrinsics, because they are the operations really implemented in hardware). Let us give names to them: `move` for moving one step, and `turn` for turning left by $\pi/2$.

Now an imperative program is very much like a shell script: from the language that we have defined, we can create a text file with one intrinsic instruction per line (this form of machine code is typically called assembler).

The program
```
move
turn
turn 
move
```
would thus be interpreted as an imperative program like: first move into the direction you are facing, then turn to the left, then turn again to the left, then move again.

So far, we have introduced a few concepts that should be highlighted:
- intrinsic instructions are those steps that a physical computing machine can perform immediately
- Each intrinsic instruction gets   a name
- A series of intrinsic instructions can be written into a file which is an imperative program and interpreted as a sequential instruction

Let us reflect a bit more on the situation of such a robot. In a certain sense, the previous program does define very precisely what the robot is supposed to do, but neither in which state (location and orientation) it has been in the beginning nor in which state it is afterwards. In fact, each operation is well-defined local to the robot (we know how the wheels are to be moving), but not well-defined with respect to the robot in the world. Therefore, we would need to give or fix initial conditions. 

For a real imperative program, these intiial conditions are the state that is held in the operating system about the program, for example, the current working directory (CWD).

## Procedures
A very typic additional definition in an imperative programming setting is the notion of a procedure. A procedure is an imperative program (e.g., a sequence of instructions) such that this sequence can be referred to as a new operation in the programming language. These are the so-called non-intrinsic operations.

For our robot, the following program
```
turn 
turn
turn
```` 
means to turn left for three times. This, of course mimicks the result of turning right. In many programming languages, there is a way to make this a new instruction of the language called a procedure.
```
proc turnright:
  turn 
  turn 
  turn
```
Our minimal computer (the robot) with its tiny set of intrinsic instructions (move and rotate) can now be programmed with a third instruction `turnright`

## Ports and Functions
As a next step in the co-evolution of a computer and a programming language, one might want to be able to react on real-world input, that is, something coming from outside the robot. For a robot, we could imagine a sensor that just tells us whether the place we would move to is occupied or not.

That is, we extend our hardware with something we will call a port as it brings external information into the system. And we will extend the programming language with an intrinsic function to model this port.

A function is a procedure in the sense that it can be run and that it can be built together from other instructions and functions, but it **returns a value.** For the case of the port letting us experience the next location being occupied, this return value can have two states: occupied or not occupied. Due to the huge impact of George Bool on the behavior of such values (this British mathematician passed away already in 1864 long before digital computers have been realized), any two-valued information in a computer is called a Boolean value or bool for short.

Concretely speaking, a function would now look like `is_empty` and when this is `called` it would turn into the current value associated with the hardware port.

Now, with having ports, we can observe aspects of the surroundings (information exterior to the system itself) and in order to react to them, two aspects are introduced in imperative programming:
- control structures and
- expressions

## Control Structures

As we are still looking for a minimal programming language, we could imagine that our robot is supposed not to crash with the surroudings, so maybe we just need to be able to make instructions like move **conditional** to the value of the port.

This control structure is often nown as if .. then .. else ..
More concretely, we enable the following snippet of source code:
```
if is_empty then move else turn
```
This program would now always first check the condition of the if (run the intrinsic function) and if move is possible, it would move and if not, it would turn in the hope that we can move afterwards.

To complete this exposition of minimal control structures, there is another common way to use boolean information in imperative programs: to control the repeated execution of something. To this end, we introduce a loop called while:
```
while is_empty do move done
```
This means: as long as it is possible to move, continue moving. Note that by introducing a Boolean function, we would typically also introduce the two Boolean values as constants for our programs. They are typically referred to as true and false, hence, we can also write
```
while true do 
  while is_empty do
    move
  done
  turn
done
```
## Scopes
Another concept we silently introduced in the previous example is the idea of scopes. It is so common that within a conditional branch or a loop multiple instructions need to be placed that we try to avoid to introduce a function for it. Because if we had to, we would make things into functions that are used only once. As an alternative, a **scope** is introduced which is a sequence of instructions that is taking the role of a single instruction like the loop body (what to do as long as a condition is true) or the two branches of a conditional information (what to do when the value is true, what to do otherwise).

Scopes have varying notations: sometimes with braces (C++, Java)
```
{
move
turn
}
```
sometimes with indentation (Python)
```
while true:
  move 
  turn
```
sometimes with barrier words (Bash)
```
while true do
move
turn
done
```
sometimes with round brackets (DOS/Windows BAT files)
```
(
)
```
But they all serve the same purpose of quickly and locally (on the screen in the right location) bundling together instructions.

# Memory
Now, this very small robot can be extended further to interact with a physical world. As you may have noticed, the robot is currently limited to a grid of points it can reach as we only implement movement by $\pi/2$. Assume now, we give the robot some small things it can deposit into the grid cell he is currently in, and then also sense, and maybe even pick up. That is, we extend the robot device with three functions represented by three intrinsics:
- a function deposit to put something into the current cell. Let us assume that it fails if the cell is already filled with such an item.
- a function pick to clean the current cell 
- a function has_item to check if the current cell is filled with an item.


With these three intrinsics, we can write a lot of algorithms and it can be fun. The interesting aspect is that the 2D world provides us with the ability to have a concept like a variable.
## Variables
A variable is an area of memory to hold information together with an interpretation associated with this information. For the 2D robot case, a variable is often such a thing as a stack of items like in the following drawing. The identity of the variable being the column in the grid while the value is the height of the stack.

In all imperative programming languages, the idea is similar: there is an axis of varying identity (think like rows in a table) and each variable typically has a name (just a string) in order to use it. The second axis in programming languages describes together the amount of space that is needed and the interpretation of the space. For example, you can have a 32 bit integer number (reserving 32 bits = 4 bytes of memory) assigned an identity like `i` or the same amount of memory for a 32 bit floating point number `f`.

In high-level languages, it is not uncommon that variables are accessible by name during runtime, in lower level languages, the names are only available during compilation and will be removed (for efficiency) while compiling the source code to a executable.

## An example robot program sketch

Assume we have our robot being on the lowest block of a tower of blocks each with a marker. Let us assume, we want to interpret the height of this tower as an integer number, say `h` like height. Let us assume further, we want to compute the value `2h`. How would we proceed?

### Algorithm Design
It is pretty clear and intuitive, how the robot can solve the problem: For each marked block, it creates two marked blocks somewhere else. More concretely, let me lay down a proposal as follows:

- The robot starts on the lowest block of a tower
- The robot walks upwards to the highest block
- The robot picks up the marker (the tower has reduced in height by one)
- The robot goes down as long as markers are there (to the ground floor, so to say)
- The robot goes a step to the right
- THe robot walks up the tower as long as possible going to the first non-marked place
- The robot deposits a marker
- The robot goes up
- The robot deposits a marker
- The robot goes up
- The robot deposits a marker
- The robot goes down as long as possible
- The robot goes left (and is back in the state we want)

This needs to be repeated until we have taken the whole first tower.

Now, with this overview of the algorithm, we continue with an implementation strategy: there are quite a few things that are semantically bounded in the sense that we can precisely and simply describe the state before and after a part of our program. We could for example implement a procedure `climb` and use it twice: once to climb up the left tower and once to climb up the second tower. Which tower to climb will just be based on the current location of the robot.

Our program skeleton grows slowly. In order to have a more narrative programming style, we introduce another idea of programming, namely to put human readable text comments into
the source code to illustrate some aspects and further to use such comments to specify the expectations of implementations. Note that some modern programming languages like C++ allow us to have such specifications during compilation in one or another way, but this is a rather new feature and has not yet been voted into many standards. But the topic to keep an eye on is known as [contracts](https://en.wikipedia.org/wiki/Design_by_contract).
```
# function climb
# precondition: the robot looks up
# invariant: the robot keep the same X coordinate
# postcondition: has_marker == false && has_marker @ below would be true
def climb:
  # needs to be written
```
Only with this contract information, it is possible to write
a semantically correct climb function, especially the precondition is requried: otherwise we would never know where we are going and the robot would need a compass or other means to find its orientation.

Let us complete this procedure at least:
```
# function climb
# precondition: the robot looks up
# invariant: the robot keep the same X coordinate
# postcondition: has_marker == false && has_marker @ below would be true
def climb:
  while has_marker:
    climb
```
Hence, we can start writing a part of our program completely assuming we are in the start location (bottom of left tower):
```
climb
turn
turn 
move
pickup 
climb # this now climbs down
```

Now we realize that our first intuition that there is a climb function is not a very good and compact one as we also have to climb down. So let us update the precodnition
```
# function climb
# precondition: the robot looks up or down
```` 

We can then extend the program by going to the side
```
...
turn 
move 
turn
```
Now, we are one block to the side looking up again.
We can then deposit markers twice:
```
climb  # go up
deposit # marker one
climb  # go up
deposit # marker two
turn    #look down
turn
climb   # walk down
turn   # look back
turn
turn 
move
turn    # up in origin
```
This completes our imperative formulation with a function 
climb that we have used multiple times making it much easier to use. And we have seen that even our simple robot can do computations (doubling an integer number represented as the height of a stack of markers).

In fact, similar robots are used to teach programming. For example, Richard Pattis has introduced Karel the robot with a very similar set of features as our imaginary robot and Nikolaus Wirth has popularized this in Germany as [Niki the robot](https://de.wikipedia.org/wiki/Niki_%E2%80%93_der_Roboter)

Actually, I found that Niki is still available in a historic Windows version and it runs at least on my Windows 11. So please go ahead and have a look at Niki the robot. 
