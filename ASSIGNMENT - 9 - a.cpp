/*                  APPROXIMATE SEARCH
    AUTHOR  : R.Neel Prabhanjan
    PURPOSE : Program to find the word of a sentence in the dictionary.
    DATE    : 11-4-22 - MONDAY
    TIME-TAKEN : 2.5 hrs.
*/

#include<bits/stdc++.h>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

//Global vector for storing longest common subsequences of each word of the sentence.
vector <string> lcs(100,"");

//Edit distance DP.
int edit(string word , string key)
{
    int m=word.length();
    int n=key.length();
    int E[m+1][n+1];

    for(int i=0 ; i<m+1 ; i++)
    {
        E[i][0]=i;
    }
    for(int i=1 ; i<n+1 ; i++)
    {
        E[0][i]=i;
    }

    for(int i=1 ; i<m+1 ; i++)
    {
        for(int j=1 ; j<n+1 ; j++)
        {
            int k=1;
            if(word[i-1]==key[j-1]) k=0;
            E[i][j]=min(E[i-1][j]+1,E[i][j-1]+1);
            E[i][j]=min(E[i][j],E[i-1][j-1]+k);
        }
    }

    return E[m][n];
}

//Longest Common Subsequence DP.
int LCSf(string word , string key , int l)
{
    int m=word.length(),n=key.length();
    int C[m+1][n+1];

    for(int i=0 ; i<m+1 ; i++)
    {
        C[i][0]=0;
    }
    for(int i=1 ; i<n+1 ; i++)
    {
        C[0][i]=0;
    }

    for(int i=1 ; i<m+1 ; i++)
    {
        for(int j=1 ; j<n+1 ; j++)
        {
            if(word[i-1]==key[j-1]) C[i][j]=C[i-1][j-1]+1;
            else C[i][j]=max(C[i][j-1],C[i-1][j]);
        }
    }

    string sent="";

    int i=m,j=n;
    while (i>0 && j>0)
    {
        if (word[i-1] == key[j-1]) {
            sent+=word[i-1];
            i--;
            j--;
        }

        else if (C[i-1][j]>C[i][j-1]) i--;
        else j--;
    }

        reverse(sent.begin(),sent.end());
        lcs[l]=sent;

    return C[m][n];
}

int main()
{
    int n,d;
    int i,j,k;

    cin >> n;

    vector <string> sentence;
    vector <string> dict;

    for(i=0 ; i<n ; i++)
    {
        string word;
        cin >> word;
        sentence.push_back(word);
    }

    cin >> d;

    for(i=0 ; i<d ; i++)
    {
        string word;
        cin >> word;
        dict.push_back(word);
    }

    int mined,maxLCS;

    for(i=0 ; i<n ; i++)
    {
        string word=sentence[i];

        vector <int> editdist;
        vector <int> LCS(d,-1);

        //Finding minimum edit distance out of the words of the sentence.
        for(j=0 ; j<d ; j++)
        {
            string key=dict[j];
            editdist.push_back(edit(word,key));
        }
        mined=*min_element(editdist.begin(),editdist.end());

        //Finding maxmimum LCS length among the equal minimum edit distances of the words of the sentence.
        for(j=0 ; j<d ; j++)
        {
            if(editdist[j]==mined)
            {
                string key=dict[j];
                LCS[j]=LCSf(word,key,j);
            }
            maxLCS=*max_element(LCS.begin(),LCS.end());
        }

        //Printing the words with least edit distance and maximum LCS length in required format. 
        for(j=0 ; j<d ; j++)
        {
            if(LCS[j]==maxLCS)
            {
                cout << word << endl;
                cout << dict[j] << endl;
                if(lcs[j]!="") cout << lcs[j] << endl;
                else cout << "EMPTY" << endl;
                cout << editdist[j] << endl;
            }
        }
        //Clearing the vector for usability of other words.
        lcs.clear();
    }

    return 0;
}
