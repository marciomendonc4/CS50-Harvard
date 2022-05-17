#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 512

typedef uint8_t BYTE;

bool isJpeg(BYTE *buffer);

int main(int argc, char *argv[])
{
    //Check if only 1 command line argument was typed
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    char filename[15];
    int i = 0, photoCount = 0;
    
    //opening the file
    FILE *file  = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("%s couldn't be opened", argv[1]);
        return 1;
    }
    
    FILE *photo;
    //Allocating memory for the buffer
    BYTE *buffer = malloc(MAX * sizeof(BYTE));
    
    //Looping through the file, reading a chunk of 512bytes at time
    while (fread(buffer, MAX, 1, file) == 1)
    {
        
        if (isJpeg(buffer))
        {
            //Checking if it's the first JPEG of the file
            if (photoCount == 0)
            {
                sprintf(filename, "%03i.jpg", i++);
                
                photo = fopen(filename, "w");
                if (photo == NULL)
                {
                    return 1;
                }
                
                fwrite(buffer, sizeof(BYTE), MAX, photo);
                
                photoCount++;
            }
            else
            {
                //Closing the previous file and opening a new one
                fclose(photo);
                
                sprintf(filename, "%03i.jpg", i++);
                
                photo = fopen(filename, "a");
                if (photo == NULL)
                {
                    return 1;
                }
                fwrite(buffer, sizeof(BYTE), MAX, photo);
            }
        }
        //Condition that ensures that a file will keep being written till a new JPEG is found
        else if (photoCount != 0)
        {
            fwrite(buffer, sizeof(BYTE), MAX, photo);
        }
    }
    //freeing the allocated memory and closing all files
    free(buffer);
    fclose(file);
    fclose(photo);
}

//Function that checks if a file is a JPEG
bool isJpeg(BYTE *buffer)
{
    return (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0));
}
