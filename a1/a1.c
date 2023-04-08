#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

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

void permCheck(const char *path, const char *permission)
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
            
            char *a = malloc(10);

	    snprintf(a, 10, "%c%c%c%c%c%c%c%c%c",          //luat de pe net snprintf-uls
             (statbuf.st_mode & S_IRUSR) ? 'r' : '-',
             (statbuf.st_mode & S_IWUSR) ? 'w' : '-',
             (statbuf.st_mode & S_IXUSR) ? 'x' : '-',
             (statbuf.st_mode & S_IRGRP) ? 'r' : '-',
             (statbuf.st_mode & S_IWGRP) ? 'w' : '-',
             (statbuf.st_mode & S_IXGRP) ? 'x' : '-',
             (statbuf.st_mode & S_IROTH) ? 'r' : '-',
             (statbuf.st_mode & S_IWOTH) ? 'w' : '-',
             (statbuf.st_mode & S_IXOTH) ? 'x' : '-');

            if(strcmp(permission, a) == 0)
                printf("%s\n", fullPath);
            free(a);
        }
    }
    closedir(dir);
}

void permCheckRecursive(const char *path, const char *permission)
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
            
            char *a = malloc(10);

        snprintf(a, 10, "%c%c%c%c%c%c%c%c%c",                //luat de pe net snprintf-ul
             (statbuf.st_mode & S_IRUSR) ? 'r' : '-',
             (statbuf.st_mode & S_IWUSR) ? 'w' : '-',
             (statbuf.st_mode & S_IXUSR) ? 'x' : '-',
             (statbuf.st_mode & S_IRGRP) ? 'r' : '-',
             (statbuf.st_mode & S_IWGRP) ? 'w' : '-',
             (statbuf.st_mode & S_IXGRP) ? 'x' : '-',
             (statbuf.st_mode & S_IROTH) ? 'r' : '-',
             (statbuf.st_mode & S_IWOTH) ? 'w' : '-',
             (statbuf.st_mode & S_IXOTH) ? 'x' : '-');

            if(S_ISDIR(statbuf.st_mode))
            {
                if(strcmp(permission, a) == 0)
                    printf("%s\n", fullPath);
                free(a);
                permCheckRecursive(fullPath,permission);
            }
            else
            {
                if(strcmp(permission, a) == 0)
                    printf("%s\n", fullPath);
                free(a);
            }
        }
    }
    closedir(dir);
}

void fileSize(const char* dirPath, const int f_size)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;

    dir = opendir(dirPath);
    if(dir == NULL)
    {
        perror("opendir");
        return ;
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", dirPath, entry->d_name);
            if(lstat(fullPath, &statbuf) != 0)
            {
                perror("lstat");
                continue;
            }

            if(S_ISREG(statbuf.st_mode))
            {
                if(statbuf.st_size < f_size)
                    printf("%s\n", fullPath);
            }
        }
    }
    closedir(dir);
}

void fileSizeRecursive(const char* dirPath, const int f_size)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;

    dir = opendir(dirPath);
    if(dir == NULL)
    {
        perror("opendir");
        return ;
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", dirPath, entry->d_name);
            if(lstat(fullPath, &statbuf) != 0)
            {
                perror("lstat");
                continue;
            }

            if(S_ISREG(statbuf.st_mode))
            {
                if(statbuf.st_size < f_size)
                    printf("%s\n", fullPath);
            }
            else
            {
                if(S_ISDIR(statbuf.st_mode))
                    fileSizeRecursive(fullPath,f_size);

            }
        }
    }
    closedir(dir);
}

void parsing(const char* path)
{
    int f = -1;
    f = open(path, O_RDONLY);
    if(f == -1)
        return ;

    lseek(f,0,SEEK_SET);
    char a[5], d[256][128];
    int b=0, c=0, e[256] = {0}, g[256] = {0};
    read(f,a,4);
    a[4] = '\0';
    lseek(f,6,SEEK_SET);
    read(f,&b,2);
    read(f,&c,1);
    for(int i = 0; i < c; i++)
    {
        lseek(f,9+i*19,SEEK_SET);
        read(f,d[i],7);
        d[i][7] = '\0';
        lseek(f,16+i*19,SEEK_SET);
        read(f,&e[i],4);
        lseek(f,24+i*19,SEEK_SET);
        read(f,&g[i],4);
    }

    if(strcmp(a,"BxQS") != 0)
    {
        printf("ERROR\nwrong magic\n");
        close(f);
        return ;
    }
    if(b < 124 || b > 221)
    {
        printf("ERROR\nwrong version\n");
        close(f);
        return ;
    }
    if(c < 6 || c > 13)
    {
        printf("ERROR\nwrong sect_nr\n");
        close(f);
        return ;
    }
    int z = 0;
    for(int i = 0; i < c; i++)
    {
        if(e[i] != 96 && e[i] != 72 && e[i] != 79 && e[i] != 35 && e[i] != 63)
            z = 1;
    }
    if(z == 1)
    {
        printf("ERROR\nwrong sect_types\n");
        close(f);
        return ;
    }
    printf("SUCCESS\nversion=%d\n",b);
    printf("nr_sections=%d\n",c);
    for(int i = 1; i <=c; i++)
    {
        printf("section%d: %s %d %d\n",i, d[i-1], e[i-1], g[i-1]);
        close(f);
    }
    close(f);
}

int pentru_findall(const char* path)
{
    int f = -1;
    f = open(path, O_RDONLY);
    if(f == -1)
        return -1;

    lseek(f,0,SEEK_SET);
    char a[5], d[256][128];
    int b=0, c=0, e[256] = {0}, g[256] = {0};
    read(f,a,4);
    a[4] = '\0';
    lseek(f,6,SEEK_SET);
    read(f,&b,2);
    read(f,&c,1);
    for(int i = 0; i < c; i++)
    {
        lseek(f,9+i*19,SEEK_SET);
        read(f,d[i],7);
        d[i][7] = '\0';
        lseek(f,16+i*19,SEEK_SET);
        read(f,&e[i],4);
        lseek(f,24+i*19,SEEK_SET);
        read(f,&g[i],4);
    }

    if(strcmp(a,"BxQS") != 0)
    {
        close(f);
        return -1;
    }
    if(b < 124 || b > 221)
    {
        close(f);
        return -1;
    }
    if(c < 6 || c > 13)
    {
        close(f);
        return -1;
    }
    int z = 0, w = 0;
    for(int i = 0; i < c; i++)
    {
        if(e[i] != 96 && e[i] != 72 && e[i] != 79 && e[i] != 35 && e[i] != 63)
            z = 1;
        if(e[i] == 35)
            w++;
    }
    if(z == 1)
    {
        close(f);
        return -1;
    }
    close(f);
    return w;
}

void findall(const char* dirPath)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;

    dir = opendir(dirPath);
    if(dir == NULL)
    {
        perror("opendir");
        return ;
    }
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(fullPath, 512, "%s/%s", dirPath, entry->d_name);
            if(lstat(fullPath, &statbuf) != 0)
            {
                perror("lstat");
                continue;
            }

            if(S_ISREG(statbuf.st_mode))
            {
                if(pentru_findall(fullPath) > 0)
                    printf("%s\n", fullPath);
            }
            else
            {
                if(S_ISDIR(statbuf.st_mode))
                    findall(fullPath);

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
                if(argv[3][0] == 'p' && argv[3][1] == 'e' && argv[3][2] == 'r')
                {
                    printf("SUCCESS\n");
                    char *str = malloc(strlen(argv[4])+1);
                    char *perm = malloc(strlen(argv[3])+1);
                    strcpy(str, argv[4]+5);
                    strcpy(perm, argv[3]+12);
                    permCheckRecursive(str, perm);
                    free(perm);
                    free(str);
                }
                else
                {
                    if(argv[3][0] == 's' && argv[3][1] == 'i' && argv[3][2] == 'z')
                    {
                        printf("SUCCESS\n");
                        char *str = malloc(strlen(argv[4])+1);
                        char *sze = malloc(strlen(argv[3])+1);
                        strcpy(str, argv[4]+5);
                        strcpy(sze, argv[3]+13);
                        int sz = atoi(sze);
                        fileSizeRecursive(str, sz);
                        free(sze);
                        free(str);
                    }
                    else
                    {
                        printf("SUCCESS\n");
                        char *str = malloc(strlen(argv[3])+1);
                        strcpy(str, argv[3]+5);
                        listRec(str);
                        free(str);
                    }
                }
            }
            else 
            {
                if(strcmp(argv[1], "list") == 0)
                {

                    if(argv[2][0] == 'p' && argv[2][1] == 'a' && argv[2][2] == 't')
                    {
                        printf("SUCCESS\n");
                        char *str = malloc(strlen(argv[2])+1);
                        strcpy(str, argv[2]+5);
                        listRecSingle(str);
                        free(str);
                    }
                    else
                    {
                        if(argv[2][0] == 'p' && argv[2][1] == 'e' && argv[2][2] == 'r')
                        {
                            printf("SUCCESS\n");
                            char *str = malloc(strlen(argv[3])+1);
                            char *perm = malloc(strlen(argv[2])+1);
                            strcpy(str, argv[3]+5);
                            strcpy(perm, argv[2]+12);
                            permCheck(str, perm);
                            free(perm);
                            free(str);
                        }
                        else
                        {
                            if(argv[2][0] == 's' && argv[2][1] == 'i' && argv[2][2] == 'z')
                            {
                                printf("SUCCESS\n");
                                char *str = malloc(strlen(argv[3])+1);
                                char *sze = malloc(strlen(argv[2])+1);
                                strcpy(str, argv[3]+5);
                                strcpy(sze, argv[2]+13);
                                int sz = atoi(sze);
                                fileSize(str, sz);
                                free(sze);
                                free(str);
                            }
                        }
                    }
                }
                else
                {
                    if(strcmp(argv[1], "parse") == 0)
                    {
                        if(argv[2][0] == 'p' && argv[2][1] == 'a' && argv[2][2] == 't')
                        {
                            char *str = malloc(strlen(argv[2])+1);
                            strcpy(str, argv[2]+5);
                            parsing(str);
                            free(str);
                        }
                    }
                    else
                    {
                        if(strcmp(argv[1], "findall") == 0)
                        {
                            char *str = malloc(strlen(argv[2])+1);
                            strcpy(str, argv[2]+5);
                            printf("SUCCESS\n");
                            findall(str);
                            free(str);
                        }
                    }
                }
            }
        }
    }
    return 0;
}
