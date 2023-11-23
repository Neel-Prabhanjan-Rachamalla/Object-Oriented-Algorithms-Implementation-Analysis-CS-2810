/*                  STRINGS AND STL
    AUTHOR  : R.Neel Prabhanjan
    PURPOSE : Program to replace strings with their given prefixes using TRIE.
    DATE    : 8-3-22 - TUESDAY
    TIME-TAKEN : 6 hrs.
*/

#include<iostream>
#include<vector>
#include<string.h>
using namespace std;

// NODE CLASS.
class Node
{
private :
    bool isEnd;
    vector <Node*> next;

public :
    Node()
    {
        isEnd=false;

        for(int i=0 ; i<26 ; i++)
        {
            next.push_back(NULL);
        }
    }

    // PRIVATE MEMBERS ACCESSING FUNCTIONS.
    bool getisEnd()
    {
        return isEnd;
    }
    void setisEnd(bool val)
    {
        isEnd=val;
    }
    Node* getvector(int i)
    {
        return next[i];
    }
    void setvector(int i,Node* node)
    {
        next[i]=node;
    }

};

// TRIE CLASS.
class TRIE
{
private :
    Node* root;

public :
    TRIE()
    {
        root=new Node();
    }

    Node* insertnode()
    {
        Node* newnode=new Node();
        return newnode;
    }

    // INSERTING A STRING INTO THE TRIE.
    void insert(string word)
    {
        Node* currnode=root;
        for(int i=0 ; i<word.length() ; i++)
        {
            if(currnode->getvector(word[i]-97)==NULL)
            {
                currnode->setvector(word[i]-97,insertnode());
            }
            currnode=currnode->getvector(word[i]-97);
        }
    }

    // FINDING A GIVEIN PREFIX IN THE TRIE.
    Node* findprefix(string prefix)
    {
        Node* node=root;

        for(int i=0 ; i<prefix.length() ; i++)
        {
            if(node->getvector(prefix[i]-97)==NULL) return NULL;
            else
            {
                node=node->getvector(prefix[i]-97);
            }
        }

        return node;
    }

    // REPLACING WORD.
    void replaceword(string prefix)
    {
        Node* node=findprefix(prefix);

        if(node==NULL) return;

        node->setisEnd(true);

        return;
    }

    // PRINTING THE WORD.
    void printword(string word)
    {
        Node* node=root;

        for(int i=0 ; i<word.length(); i++)
        {
            if(!node->getisEnd() || checkend(node->getvector(word[i]-97),word,i))
            {
                cout << word[i];
                node=node->getvector(word[i]-97);
            }
            else break;
        }

        return;
    }

    // CHECKING WHETHER THE END OF THE WORD IS REACHED.
    int checkend(Node* node,string word,int j)
    {
        for(int i=j+1 ; i<word.length() ; i++)
        {
            if(node->getisEnd()==true) return 1;
            node=node->getvector(word[i]-97);
        }
        return 0;
    }
};

int main()
{
    int p,n;
    int i,j=0,k;

    string num;
    getline(cin,num);

    p=stoi(num);

    string prefix[p],prefixes;

    // TAKES COMPLETE SENTENCE AS INPUT INCLUDING SPACES.
    getline(cin,prefixes);

    for(int i=0 ; i<prefixes.length() ; i++)
    {
        if(prefixes[i]==' ') j++;
        else prefix[j]+=prefixes[i];
    }

    TRIE T;

    string nu;
    getline(cin,nu);

    n=stoi(nu);

    string words[n],word;

    getline(cin,word);

    for(i=0,j=0 ; i<word.length() ; i++)
    {
        if(word[i]==' ') j++;
        else words[j]+=word[i];
    }
    for(i=0 ; i<n ; i++)
    {
        T.insert(words[i]);
    }

    for(i=0 ; i<p ; i++)
    {
        T.replaceword(prefix[i]);
    }

    for(i=0 ; i<n ; i++)
    {
        T.printword(words[i]);
        cout << " ";
    }
    cout << endl;

    return 0;
}
