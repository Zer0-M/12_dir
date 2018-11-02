#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int our_ls(DIR * d){
    if (d) {
        struct dirent* entry;
        entry = readdir(d);
        if (entry) {
            int size = 0;
            printf("STATISTICS FOR DIRECTORY: \n");
            int i = 0;
            while (entry) {
                i ++;
                struct stat* b = malloc(sizeof(struct stat));
                if (entry->d_type == DT_DIR) {
                    printf("directory: %s\n", entry->d_name);
                    /*if (i > 2) {*/
                        /*DIR * sub;*/
                        /*sub = opendir(entry->d_name);*/
                        /*size += our_ls(sub);*/
                        /*closedir(sub);*/
                    /*}*/
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
            return size;
        }
    } else {
        printf("error: %s\n", strerror(errno));
    }

    return 0; 
}
// main function
int main(int argc, char* argv[]) {
    if (argc > 1 ) {
        DIR* d;
        d = opendir(argv[1]);
        our_ls(d);
        closedir(d);
    } else {
        printf("please specify directory:\n");
        char * s;
        scanf("%s",s);
        DIR* nd;
        nd = opendir(s);
        our_ls(nd);
        closedir(nd);
    }
    return 0;
}


