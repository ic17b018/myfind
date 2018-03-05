
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void do_dir (const char * file_name, const char * const *parms);
void do_file (const char * file_name, const char *const *parms, struct dirent *curstruct);

int main(int argc, const char * argv[]) {
    
    const char *parms [1] = {argv[1]};
    char path[strlen(argv[1])];
    strcpy(path, argv[1]);
    
    do_dir(path, parms);
    
    return 0;
}

void do_dir (const char * file_name, const char * const *parms)
{
    DIR *curdir = opendir(file_name);
    struct dirent *curstruct;
    while ((curstruct = readdir(curdir)))
    {
        if ((strcmp(curstruct->d_name, ".") == 0) || (strcmp(curstruct->d_name, "..") == 0))  continue;
        char newpath[(strlen(file_name))+(strlen(curstruct->d_name))+1];
        strcpy(newpath, file_name);
        strcat(newpath, "/");
        strcat(newpath, curstruct->d_name);
        
        do_file(newpath, parms, curstruct);
    }
}



void do_file (const char * file_name, const char *const *parms, struct dirent *curstruct)
{
    printf("%s\n", file_name);
    
    if (curstruct->d_type == 4) do_dir(file_name, parms);
    
}

