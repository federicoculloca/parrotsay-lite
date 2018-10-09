# parrotsay-lite
Like parrotsay, but in C

Feed it text either via the command line or via the standard input and see a nice party parrot repeating it to you :)

This is basically a naive re-implementation of cowsay, in C, with a colorful parrot instead of the cow.

Inspired by [parrotsay](https://github.com/matheuss/parrotsay).

## Building.

This has been tested only with gcc 6.3.0 and TinyCC 0.9.27 in Debian Stretch.

To build just do

    gcc parrotsay.c -o parrotsay
    
