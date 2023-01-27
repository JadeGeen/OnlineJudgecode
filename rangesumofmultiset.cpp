#include <iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

struct Node
{
    long long value;
    double priority;
    long long leftsize;
    long long rightsize;
    long long samecount;
    Node *left;
    Node *right;
};

void leftrotation(Node* &node)
{
    Node *temp = node->right;
    node->rightsize-=temp->value*temp->samecount + temp->rightsize;
    temp->leftsize+=node->value*node->samecount + node->leftsize;
    node->right = temp->left;
    temp->left = node;
    node = temp;
}

void rightrotation(Node* &node)
{
    Node *temp = node->left;
    node->leftsize-=temp->value*temp->samecount + temp->leftsize;
    temp->rightsize+=node->value*node->samecount + node->rightsize;
    node->left = temp->right;
    temp->right = node;
    node = temp;
}

void treapinsert(Node* &node, long long value, double priority)
{
    if (node == NULL)
    {
        node = (Node *)new Node;
        node->left = NULL;
        node->right = NULL;
        node->value = value;
        node->priority = priority;
        node->leftsize=0;
        node->rightsize=0;
        node->samecount=1;
    }
    else if(node->value==value)
    	node->samecount+=1;
    else if (node->value > value)
    {
        node->leftsize+=value;
		treapinsert(node->left, value, priority);
        if (node->left->priority > node->priority)
            rightrotation(node);
    }
    else
    {
        node->rightsize+=value;
		treapinsert(node->right, value, priority);
        if (node->right->priority > node->priority)
            leftrotation(node);
    }
}

void treapdel(Node* &node, long long value)
{
    if (node != NULL)
    {
        if (node->value > value)
        {
        	node->leftsize-=value;
			treapdel(node->left, value);
    	}    
        else if (node->value < value)
        {
			node->rightsize-=value;  
			treapdel(node->right, value);
		}
        else
        {
        	if(node->samecount>1){
        		node->samecount--;
        		return;
			}
            if (node->left == NULL)
                node = node->right;
            else if (node->right == NULL)
                node = node->left;
            else
            {
                if (node->left->priority < node->right->priority)
                {
                    leftrotation(node);
                    node->leftsize-=value;
                    treapdel(node->left, value);
                }
                else
                {
                    rightrotation(node);
                    node->rightsize-=value;
                    treapdel(node->right, value);
                }
            }
        }
    }
}

long long valuecount(Node *node, long long value)
{
    if (node == NULL)
        return 0;
    if (node->value == value)
		return node->samecount;
    else if (node->value > value)
        return valuecount(node->left, value);
    else
        return valuecount(node->right, value);
}

long long sumcompute(Node *node, long long left, long long right)
{
    if (node == NULL)
        return 0;
    long long sum = 0;
    if (node->value > left && node->value <= right)
    {
        sum += node->value*node->samecount;
        if(node->right!=NULL){
        	if(node->right->value<=right)
        		sum+=node->rightsize - node->right->rightsize + sumcompute(node->right->right, left, right);
        	else 
        		sum+=sumcompute(node->right->left,left,right);	
		}
        if(node->left!=NULL){
        	if(node->left->value>left)
        		sum+=node->leftsize - node->left->leftsize + sumcompute(node->left->left, left, right);
        	else
        		sum+=sumcompute(node->left->right,left,right);
		}    
    }
    else if (node->value <= left)
        sum += sumcompute(node->right, left, right);
    else
        sum += sumcompute(node->left, left, right);
    return sum;
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    Node *root=NULL;
    srand(time(0));
    long long q, mod;
    cin >> q >> mod;
    long long lans = 0;
    for (long long i = 0; i < q; i++)
    {
        int op;
        long long val1, val2;
        double priority;
        long long count;
        cin >> op >>val1;
        val1=(val1+lans)%mod;
        switch (op)
        {
        case 0:
            priority=rand()/rand();
            treapinsert(root,val1,priority);
            //cout<<"insert "<<val1<<endl;
            break;
        case 1:
            count=valuecount(root,val1);
            if(count>0)
            	treapdel(root,val1);
            //cout<<val1<<" is "<<count<<endl;
            cout<<count<<endl;
            break;
        case 2:
            cin>>val2;
            val2=(val2+lans)%mod;
            if(val1>val2)
                count=sumcompute(root,val2,val1);
            else
                count=sumcompute(root,val1,val2);
            lans=count;
            //cout<<"sum and new lans is "<<count<<endl;
            cout<<count<<endl;
            break;
        default:
            break;
        }
    }
    return 0;
}