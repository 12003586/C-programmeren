//gcc -Wall -pedantic main.c -o test.exe

// Bo Mengels & Tibo Lambrechts

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __DEBUG

#define BMPINPUTFILE "test.bmp"
#define SECRETMESSAGE "message.txt"

int messageSize();
void readMessage();
void printHelp();

int main(int argc, char*argv[])
{
	if(argc > 1)
	{
		for (int i = 0; i< argc; i++)
		{
			if(strcmp(argv[i], "--help")==0)
			{
				printHelp();
			}
			else if(strcmp(argv[i],"-c")==0)
			{
				char * compress = argv[i+1];
			}
			else if(strcmp(argv[i],"-s") == 0)
			{
				char * inputTextFile = argv[i+1];
			}
			else if(strcmp(argv[i],"-i") ==0)
			{
				char * inputBmpFile = argv[i+1];
			}
			else if(strcmp(argv[i],"-o")==0);
			{
				char * outputImageName = argv[i+1];
			}
		}
	}
	else
	{
		printHelp();
	}
	

    #ifdef __DEBUG
        printf("DEBUG info: BMP transformer\n");
    #endif

    FILE* inputFilePointer = fopen(BMPINPUTFILE, "rb"); //maak een file pointer naar de afbeelding
    if(inputFilePointer == NULL) //Test of het open van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", BMPINPUTFILE);
        exit(EXIT_FAILURE);
    }

    #ifdef __DEBUG
        printf("DEBUG info: Opening File OK: %s\n", BMPINPUTFILE);
    #endif

    unsigned char bmpHeader[54]; // voorzie een array van 54-bytes voor de BMP Header
    fread(bmpHeader, sizeof(unsigned char), 54, inputFilePointer); // lees de 54-byte header

    //Informatie uit de header (wikipedia)
    // haal de hoogte en breedte uit de header
    int breedte = *(int*)&bmpHeader[18];
    int hoogte = *(int*)&bmpHeader[22];

    #ifdef __DEBUG
        printf("DEBUG info: breedte = %d\n", breedte);
        printf("DEBUG info: hoogte = %d\n", hoogte);
    #endif

    int imageSize = 3 * breedte * hoogte; //ieder pixel heeft 3 byte data: rood, groen en blauw (RGB)
    unsigned char* inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); // allocate een array voor alle pixels
	

	
    fread(inputPixels, sizeof(unsigned char), imageSize, inputFilePointer); // Lees alle pixels (de rest van de file
    fclose(inputFilePointer);
	for(int i =0; i < imageSize-2; i+=3)
	{
		printf("pixel %d: B= %d, G=%d, R=%d\n", i/3, inputPixels[i], inputPixels[i+1], inputPixels[i+2]);
	}
	
	
   
    fclose(inputFilePointer);
    free(inputPixels);
	
	
	
	char * messageInput = (char*) malloc(messageSize());
	printf("%d\n",messageSize());
	
	readMessage(messageInput);
	
	int getal[7];
	
	for(int k = 0; k<messageSize(); k++)
	{
		printf("%c\t", messageInput[k]);
		printf("%d\t",messageInput[k]);
		
		for (int j = 7;  j >= 0; j--)
		{
			int binaer = messageInput[k] >> j;
			
			if (binaer & 1)
			{
				getal[j]= 1;
			}
			else 
			{
				getal[j] = 0;
			}
		}
		//om te kijken of het getal in een array staat
		for ( int i = 7; i >=0 ; i--)
		{
			printf("%d", getal[i]);
		}
		printf("\n");
	}
	
	



	
	
	

	
	free(messageInput);
    
    return 0;
}

void readMessage(char* buffer)
{
	FILE* messagePointer = fopen(SECRETMESSAGE, "r");
	
	if(messagePointer == NULL)
	{
		printf("Something went wrong while trying to open %s\n", SECRETMESSAGE);
		exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i< messageSize(); i++)
	{
		buffer[i]=0;
	}
	
	fread(buffer, sizeof(char), messageSize(), messagePointer);
	fclose(messagePointer);
	
}


int messageSize()
{
	FILE* messagePointer = fopen(SECRETMESSAGE, "rb");
	
	
	if(messagePointer == NULL)
	{
		printf("Something went wrong while trying to open %s\n", SECRETMESSAGE);
		exit(EXIT_FAILURE);
	}
	
	fseek(messagePointer, 0, SEEK_END);
	long int size = ftell(messagePointer);
	fclose(messagePointer);
	return size;
}

void printHelp()
{
	printf("%s\n" "Dit is de help\n -c = compress\n -s = input text file\n -i = input bmp file\n -o = output image name\n");
	
	
}