extern void writeInteger(int);
extern void writeString(char[]);
extern int readInteger();

bool isPrime(int num)
{
    if (num == 1)
    {
        return false;
    }

    if (num == 2)
    {
        return true;
    }

    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}

int main ()
{
    int num = readInteger();
    writeInteger(isPrime(num));
    return 0;
}