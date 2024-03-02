#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

void check(int *w, int *h)
{
	if(((*w + 1) * *h)%4 == 0)
	{
		*w = *w + 1;
	}
	else if(((*h + 1) * *w)%4 == 0)
	{
		*h = *h + 1;
	}
	else
	{
		*w = *w + 1;
		*h = *h + 1;
	}
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
    	fprintf(stderr, "Usage: calc.exe width height");
    }
    int width = atoi(argv[1]), height = atoi(argv[2]);
    check(&width, &height);
    printf("Width: %d; Height: %d\n", width, height);
    printf("Sizeof rgbtriple: %ld\n", sizeof(RGBTRIPLE));
}
