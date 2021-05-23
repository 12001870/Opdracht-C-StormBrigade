#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// grootte van de image
int imageSize(FILE *fp1);

//voor de secret message die in de file wordt gebruikt
void secretMessageText(FILE *fp2);

//code voor de grote van de secret message 
int SecretMessageTextSize(FILE *fp2);

// code voor de bits van de secret message
int SecretMessageTextBits(char byte, int bit);

// decompressen van secret message
void secretMessageDecode(int size_txt,FILE *pf1, FILE *pf2);

int main(int argc,char *argv[])
{
	
	if (argc > 1)
	{
	if (argc > 1 && strcmp(argv[1], "--help") == 0)
	{
		printf("EXECUTION INPUTS: ");
		printf("\n");
		printf("\nCompress ==> stormbrigade -c -s inputfile.bmp -i inputfile.txt -o outputfile.bmp\n\n");
		printf("Decompress ==> stormbrigade -d -i outputfile.bmp -o inputfile.txt\n\n");
		return 0;
	}
	}
	
	else 
	{
		printf("%s\n", "You have entered an incorrect input. Use the command '--help' for more info.");
		exit(EXIT_FAILURE);
	}
	FILE *fp = NULL; 
	FILE *inputFilePointer = NULL;  
    int i = 0;
	int x = 0;
    char *argv_2,*argv_4,*argv_6;

    switch(argc)
    {
			//voor het compressen
	case 8 :	if(!strcmp(argv[1],"-c"))
			{
			    for (int i = 2; i < 8; i++)
			    {
				if (!strcmp(argv[i],"-s"))
				    argv_2 = argv[i+1];

				if (!strcmp(argv[i],"-i"))
				    argv_4 = argv[i+1];

				if (!strcmp(argv[i],"-o"))
				    argv_6 = argv[i+1];
			    }			    
			    Encoding(argv_2, argv_4, argv_6);
			    break;
			}
			//voor het decompressen
	case 6 :	if(!strcmp(argv[1], "-d"))
			{
			    for (i = 2; i < 6; i++)
			    {
				if (!strcmp(argv[i],"-i"))
				    argv_2 = argv[i+1];
				if (!strcmp(argv[i],"-o"))
				    argv_4 = argv[i+1];
			    }			    

			    Decode(argv_2, argv_4);
			    break;
			}
    }	
	
    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

//groote van de image
int imageSize(FILE *fp1)
{
	int breedte =0;
	int hoogte =0;

	fseek(fp1, 0x12, SEEK_SET);	
	fread(&breedte, sizeof(int), 1, fp1);	
	fread(&hoogte, sizeof(int), 1, fp1);	
	printf("size of the Image is %d x %d \n", breedte, hoogte);
	fseek(fp1, 0L, SEEK_SET);	

	return ((breedte * hoogte * 3) / 8);
}

//voor de secret message die in de file wordt gebruikt
void SecretMessageText(FILE *fp2)
{
	char secretmessage;
	while ((secretmessage = getchar())!=EOF)
	{
		putc(secretmessage,fp2);	
	}
}

//code voor de grote van de secret message 
int SecretMessageTextSize(FILE *fp2)
{
	int size_txt;
	fseek(fp2, 0L, SEEK_END);
	size_txt = ftell(fp2);
	fseek(fp2, 0L, SEEK_SET);
	return size_txt;
}
// code voor de bits van de secret message
int SecretMessageTextBits(char byte, int bit)
{
	return ((byte >> 8-bit) & 1);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------




int Encoding(char *argv_2,char *argv_3,char *argv_4)
{
	FILE *fp1, *fp2, *fp3;

	//openen van image file
	if((fp1 = fopen(argv_2, "r+")) == NULL) 
	{
		printf("Could not open file %s.\n", argv_2);
		return 1;
	}

	int totaalImageSize = imageSize(fp1);
	printf("Totaal %d tekens kunnen worden opgeslagen in %s.\n", totaalImageSize, argv_2);

	//openen van tekst file
	fp2 = fopen(argv_3, "w+");

	// secret message schrijven in de tekst file
	printf("Enter your secret text, press enter and Press CTRL + C To Stop : \t");
	SecretMessageText(fp2);

	int totaalSecretMessageTextSize = SecretMessageTextSize(fp2);
	printf("\ngroote van Secret Message is ==> %d\n", totaalSecretMessageTextSize);


	//openen van bmp file
	fp3 = fopen(argv_4, "w+");
	if (fp3== NULL) 
	{
		fprintf(stderr, "Could not open file %s\n",argv_4);
		exit(1);
	}
}
	
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------	
	
/*
// decompressen van secret message
void secretMessageDecode(int SizeTxtFile, FILE *pf1, FILE *pf2)
{
	int file_buffer=0;
	int i =0;
	int counter = 0; 
	int array=0;
	int var;
	int bit_msg;
	char output[250] = {0};
	for (i = 0; i < (SizeTxtFile * 8); i++)
	{
		counter++;
		var = fgetc(pf1);
		bit_msg = (var & 1);
		if (bit_msg)
		{
			file_buffer = (file_buffer << 1) | 1;
		}
		else
		{
			file_buffer = file_buffer << 1;
		}

		if ( counter == 8)
		{
			putc(file_buffer, pf2);
			output[array++]= file_buffer;
			counter=0;
			file_buffer = 0;
		}
	}
	printf("\n*** Secret Text Is ==> %s\n\n", output);
}
*/
int Decode(char *argv_2, char *argv_4)
{
	FILE *pf1, *pf2;
	

	//contoleren op openen van bmp image file
	if((pf1 = fopen(argv_2, "r")) == NULL) 
	{
		printf("Could not open file %s.\n", argv_2);
		return 1;
	}

	//contoleren op openen van tekst file
	if((pf2 = fopen(argv_4, "w+")) == NULL) 
	{
		printf("Could not open file %s.\n", argv_4);
		return 1;
	}

}