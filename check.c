// Resize a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    BITMAPINFOHEADER bi;
    
    // change size
    bi.biHeight = -8;
    bi.biWidth = 8;

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
            	condition = 2;
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
	    	if( (i < biHeight/8 && (j < 0.25 * bi.biWidth || j >= 0.75 * bi.biWidth )   ) || 
	    	( i == biHeight/8 && (j < bi.biWidth/8 || j >= 0.25 * bi.biWidth) ) || 
	    	(i == 0.25 * biHeight && 
	    	(j == bi.biWidth/8 || 
	    	j == 3 * bi.biWidth/8 || 
	    	j == 0.5 * bi.biWidth || j == 0.75 * bi.biWidth) ) || 
	    	(i == 3 * biHeight/8 && ( j == bi.biWidth/8 || j == 0.25 * bi.biWidth ||
	    	3 * bi.biWidth/8 || j == 0.5 * bi.biWidth || j == 5 * bi.biWidth/8 || 
	    	j == 0.75 * bi.biWidth) ) || 
	    	(i == 0.5 * biHeight && 
	    	(j == bi.biWidth/8 || j == 3 * bi.biWidth/8 || 
	    	j == 0.5 * bi.biWidth || j == 0.75 * bi.biWidth)  ) || 
	    	(i == 5 * bi.biWidth/8 && (j == bi.biWidth/8 || j == 0.25 * bi.biWidth ||
	    	j == 5 * bi.biWidth/8 || j == 0.75 * bi.biWidth)  ) || 
	    	(i == 0.75 * biHeight && (j < bi.biWidth/8 || j == 0.25 * bi.biWidth || 
	    	j == 3 * bi.biWidth/8 || j == 0.5 * bi.biWidth || 5 * bi.biWidth/8 || j < bi.biWidth) ) || 
	    	(i < biHeight && (j <= bi.biWidth/8 || j >= 0.75 * bi.biWidth)  ))
	    	{
	    		triple.rgbtRed = 255;
	    		triple.rgbtGreen = 255;
	    		triple.rgbtBlue = 255;
	    	} else
	    	{
	    		triple.rgbtRed = 255;
	    		triple.rgbtGreen = 0;
	    		triple.rgbtBlue = 0;
	    	}
	    }
            // write RGB triple to outfile
            printf("i=%f,j=%f,r=%d,g=%d,b=%d\n",i,j,triple.rgbtRed,triple.rgbtGreen,triple.rgbtBlue);
        }
    }

    // success
    return 0;
}
