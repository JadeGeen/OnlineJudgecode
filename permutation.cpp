#include <iostream>
#include <algorithm>
#include <queue>
#include <string.h>
#include <stack>
#include <assert.h>
using namespace std;

struct LR
{
    int L;
    int R;
};

bool cmp(LR a, LR b) { return a.L < b.L; }

struct cmp1
{
    bool operator()(const LR a, const LR b)
    {
        return a.R > b.R;
    }
};

struct edge
{
    int u, next;
};
edge e[100020];
int idx = 0;
int link[100020] = {0};
int indegree[100020] = {0}; //save indegree
int topo[100000] = {0};     //save topo order

bool dfstopo(int n)
{
    stack<int> s;
    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] != -1)
            count++;
        if (indegree[i] == 0)
            s.push(i);
    }
    int j = 0;
    while (!s.empty())
    {
        topo[j] = s.top();
        s.pop();
        for (int i = link[topo[j]]; i != 0; i = e[i].next)
        {
            int temp = e[i].u;
            indegree[temp]--;
            if (indegree[temp] == 0)
                s.push(temp);
        }
        j++;
    }
    if (j != count)
        return false;
    else
        return true;
}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n, m;
        cin >> n >> m;
        LR set[n];
        for (int j = 0; j < n; j++)
        {
            int l, r;
            cin >> l >> r;
            set[j].L = l;
            set[j].R = r;
        }

        bool OK = true;

        if (m != 0)
        {
            memset(link, 0, (n + 1) * sizeof(int));
            memset(indegree, -1, (n + 1) * sizeof(int));
            memset(topo, 0, (n + 1) * sizeof(int));
            idx = 0;
            memset(e, 0, (m + 1) * sizeof(edge));

            for (int j = 0; j < m; j++)
            {
                int u, v;
                cin >> u >> v;
                e[++idx] = {u, link[v]};
                link[v] = idx; // insert(v,u)
                if (indegree[v] == -1)
                    indegree[v] = 0;
                if (indegree[u] == -1)
                    indegree[u] = 1;
                else
                    indegree[u]++;
            }
            OK = dfstopo(n);
            for (int j = 0; topo[j] != 0; j++)
            {
                if (!OK)
                    break;
                int temp = link[topo[j]];
                for (int k = temp; k != 0; k = e[k].next)
                {
                    int ver = e[k].u - 1;
                    int val = set[topo[j] - 1].R - 1;
                    set[ver].R = set[ver].R > val ? val : set[ver].R;
                    if (set[ver].R < set[ver].L)
                    {
                        OK = false;
                        break;
                    }
                }
            }
        }
        if (OK)
        {
            sort(set, set + n, cmp);
            priority_queue<LR, vector<LR>, cmp1> q;
            int R = 0;
            for (int j = 1; j <= n; j++)
            {
                for (; R < n; R++)
                {
                    if (set[R].L > j)
                        break;
                    else
                        q.push(set[R]);
                }
                if (q.empty())
                {
                    OK = false;
                    break;
                }
                LR temp = q.top();
                q.pop();
                if (temp.L > j || temp.R < j)
                {
                    OK = false;
                    break;
                }
            }
        }
        if (OK)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
