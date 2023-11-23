/*                  CARGO LOADING PROCESS
    AUTHOR  : R.Neel Prabhanjan
    PURPOSE : Program to implement knapsack problem using abstract base class.
    DATE    : 19-4-22 - TUESDAY
    TIME-TAKEN : 45 min.
*/

#include<iostream>
using namespace std;

//Global arrays for weights and values.
int w[10000],v[10000];

//Abstract base class.
class baseknapsack
{
    public :

    int optimum,N;

    virtual void knapsackdp(int W , int n)=0;
};

//Derived class.
class knapsack : public baseknapsack
{
    public :

    //Knapsack solving function.
    void knapsackdp(int W , int n)
    {
        N=n;
        int k[W+1];
        k[0]=0;

        for(int i=1 ; i<W+1 ; i++)
        {
            k[i]=0;

            for(int j=0 ; j<N ; j++)
            {
                if(w[j]<=i) k[i]=max(k[i],k[i-w[j]]+v[j]);
            }
        }

        optimum=k[W];

        cout << optimum << endl;
    }
};

int main()
{
    int W,n;
    int i,j,k;

    cin >> W >> n;

    for(i=0 ; i<n ; i++)
    {
        cin >> v[i];
    }
    for(i=0 ; i<n ; i++)
    {
        cin >> w[i];
    }

    knapsack dp;

    dp.knapsackdp(W,n);

    return 0;
}