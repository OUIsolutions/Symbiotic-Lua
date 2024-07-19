

LuaCEmbedResponse * get_bin(LuaCEmbed *args) {
    char *bin_path = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }
    for(int i=0; i < bins_size;i++) {
        Bin *current =&bins[i];
        if(current->path == bin_path && current->content) {
            return  lua.response.send_raw_string((char*)current->content,current->size);
        }
    }
    return  NULL;
}

LuaCEmbedResponse * list_bin_files_recursively(LuaCEmbed *args) {

    LuaCEmbedTable *elements = lua.tables.new_anonymous_table(args);
    int total_included  = 0;

    for(int i=0; i < bins_size;i++) {
        Bin *current =&bins[i];
        lua.tables.append_string(elements,current->path);
        total_included+=1;
    }
    LuaCEmbedTable *multi_response = lua.tables.new_anonymous_table(args);
    lua.tables.append_table(multi_response,elements);
    lua.tables.append_long(multi_response,total_included);
    return lua.response.send_multi_return(multi_response);
}