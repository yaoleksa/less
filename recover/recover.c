#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // check command line arguments quantity
    if(argc != 2)
    {
        fprintf(stderr, "Usage: recover.exe filename\n");
        return 1;
    }
    
    // open file
    FILE *file = fopen(argv[1], "rb");
    
    if(file == NULL)
    {
        fprintf(stderr, "Could not open file\n");
        return 2;
    }
    
    // read file by bytes
    uint8_t ch[3];
    int eof;
    int i = 0;
    FILE *outfile = NULL; // Initialize to NULL
    int file_opened = 0; // Flag to check if outfile is opened
    while(eof != EOF)
    {
        fread(&ch, sizeof(ch), 1, file);
        eof = getc(file);
        char buffer[19];
        if(ch[0] == 255 && ch[1] == 216 && ch[2] == 255)
        {
            if(i < 10)
            {
                sprintf(buffer, "00%d.jpeg", i);
            }
            else if(i < 100)
            {
                sprintf(buffer, "0%d.jpeg", i);
            }
            else
            {
                sprintf(buffer, "%d.jpeg", i);
            }
            if(file_opened) // If outfile is already opened, close it
            {
                fclose(outfile);
            }
            outfile = fopen(buffer, "wb");
            if(outfile == NULL)
            {
                fprintf(stderr, "Could not create file %s\n", buffer);
                fclose(file);
                return 3;
            }
            fwrite(&ch, sizeof(ch), 1, outfile);
            file_opened = 1; // Set flag to indicate outfile is opened
            i++;
        }
        else if(file_opened)
        {
            fwrite(&ch, sizeof(ch), 1, outfile);
        }
    }
    // Close .raw file
    fclose(file);
    if(file_opened) // If outfile is opened, close it
    {
        fclose(outfile);
    }
    return 0;
}
