#include <iostream>
using namespace std;

class Node
{
public:
    int contact;
    Node *next;
    Node(int contact)
    {
        this->contact = contact;
        this->next = NULL;
    }
};

class contact
{
public:
    string name;
    Node *head;

    contact(string name)
    {
        this->name = name;
        this->head = NULL;
    }
    void createContact(int contactNo)
    {
        if (head == NULL)
        {
            Node *newNode = new Node(contactNo);
            head = newNode;
            return;
        }
        else
        {
            Node *newNode = new Node(contactNo);
            Node *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display()
    {
        Node *temp = head;
        cout << name << ": ";
        if (head == NULL)
        {
            cout << "no details! " << endl;
        }
        else
        {
            while (temp != NULL)
            {
                cout << temp->contact << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

int main()
{
    contact person1("Hadi");
    person1.createContact(321);
    person1.createContact(432);
    person1.display();
    contact person2("Ali");
    person2.display();
}