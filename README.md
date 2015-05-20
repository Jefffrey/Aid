#Aid

###Synopsis

This repositories contains data structures and algorithms that I've wrote once and never ever want to write again.
It can be seen as a simple C++ toolbox like any other.

###Dependencies

The library depends on:

 - C++14
 - [Boost.Any](http://www.boost.org/doc/libs/1_58_0/doc/html/any.html)

Additionally, testing depends on:

 - Python
 - [Ninja](https://martine.github.io/ninja/)

###Installation

This is an header-only library, so the installation is as simple as pasting the content of the `include/` folder into some accessible path.

Anyway, by invoking:

```
ninja install
```

the files and folders inside `include/` will be copied in the installation path specified by `--install-path` of `./bootstrap.py` (it defaults to `/usr/local/`). 

I'd recommend inspecting the actual command being run before running it, as the syntax is different between operating systems.

###Testing

To run tests, execute the following commands from the root of this folder:

```
./bootstrap.py
ninja
./tests
```
