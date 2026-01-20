# GameOfLife
Programming GameOfLife, virtualisation of cellular life in time where life follows deterministic rules and each generation is the product of the relation between past generation * rules;


Compilation: cc life.c -o life

Run as: echo 'sdxddssaaww' | ./a.out 5 5 O | cat - e
Where stdin string is the first generation:
Imagine a pen starting in the top left corner of the board.
Each command is one of these characters:
	w a s d -> move the pen up, left, bottom, and right.
	x 		-> lift lower the pen in order to start or stop drawing.

  args are: width height iterations
