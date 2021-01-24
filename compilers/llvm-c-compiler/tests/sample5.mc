extern void writeInteger(int);
extern void writeChar(char);
extern int readInteger();

void permute(int arr[1024], int size, int N) 
{ 
    if (size == 1) 
    { 
        for (int i = 0; i < N; i++)
        {
            int value = arr[i];
            writeInteger(value);
            writeChar(' ');
        }
        writeChar(10);
    }
    else
    {
        for (int i = 0; i < size; i++) 
        { 
            permute(arr, size - 1, N); 
    
            if (size%2==1)
            {
                int temp = arr[0];
                arr[0] = arr[size - 1];
                arr[size - 1] = temp;
            }
            else
            {
                int temp = arr[i];
                arr[i] = arr[size - 1];
                arr[size - 1] = temp;
            }
        }    
    }
} 

void main ()
{
    // writeString("Please enter N: ");
    int N;
    N = readInteger();

    int arr[1024];
    for (int i = 0; i < N; i++)
    {
        arr[i] = i;
    }

    permute(arr, N, N);
}