
#include "dependencies/all.h"
#include "lua_code.h"
LuaCEmbedNamespace lua;
#include "callbacks/declaration.h"

#include "callbacks/definition.h"

void add_callbacks(LuaCEmbed *main_obj){
    lua.add_callback(main_obj,"print",custom_print);
}


int main(){
    lua  = newLuaCEmbedNamespace();
    LuaCEmbed * main_obj = lua.newLuaEvaluation();
    add_callbacks(main_obj);
    printf("%s\n",lua_code);
    // lua.evaluate(main_obj,lua_code);
    if(lua.has_errors(main_obj)){
        char *error = lua.get_error_message(main_obj);
        printf("%s\n",error);
        lua.free(main_obj);
        return 1;
    }
    lua.free(main_obj);
    return 0;
}