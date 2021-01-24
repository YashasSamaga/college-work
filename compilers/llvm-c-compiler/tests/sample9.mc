extern void writeInteger(int);
extern void writeString(char[]);
extern int readInteger();

void main ()
{
    // writeString("Please enter dimensions (M, N): ");
    int M;
    int N;
    M = readInteger();
    N = readInteger();

    int A[1024];
    // writeString("Please enter matrix A: ");
    for (int i = 0; i < M * N; i++)
    {
        A[i] = readInteger();
    }

    int B[1024];
    // writeString("Please enter matrix B: ");
    for (int i = 0; i < M * N; i++)
    {
        B[i] = readInteger();
    }

    for (int i = 0; i < M * N; i++)
    {
        A[i] += B[i];
    }

    // writeString("Output matrix: ");
    for (int i = 0; i < M * N; i++)
    {
        writeInteger(A[i]);
        // writeString(" ");
    }
}