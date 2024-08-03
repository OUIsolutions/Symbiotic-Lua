
#include "definition.c"

void add_callbacks(LuaCEmbed *main_obj){

    LuaCEmbedTable *bin = lua.globals.new_table(main_obj,"bin");
    lua.tables.set_method(bin,"getbin",get_bin);
    lua.tables.set_method(bin,"isfile",is_bin_file);
    lua.tables.set_method(bin,"isdir",is_bin_dir);
    lua.tables.set_method(bin,"exist",bin_exist);
    lua.tables.set_method(bin,"list_files_recursively",list_bin_files_recursively);
    lua.tables.set_method(bin,"list_files",list_bin_files);
    lua.tables.set_method(bin,"list_dirs_recursively",list_bin_dirs_recursively);
    lua.tables.set_method(bin,"list_dirs",list_bin_dirs);
    lua.tables.set_method(bin,"list_all_recursively",list_bin_all_recursively);
    lua.tables.set_method(bin,"list_all",list_bin_all);
}


int main(int argc,char *argv[]){
    argv_size = argc;
    argv_etries = argv;
    lua  = newLuaCEmbedNamespace();
    stack_module = newCTextStackModule();
    LuaCEmbed * main_obj = lua.newLuaEvaluation();

    lua.load_lib_from_c(main_obj,load_luaDoTheWorld,"dtw");

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
