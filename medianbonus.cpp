#include <iostream>
using namespace std;

static int maxheap_size = 0;
static int minheap_size = 0;

void heapinsert_maxheap(int maxheap[], int x)
{
    maxheap_size++;
    maxheap[maxheap_size] = x;
    int idx = maxheap_size;
    while (idx > 1 && maxheap[idx / 2] < maxheap[idx])
    {
        int temp = maxheap[idx];
        maxheap[idx] = maxheap[idx / 2];
        maxheap[idx / 2] = temp;
        idx = idx / 2;
    }
}

void maxheapify(int maxheap[], int idx)
{
    int idx_l = 2 * idx;
    int idx_r = 2 * idx + 1;
    int idx_max = (idx_l <= maxheap_size && maxheap[idx_l] > maxheap[idx]) ? idx_l : idx;
    idx_max = (idx_r <= maxheap_size && maxheap[idx_r] > maxheap[idx_max]) ? idx_r : idx_max;
    if (idx_max != idx)
    {
        int temp = maxheap[idx];
        maxheap[idx] = maxheap[idx_max];
        maxheap[idx_max] = temp;
        maxheapify(maxheap, idx_max);
    }
}

int maxextractmax(int maxheap[])
{
    int max_item = maxheap[1];
    maxheap[1] = maxheap[maxheap_size];
    maxheap_size--;
    maxheapify(maxheap, 1);
    return max_item;
}

void heapinsert_minheap(int minheap[], int x)
{
    minheap_size++;
    minheap[minheap_size] = x;
    int idx = minheap_size;
    while (idx > 1 && minheap[idx / 2] > minheap[idx])
    {
        int temp = minheap[idx];
        minheap[idx] = minheap[idx / 2];
        minheap[idx / 2] = temp;
        idx = idx / 2;
    }
}

void minheapify(int minheap[], int idx)
{
    int idx_l = 2 * idx;
    int idx_r = 2 * idx + 1;
    int idx_min = (idx_l <= minheap_size && minheap[idx_l] < minheap[idx]) ? idx_l : idx;
    idx_min = (idx_r <= minheap_size && minheap[idx_r] < minheap[idx_min]) ? idx_r : idx_min;
    if (idx_min != idx)
    {
        int temp = minheap[idx];
        minheap[idx] = minheap[idx_min];
        minheap[idx_min] = temp;
        minheapify(minheap, idx_min);
    }
}

int minextractmin(int minheap[])
{
    int min_item = minheap[1];
    minheap[1] = minheap[minheap_size];
    minheap_size--;
    minheapify(minheap, 1);
    return min_item;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, k;
    cin >> n >> k;
    int e[n + 1];
    for (int i = 1; i <= n; i++)
        cin >> e[i];
    int maxheap[n + 1];
    int minheap[n + 1];
    for (int i = 1; i <= k; i++)
    {
        heapinsert_maxheap(maxheap, e[i]);
        int exchange = maxextractmax(maxheap);
        heapinsert_minheap(minheap, exchange);
        if (maxheap_size <= minheap_size)
        {
            int exchange2 = minextractmin(minheap);
            heapinsert_maxheap(maxheap, exchange2);
        }
        if (i == k)
            cout << maxheap[1] << " ";
    }
    for (int j = k + 1; j <= n; j++)
    {
        heapinsert_maxheap(maxheap, e[j]);
        int exchange = maxextractmax(maxheap);
        heapinsert_minheap(minheap, exchange);
        int key=maxheap[1];
        if(e[j-k]<=key){
            int exchange2 = minextractmin(minheap);
            heapinsert_maxheap(maxheap, exchange2);
        }
        cout<<maxheap[1]<<" ";
    }
    return 0;
}
