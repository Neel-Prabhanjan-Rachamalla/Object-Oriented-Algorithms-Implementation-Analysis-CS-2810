/*                  ASSIGNMENT - 4
    AUTHOR  : R.Neel Prabhanjan
    PURPOSE : Program to design a printer using template and handle exceptions wisely.
    DATE    : 15-02-22 - TUESDAY
    TIME-TAKEN : 2 hrs.
*/

#include<iostream>
using namespace std;

//NODE CLASS TEMPLATE.
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

//DOUBLY LINKED LIST CLASS TEMPLATE.
template <typename T>
class DoublyLinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    //CONSTRUCTOR.
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

//QUEUE CLASS TEMPLATE.
template <typename T>
class Queue
{
private:
    DoublyLinkedList<T>DLL;

public:
    //ENQUEUE INTO QUEUE.
    void enqueue(T element)
    {
        DLL.push_front(element);
    }

    //DEQUEUE FROM QUEUE.
    T dequeue()
    {
        return DLL.pop_end();
    }

    //RETURNS SIZE OF QUEUE.
    int Size()
    {
        return DLL.Size();
    }

    //CHECKS IF THE QUEUE IS EMPTY.
    bool isEmpty()
    {
        if(DLL.Size()==0) return true;
        return false;
    }
};

//PRINTER CLASS TEMPLATE.
template<typename T>
class Printer
{
private:
    Queue<T>queue;
    int capacity;
    int ink;

public:
    //EXCEPTION CLASS FOR INSUFFICIENT INK.
    class InsufficientInk
    {
    public:
        string reason;
        InsufficientInk(string reas)
        {
            reason=reas;
        }
    };
    //EXCEPTION CLASS FOR PRINTER BUSY.
    class PrinterBusy
    {
    public:
        string reason;
        PrinterBusy(string reas)
        {
            reason=reas;
        }
    };
    //EXCEPTION CLASS FOR NO DOCUMENT.
    class NoDocument
    {
    public:
        string reason;
        NoDocument(string reas)
        {
            reason=reas;
        }
    };

    //CONSTRUCTOR.
    Printer(int cap , int inkcap)
    {
        capacity=cap;
        ink=inkcap;
    }

    //ADD DOCUMENT.
    void addDocument(T document)
    {
        if(queue.Size()==capacity)
        {
            throw PrinterBusy("PRINTER_BUSY");
        }

        queue.enqueue(document);
    }

    //PRINT DOCUMENT.
    T printDocument()
    {
        if(queue.isEmpty())
        {
            throw NoDocument("NO_DOCUMENT");
        }
        else if(ink==0)
        {
            throw InsufficientInk("INSUFFICIENT_INK");
        }

        ink--;

        return queue.dequeue();
    }

    //FILL INK.
    void fillInk(int inkfill)
    {
        ink=inkfill;
    }
};

int main()
{
    int M,N;
    char T;

    cin >> M  >> N >> T;

    int Q;
    cin >> Q;

    switch(T)
    {
        //INTEGER PRINTER.
    case 'I' :
        {
            Printer<int>P(M,N);

            while(Q--)
            {
                int query;
                cin >> query;

                switch(query)
                {
                case 1 :
                    {
                        int doc;
                        cin >> doc;

                        //TRY BLOCK.
                        try
                        {
                            P.addDocument(doc);
                        }
                        //CATCH BLOCK.
                        catch(Printer<int>::PrinterBusy pbs)
                        {
                            cout << pbs.reason << endl;
                        }

                        break;
                    }

                case 2 :
                    {
                        //TRY BLOCK.
                        try
                        {
                            cout << P.printDocument() << endl;
                        }
                        //CATCH BLOCK 1.
                        catch(Printer<int>::InsufficientInk pii)
                        {
                            cout << pii.reason << endl;
                        }
                        //CATCH BLOCK 1.
                        catch(Printer<int>::NoDocument pnd)
                        {
                            cout << pnd.reason << endl;
                        }

                        break;
                    }

                case 3 :
                    {
                        int ink;
                        cin >> ink;

                        P.fillInk(ink);

                        break;
                    }
                }
            }

            break;
        }
        //CHARACTER PRINTER.
    case 'C' :
        {
            Printer<char>P(M,N);

            while(Q--)
            {
                int query;
                cin >> query;

                switch(query)
                {
                case 1 :
                    {
                        char doc;
                        cin >> doc;

                        //TRY BLOCK.
                        try
                        {
                            P.addDocument(doc);
                        }
                        //CATCH BLOCK.
                        catch(Printer<char>::PrinterBusy pbs)
                        {
                            cout << pbs.reason << endl;
                        }

                        break;
                    }

                case 2 :
                    {
                        //TRY BLOCK.
                        try
                        {
                            cout << P.printDocument() << endl;
                        }
                        //CATCH BLOCK 1.
                        catch(Printer<char>::InsufficientInk pii)
                        {
                            cout << pii.reason << endl;
                        }
                        //CATCH BLOCK 2.
                        catch(Printer<char>::NoDocument pnd)
                        {
                            cout << pnd.reason << endl;
                        }

                        break;
                    }

                case 3 :
                    {
                        int ink;
                        cin >> ink;

                        P.fillInk(ink);

                        break;
                    }
                }
            }

            break;
        }
        //FLOAT PRINTER.
       case 'F' :
        {
            Printer<float>P(M,N);

            while(Q--)
            {
                int query;
                cin >> query;

                switch(query)
                {
                case 1 :
                    {
                        float doc;
                        cin >> doc;

                        //TRY BLOCK.
                        try
                        {
                            P.addDocument(doc);
                        }
                        //CATCH BLOCK.
                        catch(Printer<float>::PrinterBusy pbs)
                        {
                            cout << pbs.reason << endl;
                        }

                        break;
                    }

                case 2 :
                    {
                        //TRY BLOCK.
                        try
                        {
                            cout << P.printDocument() << endl;
                        }
                        //CATCH BLOCK 1.
                        catch(Printer<float>::InsufficientInk pii)
                        {
                            cout << pii.reason << endl;
                        }
                        //CATCH BLOCK 2.
                        catch(Printer<float>::NoDocument pnd)
                        {
                            cout << pnd.reason << endl;
                        }

                        break;
                    }

                case 3 :
                    {
                        int ink;
                        cin >> ink;

                        P.fillInk(ink);

                        break;
                    }
                }
            }

            break;
        }
    }

    return 0;
}
