/*                  MATRIX OPERATIONS LAB-1
    AUTHOR  : R.Neel Prabhanjan
    PURPOSE : Program to implement classes for performing certain matrix operations.
    DATE    : 24-1-22 - MONDAY
    TIME-TAKEN : 5 hrs.
*/

#include<iostream>
using namespace std;

#define SIZE 1000000

class Matrix
{
private:

    int rows;
    int columns;
    int* mat;

public:

    Matrix()
    {
        rows=0;
        columns=0;

        mat=new int[SIZE];
    }

    Matrix(int nrows , int mcolumns)
    {
        rows=nrows;
        columns=mcolumns;
        mat=new int[rows*columns];

        for(int i=0 ; i<rows ; i++)
        {
            for(int j=0 ; j<columns ; j++)
            {
                mat[columns*i+j]=0;
            }
        }
    }

    Matrix(int nrows , int mcolumns , int* matrix)
    {
        rows=nrows;
        columns=mcolumns;
        mat=new int[rows*columns];

        for(int i=0 ; i<rows ; i++)
        {
            for(int j=0 ; j<columns ; j++)
            {
                mat[columns*i+j]=matrix[columns*i+j];
            }
        }
    }

    void setValue(int row , int col , int val)
    {
        mat[columns*row+col]=val;
    }

    int getValue(int row , int col)
    {
        return mat[columns*row+col];
    }

    int getNoRows()
    {
        return rows;
    }

    int getNoColumns()
    {
        return columns;
    }

    void printSpiral()
    {
        int r=rows;
        int c=columns;
        int i,j,k;
        int counter=0,e=rows*columns;


        for(i=0,j=0 ; i<r,j<c ; i++,j++,r--,c--)
        {
            for(k=j ; k<c && counter<e ; k++)
            {
                cout << mat[columns*i+k] << " ";
                counter++;
            }
            for(k=i+1 ; k<r-1 && counter<e ; k++)
            {
                cout << mat[columns*k+c-1] << " ";
                counter++;
            }
            for(k=c-1 ; k>=j && counter<e ; k--)
            {
                cout << mat[columns*(r-1)+k] << " ";
                counter++;
            }
            for(k=r-2 ; k>i && counter<e ; k--)
            {
                cout << mat[columns*k+j] << " ";
                counter++;
            }
        }

        cout << endl;
    }

    int trace()
    {
        if(rows!=columns) return -1;

        int trace=0;
        for(int i=0 ; i<rows ; i++)
        {
            trace+=mat[columns*i+i];
        }

        return trace;
    }

    bool checkTriangular()
    {
        if(rows!=columns) return false;
        int i,j,k,flag1=0,flag2=0;

        for(i=0,j=0 ; i<rows,j<columns ; i++,j++)
        {
            for(k=j+1 ; k<columns ; k++)
            {
                if(mat[columns*i+k]!=0)
                {
                    flag1=1;
                    break;
                }
            }
            if(flag1) break;
        }
        for(i=0,j=0 ; i<rows,j<columns ; i++,j++)
        {
            for(k=i+1 ; k<rows ; k++)
            {
                if(mat[columns*k+j]!=0)
                {
                    flag2=1;
                    break;
                }
            }
            if(flag2) break;
        }

        if(flag1 && flag2) return false;
        else return true;
    }

    bool isSpecialMatrix()
    {
        int i,j,k;
        int rsum[rows]={0},csum[columns]={0};
        for(int i=0 ; i<rows ; i++)
        {
            for(int j=0 ; j<columns ; j++)
            {
                rsum[i]+=mat[columns*i+j];
            }
        }
        for(int i=0 ; i<columns ; i++)
        {
            for(int j=0 ; j<rows ; j++)
            {
                csum[i]+=mat[columns*j+i];
            }
        }
        for(i=1 ; i<rows ; i++)
        {
            if(rsum[i]!=rsum[i-1]) return false;
        }
        for(i=1 ; i<columns ; i++)
        {
            if(csum[i]!=csum[i-1]) return false;
        }
        if(rsum[0]!=csum[0]) return false;
        else return true;
    }
};

int main()
{
    int n,m;
    int i,j,k;

    cin >> n >> m;

    int* a;
    a=new int[SIZE];

    for(i=0 ; i<n ; i++)
    {
        for(j=0 ; j<m ; j++)
        {
            cin >> a[m*i+j];
        }
    }

    Matrix M(n,m,a);

    int Q;
    cin >> Q;

    while(Q--)
    {
        int query;
        cin >> query;

        switch(query)
        {
        case 1 :
            {
                M.printSpiral();
                break;
            }

        case 2 :
            {
                cout << M.trace() << endl;
                break;
            }
        case 3 :
            {
                if(M.checkTriangular()) cout << "true" << endl;
                else cout << "false" << endl;
                break;
            }
        case 4 :
            {
                if(M.isSpecialMatrix()) cout << "true" << endl;
                else cout << "false" << endl;
                break;
            }
        }
    }

    return 0;
}
