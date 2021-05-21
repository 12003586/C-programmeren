#include <stdio.h>
#include <string.h>

void printHelp();

int main(int argc, char* argv[])
{
	
	if(argc > 1)
	{
		for (int i = 0; i< argc; i++)
		{
			if(strcmp(argv[i], "--help")==0)
			{
				printHelp();
			}
			else if(strcmp(argv[i],"-d")==0)
			{
				char * decompress = argv[i+1];
			}
			else if(strcmp(argv[i],"-i") ==0)
			{
				char * inputBmpFile = argv[i+1];
			}
			else if(strcmp(argv[i],"-o")==0);
			{
				char * outputTextFile = argv[i+1];
			}
		}
	}
	else
	{
		printHelp();
	}
	
	
	return 0;
}
void printHelp()
{
	printf("%s\n" "Dit is de help\n -d = decompress\n  -i = input bmp file\n -o = output text file\n");
	
	
}	