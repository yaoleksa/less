#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    // check command line arguments quantity
    if(argc != 2) {
        fprintf(stderr, "Usage: recover.exe filename\n");
        return 1;
    }
    
    // open file
    FILE *file = fopen(argv[1], "rb");
    
    if(file == NULL) {
        fprintf(stderr, "Could not open file\n");
        return 2;
    }
    
    // read file by bytes
    uint8_t ch[512]; // 512 bytes buffer
    int i = 0;
    FILE *outfile = NULL; // Initialize to NULL
    while (fread(&ch, sizeof(ch), 1, file) == 1) {
        char buffer[8];
        if (ch[0] == 0xff && ch[1] == 0xd8 && ch[2] == 0xff && (ch[3] & 0xf0) == 0xe0) {
            if (outfile != NULL) {
                fclose(outfile);
            }
            sprintf(buffer, "%03d.jpg", i);
            outfile = fopen(buffer, "wb");
            if (outfile == NULL) {
                fprintf(stderr, "Could not create file %s\n", buffer);
                fclose(file);
                return 3;
            }
            fwrite(&ch, sizeof(ch), 1, outfile);
            i++;
        } else if (outfile != NULL) {
            fwrite(&ch, sizeof(ch), 1, outfile);
        }
    }
    
    // Close files
    fclose(file);
    if(outfile != NULL) {
        fclose(outfile);
    }
    
    return 0;
}
