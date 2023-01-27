#include <iostream>
#include <assert.h>
using namespace std;

struct Node
{
    int flag;
    Node *father;
};

Node *map[51][100001] = {NULL};
Node *father[100000]={NULL};
int index = 2;

Node *find(Node *node)
{
    //assert(node!=NULL);
    //cout<<"flag:"<<node->flag<<endl;
	if (node->father == NULL)
        return node;
    else return find(node->father);
}

void compress(Node *&node,Node *des)
{
    if(node->father->flag==des->flag)
        return;
    Node*p=node->father;
    node->father=des;
    compress(p,des);
}

bool check(Node *&node1, Node *&node2)
{
    if(node1==NULL||node2==NULL)return false;
    Node* temp1=find(node1);
    Node* temp2=find(node2);
    compress(node1,temp1);
    compress(node2,temp2);
	return temp1->flag == temp2->flag; 
}

void unionupdate(Node *father, Node *&node2)
{
    assert(father!=NULL||node2!=NULL);
	Node *father2 = find(node2);
    compress(node2,father2);
    if (father2->flag != father->flag)
        father2->father = father;
}

void makeset(int x1, int y1, int x2, int y2)
{
    father[index] = (Node *)new Node;
    father[index]->father = NULL;
    father[index]->flag = index;
	for (int i = x1; i <= x2; i++)
    {
        for (int j = y1; j <= y2; j++)
        {
			if(map[i][j]==NULL) map[i][j]=(Node*)new Node;
			map[i][j]->father = father[index];
            map[i][j]->flag = 1;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int opt, x1, y1, x2, y2;
        cin >> opt >> x1 >> y1 >> x2 >> y2;
        switch (opt)
        {
        case 0:
        {
            int min_x = min(x1, x2);
            int min_y = min(y1, y2);
            int max_x = max(x1, x2);
            int max_y = max(y1, y2);
            makeset(min_x, min_y, max_x, max_y);
			
			/*for(int k =1;k<=8;k++)
        	{
        		for (int j =1;j<=8;j++){
        			if(map[k][j]!=NULL)
            			cout<<find(map[k][j])->flag;
            		else
            			cout<<0;
				}
				cout<<endl;
			}*/
			        
            for (int k = min_x; k <= max_x; k++)
            {
                if (map[k][min_y - 1]!=NULL&&min_y - 1 > 0)
                    if (map[k][min_y - 1]->flag == 1)
                    {
                        unionupdate(father[index], map[k][min_y - 1]);
                    }
                if (map[k][max_y + 1]!=NULL&&max_y + 1 <= 100000)
                    if (map[k][max_y + 1]->flag == 1)
                    {
                        unionupdate(father[index], map[k][max_y + 1]);
                    }
            }
            for (int k = min_y; k <= max_y; k++)
            {
                if (map[min_x - 1][k]!=NULL&&min_x - 1 > 0)
                    if (map[min_x - 1][k]->flag == 1)
                    {
                        unionupdate(father[index], map[min_x - 1][k]);
                    }
                if (map[max_x + 1][k]!=NULL&&max_x + 1 <= 50)
                    if (map[max_x + 1][k]->flag == 1)
                    {
                        unionupdate(father[index], map[max_x + 1][k]);
                    }
            }
            index++;
            break;
        }

        case 1:
        {
            bool x = check(map[x1][y1], map[x2][y2]);
            if (x)
                cout << 1 << endl;
            else
                cout << 0 << endl;
            break;
        }
        default:
            break;
        }
    }
    return 0;
}