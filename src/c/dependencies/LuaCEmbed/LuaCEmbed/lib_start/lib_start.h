
int private_LuaCemb_internal_free(lua_State *L);

LuaCEmbed * newLuaCEmbedLib(lua_State *state,bool public_functions);

int LuaCembed_perform(LuaCEmbed *self);
