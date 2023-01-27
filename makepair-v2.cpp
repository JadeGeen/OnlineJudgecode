#include <iostream>
#include <queue>
using namespace std;

void maxheapify(long long maxheap[], long long idx, long long maxheap_size)
{
    long long idx_l = 2 * idx;
    long long idx_r = 2 * idx + 1;
    long long idx_max = (idx_l <= maxheap_size && maxheap[idx_l] > maxheap[idx]) ? idx_l : idx;
    idx_max = (idx_r <= maxheap_size && maxheap[idx_r] > maxheap[idx_max]) ? idx_r : idx_max;
    if (idx_max != idx)
    {
        long long temp = maxheap[idx];
        maxheap[idx] = maxheap[idx_max];
        maxheap[idx_max] = temp;
        maxheapify(maxheap, idx_max, maxheap_size);
    }
}

long long maxextractmax(long long maxheap[], long long maxheap_size)
{
    long long max_item = maxheap[1];
    maxheap[1] = maxheap[maxheap_size];
    maxheap_size--;
    maxheapify(maxheap, 1, maxheap_size);
    return max_item;
}

void buildmaxheap(long long data[], long long heap_size)
{
    for (int i = heap_size / 2; i >= 1; i--)
    {
        maxheapify(data, i, heap_size);
    }
}

void heapsort(long long data[], long long heap_size)
{
    buildmaxheap(data, heap_size);
    for (long long i = heap_size; i >= 2; i--)
    {
        long long cur_max = maxextractmax(data, i);
        data[i] = cur_max;
    }
}

long long checkcount(long long value, long long a[], long long b[], long long n)
{
    long long count = 0;
    long long i = 1, j = n;
    while (i <= n && j >= 1)
    {
        if (a[i] + b[j] <= value)
        {
            count += j;
            i++;
        }
        else
            j--;
    }
    return count;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    long long n, k;
    cin >> n >> k;
    long long a[n + 1], b[n + 1];
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    heapsort(a, n);
    heapsort(b, n);
    long long left = a[1] + b[1];
    long long right = a[n] + b[n];
    while (left < right)
    {
        long long mid = (left + right) / 2;
        if (checkcount(mid, a, b, n) < k)
        {
            left = mid+1;
        }
        else
        {
            right = mid;
        }
    }
    cout << left;
    return 0;
}
