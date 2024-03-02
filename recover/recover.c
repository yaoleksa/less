#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
	while(eof != EOF)
	{
		fread(&ch, sizeof(ch) * 3, 1, file);
		printf("%c %c %c\n", ch[0], ch[1], ch[2]);
		eof = getc(file);
		if(ch[0] == 255 && ch[1] == 216 && ch[2] == 255)
		{
			printf("OKI\n");
			break;
		}
		i++;
	}
	printf("%d\n", i);
	fclose(file);
	return 0;
}
