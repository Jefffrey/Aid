#Aid

###Synopsis

This repositories contains data structures and algorithms that I've wrote once and never ever want to write again.
It can be seen as a simple C++ toolbox like any other.

###Installation

In order to install this library you just have to copy the content of the `include` folder and paste it in some accessible path, and then include any of the header files provided.

There's a quick and dirty installation rule in the makefile, activable via:

```
make install
```

But I would highly recommend that you take a look at what it does, before running it.

###Testing

To run tests, execute the following commands from the root of this folder:

```
make suite
make test
```

In order to remake all binary files, you can use either of the followings:

```
make remake
make clean && make suite
```
