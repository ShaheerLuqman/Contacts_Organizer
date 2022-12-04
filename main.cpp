#include <iostream>
#include <fstream>
// #include <vector>
// #include <iterator>
#include <string>
#include <iomanip>
// #include <algorithm>
#include <unordered_map>

using namespace std;

unordered_map<string, contact> book;

class contact
{
private:
    string name;
    int n = 0;
    string numbers[4] = {""};

public:
    friend void storeContact(contact &);
    friend void retrieveContact();
    contact(string name) : name(name) {}
    contact(string name, string number) : name(name) { addNumber(number); }
    void addNumber(string number)
    {
        if (n >= 4)
        {
            // cout << "Cannot add more than 4 numbers" << endl;
            return;
        }
        if (number != "")
        {
            numbers[n] = number;
            n++;
        }
    };
    void printNumbers()
    {
        for (int i = 0; i < n; i++)
            cout << i + 1 << ". " << numbers[i] << endl;
    }

    void printContacts()
    {
        cout << "Name: " << name << endl;
        for (int i = 0; i < n; i++)
            cout << i + 1 << ". " << numbers[i] << endl;
        cout << endl;
    }
    void changeName(string n) { name = n; }
    void removeNumber()
    {
        int choice;
        printNumbers();
        cout << "Which number to remove: ";
        cin >> choice;
        choice--;
        if (choice >= 0 && choice < n)
        {
            numbers[choice] = numbers[n];
            numbers[n] = "";
            n--;
        }
    }
};

void storeContact(contact &cont)
{
    fstream f("contactsFile.csv", ios::out | ios::app);
    if (!f.is_open())
    {
        cout << "could not open file\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        f << cont.name << ","; // Name
        int i = 0;
        if (i < cont.n)
            f << cont.numbers[i]; // Phone 1 - Value
        i++;
        f << ",";
        if (i < cont.n)
            f << cont.numbers[i]; // Phone 2 - Value
        i++;
        f << ",";
        if (i < cont.n)
            f << cont.numbers[i]; // Phone 3 - Value
        i++;
        f << ",";
        if (i < cont.n)
            f << cont.numbers[i]; // Phone 4 - Value
        i++;
        f << ",";
        f << endl;
    }
};

void retrieveContact()
{
    fstream f;
    // contact temp("name");
    string line, stemp;

    f.open("contactsGoogleBackup.csv", ios::in);
    if (!f.is_open() && f.fail())
    {
        cout << "\nNo record found\n";
        f.close();
    }
    else
    {
        while (!f.eof())
        {
            contact temp("name");

            getline(f, line);
            stringstream input_stringstream(line);
            getline(input_stringstream, stemp, ',');
            temp.name = stemp;
            // cout << stemp << ", ";

            for (int i = 0; i < 4; i++)
            {
                getline(input_stringstream, stemp, ',');
                temp.addNumber(stemp);
                // cout << stemp << ", ";
            }

            cout << endl;
            temp.printContacts();
            cout << endl;
        }
    }
};

int main()
{
    contact hi("M. Shaheer Luqman", "03100124127");
    hi.addNumber("03352904355");
    hi.addNumber("05845131541");
    // hi.addNumber("48412154421");
    // hi.addNumber("asfasfafaga");
    // hi.printContacts();
    // hi.removeNumber();
    // cout << endl;
    // hi.printContacts();

    // storeContact(hi);
    retrieveContact();
}