/*                  ASSIGNMENT-2
    AUTHOR  : R.Neel Prabhanjan
    PURPOSE : Program to use classes involving inheritance,virtual etc.
    DATE    : 2-2-22
    TIME-TAKEN : 7 hrs.
*/

#include<iostream>
using namespace std;

class Book
{
public:
    string title;
    string author;
    int year;
    int price;
};

class Node
{
public:

    Book book;
    Node* next;

    Node()
    {
        next=NULL;
    }
};

class Bookshelf
{
public:
    virtual void addBook(Book)=0;
    virtual void removeBook()=0;
    int checkEmpty(Node* ptr)
    {
        if(ptr==NULL) return 1;
        else return 0;
    }
    virtual void List()=0;
    virtual void findCheap()=0;
    virtual void reverseUnique()=0;
};

class VerticalBookshelf : public Bookshelf
{
public:
    Node *head;
    Node *tail;

    VerticalBookshelf()
    {
        head=NULL;
        tail=NULL;
    }

    void addBook(Book newbook)
    {
        Node* ptr=new Node();
        ptr->book=newbook;

        if(tail==NULL)
        {
            tail=ptr;
        }
        ptr->next=head;
        head=ptr;
    }

    void removeBook()
    {
        if(checkEmpty(head))
        {
            cout << "e" << endl;
            return;
        }

        Node *ptr=head;
        head=head->next;
        if(head==NULL) tail=NULL;

        free(ptr);
    }

    void findCheap()
    {
        if(checkEmpty(head))
        {
            cout << 'e' << endl;
            return;
        }
        int cheap=head->book.price;
        Node* ptr=head;

        while(ptr!=NULL)
        {
            if(ptr->book.price>cheap) cout << cheap;
            else
            {
                cheap=ptr->book.price;
                cout << -1;
            }

            ptr=ptr->next;
            if(ptr!=NULL) cout << ",";
        }

        cout << endl;
    }

    void List()
    {
        if(checkEmpty(head))
        {
            cout << "e" << endl;
            return;
        }

        Node* ptr=head;
        while(ptr!=NULL)
        {
            cout << ptr->book.title << "," << ptr->book.author << "," << ptr->book.year << "," << ptr->book.price << endl;

            ptr=ptr->next;
        }
    }

    void reverseUnique()
    {
        if(checkEmpty(head)) return;

        VerticalBookshelf newvbs1;
        VerticalBookshelf newvbs2;

        while(head!=NULL)
        {
            newvbs1.addBook(head->book);
            removeBook();
        }
        while(newvbs1.head!=NULL)
        {
            Node *ptr;
            int flag=1;

            for(ptr=newvbs2.head ; ptr ; ptr=ptr->next)
            {
                if(ptr->book.title==newvbs1.head->book.title)
                {
                    flag=0;
                    break;
                }
            }
            if(flag) newvbs2.addBook(newvbs1.head->book);
            newvbs1.removeBook();
        }
        while(newvbs2.head!=NULL)
        {
            addBook(newvbs2.head->book);
            newvbs2.removeBook();
        }
    }
};

class HorizontalBookshelf : public Bookshelf
{
public:
    Node *head;
    Node *tail;

    HorizontalBookshelf()
    {
        head=NULL;
        tail=NULL;
    }

    void addBook(Book newbook)
    {
        Node* ptr=new Node();
        ptr->book=newbook;

        if(tail!=NULL)
        {
            tail->next=ptr;
        }
        tail=ptr;

        if(head==NULL)
        {
            head=ptr;
        }
    }

    void removeBook()
    {
        if(checkEmpty(head))
        {
            cout << "e" << endl;
            return;
        }

        Node *ptr=head;
        head=head->next;
        if(head==NULL) tail=NULL;

        free(ptr);
    }

    void findCheap()
    {
        if(checkEmpty(head))
        {
            cout << 'e' << endl;
            return;
        }
        int cheap=head->book.price;
        Node* ptr=head;

        while(ptr!=NULL)
        {
            if(ptr->book.price>cheap) cout << cheap;
            else
            {
                cheap=ptr->book.price;
                cout << -1;
            }

            ptr=ptr->next;
            if(ptr!=NULL) cout << ",";
        }

        cout << endl;
    }

    void List()
    {
        if(checkEmpty(head))
        {
            cout << "e" << endl;
            return;
        }

        Node* ptr=head;
        while(ptr!=NULL)
        {
            cout << ptr->book.title << "," << ptr->book.author << "," << ptr->book.year << "," << ptr->book.price << endl;

            ptr=ptr->next;
        }
    }

    void reverseUnique()
    {
        if(checkEmpty(head)) return;

        VerticalBookshelf newvbs1;

        while(head!=NULL)
        {
            Node *ptr;
            int flag=1;

            for(ptr=newvbs1.head ; ptr ; ptr=ptr->next)
            {
                if(ptr->book.title==head->book.title)
                {
                    flag=0;
                    break;
                }
            }
            if(flag) newvbs1.addBook(head->book);
            removeBook();
        }
        while(newvbs1.head!=NULL)
        {
            addBook(newvbs1.head->book);
            newvbs1.removeBook();
        }
    }
};

int main()
{
    int i,j,k;

    VerticalBookshelf ver;
    HorizontalBookshelf hor;

    int Q;

    cin >> Q;

    while(Q--)
    {
        string query;
        cin >> query;

        if(query=="ADD")
            {
                char shelf;
                cin>> shelf;

                Book book;
                cin >> book.title;
                cin >> book.author;
                cin >> book.year;
                cin >> book.price;

                if(shelf=='v') ver.addBook(book);
                else hor.addBook(book);
            }

        else if(query=="REMOVE")
            {
                int n;
                char shelf;

                cin >> n >> shelf;

                if(shelf=='v') while(n--) ver.removeBook();
                else while(n--) hor.removeBook();
            }

        else if(query=="LIST")
            {
                char shelf;
                cin >> shelf;

                if(shelf=='v') ver.List();
                else hor.List();
            }

        else if(query=="FINDC")
            {
                char shelf;
                cin >> shelf;

                if(shelf=='v') ver.findCheap();
                else hor.findCheap();
            }

        else if(query=="REVUNI")
            {
                char shelf;
                cin >> shelf;

                if(shelf=='v') ver.reverseUnique();
                else hor.reverseUnique();
            }
    }
    return 0;
}
