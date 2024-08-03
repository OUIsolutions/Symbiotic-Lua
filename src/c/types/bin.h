#include <stdbool.h>
#ifndef BIN_H
#define BIN_H

typedef struct {
    const char *path;
    long size;
    bool is_binary;
    const char *content;
}Bin;
#endif
