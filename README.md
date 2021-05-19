# **SHORTEST PATH-MAZE** #
Display the shortest path around obstacles in a big environment!
- Made-by: Sean Chung ([seanchung2001](http://www.github.com/seanchung2001))

## Minimum Requirements ##
- OS that allows compilation of C programs
- Compiler

## Tools ##
- GDB debugger
- Valgrind
- Gcc compiler
- Gedit

## Features ##
- Create an environment with multiple obstacles of various sizes, placed randomly within the created environment. This program will:
  - Create and display every vertice for each obstacle.
  - Create edges for every vertice of every obstacle and display the edges.
  - Removes the edges that do not produce the shortest path around an obstacle.
  - Gracefully shuts down the server.

## Compiling Instructions ##
- **(1)**: Download all files included in this repository.
- **(2)**: Open the terminal and _cd_ into the proper directory.
- **(3)**: Type '_make_' into the terminal and wait for the compiler.
- **(4)**: We can now run the executable by doing '_./plannerTester_' in the terminal. The environment with blue obstacles should appear on your screen.
- **(5)**: While the program is running: press enter once to create and display the vertices. Press enter again to create and display all edges. Press enter a third time to remove all edges that do not produce the shortest paths. Finally, press enter one last time to shutdown the environment.
- **(6)**: Type '_make clean_' in the terminal to remove all object files.
