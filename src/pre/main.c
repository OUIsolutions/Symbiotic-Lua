

#include "dependencies/all.h"
const char * LUA_FOLDER = "lua";
const char *OUTPUT = "c/lua_code.h";
const char *LUA_VAR_NAME = "lua_code";
DtwNamespace dtw;
CTextStackModule stack;

void parse_code(CTextStack *final,const char *content){
    int content_size = strlen(content);
    for(int i = 0; i < content_size; i++)
    {
        char buffer[10] = {0};
        sprintf(buffer,"\\x%x",content[i]);
        stack.format(final,"%s",buffer);
    }

}

int main(){
    dtw = newDtwNamespace();
    UniversalGarbage *garbage = newUniversalGarbage();
    stack = newCTextStackModule();
    DtwStringArray * listage = dtw.list_files_recursively(LUA_FOLDER,DTW_CONCAT_PATH);
    UniversalGarbage_add(garbage,dtw.string_array.free,listage);

    CTextStack * final = stack.newStack_string_format("const char *%s= \"",LUA_VAR_NAME);
    UniversalGarbage_add(garbage,stack.free,final);
    char *content = NULL;
    UniversalGarbage_add_simple(garbage,content);

    for(int i = 0; i < listage->size;i++){
        char *path = listage->strings[i];

        content = dtw.load_string_file_content(path);
        UniversalGarbage_resset(garbage,content);

        if(content == NULL){
            continue;
        }
        parse_code(final,content);
    }
    parse_code(final,"\nmain()");
    stack.format(final,"\";");
    
    dtw.write_string_file_content(OUTPUT,final->rendered_text);
    UniversalGarbage_free(garbage);
    return 0;
}
