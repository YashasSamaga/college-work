extern void writeInteger(int);
extern void writeString(char[]);
extern int readInteger();

void main ()
{
    writeString("Please enter dimensions (M, K, N): ");
    int M;
    int K;
    int N;
    M = readInteger();
    K = readInteger();
    N = readInteger();

    int A[1024];
    // writeString("Please enter matrix A: ");
    for (int i = 0; i < M * K; i++)
    {
        A[i] = readInteger();
    }

    int B[1024];
    // writeString("Please enter matrix B: ");
    for (int i = 0; i < K * N; i++)
    {
        B[i] = readInteger();
    }

    int C[1024];
    for (int i = 0; i < M * N; i++)
    {
        C[i] = 0;
    }

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < K; k++)
            {
                C[i * N + j] += A[i * K + k] + B[k * N + j]; 
            }
        }
    }

    // writeString("Output matrix: ");
    for (int i = 0; i < M * N; i++)
    {
        writeInteger(C[i]);
        // writeString(" ");
    }
}