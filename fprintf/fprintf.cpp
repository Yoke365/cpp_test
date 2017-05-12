#include <stdio.h>

FILE *stream;


int  main( int argc, char **argv)
{
	int i = 10;
	double fp = 1.5;
	char s[] = "this is a string";
	char c = '\n';
    
    printf("test console\r\n");
    
	stream = fopen( "fprintf.out", "a+" );
	fprintf( stream, "%s%c", s, c );

	fprintf( stream, "%d\n", i );
	fprintf( stream, "%f\n", fp );
	
	fclose( stream );
}
