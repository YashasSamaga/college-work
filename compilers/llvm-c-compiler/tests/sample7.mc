extern void writeInteger(int);
extern void writeString(char[]);
extern int readInteger();

void merge(int arr[], int l, int m, int r) 
{ 
    int left_size = m - l;
    int right_size = r - m;
  
    int left[1024];
    int right[1024]; 
  
    for (int i = 0; i < left_size; i++) 
    {
        left[i] = arr[l + i];
    }

    for (int i = 0; i < right_size; i++) 
    {
        right[i] = arr[l + i];
    }

    int i = 0;
    int j = 0; 
    int k = l; 
    while (i < left_size && j < right_size)
    {
        if (left[i] <= right[j])
        { 
            arr[k] = left[i]; 
            i++;
        }
        else
        {
            arr[k] = right[j]; 
            j++; 
        }
        k++; 
    } 
  

    while (i < left_size) { 
        arr[k] = left[i]; 
        i++; 
        k++; 
    } 
  
    while (j < right_size) { 
        arr[k] = right[j]; 
        j++; 
        k++; 
    } 
} 
  
// [left, right)
void mergeSplit(int arr[], int left, int right) 
{ 
    if (left < right)
    { 
        int mid;
        mid = (left + right) / 2; 
        mergeSplit(arr, left, mid); 
        mergeSplit(arr, mid, right); 
        merge(arr, left, mid, right); 
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

    mergeSplit(arr, 0, N);

    for (int i = 0; i < N; i++)
    {
        writeInteger(arr[i]);
        //writeString(" ");
    }
}