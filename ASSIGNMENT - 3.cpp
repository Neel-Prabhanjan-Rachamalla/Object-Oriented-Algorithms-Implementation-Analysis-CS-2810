/*                  TEMPLATE STACK
    AUTHOR  : R.Neel Prabhanjan
    PURPOSE : Program to use template to create a own STACK using template designed Doubly Linked List.
    DATE    : 8-2-22 - TUESDAY
    TIME-TAKEN : 3 hrs.
*/

#include<iostream>
using namespace std;

//Node class template.
template <typename T>
class Node
{
public:
    T data;
    Node* next;
    Node* previous;

    Node()
    {
        next=NULL;
        previous=NULL;
    }
};

//DoublyLinkedList class template.
template <typename T>
class DoublyLinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
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
    void push_front(T element)
    {
        size++;
        Node<T>* newptr=new Node<T>;
        newptr->data=element;

        newptr->next=head;
        if(head!=NULL) head->previous=newptr;
        head=newptr;
        if(tail==NULL) tail=newptr;
    }

    //PUSH_END.
    void push_end(T element)
    {
        size++;
        Node<T>* newptr=new Node<T>;
        newptr->data=element;

        newptr->previous=tail;
        if(tail!=NULL) tail->next=newptr;
        tail=newptr;
        if(head==NULL) head=newptr;
    }

    //POP_FRONT.
    T pop_front()
    {
        size--;
        Node<T>* ptr=head;
        head=head->next;
        if(head!=NULL) head->previous=NULL;
        T dat=ptr->data;

        free(ptr);
        if(head==NULL) tail=NULL;

        return dat;
    }

    //POP_END.
    T pop_end()
    {
        size--;
        Node<T>* ptr=tail;
        tail=tail->previous;
        if(tail!=NULL) tail->next=NULL;
        T dat=ptr->data;

        free(ptr);
        if(tail==NULL) head=NULL;

        return dat;
    }

    //SIZE.
    int Size()
    {
        return size;
    }
};

//Stack class template.
template <typename T>
class Stack
{
private:
    DoublyLinkedList<T>DLL;

public:
    //PUSH INTO STACK.
    void push(T element)
    {
        DLL.push_front(element);
    }

    //POP OUT FROM STACK.
    void pop()
    {
        T popped1=DLL.pop_front();
        cout << popped1;
    }

    //TOP ELEMENT OF STACK.
    T top()
    {
        if(!checksize())
        {
            T popped=DLL.pop_front();
            DLL.push_front(popped);
            return popped;
        }
        else return -1;
    }

    //CHECKS IF EMPTY.
    int checksize()
    {
        if(DLL.Size()==0) return 1;
        else return 0;
    }

    //Compares current element with top element of stack.
    bool compare(T element)
    {
        if(element>top()) return true;
        else return false;
    }
};

int main()
{
    int N;
    char T;

    cin >> N >> T;

    switch(T)
    {
        //INTEGER STACK.
    case 'I' :
        {
            Stack<int>S;

            while(N--)
            {
                int n;
                cin >> n;

                while(!S.checksize())
                {
                    if(S.compare(n))
                    {
                        S.push(n);
                        break;
                    }
                    else S.pop();
                }

                if(S.checksize()) S.push(n);
            }

            while(!S.checksize()) S.pop();

            break;
        }

        //CHARACTER STACK.
        case 'C' :
        {
            Stack<char>S;

            while(N--)
            {
                char n;
                cin >> n;

                while(!S.checksize())
                {
                    if(S.compare(n))
                    {
                        S.push(n);
                        break;
                    }
                    else S.pop();
                }

                if(S.checksize()) S.push(n);
            }

            while(!S.checksize()) S.pop();

            break;
        }

        //FLOAT STACK.
        case 'F' :
        {
            Stack<float>S;

            while(N--)
            {
                float n;
                cin >> n;

                while(!S.checksize())
                {
                    if(S.compare(n))
                    {
                        S.push(n);
                        break;
                    }
                    else S.pop();
                }

                if(S.checksize()) S.push(n);
            }

            while(!S.checksize()) S.pop();

            break;
        }
    }
    cout << endl;

    return 0;
}
