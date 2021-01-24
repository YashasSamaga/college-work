extern void writeInteger(int);
extern void writeString(char[]);
extern int readInteger();
extern int file_open(char[]);
extern char file_getc(int);

void main ()
{
    int fd;
    fd = file_open("inputfile.txt");

    char c;
    c = file_getc(fd);

    int count[256];
    while(c != -1)
    {
        count[c]++;
        c = file_getc(fd);
    }

    for (int i = 'a'; i <= 'z'; i++)
    {
        char str[5] = "a ";
        str[0] = i;
        writeString(str);
        writeInteger(count[i]);
        writeString("\n");
    }

    for (int i = 'A'; i <= 'Z'; i++)
    {
        char str[5] = "a ";
        str[0] = i;
        writeString(str);
        writeInteger(count[i]);
        writeString("\n");
    }
}