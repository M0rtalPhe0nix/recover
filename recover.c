#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Incorrect Usage");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        return 1;
    }
    
    BYTE buffer[512];
    int c = 0;
    char filename[8] = "###.jpg";
    FILE *img = NULL;
    while (fread(buffer, sizeof(BYTE), 512, f) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (c == 0)
            {
                sprintf(filename, "%03i.jpg", c); 
                img = fopen(filename, "w");
                c++;
                fwrite(buffer, sizeof(BYTE), 512, img);
                
            }
            else
            {
                
                fclose(img);
                sprintf(filename, "%03i.jpg", c); 
                img = fopen(filename, "w");
                c++;
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
        else
        {
            if (img != NULL)
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
    }
    
    
    
    
}
