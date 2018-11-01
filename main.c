#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void our_ls(DIR * d){
    struct dirent* entry;
    entry = readdir(d);
    int size = 0;
    while (entry) {
        struct stat* b = malloc(sizeof(struct stat));
        if (entry->d_type == DT_DIR)
            printf("directory: %s\n", entry->d_name);
            if(!(strcmp(entry->d_name,"./"))||!(strcmp(entry->d_name,"../"))){
                DIR * sub;
                sub=opendir(entry->d_name);
                our_ls(sub);
                closedir(sub);
            }
        if (entry->d_type == DT_REG) {
            printf("regular: %s\n", entry->d_name);
            stat(entry->d_name, b);
            size += b->st_size;
        }
        entry = readdir(d);
        free(b);
    }
    printf("total size of not directory files: %d\n", size);
}
// main function
int main() {
    DIR* d;
    d = opendir("./");
    our_ls(d);
    closedir(d);
}


