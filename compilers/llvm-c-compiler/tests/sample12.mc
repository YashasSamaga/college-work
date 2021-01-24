extern void writeInteger(int);
extern void writeString(char[]);
extern int readInteger();
extern int file_open(char[]);
extern char file_getc(int);

bool isspace(char c)
{
    return c == ' ' || c == '\n' || c == -1;
}

bool issame(char a[], char b[])
{
    int i = 0;
    while (1)
    {
        if (a[i] == 0 && b[i] != 0)
        {
            return false;
        }

        if (a[i] != 0 && b[i] == 0)
        {
            return false;
        }

        if (a[i] != b[i])
        {
            return false;
        }

        if (a[i] == b[i] && a[i] == 0)
        {
            return true;
        }
    }

    return true;
}

void main ()
{
    int fd;
    fd = file_open("inputfile.txt");

    int count = 0;
    char words[1024][32];

    char c;
    c = file_getc(fd);
    while(c != -1)
    {
        int l = 0;
        char word[32];
        
        while(!isspace(c))
        {
            word[l] = c;
            l++;
            c = file_getc(fd);
        }

        if (l > 0)
        {
            word[l] = 0;
            bool present = false;
            for (int i = 0; i < count; i++)
            {
                if (issame(word, words[i]))
                {
                    present = true;
                    break;
                }
            }

            if (present)
            {
                for (int i = 0; i <= l; i++)
                {
                    words[count][i] = word[i];
                }
                count++;
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        writeString(words[i]);
        writeString(" ");
    }
}