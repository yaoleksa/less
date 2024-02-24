// Fetch metadata from a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./data.exe file\n");
        return 1;
    }

    // remember filename
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    for(int i = 0; i < abs(bi.biHeight); i++)
    {
    	for(int j = 0; j < bi.biWidth; j++)
    	{
    		RGBTRIPLE triple;
    		fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    		printf("i = %d, j = %d, red = %d, green = %d, blue = %d\n", i, j, triple.rgbtRed, 
    		triple.rgbtGreen, triple.rgbtBlue);
    	}
    }
    printf("width = %d; height = %d\n\n\n", bi.biWidth, bi.biHeight);
    
    fclose(inptr);

    // success
    return 0;
}
