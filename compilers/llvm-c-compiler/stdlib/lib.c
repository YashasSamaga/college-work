#include <stdio.h>

void writeString(char str[])
{
	printf("%s", str);
}

void writeChar(char c)
{
	printf("%c", c);
}

void writeInteger(int n)
{
	printf("%d", n);
}

int readInteger()
{
    int n;
    scanf("%d", &n);
    return n;
}

int file_open(char str[])
{
	FILE* file = fopen(str, "rw");
	return fileno(file);
}

int file_getc(int file)
{
	FILE *f = fdopen(file, "rw");
	return fgetc(f);
}
