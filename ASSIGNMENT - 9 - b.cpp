/*                      UNLIMITED POWER
    AUTHOR  : R.Neel Prabhanjan
    PURPOSE : Program to find the maximum power that can be gained by choosing a sequence of infinity stones.
    DATE    : 12-4-22 - TUESDAY
    TIME-TAKEN : 5 hrs.
*/

#include<iostream>
using namespace std;

//Global 2-D array to store the maxpowerup of the subarray(i,j).
int powerup[102][102];

//Function to find the maximum powerup of the subarray(i,j).
int power(int i , int j , int* a)
{
    if(i>j) return 0;
    if(i==j || powerup[i][j]!=-1) return powerup[i][j];
    
    for(int l=i ; l<j+1 ; l++)
    {
        powerup[i][j]=max(powerup[i][j],power(i,l-1,a)+power(l+1,j,a)+a[i-1]*a[l]*a[j+1]);
    }

    return powerup[i][j];
}

int main()
{
    int n;
    int i,j,k;

    cin >> n;
    int a[n+2];
    for(i=0 ; i<n+2 ; i++)
    {
        if(i==0 || i==n+1) a[i]=1;
        else cin >> a[i];
    }

    int target;
    cin >> target;

    //Initializing the powerup array.
    for(i=1 ; i<n+1 ; i++)
    {
        for(j=1 ; j<n+1 ; j++)
        {
            if(i!=j) powerup[i][j]=-1;
            else powerup[i][j]=a[i-1]*a[i]*a[i+1];
        }
    }

    int maxpower=power(1,n,a);
    cout << maxpower << endl;
    if(maxpower>=target) cout << "YES" << endl;
    else cout << "NO" << endl;
}