
## Symbiotic-Lua

Symbiotic-Lua  is a template for hybrid development between C and Lua, being very useful for hybrid teams, or to facilitate the creation of programs. It generates a native Windows/Linux binary, without the need to install Lua, so it can be used to build desktop apps, or run in environments that cannot install Lua.
## Install
For instalation  just download the [src folder](https://github.com/OUIsolutions/Symbiotic-Lua/archive/refs/tags/v0.05.zip)  into your project

than type to get into the folder (these its important):
```shel
cd src
```
after it, you can compile and run the build

```shel
gcc build/main.c -o build.o  &&./build.o
```

these will produce the file final.o, which its the final embed binary
you can run it with

```shel
./final.o
```


## How it works:
 The system works through 2 stages, the first being build, in the build stage, after compiled,
build.c will create a string called **lua_code** in the  globals/lua_code.c file,containing all
the contents of the lua/ folder (main.lua its required).
In step two, the main folder C imports this string and generates an evaluation on it.
you also, can put binaryis in the **/bin** folder ,based on the os , or all, they will be inserted
into globals/bin.c
This way, the entire lua virtual machine is embedded in the binary, without the need for external dependencies.

## what These template its not ?
- a replacer for lua
- a full build tool
- a "lua runtimer"
