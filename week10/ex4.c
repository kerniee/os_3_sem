#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>

struct file {
    unsigned long ino;
    unsigned long nlink;
    char name[256];
};

int count_files(const char *path) {
    DIR *dirp = opendir(path);
    int count = 0;
    while (readdir(dirp) != NULL) {
        count++;
    }
    (void) closedir(dirp);
    return count;
}

int main() {
    DIR *dirp;
    struct dirent *dp;
    const char *dirpath = "tmp";
    char filepath[256];
    struct stat *buf = malloc(sizeof(struct stat));
    struct file *files = malloc(count_files(dirpath) * sizeof(struct file));

    // read files
    dirp = opendir(dirpath);
    if (dirp == NULL) { return (1); }
    int file_count = 0;
    while ((dp = readdir(dirp)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            memcpy(filepath, dirpath, sizeof(filepath));
            strcat(filepath, "/");
            strcat(filepath, dp->d_name);
            stat(filepath, buf);

            strcpy(files[file_count].name, dp->d_name);
            files[file_count].ino = buf->st_ino;
            files[file_count].nlink = buf->st_nlink;
            file_count++;
        }
    }
    (void) closedir(dirp);

    // check
    printf("File ---- Hard Links\n");
    for (int i = 0; i < file_count; ++i) {
        if (files[i].nlink > 1) {
            printf("%s ---- ", files[i].name);
            for (int j = 0; j < file_count; ++j) {
                if (files[i].ino == files[j].ino) {
                    printf("%s, ", files[j].name);
                }
            }
            printf("\n");
        }
    }

    return 0;
}
