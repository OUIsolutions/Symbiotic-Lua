
## Symbiotic-Lua

Symbiotic-Lua  is a template for hybrid development between C and Lua, being very useful for hybrid teams, or to facilitate the creation of programs. It generates a native Windows/Linux binary, without the need to install Lua, so it can be used to build desktop apps, or run in environments that cannot install Lua.
## Install 
For instalation  just run the following comands




## How it works:
 The system works through 2 stages, the first being build, in the build stage, after compiled, build.c will create a string called **lua_code** in the lua_code.h file. In step two, the main folder C imports this string and generates an evaluation on it.
This way, the entire lua virtual machine is embedded in the binary, without the need for external dependencies.

