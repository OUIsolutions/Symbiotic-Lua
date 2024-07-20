

long  pack_folder(CTextStack *data,const char *folder) {
    DtwStringArray *listage = dtw.list_all_recursively(folder,false);
    long listage_size = listage->size;
    for(int i=0; i < listage->size;i++) {

        stack.text(data,"\n\t{\n");
        char *item = listage->strings[i];
        stack.format(data,"\t\t.path=\"%s\",\n",item);
        char *full_path = dtw.concat_path(folder,item);
        if(dtw.entity_type(full_path) == DTW_FILE_TYPE) {
            long size;
            bool is_binary;
            unsigned char *content = dtw.load_any_content(full_path,&size,&is_binary);
            stack.format(data,"\t\t.exist=true,\n");
            stack.format(data,"\t\t.size=%d,\n",size);
            stack.format(data,"\t\t.is_binary=%s,\n",is_binary? "true":"false");
            stack.format(data,"\t\t.content=\"");
            parse_bin(data,content,size);
            stack.format(data,"\"\n");
        }
        else {
            stack.format(data,"\t\t.exist=false\n");
        }

        free(full_path);
        stack.text(data,"\t},\n");

    }
    dtw.string_array.free(listage);
    return  listage_size;
}


void create_bins(){

    UniversalGarbage *garbage = newUniversalGarbage();
    CTextStack *data = stack.newStack_string(
        "typedef struct {\n"
            "\tconst char *path;\n"
            "\tbool exist;\n"
            "\tlong size;\n"
            "\tbool is_binary;\n"
            "\tconst char *content;\n"
            "}Bin;\n"
            "Bin bins[] = {\n"
    );
    long size = pack_folder(data,"bin/all");
    #ifdef __linux__
       size+= pack_folder(data,"bin/linux");
    #endif

    #ifdef _WIN32
        size+=pack_folder(data,"bin/windows");
    #endif

    stack.text(data,"};\n");
    stack.format(data,"int bins_size = %d;\n",size);

    dtw.write_string_file_content(BIN_COUDE,data->rendered_text);

    stack.free(data);

}