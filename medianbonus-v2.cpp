#include <iostream>
#include <queue>
using namespace std;

struct node
{
    int value;
    int index;
};

struct cmp1
{
    bool operator()(const node a, const node b)
    {
        return a.value > b.value;
    }
};

struct cmp2
{
    bool operator()(const node a, const node b)
    {
        return a.value < b.value;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, k;
    cin >> n >> k;
    int e[n];
    for (int i = 0; i < n; i++)
        cin >> e[i];
    priority_queue<node, vector<node>, cmp2> maxheap;
    priority_queue<node, vector<node>, cmp1> minheap;
    for (int i = 0; i < k; i++)
    {
        node newelement;
        newelement.value = e[i];
        newelement.index = i;
        maxheap.push(newelement);
        node exchange = maxheap.top();
        minheap.push(exchange);
        maxheap.pop();
        if (maxheap.size() <= minheap.size())
        {
            node exchange2 = minheap.top();
            minheap.pop();
            maxheap.push(exchange2);
        }
        if (i == k-1)
            cout << maxheap.top().value << " ";
    }
    for (int j = k; j < n; j++)
    {
        node newelement;
        newelement.value = e[j];
        newelement.index = j;
        maxheap.push(newelement);
        node exchange = maxheap.top();
        minheap.push(exchange);
        maxheap.pop();
        while(maxheap.top().index<j-k)
			maxheap.pop(); 
        int key = maxheap.top().value;
        if (e[j - k] <= key)
        {
            while (minheap.top().index <= j - k)
                minheap.pop();
            node exchange2 = minheap.top();
            maxheap.push(exchange2);
            minheap.pop();
        }
        cout << maxheap.top().value << " ";
    }
    return 0;
}
