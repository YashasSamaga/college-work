void main ()
{
    int N;
    N = readInteger();

    int arr[1024];
    for (int i = 0; i < N; i++)
    {
        arr[i] = readInteger();
    }

    for (int i = 1; i < N; i++)
    {
        int key;
        key = arr[i];

        int j = i - 1;
        for (; j >= 0 && arr[j] > key; j--)
        {
            arr[j + 1] = arr[j];
        }

        arr[j + 1] = key;
    }

    for (int i = 0; i < N; i++)
    {
        writeInteger(arr[i]);
        writeString(" ");
    }
}