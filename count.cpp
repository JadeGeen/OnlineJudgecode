#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

using namespace std;

int bitcount(int val, int width)
{
    // cout<<val<<endl;
    int count = 0;
    unsigned int temp = 1;
    for (int i = 0; i < width; i++)
    {
        if ((val & temp) != 0)
            count++;
        temp = temp << 1;
    }
    return count;
}

int reverse(int val, int m)
{
    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        ans <<= 1;
        ans += ((val) & (1 << i)) ? 1 : 0;
    }
    return ans;
}

int graph[700][700] = {0}; //(x,y)：0，无穷；1，直接匹配；2，y需要reverse才能匹配x。
int color[700] = {0};      //染色：0未访问；1，该点未翻转；2，该点已翻转。
int bitstr[700] = {0};

bool initgraph(int n, int m, int k)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int count = bitcount(bitstr[i] & bitstr[j], m);
            // cout << "count=" << count << endl;
            int count_r = bitcount(bitstr[i] & reverse(bitstr[j], m), m);
            // cout << "count_r=" << count_r << endl;
            if (count < k && count_r < k)
                return false;
            else if (count >= k && count_r >= k)
                ;
            else if (count >= k && count_r < k)
            {
                graph[i][j] = 1;
                graph[j][i] = 1;
            }
            else if (count < k && count_r >= k)
            {
                graph[i][j] = 2;
                graph[j][i] = 2;
            }
            else
                assert(0);
        }
    }
    return true;
}

bool checkvert(int index, int n)
{
    bool ret = true;
    int curcolor = color[index]; //目前结点的染色
    int r_color;                 //异色
    if (curcolor == 1)
        r_color = 2;
    else
        r_color = 1;
    assert(curcolor != 0);

    int setcolor = 0; //根据边的种类，下一个结点的颜色
    for (int j = 0; j < n; j++)
    {
        if (graph[index][j] == 0) //不连通，跳过
            continue;
        else
        {
            if (graph[index][j] == 1) //同色
                setcolor = curcolor;
            else if (graph[index][j] == 2) //异色
                setcolor = r_color;
            else
                assert(0);
            if (color[j] == 0)
            {
                color[j] = setcolor;
                ret = checkvert(j, n);
                if (!ret)
                    return false;
            }
            else
            {
                if (color[j] != setcolor)
                {
                    ret = false;
                    return false;
                }
            }
        }
    }
    return ret;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int n, m, k;
        cin >> n >> m >> k;
        memset(bitstr, 0, 700 * sizeof(int));
        memset(graph, 0, 700 * 700 * sizeof(int));
        memset(color, 0, 700 * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            string s;
            cin >> s;
            bitstr[j] = stoi(s, 0, 2);
        }
        bool init = initgraph(n, m, k);
        unsigned int count = 0;
        if (init == 1)
        {
            for (int j = 0; j < n; j++)
            {
                if (color[j] == 0)
                {
                    color[j] = 1;
                    int ret = checkvert(j, n);
                    if (!ret)
                    {
                        count = 0;
                        break;
                    }
                    else
                        count++;
                }
            }
        }
        if (count == 0)
            cout << 0 << endl;
        else
        {
            long long ans = 1;
            for (unsigned int j = 0; j < count; j++)
            {
                ans <<= 1;
                ans %= 998244353;
            }
            cout << ans << endl;
        }
    }
    return 0;
}