#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <map>
// #include <unordered_map>

using namespace std;

class contact
{
private:
    string name;
    int n = 0;
    string numbers[4] = {""};

public:
    bool potentiallyInvalid = false;
    friend void storeContactCSV(contact &);
    friend void importContacts();
    friend bool isInvalidContact(contact &);

    contact() {}
    contact(string name, string number) : name(name) { addNumber(number); }

    int getN() const { return n; }
    string getName() const { return name; }
    string getNumber1() const { return numbers[0]; }
    string getNumber2() const { return numbers[1]; }
    string getNumber3() const { return numbers[2]; }
    string getNumber4() const { return numbers[3]; }
    void setName(string name) { this->name = name; }
    void setNumber1(string number) { numbers[0] = number; }
    void setNumber2(string number) { numbers[1] = number; }
    void setNumber3(string number) { numbers[2] = number; }
    void setNumber4(string number) { numbers[3] = number; }

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
        isInvalidContact();
    };

    void updateName(string newName)
    {
        deleteContact(*this);
        setName(newName);
        storeContactCSV(*this);
    }

    void printNumbers()
    {
        for (int i = 0; i < n; i++)
            cout << i + 1 << ". " << numbers[i] << endl;
    }

    void printContact()
    {
        cout << "Name: " << name << endl;
        for (int i = 0; i < n; i++)
            cout << i + 1 << ". " << numbers[i] << endl;
        cout << endl;
    }

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

    bool missingInformation()
    {
        for (int i = 0; i < n; i++)
            if (isEmpty())
                return true;

        return false;
    };

    string popNumber()
    {
        if (n > 0)
        {
            string num;
            num = numbers[n - 1];
            numbers[n - 1] = "";
            n--;
            return num;
        }
    }

    bool isEmpty()
    {
        if (numbers[0] == "")
            return true;
        else
            return false;
    };

    void isInvalidContact()
    {
        potentiallyInvalid = false;
        string num;
        int len;
        for (int i = 0; i < n; i++)
        {
            num = numbers[i];
            len = num.length();
            if (len > 14 || len < 10) // contact can not be longer than 14 and shorter than 10
                potentiallyInvalid = true;
            else
            {
                if (!(num[0] == '0' || num[0] == '+')) // first digit other than 0 or +
                    potentiallyInvalid = true;

                else
                {
                    for (int i = 1; i < len; i++) // any non zero digit after first digit
                        if (num[i] < '0' || num[i] > '9')
                            potentiallyInvalid = true;
                }
            }
        }
    };

    void internationalize()
    {
        for (int i = 0; i < n; i++)
        {
            if (numbers[i][0] == '0' && numbers[i][1] == '2')
            {
                numbers[i].erase(0, 2);
                string ch = "+922";
                numbers[i] = ch + numbers[i];
            }
            else if (numbers[i][0] == '0' && numbers[i][1] == '3')
            {
                numbers[i].erase(0, 2);
                string ch = "+923";
                numbers[i] = ch + numbers[i];
            }
        }
        return;
    }

    void capitalize()
    {
        char ch;
        int len, i;
        len = name.size();
        for (i = 0; i < len; ++i)
        {
            if (i == 0)
            {
                if (islower(name[i]))
                    name[i] = toupper(name[i]);
            }
            else
            {
                if (name[i] != ' ')
                {
                    if (isupper(name[i]))
                        name[i] = tolower(name[i]);
                }
                else
                {
                    i++;
                    if (islower(name[i]))
                        name[i] = toupper(name[i]);
                }
            }
        }
        return;
    }

    void simplify()
    {
        for (int i = 0; i < n; i++)
        {
            numbers[i].erase(remove(numbers[i].begin(), numbers[i].end(), ' '), numbers[i].end());
        };
    };
};

map<string, contact> book;

void storeContactCSV(contact &cont)
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

void fillInEmptyContacts()
{
    if (book.find("") != book.end())
    {
        string line;
        cout << "Enter new Name: ";
        getline(cin, line);
        book[""].updateName(line);
    }
    else
        cout << " : Not found" << endl;
}

void missingInformationContact()
{
    cout << "Contacts with missing Information" << endl
         << endl;
    map<string, contact>::iterator it = book.begin();
    while (it != book.end())
    {
        it->second.missingInformation();
        if (it->second.missingInformation())
        {
            it->second.printContact();
        }
        it++;
    }
    return;
};

void storeContactHash(contact &cont)
{
    string stemp = cont.getName();
    transform(stemp.begin(), stemp.end(), stemp.begin(), ::tolower);
    book.insert(make_pair(stemp, cont));
}

void importContacts()
{
    fstream f;
    string line, stemp;

    f.open("contactsFile.csv", ios::in);
    if (!f.is_open() && f.fail())
    {
        cout << "\nNo record found\n";
        f.close();
    }
    else
    {
        while (!f.eof())
        {
            getline(f, line);
            if (line != "")
            {
                contact temp;
                stringstream input_stringstream(line);
                getline(input_stringstream, stemp, ',');
                temp.name = stemp;

                for (int i = 0; i < 4; i++)
                {
                    getline(input_stringstream, stemp, ',');
                    temp.addNumber(stemp);
                }
                storeContactHash(temp);
                // temp.printContact();
            }
        }
    }
};

contact *searchContact()
{
    string input;
    fflush(stdin);
    cout << "Enter contact name to search: ";
    getline(cin, input);
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    contact *temp;
    temp = &book[input];

    if (temp->getName() != "" && temp->isEmpty() != true)
    {
        temp->printContact();
        return temp;
    }
    else
        cout << "No contact found!" << endl;
}

void createContact()
{
    contact a;
    string input;
    int count;
    cout << "Creating New Contact\n"
         << "Enter Name: ";
    getline(cin, input);
    a.setName(input);

    do
    {
        cout << "How many numbers do want to add in this contact: ";
        cin >> count;
    } while (count > 4 || count < 0);

    for (int i = 0; i < count; i++)
    {
        cout << "Enter Contact Number: ";
        cin >> input;
        a.addNumber(input);
    }

    storeContactHash(a);
    storeContactCSV(a);

    system("pause");
}

void SimplifyContact()
{
    cout << "Simplifying All Contacts" << endl
         << endl;

    map<string, contact>::iterator it = book.begin();
    while (it != book.end())
    {
        it->second.simplify();
        it++;
    }
    return;
}

void deleteContact(contact &con)
{
    book.erase(con.getName());
    // delete from file??
}

void mergeContact(contact &c1, contact &c2)
{

    if ((c1.getN() + c2.getN()) > 4)
    {
        cout << "Contacts can't be merged! " << endl;
        return;
    }

    for (int i = 0; i < c2.getN(); i++)
    {
        string num = c2.popNumber();
        c1.addNumber(num);
    }

    deleteContact(c2);
}

void capitalization()
{
    cout << "Capitalizing All Contacts" << endl
         << endl;

    map<string, contact>::iterator it = book.begin();
    while (it != book.end())
    {
        it->second.capitalize();
        it++;
    }
    return;
}

void internationalization()
{
    cout << "Internationalizing All Contacts" << endl
         << endl;
    map<string, contact>::iterator it = book.begin();
    while (it != book.end())
    {
        it->second.internationalize();
        it++;
    }
    return;
}

void smartSearch(); // Shaheer

// Shaharyar

void duplicateContact(){}; // Shaheer

// Preview and Confirm All Changes
void searchAndReplaceContacts(){}; // shaheer

void menu();

int main()
{
    cout << "Importing Contacts!" << endl;
    importContacts();
    cout << "Contacs Imported Successfully!" << endl;
    system("pause");

    menu();

    return 0;
}

void displayPhoneBook()
{
    system("cls");
    cout << "Displaying All Contacts" << endl
         << endl;

    cout << left << setw(40) << "Name "
         << left << setw(3) << "|"
         << left << setw(16) << "Phone 1"
         << left << setw(3) << "|"
         << left << setw(16) << "Phone 2"
         << left << setw(3) << "|"
         << left << setw(16) << "Phone 3"
         << left << setw(3) << "|"
         << left << setw(16) << "Phone 4"
         << endl;

    map<string, contact>::iterator it = book.begin();
    while (it != book.end())
    {
        cout << left << setw(40) << it->second.getName()
             << left << setw(3) << "|"
             << left << setw(16) << it->second.getNumber1()
             << left << setw(3) << "|"
             << left << setw(16) << it->second.getNumber2()
             << left << setw(3) << "|"
             << left << setw(16) << it->second.getNumber3()
             << left << setw(3) << "|"
             << left << setw(16) << it->second.getNumber4()
             << endl;
        it++;
    }
}

// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void InvalidContacts()
{
    cout << "Potentially invalid contacts." << endl;
    map<string, contact>::iterator it = book.begin();
    while (it != book.end())
    {
        if (it->second.potentiallyInvalid)
        {
            it->second.printContact();
        }
        it++;
    }
}

void menu()
{
    string choice;
    while (1)
    {
        system("cls");
        cout << "Welcome to CONTACT ORGANIZER";
        cout << "\nPress\n"
             << "   1.  View All Contacts\n"
             << "   2.  Search Contact\n"
             << "   3.  Create New Contact\n"
             << "   4.  Similar contact\n"
             << "   5.  Duplicate Contacts\n"
             << "   6.  Delete Contact\n"
             << "   7.  Fill-in Empty Contacts Names\n"
             << "   8.  Missing Information\n"
             << "   9.  Invalid Contacts\n"
             << "   10. Merge contact\n"
             << "   11. Internationalization\n"
             << "   12. Capitalization\n"
             << "   13. Simplify Numbers\n"
             << "   14. Search and Replace Contacts \n"
             << "   0.  Exit\n"
             << "Your Input: ";
        cin >> choice;
        if (choice == "0")
        {
            exit(EXIT_SUCCESS);
        }
        else if (choice == "1")
        {
            system("cls");
            displayPhoneBook();
            system("pause");
        }
        else if (choice == "2")
        {
            system("cls");
            searchContact();
            system("pause");
        }
        else if (choice == "3")
        {
            system("cls");
            createContact();
            system("pause");
        }
        else if (choice == "4")
        {
            system("cls");
            system("pause");
        }
        else if (choice == "5")
        {
            system("cls");
            system("pause");
        }
        else if (choice == "6")
        {
            system("cls");
            system("pause");
        }
        else if (choice == "7")
        {
            system("cls");
            system("pause");
        }
        else if (choice == "8")
        {
            system("cls");
            missingInformationContact();
            system("pause");
        }
        else if (choice == "9")
        {
            system("cls");
            InvalidContacts();
            system("pause");
        }
        else if (choice == "10")
        {
            system("cls");
            system("pause");
        }
        else if (choice == "11")
        {
            system("cls");
            internationalization();
            system("pause");
        }
        else if (choice == "12")
        {
            system("cls");
            capitalization();
            system("pause");
        }
        else if (choice == "13")
        {
            system("cls");
            SimplifyContact();
            system("pause");
        }
        else if (choice == "14")
        {
            system("cls");
            system("pause");
        }
        else
            cout << "Wrong Input Entered!";
    }
}
