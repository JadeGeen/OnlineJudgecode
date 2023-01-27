#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    unordered_map<long long, long long> hashtable;
    unordered_map<long long, long long>::const_iterator ht;
    long long n;
    cin >> n;
    string* str = new string[n];
    long long* index = new long long[n] {0};
    long long count = 0;
    for (long long i = 0; i < n; i++)
    {
        cin >> str[i];
        long long len = str[i].length();
        for (long long j = 0; j < len; j++)
        {
            long long temp = str[i][j] - 'a';
            index[i] = (1 << temp) ^ index[i];
        }
        ht = hashtable.find(index[i]);
        if (ht == hashtable.end())
            hashtable.insert(std::make_pair(index[i], 1));
        else
            hashtable.at(index[i]) += 1;
    }
    unordered_map<long long, long long>::const_iterator check;

    for (long long i = 0; i < n; i++)
    {
        long long counti = 0;
        check = hashtable.find(index[i]);
        counti += check->second-1;
        long long temp1 = index[i];
        unordered_map<long long, long long>::const_iterator check2;
        for (long long j = 0; j < 26; j++)
        {
            long long temp2 = (1 << j) ^ temp1;
            check2 = hashtable.find(temp2);
            if (check2 != hashtable.end())
                counti += check2->second;
        }
        count += counti;
    }
    cout << count /2 << endl;
    delete[]str;
    delete[]index;
    str = NULL;
    index = NULL;
    return 0;
}
