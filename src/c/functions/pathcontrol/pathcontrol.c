#include "../unique.definition_requirements.h"

long count_separations(const char * path){
    if(path == NULL){
        return 0;
    }
    long size = strlen(path);
    if(size == 1){
    return 0;
    }
    int count= 0;
    for(int i = 0; i <  size -1;i++){
         if(path[i] == '/') {
             count+=1;
         }
    }
    return  count;
}

bool is_any_child(const char * possible_father,const char *possible_child){
    if(possible_father == NULL || possible_child ==NULL){
        return false;
    }

    if(strncmp(possible_father, possible_child, strlen(possible_father)) == 0){

        return true;
    }

    return false;

}

bool is_first_child(const char * possible_father,const char *possible_child) {

    bool is_child =is_any_child(possible_father,possible_child);
    if(!is_child) {
        return false;
    }

    if(count_separations(possible_father) == count_separations(possible_child)-1) {
        return  true;
    }
    return false;
}
