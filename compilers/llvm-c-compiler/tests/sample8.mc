extern void writeInteger(int);
extern void writeString(char[]);
extern int readInteger();
 
int max_element(int arr[], int n) 
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
}

void main ()
{
    int N;
    N = readInteger();

    int arr[1024];
    for (int i = 0; i < N; i++)
    {
        arr[i] = readInteger();
    }

    //

    int max;
    max = max_element(arr, N); 
    for (int base = 1; max / base > 0; base *= 10)
    {
        int count[10];
        for (int i = 0; i < 10; i++)
        {
            count[i] = 0;
        } 
        
        for (int i = 0; i < N; i++)
        {
            count[(arr[i] / base) % 10]++; 
        }

        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1]; 
        }

        int temp[1024];
        for (int i = N - 1; i >= 0; i--) 
        { 
            int bin = (arr[i] / base) % 10;
            temp[count[bin] - 1] = arr[i]; 
            count[bin]--; 
        } 
        
        for (int i = 0; i < N; i++)
        {
            arr[i] = temp[i];
        }
    }

    //

    for (int i = 0; i < N; i++)
    {
        writeInteger(arr[i]);
        // writeString(" ");
    }
}