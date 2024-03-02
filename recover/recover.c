#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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
	//////
	fseek(file, 0, SEEK_END);
	unsigned long fileLen=ftell(file);
	char* file_data;
	rewind(file);
	file_data=malloc((fileLen)*sizeof(char));
	if (file_data == NULL)
	{
    		printf("Memory error\n");
	}
	int num_read=0;
	char s;
	int q = 0;
	while ((num_read = fread(&s, 1, 1, file)) && q < 10250)
	{
		strncat(file_data,&s,1);
		q++;
	}
	printf("file contents: %s\n", file_data);
	fclose(file);
	///////////////
	if(file == NULL)
	{
		fprintf(stderr, "Could not open file\n");
		return 2;
	}
	
	// read file by bytes
	char ch;
	int i = 0;
	while(ch != EOF)
	{
		ch = fgetc(file);
		printf("%ld\n", sizeof(ch));
		i++;
	}
	printf("%d\n", i);
	return 0;
}
