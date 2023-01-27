#include <iostream>
#include <queue>
using namespace std;

void maxheapify(int maxheap[], int idx, int maxheap_size)
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
        maxheapify(maxheap, idx_max, maxheap_size);
    }
}

int maxextractmax(int maxheap[], int maxheap_size)
{
    int max_item = maxheap[1];
    maxheap[1] = maxheap[maxheap_size];
    maxheap_size--;
    maxheapify(maxheap, 1, maxheap_size);
    return max_item;
}

void buildmaxheap(int data[], int heap_size)
{
    for (int i = heap_size / 2; i >= 1; i--)
    {
        maxheapify(data, i, heap_size);
    }
}

void heapsort(int data[], int heap_size)
{
    buildmaxheap(data, heap_size);
    for (int i = heap_size; i >= 2; i--)
    {
        int cur_max = maxextractmax(data, i);
        data[i] = cur_max;
    }
}

struct e
{
    int value;
    int ia;
    int ib;
    friend bool operator<(e a, e b)
    {
        return a.value > b.value;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, k;
    cin >> n >> k;
    int a[n + 1], b[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }
    heapsort(a, n);
    heapsort(b, n);
    priority_queue<e, deque<e>> q;
    if (k <= n)
    {
        for (int i = 1; i <= k; i++)
        {
            e newe;
            newe.value = a[i] + b[1];
            newe.ia = i;
            newe.ib = 1;
            q.push(newe);
        }
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            e newe;
            newe.value = a[i] + b[1];
            newe.ia = i;
            newe.ib = 1;
            q.push(newe);
        }
    }
    for (int i = 0; i < k; i++)
    {
        e temp = q.top();
        q.pop();
        if (i == k - 1)
        {
            cout << temp.value;
            break;
        }
        if (temp.ia > n || temp.ib + 1 > n)
            continue;
        e newe;
        newe.value = a[temp.ia] + b[temp.ib + 1];
        newe.ia = temp.ia;
        newe.ib = temp.ib + 1;
        q.push(newe);
    }
    return 0;
}