#include <stdio.h>

int main(void)
{
	FILE *stream;

	stream = fopen("MYFILE.TXT", "w+");
	fprintf(stream, "This is a test");
	printf("The file pointer is at byte \
		%ld\n", ftell(stream));
	fclose(stream);

	return 0;
}
