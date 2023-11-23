/*                  IMPLEMENTATION OF DICTIONARY CLASS
    AUTHOR  : R.Neel Prabhanjan
    PURPOSE : Program to implement dictionary class and perform certain functions.
    DATE    : 15-03-22 - TUESDAY
    TIME-TAKEN : 3 hrs.
*/

#include<iostream>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
using namespace std;

class Dictionary
{
private :
    map<int,vector<string>>dict;

public :
    // Initializing the dictionary.
    void buildDict(vector<string>words)
    {
        vector<string>::iterator i;

        for(i=words.begin() ; i!=words.end() ; i++)
        {
            int len=(*i).length();
            dict[len].push_back(*i);
        }
    }

    // Adding word to dictionary.
    void addWordToDict(string word)
    {
        dict[word.length()].push_back(word);
    }

    // Searching the target string in the dictionary.
    bool search(string target)
    {
        int len=target.length();

        map<int,vector<string>>::iterator itr;

        itr=dict.find(len);

        if(itr==dict.end()) return false;

        for(auto i=(itr->second).begin() ; i!=(itr->second).end() ; i++)
        {
            if((*i)==target) return true;
        }

        return false;
    }

    // Returns set of adjacent words.
    set<string> getWordsAfterReplace(string target)
    {
        set<string>words;

        int len=target.length();

        map<int,vector<string>>::iterator itr;
        vector<string>::iterator i;

        itr=dict.find(len);

        if(itr==dict.end()) return words;

        for(i=(itr->second).begin() ; i!=(itr->second).end() ; i++)
        {
            int nmatches=0;

            for(int j=0 ; j<len ; j++)
                {
                    string w=*i;
                    if(w[j]!=target[j]) nmatches++;
                }
                if(nmatches<=1) words.insert(*i);
        }

        return words;
    }

    // Returns set of words which are obtained by swapping adjacent letters.
    set<string> getWordsAfterSwap(string target)
    {
        set<string>words;
        int len=target.length();

        string rword=target;
        for(int i=0 ; i<len-1 ; i++)
        {
            char t=rword[i];
            rword[i]=rword[i+1];
            rword[i+1]=t;

            if(search(rword)) words.insert(rword);
            rword=target;
        }

        return words;
    }

    // Returns the maximum number of distinct adjacent words any dictionary word may have.
    int maxChangeableWord()
    {
        set<string>words;
        int maxi=0;
        map<int,vector<string>>::iterator itr;
        vector<string>::iterator i,j;

        for(itr=dict.begin() ; itr!=dict.end() ; itr++)
        {
            for(i=(itr->second).begin() ; i<(itr->second).end() ; i++)
            {
                words=getWordsAfterReplace((*i));

                if(words.size()-1>maxi) maxi=words.size()-1;
            }
        }

        return maxi;
    }

    // Returns the maximum number of times a dictionary word can distinctly occur in a dictionary after swapping characters in one adjacent position from it.
    int maxSwappableWord()
    {
        set<string>words;
        int maxi=0;
        map<int,vector<string>>::iterator itr;
        vector<string>::iterator i,j;

        for(itr=dict.begin() ; itr!=dict.end() ; itr++)
        {
            for(i=(itr->second).begin() ; i<(itr->second).end() ; i++)
            {
                words=getWordsAfterSwap((*i));

                if(words.size()>maxi) maxi=words.size();
            }
        }

        return maxi;
    }
};

int main()
{
    int N,Q;
    int i,j,k;

    cin >> N;

    Dictionary dict;

    vector<string>words;

    for(i=0 ; i<N ; i++)
    {
        string word;
        cin >>word;
        words.push_back(word);
    }

    cin >> Q;

    dict.buildDict(words);

    while(Q--)
    {
        int query;
        cin >> query;

    switch(query)
    {
    case 1 :
        {
            string word;
            cin >> word;

            dict.addWordToDict(word);

            break;
        }

    case 2 :
        {
            string word;
            cin >> word;

            if(dict.search(word)) cout << "true" << endl;
            else cout << "false" << endl;

            break;
        }

    case 3 :
        {
            string word;
            cin >> word;

            set<string>words;
            words=dict.getWordsAfterReplace(word);

            if(words.size()==0) cout << -1 << endl;

            else
            {
                set<string>::iterator itr;

                for(itr=words.begin() ; itr!=words.end() ; itr++)
                {
                    cout << *itr << " ";
                }
                cout << endl;
            }

            break;
        }

        case 4 :
        {
            string word;
            cin >> word;

            set<string>words;
            words=dict.getWordsAfterSwap(word);

            if(words.size()==0) cout << -1 << endl;

            else
            {
                set<string>::iterator itr;

                for(itr=words.begin() ; itr!=words.end() ; itr++)
                {
                    cout << *itr << " ";
                }
                cout << endl;
            }

            break;
        }

        case 5 :
            {
                cout << dict.maxChangeableWord() << endl;

                break;
            }

        case 6 :
            {
                cout << dict.maxSwappableWord() << endl;

                break;
            }
        }
    }
    return 0;
}
