# The structure for the Obsidian IR

Generally, we have a couple main tasks we need to do:

First we need to run lexical analysis on the file. This means remove comments, and break the file down into tokens

Then we need to parse the file into a clear flow, break file by ------------- into seperate sections

Next we need to read the included stuff in the first section,
and import add the extern statements for every included file

After that we read the prototyped functions from the second section,
this is different from the imports. Imports are just the linker paths,
this tells the semantic analysis all the existing functions

Next we need to read all global variables in the third section,
and link them all to a data region (.rodata for constants, .bss for uninitialized, and .data for non constants)

Last we will read every function in the fourth section and generate asm from the functions

And we will add a _start function which takes the return code from main and exits with that (Call an _exit function instead of directly exiting)

Next we need
