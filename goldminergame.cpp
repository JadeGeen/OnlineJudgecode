#include <iostream>
using namespace std;

static int subset[3000][3000] = {0};

void findsubset(int start, int end, int depth)
{
    int mid = (start + end) / 2;
    int index = 8 * depth;

    //规模为1
    if (start == end)
        return;

    //规模为2
    if (end - start == 1)
    {
        int i_x1; //寻找右上X的起始存储位置
        for (i_x1 = 0; i_x1 < 3000; i_x1++)
            if (subset[index][i_x1] == 0)
                break;
        subset[index][i_x1] = start;

        int i_y1; //寻找右上Y的起始存储位置
        for (i_y1 = 0; i_y1 < 3000; i_y1++)
            if (subset[index + 1][i_y1] == 0)
                break;
        subset[index + 1][i_y1] = end;
        return;
    }


    int i_x1; //寻找右上X的起始存储位置
    for (i_x1 = 0; i_x1 < 3000; i_x1++)
        if (subset[index][i_x1] == 0)
            break;
    for (int i = start; i < mid; i++, i_x1++)
        subset[index][i_x1] = i;

    int i_y1; //寻找右上Y的起始存储位置
    for (i_y1 = 0; i_y1 < 3000; i_y1++)
        if (subset[index + 1][i_y1] == 0)
            break;
    for (int i = mid + 1; i <= end; i++, i_y1++)
        subset[index + 1][i_y1] = i;

    int i_x2; //寻找左下X的起始存储位置
    for (i_x2 = 0; i_x2 < 3000; i_x2++)
        if (subset[index + 2][i_x2] == 0)
            break;
    for (int i = mid + 1; i <= end; i++, i_x2++)
        subset[index + 2][i_x2] = i;

    int i_y2; //寻找左下Y的起始存储位置
    for (i_y2 = 0; i_y2 < 3000; i_y2++)
        if (subset[index + 3][i_y2] == 0)
            break;
    for (int i = start; i < mid; i++, i_y2++)
        subset[index + 3][i_y2] = i;

    int i_x3; //寻找十字架竖行X的起始存储位置
    for (i_x3 = 0; i_x3 < 3000; i_x3++)
        if (subset[index + 4][i_x3] == 0)
            break;
    for (int i = start; i <= end; i++)
    {
        if (i == mid || i == mid + 1)
            continue;
        subset[index + 4][i_x3] = i;
        i_x3++;
    }

    int i_y3; //寻找十字架竖行Y的起始存储位置
    for (i_y3 = 0; i_y3 < 3000; i_y3++)
        if (subset[index + 5][i_y3] == 0)
            break;
    subset[index + 5][i_y3] = mid;

    int i_x4; //寻找十字架横行X的起始存储位置
    for (i_x4 = 0; i_x4 < 3000; i_x4++)
        if (subset[index + 6][i_x4] == 0)
            break;
    subset[index + 6][i_x4] = mid;

    int i_y4; //寻找十字架横行Y的起始存储位置
    for (i_y4 = 0; i_y4 < 3000; i_y4++)
        if (subset[index + 7][i_y4] == 0)
            break;
    for (int i = start; i <= end; i++)
    {
        if (i == mid - 1 || i == mid)
            continue;
        subset[index + 7][i_y4] = i;
        i_y4++;
    }

    findsubset(start, (start + end) / 2 - 1, depth + 1);
    findsubset((start + end) / 2 + 1, end, depth + 1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    findsubset(1, n, 0);
    for (int i = 0; i < 3000; i++)
    {
        if (subset[i][0] == 0)
            continue;
        for (int j = 0; j < 3000; j++)
        {
            if (subset[i][j] == 0)
                break;
            cout << subset[i][j] << " ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}
