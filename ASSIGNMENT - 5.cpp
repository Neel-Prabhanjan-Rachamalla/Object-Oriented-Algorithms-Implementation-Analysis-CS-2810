/*                  LAB-5
    AUTHOR  : R.Neel Prabhanjan
    PURPOSE : Program to perform graph related operations using overloading.
    DATE    : 1-3-22 - TUESDAY
    TIME-TAKEN : 5 hrs.
*/

#include<iostream>
#include<utility>
using namespace std;

#define N 100

//Node class.
class Node
{
public:
    int data;
    Node* next;
    Node* previous;

    Node()
    {
        next=NULL;
        previous=NULL;
    }
};

//DoublyLinkedList class.
class DoublyLinkedList
{
private:
    Node* head;
    Node* tail;
    int size;

public:
    //Constructor.
    DoublyLinkedList()
    {
        head=NULL;
        tail=NULL;
        size=0;
    }

    //PUSH_FRONT.
    void push_front(int element)
    {
        size++;
        Node* newptr=new Node;
        newptr->data=element;

        newptr->next=head;
        if(head!=NULL) head->previous=newptr;
        head=newptr;
        if(tail==NULL) tail=newptr;
    }

    //POP_FRONT.
    int pop_front()
    {
        if(size==0) return -1;
        size--;
        Node* ptr=head;
        head=head->next;
        if(head!=NULL) head->previous=NULL;
        int dat=ptr->data;

        free(ptr);
        if(head==NULL) tail=NULL;

        return dat;
    }

    //SIZE.
    int Size()
    {
        return size;
    }
};

//STACK CLASS.
class Stack
{
private:
    DoublyLinkedList DLL;

public:
    //PUSH INTO STACK.
    void push(int element)
    {
        DLL.push_front(element);
    }

    //POP OUT FROM STACK.
    int pop()
    {
        return DLL.pop_front();
    }

    //TOP ELEMENT OF STACK.
    int top()
    {
        if(!isEmpty())
        {
            int popped=DLL.pop_front();
            DLL.push_front(popped);
            return popped;
        }
        else return -1;
    }

    //CHECKS IF EMPTY.
    int isEmpty()
    {
        if(DLL.Size()==0) return 1;
        else return 0;
    }
};

//Graph class.
class Graph
{
private :
    int vertices;
    int adj[N][N];

public :
    Graph(int n)
    {
        vertices=n;
        for(int i=0 ; i<n ; i++)
        {
            for(int j=0 ; j<n ; j++)
            {
                adj[i][j]=0;
            }
        }
    }

    //Operator overloading.
    friend Graph& operator += (Graph& G , const pair<int,int>& edge);

    friend Graph& operator -= (Graph& G , const pair<int,int>& edge);

    //Detect Cycle.
    int detectCycle()
    {
        int visited[vertices]={0};

        for(int i=0 ; i<vertices ; i++)
        {
            if(!visited[i])
            {
                if(detectCyclerecur(i,visited,-1)) return 1;
            }
        }

        return 0;
    }
    //Helper function for detect cycle.
    int detectCyclerecur(int v , int visited[] , int p)
    {
        visited[v]=1;

        for(int i=0 ; i<vertices ; i++)
        {
            if(adj[v][i])
            {
                if(!visited[i])
                {
                    if(detectCyclerecur(i,visited,v)) return 1;
                }
                else if(i!=p) return 1;
            }
        }

        return 0;
    }

    //Reach function.
    int reach(int u , int v)
    {
        int visited[vertices]={0};
        Stack S;

        S.push(u);
        visited[u]=1;

        while(!S.isEmpty())
        {
            int k=S.pop();

            for(int i=0 ; i<vertices ; i++)
            {
                if(adj[k][i] && visited[i]!=1)
                {
                    visited[i]=1;
                    if(i==v) return 1;

                    S.push(i);
                }
            }
        }
        return 0;
    }

    //Operator overloading.
    friend ostream& operator << (ostream& o , const Graph& G);

};

//+= Operator overloading function.
Graph& operator += (Graph& G , const pair<int,int>& edge)
    {
        G.adj[edge.first][edge.second]=1;
        G.adj[edge.second][edge.first]=1;

        return G;
    }

//+= Operator overloading function.
Graph& operator -= (Graph& G , const pair<int,int>& edge)
    {
        G.adj[edge.first][edge.second]=0;
        G.adj[edge.second][edge.first]=0;

        return G;
    }

//<< Operator overloading function.
ostream& operator << (ostream& o , const Graph& G)
{
    for(int i=0 ; i<G.vertices ; i++)
    {
        for(int j=0 ; j<G.vertices ; j++)
        {
            o << G.adj[i][j] << " ";
        }
        o << endl;
    }

    return o;
}

int main()
{
    int Q,n,m;
    int i,j,k;

    cin >> Q;

    Stack S;

    while(Q--)
    {
        string query;
        cin >> query;

        if(query=="push")
            {
                int x;
                cin >> x;

                S.push(x);
            }

        else if(query=="pop")
            {
                cout << S.pop() << endl;
            }

        else if(query=="top")
            {
                cout << S.top() << endl;
            }

        else if(query=="empty")
            {
                cout << S.isEmpty() << endl;
            }
    }

    cin >> n >> m;

    Graph G(n);

    while(m--)
    {
        string query;
        cin >> query;

        if(query=="add")
            {
                int u,v;
                cin >> u >> v;
                pair <int,int> edge(u,v);

                G+=edge;
            }

        else if(query=="del")
            {
                int u,v;
                cin >> u >> v;

                pair <int,int> edge(u,v);

                G-=edge;
            }

        else if(query=="cycle")
            {
                cout << G.detectCycle() << endl;
            }

        else if(query=="print")
            {
                cout << G;
            }

        else if(query=="reach")
            {
                int u,v;
                cin >> u >> v;

                cout << G.reach(u,v) << endl;
            }
        }

    return 0;
}
