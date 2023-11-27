#include <stdio.h>
#include <dirent.h> 
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _path_list {
    char path[300];
    struct _path_list* next;
    struct _path_list* prev;
}path_list_t;

path_list_t* path = NULL;

FILE *fp;
char name[100];

int main (int argc, char** argv)
{
    printf("Hello  world!\n");

    const char* currentDir = ".";

    DIR * dir = opendir(currentDir);

    if( dir != NULL )
    {
        struct dirent* files = NULL;

        while ((files = readdir(dir)) != NULL)
        {
            if(strstr(files->d_name, ".geo"))
            {
                printf("Geo files: %s/%s\n", currentDir, files->d_name);

                name[0] = '\0';
                strcat(name, currentDir);
                strcat(name, "/");
                strcat(name, files->d_name);
                
                if( path == NULL )
                {
                    path = malloc(sizeof(path_list_t));
                }
                else
                {
                    path->next = malloc(sizeof(path_list_t));
                    path->next->prev = path;
                    path = path->next;
                }

                if( path != NULL )
                {
                    strcat(path->path, name);
                }


            }
            
        }
            
        closedir(dir);    


        fp = fopen(name, "r");

        if( fp != NULL )
        {
            uint8_t buff[200];

            size_t count = fread(buff, sizeof(buff[0]), 200, fp);

            printf("Readed %zu bytes from %s\n", count, name);

            printf("Reset counter value is: %u\n", buff[59]);

            fclose(fp);
        }

        while( path != NULL )
        {
            printf("%s\n", path->path);
            path = path->prev;
        }

        
    }

}