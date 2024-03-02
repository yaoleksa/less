#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// check command line arguments quantity
	if(argc != 2)
	{
		fprintf(stderr, "Usage: recover.exe filename\n");
		return 1;
	}
	
	// open file
	FILE *file = fopen(argv[1], "r");
	if(file == NULL)
	{
		fprintf(stderr, "Could not open file\n");
		return 2;
	}
	
	// read file content
	for(int i = 0; i < sizeof(file); i++)
	{
		// read each byte
		int ch;
		fread(&ch, sizeof(char), 1, file);
		printf("%d\n", ch);
	}
	return 0;
}
