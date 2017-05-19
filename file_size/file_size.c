#include <stdio.h>

long filesize(FILE*stream);

int main(void)
{
	FILE *stream;
	
	stream=fopen("MYFILE.TXT","w+");
	fprintf(stream,"Thisisatest");
	printf("FilesizeofMYFILE.TXT is [%ld]bytes\n",filesize(stream));
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
