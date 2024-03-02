// Resize a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

void check(int *w, int *h)
{
	int absH = abs(*h);
	if((*w * absH)%4 == 0)
	{
		// Do nothing
	}
	else if(((*w + 1) * absH)%4 == 0)
	{
		*w = *w + 1;
	}
	else if(((absH + 1) * *w)%4 == 0)
	{
		*h = *h - 1;
	}
	else if(((*w + 1) * (absH + 1))%4 == 0)
	{
		*w = *w + 1;
		*h = *h - 1;
	}
}

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
    float n = atof(argv[1]);
    
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
    
    // store real size
    float w = (float)bi.biWidth, h = (float)abs(bi.biHeight);
    
    // check if multiple by 4
    if(n != 1 && (int)n%2 != 0 && n != 3 && n != 5)
    {
    	check(&bi.biWidth, &bi.biHeight);
    }
    
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);;
    bf.bfSize = bi.biSizeImage + bf.bfOffBits;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

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

            	if((i < (2 * h)/3 && i >= h/3 && j < (2 * w)/3 && j >= w/3) || i >= h || j >= w)
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
	    	if((i < 0.125 * h || j < 0.125 * w) && (j > 0.25 * w - 1 && j < 0.75 * w) ||
	    	(i >= 0.875 * h || j >= 0.875 * w) && (j > 0.25 * w - 1 && j < 0.75 * w) ||
	    	(j < 0.125 * h || i < 0.125 * w) && (i > 0.25 * w - 1 && i < 0.75 * w) ||
	    	(j >= 0.875 * h || i >= 0.875 * w) && (i > 0.25 * w - 1 && i < 0.75 * w) ||
	    	(i >= 0.25 * h && i < 0.375 * h && j >= 0.25 * w && j < 0.375 * w) ||
	    	(i >= 0.25 * h && i < 0.375 * h && j >= 0.625 * w && j < 0.75 * w) ||
	    	(i >= 0.125 * h && i < 0.25 * h && j >= 0.125 * w && j < 0.25 * w) ||
	    	(i >= 0.125 * h && i < 0.25 * h && j >= 0.75 * w && j < 0.875 * w) ||
	    	(i >= 0.75 * h && i < 0.875 * h && j >= 0.125 * w && j < 0.25 * w) ||
	    	(i >= 0.75 * h && i < 0.875 * h && j >= 0.75 * w && j < 0.875 * w) ||
	    	(i >= 0.5 * h && i < 0.625 * h && j >= 0.25 * w && j < 0.375 * w) ||
	    	(i >= 0.5 * h && i < 0.625 * h && j >= 0.625 * w && j < 0.75 * w) ||
	    	(i >= 0.625 * h && i < 0.75 * h && j >= 0.375 * w && j < 0.625 * w))
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
