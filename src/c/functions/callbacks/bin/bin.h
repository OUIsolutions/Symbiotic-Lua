#include "../unique.declaration_requirements.h"

Bin * find_bin(const char *name) ;


LuaCEmbedResponse * get_bin(LuaCEmbedTable *self,LuaCEmbed *args);

LuaCEmbedResponse * is_bin_file(LuaCEmbedTable *self,LuaCEmbed *args);

LuaCEmbedResponse * is_bin_dir(LuaCEmbedTable *self,LuaCEmbed *args);

LuaCEmbedResponse * bin_exist(LuaCEmbedTable *self,LuaCEmbed *args);

LuaCEmbedResponse * bin_exist(LuaCEmbedTable *self,LuaCEmbed *args);

LuaCEmbedResponse * list_bin_files(LuaCEmbedTable *self,LuaCEmbed *args);

LuaCEmbedResponse * list_bin_files_recursively(LuaCEmbedTable *self,LuaCEmbed *args);

LuaCEmbedResponse * list_bin_dirs(LuaCEmbedTable *self,LuaCEmbed *args);

LuaCEmbedResponse * list_bin_dirs_recursively(LuaCEmbedTable *self,LuaCEmbed *args);


LuaCEmbedResponse * list_bin_all(LuaCEmbedTable *self,LuaCEmbed *args);

LuaCEmbedResponse * list_bin_all_recursively(LuaCEmbedTable *self,LuaCEmbed *args);
