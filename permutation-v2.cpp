#include <iostream>
#include <algorithm>
#include <queue>
#include <string.h>
#include <vector>
#include <set>
using namespace std;

struct LR
{
    int L;
    int R;
    bool visited;
    int val;
    int oridx;
};

LR nset[100001];
LR *sortedidx[100001];
bool OK;
vector<vector<int>> limit;
set<int> nums;

bool cmp(LR a, LR b) { return a.L < b.L; }

bool cmp2(LR a, LR b) { return a.R < b.R; }

struct cmp1
{
    bool operator()(const LR a, const LR b)
    {
        return a.R > b.R;
    }
};

bool solve(LR *node, int idx);

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n, m;
        cin >> n >> m;
        bool OK = true;
        memset(nset, 0, (n + 1) * sizeof(LR));
        for (int j = 1; j <= n; j++)
        {
            int l, r;
            cin >> l >> r;
            nset[j].L = l;
            nset[j].R = r;
            nset[j].oridx = j; // for m!=0
            nset[j].val = -1;
            nset[j].visited = false;
        }
        if (m == 0)
        {
            sort(nset + 1, nset + n + 1, cmp);
            priority_queue<LR, vector<LR>, cmp1> q;
            int R = 1;
            for (int j = 1; j <= n; j++)
            {
                for (; R <= n; R++)
                {
                    if (nset[R].L > j)
                        break;
                    else
                        q.push(nset[R]);
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
        else
        {
            memset(sortedidx, 0, (n + 1) * sizeof(LR *));
            limit.clear();
            nums.clear();
            sort(nset + 1, nset + n + 1, cmp2);
            for (int j = 1; j <= n; j++)
            {
                sortedidx[nset[j].oridx] = &nset[j];
                nums.insert(j); // initial set
            }
            for (int j = 0; j <= n; j++)
            {
                vector<int> temp;
                temp.push_back(0);
                limit.push_back(temp);
                temp.clear();
            }
            for (int j = 0; j < m; j++)
            {
                int u, v;
                cin >> u >> v;
                limit[v].push_back(u);
            }
            for (int j = 1; j <= n; j++)
            {
                if (!nset[j].visited)
                {
                    OK = solve(sortedidx[nset[j].oridx], nset[j].oridx);
                    if (!OK)
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

bool solve(LR *node, int idx)
{
    node->visited = true;

    bool temp = true;
    int inf = node->L;
    for (int i = 1; i < limit[idx].size(); i++)
    {
        if (!sortedidx[limit[idx][i]]->visited)
            temp = solve(sortedidx[limit[idx][i]], limit[idx][i]);
        if (temp == false)
            return false;
        if (sortedidx[limit[idx][i]]->val == -1)
            return false;
        int tempval = sortedidx[limit[idx][i]]->val;
        inf = inf > tempval + 1 ? inf : tempval + 1;
        if (inf > node->R)
            return false;
    }
    set<int>::iterator newval; //利用set取下界，舍友教的谢谢舍友
    newval = nums.lower_bound(inf);
    if (newval == nums.end() || *newval > node->R)
        return false;
    node->val = *newval;
    nums.erase(newval);
    return true;
}