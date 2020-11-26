
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <assert.h>
#include "zlib.h"
#include "main.h"

int main(int argc, char* argv[]) { 
  
	if (argc != 3) {
		printf("\n");
	  	printf("Usage: habitUnZip <fileIn> <fileOut>\n");
		printf("\n");
		printf("Unzipper <fileIn> vha zlib. Den unzippa fila lagres i <fileOut>\n");
		printf("Programmet kan benyttes til å unippe haBit ElCad swap-filer.\n");
		printf("\n");
	    return 1;
    }	      

	FILE *fptrIn;
	fptrIn = fopen(argv[1],"rb");

	if (fptrIn == 0) {
		printf("Can't open file: %s\n",argv[1]);
		return 1;
	}

	FILE *fptrOut;
	fptrOut = fopen(argv[2],"wb");

	fseek(fptrIn, 0L, SEEK_END);
	int sz = ftell(fptrIn);
	rewind(fptrIn);
	printf("Size: %d bytes (%s)\n",sz,argv[1]);

	unsigned char *databuff;
	databuff = (unsigned char*) malloc(sz);
	fread(databuff,sz,1,fptrIn);

	int magic = 0;

	// Finn posisjonen til ':'
	int p = 0;
	for (int i=0;i<10;i++) {
		printf("%d [%u dec|%X hex|%c ascii] \n",
			i,
			databuff[i], 
			databuff[i],
			databuff[i] );
		if (databuff[i] == ':') {
			p = i;
			magic = 1;
			break;              
		}	
	}
	
	if (magic == 0) {
		printf("Error. Dette er neppe ei haBit swap-fil. Mangler nnnn: i starten av fila. nnnn skal angi hvor stor den utpakka fila er.");
		return 1;
	}
	
	printf("Zipdata starts at position %d\n",p);

	unsigned char strbuff[4];

	int x = 0;
	for (int i=p-1; i>=0; i--) {

		strbuff[0] = databuff[i];
		strbuff[1] = '\0';

		int y2 = atoi((char*)strbuff);

		int f = p-i-1;
		x += mypow((double)10 ,(double)f) * y2;
		printf("f=%d y=%s x=%d \n",f,strbuff,x);
	}

	printf("x=%d \n",x);
	
	char *byteArray = (char*)malloc(x);
	
	if (byteArray == NULL) {
		printf("Error. Klarte ikke å allocere minne.");
		return 1;		
	}

	//return 0;

    // placeholder for the UNcompressed (inflated) version of "b"
    //char c[15000];
     

    // zlib struct
    z_stream infstream;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;
    infstream.avail_in = sz - 5; 
    infstream.next_in = (Bytef *) databuff+(p+1); // input char array
    infstream.avail_out = (uInt)sizeof(c); // size of output
    infstream.next_out = (Bytef *)c; // output char array
     
    // the actual DE-compression work.
    inflateInit(&infstream);
    inflate(&infstream, Z_NO_FLUSH);
    inflateEnd(&infstream);
     
	 
	long usize = strlen(c); 
    printf("Uncompressed size is: %lu\n",usize);
    

    // make sure uncompressed is exactly equal to original.
    //assert(strcmp(a,c)==0);

    return 0;
}


int mypow(int base, unsigned int exp) {
	int i, result = 1;
    	for (i = 0; i < exp; i++)
        	result *= base;
    	return result;
}


