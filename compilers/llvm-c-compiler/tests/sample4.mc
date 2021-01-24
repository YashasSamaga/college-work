extern void writeInteger(int);
extern void writeChar(char);
extern int readInteger();

int generate(int z_limit) 
{ 
    int count = 0;
    int c = 0;
    for (int m = 2; c < z_limit; m++)
    {
        for (int n = 1; n < m; n++)
        {
            c = m * m + n * n;
            if (c > z_limit)
            {
                break;
            }

            int a = m * m - n * n;
            int b = 2 * m * n;
            writeInteger(a);
            writeChar(' ');
            writeInteger(b);
            writeChar(' ');
            writeInteger(c);
            writeChar(10);
        
            count++;
        }
    }

    return count;
}

int main ()
{
    int limit = readInteger();
    writeInteger(generate(limit));
    return 0;
}