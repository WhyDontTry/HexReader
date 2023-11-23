#include <stdio.h>
#include <dirent.h> 
#include <string.h>
#include <stdint.h>

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


                strcat(name, currentDir);
                strcat(name, "/");
                strcat(name, files->d_name);

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

        
    }

}