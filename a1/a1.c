#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void listRecSingle(const char *path)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;

    dir = opendir(path);
    if(dir == NULL)
    {
        perror("opendir");
        return ;
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if(lstat(fullPath, &statbuf) != 0)
            {
                perror("lstat");
                continue;
            }
            printf("%s\n", fullPath);
            /*
            if(S_ISDIR(statbuf.st_mode))
            {
                printf("%s\n", fullPath);
                listRec(fullPath);
            }
            else
            {
                printf("%s\n", fullPath);
            }
            */
        }
    }
    closedir(dir);
}

void listRec(const char *path)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;

    dir = opendir(path);
    if(dir == NULL)
    {
        perror("opendir");
        return ;
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if(lstat(fullPath, &statbuf) != 0)
            {
                perror("lstat");
                continue;
            }
            if(S_ISDIR(statbuf.st_mode))
            {
                printf("%s\n", fullPath);
                listRec(fullPath);
            }
            else
            {
                printf("%s\n", fullPath);
            }
        }
    }
    closedir(dir);
}

int main(int argc, char **argv){
    if(argc >= 2){
        if(strcmp(argv[1], "variant") == 0){
            printf("73742\n");
        }
        else
        {
            if(strcmp(argv[1], "list") == 0 && strcmp(argv[2], "recursive") == 0)
            {
                printf("SUCCESS\n");
                char *str = malloc(strlen(argv[3])+1);
                strcpy(str, argv[3]+5);
                listRec(str);
                free(str);
            }
            else 
            {
                if(strcmp(argv[1], "list") == 0)
                {
                    printf("SUCCESS\n");
                    char *str = malloc(strlen(argv[2])+1);
                    strcpy(str, argv[2]+5);
                    listRecSingle(str);
                    free(str);
                }
            }
        }
    }
    return 0;
}