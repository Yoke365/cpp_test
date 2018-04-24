#include <stdio.h>

long filesize(FILE*stream);



int main(int argc, char **argv)
{
	FILE *stream;
	
	if (argc < 2) {
		printf("usage:\r\n ./filesize <filename>\r\n");

		return -1; 
	}

	char* path = argv[1];
    
	stream=fopen(path,"r+");

	//fprintf(stream,"1234567");
	printf("FilesizeofMYFILE.TXT is [%ld]bytes\n",filesize(stream));
     
    char acStr[128];
	fread(acStr, 128, 1, stream);
	printf(acStr);

	fclose(stream); 
	
	return 0;
}
 
long 
filesize(FILE*stream)
{
	long curpos,length;
	
	curpos=ftell(stream);
	fseek(stream,0L,SEEK_END);
	length=ftell(stream);
	fseek(stream,curpos,SEEK_SET);
	
	return length;
}
