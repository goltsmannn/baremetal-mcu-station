#ifndef FAT16_H
#define FAT16_H

#include <stdint.h>

#define MAX_CLUSTERS 4096


typedef struct Metadata_s {
    uint32_t file_size;
};

typedef struct DirectoryTable_s {
    char file_name[8];
    char file_extension[3];
    uint16_t start_index;
    struct Metadata_s metadata;
};

extern struct DirectoryTable_s DirTable;

uint16_t FAT[MAX_CLUSTERS];

void create_file(char file_name[8], char file_extension[3], uint16_t start_index, uint32_t file_size, struct DirectoryTable_s* dir_entry);
#endif // FAT16_H