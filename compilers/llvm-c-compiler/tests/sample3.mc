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

int sumPrimes(int N)
{
    int accumulator = 0;
    for (int i = 1; i < N; i++)
    {
        if (isPrime(i))
        {
            accumulator += i;
        }
    }

    return accumulator;
}

int main ()
{
    int N = readInteger();
    writeInteger(sumPrimes(N));
    return 0;
}