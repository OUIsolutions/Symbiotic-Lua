
#include "dependencies/all.h"
#include "lua_code.h"
#include "bin.h"
LuaCEmbedNamespace lua;

int lua_exit = 0;
int argv_size;
char **argv_etries;

#include "callbacks/declaration.h"
#include "callbacks/definition.h"

void add_callbacks(LuaCEmbed *main_obj){
    lua.add_callback(main_obj,"print",lua_print);
    lua.add_callback(main_obj,"input",lua_input);
    lua.add_callback(main_obj,"exit",generate_exit);

}


int main(int argc,char *argv[]){
    argv_size = argc;
    argv_etries = argv;
    lua  = newLuaCEmbedNamespace();
    int size = bins[0].size;
    printf("size %d\n",size);
    LuaCEmbed * main_obj = lua.newLuaEvaluation();
    add_callbacks(main_obj);
    lua.evaluate(main_obj,lua_code);
    if(lua.has_errors(main_obj)){
        char *error = lua.get_error_message(main_obj);
        if(strcmp(error,"") != 0){
            printf("%s\n",error);
        }
        lua.free(main_obj);
        return lua_exit;
    }
    lua.free(main_obj);
    return 0;
}