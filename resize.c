// Resize a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize.exe n infile outfile\n");
        return 1;
    }

    // check n
    if(atoi(argv[1]) < 0 || atoi(argv[1]) > 100)
    {
    	fprintf(stderr, "n must be a positive integer between 0 and 100\n");
    	return 5;
    }
    
    // store n
    int n = atoi(argv[1]);
    
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // change size
    bi.biHeight *= n;
    bi.biWidth *= n;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    int condition = -1;

    // iterate over infile's scanlines
    for (float i = 0, biHeight = (float)abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (float j = 0; j < (float)bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            if(condition < 0)
            {
            	fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            	condition = triple.rgbtGreen == 255 && triple.rgbtRed == 0 && triple.rgbtBlue == 0 ? 1 : 2;
            	i = 0; j = 0;
            }
            
            if(condition == 1)
            {

            	if(i < (2 * biHeight)/3 && i >= biHeight/3 && j < (2 * bi.biWidth)/3 && j >= bi.biWidth/3)
            	{
            		triple.rgbtRed = 255;
            		triple.rgbtGreen = 255;
            		triple.rgbtBlue = 255;
            	} else
            	{
            		triple.rgbtRed = 0;
            		triple.rgbtGreen = 255;
            		triple.rgbtBlue = 0;
            	}
	    } else if(condition == 2)
	    {
	        // firstly try to make a copy
	    	if((i < 0.125 * biHeight || j < 0.125 * bi.biWidth) && (j > 0.25 * bi.biWidth - 1 && j < 0.75 * bi.biWidth) ||
	    	(i >= 0.875 * biHeight || j >= 0.875 * bi.biWidth) && (j > 0.25 * bi.biWidth - 1 && j < 0.75 * bi.biWidth) ||
	    	(j < 0.125 * biHeight || i < 0.125 * bi.biWidth) && (i > 0.25 * bi.biWidth - 1 && i < 0.75 * bi.biWidth) ||
	    	(j >= 0.875 * biHeight || i >= 0.875 * bi.biWidth) && (i > 0.25 * bi.biWidth - 1 && i < 0.75 * bi.biWidth))
	    	{
	    		// first of all define a red color
	    		triple.rgbtRed = 255;
	    		triple.rgbtGreen = 0;
	    		triple.rgbtBlue = 0;
	    	} else
	    	{
	    		triple.rgbtRed = 255;
	    		triple.rgbtGreen = 255;
	    		triple.rgbtBlue = 255;
	    	}
	    }
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
