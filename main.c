#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

// main function
int main() {
    DIR* d;
    d = opendir("./");
    struct dirent* entry;
    entry = readdir(d);
    int size = 0;
    while (entry) {
        struct stat* b = malloc(sizeof(struct stat));
        if (entry->d_type == DT_DIR)
            printf("directory: %s\n", entry->d_name);
        if (entry->d_type == DT_REG) {
            printf("regular: %s\n", entry->d_name);
            stat(entry->d_name, b);
            size += b->st_size;
        }
        entry = readdir(d);
        free(b);
    }
    printf("total size of not directory files: %d\n", size);
    closedir(d);
}


