/*                  SKIP LIST
    AUTHOR  : R.Neel Prabhanjan
    PURPOSE : Program to implement dictionaries using Skip lists.
    DATE    : 05-04-22 - TUESDAY
    TIME-TAKEN : 7 hrs.
*/

#include<iostream>
#include<stdlib.h>
using namespace std;

//Generates random number and produces 0 or 1 depending on whether it is even or odd.'
int cointoss()
{
    int num=rand();
    if(num%2==0) return 1;
    else return 0;
}

//Template Class Node.
template<typename T>
class Node
{
    public :

    T key;
    T val;
    Node<T>* left;
    Node<T>* right;
    Node<T>* top;
    Node<T>* bottom;

    Node()
    {
        left=NULL;
        right=NULL;
        top=NULL;
        bottom=NULL;
    }
};

//Template class SkipList.
template<typename T>
class SkipList
{
    public :

    int h,n;
    Node<T>* S;
    Node<T>* head;
    Node<T>* tail;

    //Constructor for creating an empty list.
    SkipList()
    {
        h=0;
        n=0;
        head=NULL;
        tail=NULL;
        S=head;

        createlist();
        h++;
    }

    //Creates an new empty list[level].
    void createlist()
    {
        Node<T>* leftend=new Node<T>();
        Node<T>* rightend=new Node<T>();

        leftend->left=NULL;
        leftend->right=rightend;
        leftend->top=NULL;
        if(h==0) leftend->bottom=NULL;
        else leftend->bottom=head;

        rightend->left=leftend;
        rightend->right=NULL;
        rightend->top=NULL;
        if(h==0) rightend->bottom=NULL;
        else rightend->bottom=tail;

        if(h!=0)
        {
            head->top=leftend;
            tail->top=rightend;
        }
        head=leftend;
        tail=rightend;
        S=head;
    }

    //Searches for a given key in the SkipList.
    Node<T>* Search(T k)
    {
        Node<T>* ptr=head;

        while(ptr->right->right!=NULL && (ptr->right->key<=k))
        {
            ptr=ptr->right;
        }
        while(ptr->bottom!=NULL)
        {
            ptr=ptr->bottom;
            while(ptr->right->right!=NULL && (ptr->right->key<=k))
            {
                ptr=ptr->right;
            }

        }
        return ptr;
    }

    //Inserts a key-value pair into the SkipList.
    Node<T>* insert(T k , T v)
    {
        Node<T>* ptr=Search(k);

        int height=1;

        while(h<10 && (height==1 || cointoss()==1))
        {
            if(height>h)
            {
                createlist();
                h++;
            }

            Node<T>* newptr=new Node<T>();
            newptr->key=k;
            newptr->val=v;

            if(height==1)
            {
                newptr->left=ptr;
                newptr->right=ptr->right;
                ptr->right->left=newptr;
                ptr->right=newptr;
                ptr=newptr;
            }
            else
            {
                ptr->top=newptr;
                newptr->bottom=ptr;

                Node<T>* ptr1=ptr->left;
                while(ptr1->top==NULL) ptr1=ptr1->left;
                ptr1->top->right=newptr;
                newptr->left=ptr1->top;

                Node<T>* ptr2=ptr->right;
                while(ptr2->top==NULL) ptr2=ptr2->right;
                ptr2->top->left=newptr;
                newptr->right=ptr2->top;

                ptr=newptr;
            }

            height++;
        }

        n++;

        return  ptr;
    }

    //Deleting the node with the given key from the SkipList.
    void del(T k)
    {
        Node<T>* ptr=Search(k);
        if(ptr->left==NULL || ptr->key!=k) return;

        Node<T>* pt;
        while(ptr!=NULL)
        {
            ptr->left->right=ptr->right;
            ptr->right->left=ptr->left;
            pt=ptr;
            ptr=ptr->top;

            free(pt);

        }
        n--;
        return;
    }

    //Getting the value of n.
    int getn()
    {
        return n;
    }
};

//Template class Dictionary. 
template<typename T>
class Dictionary : public SkipList<T>
{
    public :

    //Checks if empty.
    void empty()
    {
        if(SkipList<T>::getn()==0) cout << "True" << endl;
        else cout << "False" << endl;
    }

    //Inserts a given key-value pair.
    void Insert(T k , T v)
    {
        SkipList<T>::insert(k,v);
    }

    //Deletes a node with a given key from the Dictionary.
    void Delete(T k)
    {
        SkipList<T>::del(k);
    }

    //Searches for a given key node.
    void find(T k)
    {
        if(SkipList<T>::Search(k)->left!=NULL && SkipList<T>::Search(k)->key==k) cout << SkipList<T>::Search(k)->val << endl;
        else cout << "NOT FOUND" << endl;
    }

    //Displays the number of elements in the dictionary.
    void size()
    {
        cout << SkipList<T>::getn() << endl;
    }
};

int main()
{
    string skiplist;
    cin >> skiplist;

    //String-based Dictionary.
    if(skiplist=="STRINGDICT")
    {
        Dictionary <string> D;

        int p;
        cin >> p;

        while(p--)
        {
            string query;
            cin >> query;

            if(query=="ISEMPTY")
            {
                D.empty();
            }
            else if(query=="INSERT")
            {
                string k,v;
                cin >> k >> v;

                D.Insert(k,v);
            }
            else if(query=="DELETE")
            {
                string k;
                cin >> k;

                D.Delete(k);
            }
            else if(query=="FIND")
            {
                string k;
                cin >> k;

                D.find(k);
            }
            else if(query=="SIZE")
            {
                D.size();
            }
        }
    }

    //Integer-based Dictionary.
    else if(skiplist=="INTEGERDICT")
    {
        Dictionary <int> D;

        int p;
        cin >> p;

        while(p--)
        {
            string query;
            cin >> query;

            if(query=="ISEMPTY")
            {
                D.empty();
            }
            else if(query=="INSERT")
            {
                int k,v;
                cin >> k >> v;

                D.Insert(k,v);
            }
            else if(query=="DELETE")
            {
                int k;
                cin >> k;

                D.Delete(k);
            }
            else if(query=="FIND")
            {
                int k;
                cin >> k;

                D.find(k);
            }
            else if(query=="SIZE")
            {
                D.size();
            }
        }
    }

    return 0;
}
