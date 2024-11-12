#include <sys/stat.h>
#include <stdio.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

int size_files = 0;


void size_directory(char* folder_path){
    DIR *folder;

    folder = opendir(folder_path);

    if(folder == NULL)
    {
        perror("Unable to read directory");
    }


    struct stat st;
    struct dirent *entry;
    while( (entry=readdir(folder)) )
        {   

            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf(path, sizeof(path), "%s/%s", folder_path, entry->d_name);

            if (entry->d_type == DT_DIR){
                printf ("Folder: %s\n", entry->d_name);
                size_directory(path);
            }
            else if (entry->d_type == DT_REG){
                    struct stat st;
                    stat(path, &st);
                    size_files += st.st_size;
                    printf("File %s\n", entry->d_name);
                }
            
        }
    closedir(folder);
}

int main(int argc, char *argv[])
{

    size_directory(argv[1]);
    printf("%d",  size_files);

    return(0);
}
