

void pack_folder(CTextStack *data,const char *folder) {
    DtwStringArray *listage = dtw.list_all_recursively(folder,false);

    for(int i=0; i < listage->size;i++) {
        stack.text(data,"\n\t{\n");
        char *item = listage->strings[i];
        stack.format(data,"\t\t.path=\"%s\"",item);
        char *full_path = dtw.concat_path("bin/all",item);
        if(dtw.entity_type(full_path) == DTW_FILE_TYPE) {
            stack.format(data,",\n");
            long size;
            bool is_binary;
            unsigned char *content = dtw.load_any_content(full_path,&size,&is_binary);
            stack.format(data,"\t\t.size=%d,\n",size);
            stack.format(data,"\t\t.is_binary=%s,\n",is_binary? "true":"false");
            stack.format(data,"\t\t.content=\"");
            parse_bin(data,content,size);
            stack.format(data,"\"\n");

        }
        else {
            stack.format(data,"\n");
        }
        free(full_path);
        stack.text(data,"\t},\n");
    }
    dtw.string_array.free(listage);
}


void create_bins(){

    UniversalGarbage *garbage = newUniversalGarbage();
    CTextStack *data = stack.newStack_string(
        "typedef struct {\n"
            "\tconst char *path;\n"
            "\tlong size;\n"
            "\tbool is_binary;\n"
            "\tunsigned char *content;\n"
            "}Bin;\n"
            "Bin bins[] = {\n"
    );

    pack_folder(data,"bin/all");
    #ifdef __linux__
        pack_folder(data,"bin/linux");
    #endif

    #ifdef _WIN32
        pack_folder(data,"bin/windows");
    #endif

    stack.text(data,"};\n");
    dtw.write_string_file_content("c/bin.h",data->rendered_text);

    stack.free(data);

}