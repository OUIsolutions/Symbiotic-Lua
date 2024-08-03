
#include "../unique.definition_requirements.h"

Bin * find_bin(const char *name) {


    for(int i=0; i < bins_size;i++) {
        Bin *current =&bins[i];
        if(strcmp(current->path,name) == 0) {
            return  current;
        }
    }
    return NULL;
}


LuaCEmbedResponse * get_bin(LuaCEmbedTable *self,LuaCEmbed *args) {
    char *bin_path = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }
    Bin *founded =  find_bin(bin_path);

    if(founded) {
        if(founded->content) {
            return  lua.response.send_raw_string((char*)founded->content,founded->size);
        }
    }
    return  NULL;
}
LuaCEmbedResponse * is_bin_file(LuaCEmbedTable *self,LuaCEmbed *args) {
    char *bin_path = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }
    Bin *founded =  find_bin(bin_path);

    if(founded) {
        if(founded->content) {

            return  lua.response.send_bool(true);
        }
    }

    return  lua.response.send_bool(false);
}

LuaCEmbedResponse * is_bin_dir(LuaCEmbedTable *self,LuaCEmbed *args) {
    char *bin_path = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }
    Bin *founded =  find_bin(bin_path);
    if(founded) {
        if(founded->content ==NULL) {
            return  lua.response.send_bool(true);
        }

    }

    return  lua.response.send_bool(false);
}
LuaCEmbedResponse * bin_exist(LuaCEmbedTable *self,LuaCEmbed *args) {
    char *bin_path = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }
    Bin *founded =  find_bin(bin_path);
    if(founded) {
        return  lua.response.send_bool(true);
    }
    return  lua.response.send_bool(false);
}

LuaCEmbedResponse * list_bin_files(LuaCEmbedTable *self,LuaCEmbed *args) {

    char *start_path  = NULL;
    if(lua.args.get_type(args,0) != lua.types.NILL) {

        start_path = lua.args.get_str(args,0);

    }

    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }

    LuaCEmbedTable *elements = lua.tables.new_anonymous_table(args);
    int total_included  = 0;

    for(int i=0; i < bins_size;i++) {
        Bin *current =&bins[i];
        if(current->content == NULL) {
            continue;
        }
        if(start_path == NULL) {
            if(count_separations(current->path) > 0) {
                continue;
            }
            lua.tables.append_string(elements,current->path);
            total_included+=1;
            continue;
        }
        if(is_first_child(start_path,current->path)) {
            const char *path = current->path;

            lua.tables.append_string(elements,path);
            total_included+=1;
        }
    }

    LuaCEmbedTable *multi_response = lua.tables.new_anonymous_table(args);
    lua.tables.append_table(multi_response,elements);
    lua.tables.append_long(multi_response,total_included);
    return lua.response.send_multi_return(multi_response);
}

LuaCEmbedResponse * list_bin_files_recursively(LuaCEmbedTable *self,LuaCEmbed *args) {

     char *start_path  = NULL;
    if(lua.args.get_type(args,0) != lua.types.NILL) {

        start_path = lua.args.get_str(args,0);

    }

    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }

    LuaCEmbedTable *elements = lua.tables.new_anonymous_table(args);
    int total_included  = 0;

    for(int i=0; i < bins_size;i++) {
        Bin *current =&bins[i];
        if(current->content == NULL) {
            continue;
        }
        if(start_path == NULL) {
            lua.tables.append_string(elements,current->path);
            total_included+=1;
            continue;
        }
        if(is_any_child(start_path,current->path)) {
            const char *path = current->path;

            lua.tables.append_string(elements,path);
            total_included+=1;
        }
    }

    LuaCEmbedTable *multi_response = lua.tables.new_anonymous_table(args);
    lua.tables.append_table(multi_response,elements);
    lua.tables.append_long(multi_response,total_included);
    return lua.response.send_multi_return(multi_response);
}

LuaCEmbedResponse * list_bin_dirs(LuaCEmbedTable *self,LuaCEmbed *args) {

    char *start_path  = NULL;
    if(lua.args.get_type(args,0) != lua.types.NILL) {

        start_path = lua.args.get_str(args,0);

    }

    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }

    LuaCEmbedTable *elements = lua.tables.new_anonymous_table(args);
    int total_included  = 0;

    for(int i=0; i < bins_size;i++) {
        Bin *current =&bins[i];
        if(current->content != NULL) {
            continue;
        }
        if(start_path == NULL) {
            if(count_separations(current->path) > 0) {
                continue;
            }
            lua.tables.append_string(elements,current->path);
            total_included+=1;
            continue;
        }
        if(is_first_child(start_path,current->path)) {
            const char *path = current->path;

            lua.tables.append_string(elements,path);
            total_included+=1;
        }
    }

    LuaCEmbedTable *multi_response = lua.tables.new_anonymous_table(args);
    lua.tables.append_table(multi_response,elements);
    lua.tables.append_long(multi_response,total_included);
    return lua.response.send_multi_return(multi_response);

}

LuaCEmbedResponse * list_bin_dirs_recursively(LuaCEmbedTable *self,LuaCEmbed *args) {

    char *start_path  = NULL;
    if(lua.args.get_type(args,0) != lua.types.NILL) {

        start_path = lua.args.get_str(args,0);

    }

    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }

    LuaCEmbedTable *elements = lua.tables.new_anonymous_table(args);
    int total_included  = 0;

    for(int i=0; i < bins_size;i++) {
        Bin *current =&bins[i];
        if(current->content != NULL) {
            continue;
        }
        if(start_path == NULL) {
            lua.tables.append_string(elements,current->path);
            total_included+=1;
            continue;
        }
        if(is_any_child(start_path,current->path)) {
            const char *path = current->path;

            lua.tables.append_string(elements,path);
            total_included+=1;
        }
    }

    LuaCEmbedTable *multi_response = lua.tables.new_anonymous_table(args);
    lua.tables.append_table(multi_response,elements);
    lua.tables.append_long(multi_response,total_included);
    return lua.response.send_multi_return(multi_response);
}


LuaCEmbedResponse * list_bin_all(LuaCEmbedTable *self,LuaCEmbed *args) {
    char *start_path  = NULL;
    if(lua.args.get_type(args,0) != lua.types.NILL) {

        start_path = lua.args.get_str(args,0);

    }

    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }

    LuaCEmbedTable *elements = lua.tables.new_anonymous_table(args);
    int total_included  = 0;

    for(int i=0; i < bins_size;i++) {
        Bin *current =&bins[i];

        if(start_path == NULL) {
            if(count_separations(current->path) > 0) {
                continue;
            }
            lua.tables.append_string(elements,current->path);
            total_included+=1;
            continue;
        }
        if(is_first_child(start_path,current->path)) {
            const char *path = current->path;

            lua.tables.append_string(elements,path);
            total_included+=1;
        }
    }

    LuaCEmbedTable *multi_response = lua.tables.new_anonymous_table(args);
    lua.tables.append_table(multi_response,elements);
    lua.tables.append_long(multi_response,total_included);
    return lua.response.send_multi_return(multi_response);
}

LuaCEmbedResponse * list_bin_all_recursively(LuaCEmbedTable *self,LuaCEmbed *args) {
    char *start_path  = NULL;
    if(lua.args.get_type(args,0) != lua.types.NILL) {

        start_path = lua.args.get_str(args,0);

    }

    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }

    LuaCEmbedTable *elements = lua.tables.new_anonymous_table(args);
    int total_included  = 0;

    for(int i=0; i < bins_size;i++) {
        Bin *current =&bins[i];

        if(start_path == NULL) {
            lua.tables.append_string(elements,current->path);
            total_included+=1;
            continue;
        }
        if(is_any_child(start_path,current->path)) {
            const char *path = current->path;

            lua.tables.append_string(elements,path);
            total_included+=1;
        }
    }

    LuaCEmbedTable *multi_response = lua.tables.new_anonymous_table(args);
    lua.tables.append_table(multi_response,elements);
    lua.tables.append_long(multi_response,total_included);
    return lua.response.send_multi_return(multi_response);
}
