


void create_bins(){

    UniversalGarbage *garbage = newUniversalGarbage();
    CTextStack *data = stack.newStack_string(
        "typedef struct {\n"
            "\tconst char *path;\n"
            "\tlong size;\n"
            "\tbool is_binary;\n"
            "\tunsigned char *content;\n"
            "}Bin;\n"
            "\tBin bins[] = {\n"
    );
    UniversalGarbage_add(garbage,stack.free,data);

    DtwStringArray *all = dtw.list_all_recursively("bin/all",false);
    UniversalGarbage_add(garbage,dtw.string_array.free,all);

    for(int i=0; i < all->size;i++) {
        stack.text(data,"\n\t{\n");
        char *item = all->strings[i];
        stack.format(data,"\t.path=\"%s\"\n",item);
        char *full_path = dtw.concat_path("bin/all",item);
        if(dtw.entity_type(full_path) == DTW_FILE_TYPE) {
            long size;
            bool is_binary;
            unsigned char *content = dtw.load_any_content(full_path,&size,&is_binary);
            stack.format(data,".size=%d,\n",size);
            stack.format(data,".is_binary=%s,\n",is_binary? "true":"false");
            stack.format(data,"\t.content=\"");
            parse_bin(data,content,size);
            stack.format(data,"\"\n");

        }
        free(full_path);
        stack.text(data,"};\n");
    }
    stack.text(data,"}\n");
    dtw.write_string_file_content("c/bin.h",data->rendered_text);

    UniversalGarbage_free(garbage);

}