

LuaCEmbedResponse *lua_replace_string(LuaCEmbed *args) {
    char *str =lua.args.get_str(args,0);
    char *item_to_be_replaced = lua.args.get_str(args,1);
    char *item_to_insert = lua.args.get_str(args,2);
    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }
    CTextStack *str_stack = stack_module.newStack_string(str);

}