#include <iostream>
using namespace std;

double dp[101][100001] = {0};

int main()
{
    int n;
    cin >> n;
    int a[n + 1], b[n + 1];
    int sumb = 0; //record sum b1
    double suma = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i] >> a[i];
        sumb += b[i];
        suma += a[i];
    }
    dp[0][0] = suma / 2;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j > 0; j--) //update
        {
            for (int k = sumb; k > 0; k--)
            {
                double temp = dp[j - 1][k - b[i]] + (double)a[i] / 2;
                if (k >= b[i])
                    dp[j][k] = temp > dp[j][k] ? temp : dp[j][k];
            }
        }

        /*for(int j =1;j<=2;j++){
            for(int k =1;k<=5;k++)
                cout<<dp[j][k]<<" ";
            cout<<endl;
        }*/
    }
    for (int k = 1; k <= n; k++)
    {
        double kmax = 0;
        for (int maxsum = 1; maxsum <= sumb; maxsum++)
        {
            double tempmax = dp[k][maxsum] < (double)maxsum ? dp[k][maxsum] : (double)maxsum;
            kmax = tempmax > kmax ? tempmax : kmax;
        }
        cout << kmax << endl;
    }
    return 0;
}