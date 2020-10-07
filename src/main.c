
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <assert.h>
#include "zlib.h"
#include "main.h"

int main(int argc, char* argv[]) { 
  
	if (argc != 2) {
	  	printf("Usage: habitUnZip <file>\n");
	      	return 1;
      	}	      

	FILE *fptr;
	fptr = fopen(argv[1],"rb");

	if (fptr == 0) {
		printf("Can't open file: %s\n",argv[1]);
		return 1;
	}

	fseek(fptr, 0L, SEEK_END);
	int sz = ftell(fptr);
	rewind(fptr);
	printf("Size: %d bytes (%s)\n",sz,argv[1]);

	unsigned char *databuff;
	databuff = (unsigned char*) malloc(sz);
	fread(databuff,sz,1,fptr);


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
			break;              
		}	
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



	return 0;



    // placeholder for the UNcompressed (inflated) version of "b"
    char c[15000];
     

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
     
    printf("Uncompressed size is: %lu\n", strlen(c));
    //printf("Uncompressed string is: %s\n", c);
    

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


