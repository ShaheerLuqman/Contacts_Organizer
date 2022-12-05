#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <unordered_map>

using namespace std;

class contact
{
private:
    string name;
    int n = 0;
    string numbers[4] = {""};

public:
    friend void storeContactCSV(contact &);
    friend void importContacts();

    contact() {}
    contact(string name, string number) : name(name) { addNumber(number); }

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

unordered_map<string, contact> book;

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
void storeContactHash(contact &cont)
{
    string stemp = cont.getName();
    transform(stemp.begin(), stemp.end(), stemp.begin(), ::tolower);
    book.insert(std::make_pair(stemp, cont));
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
            contact temp;

            getline(f, line);
            stringstream input_stringstream(line);
            getline(input_stringstream, stemp, ',');
            temp.name = stemp;

            for (int i = 0; i < 4; i++)
            {
                getline(input_stringstream, stemp, ',');
                temp.addNumber(stemp);
            }
            storeContactHash(temp);
            temp.printContacts();
        }
    }
};

bool isEmpty(contact &temp)
{
    if (temp.getNumber1() == "" && temp.getNumber2() == "" && temp.getNumber3() == "" && temp.getNumber4() == "")
        return true;
    else
        return false;
};

contact searchContact()
{
    string input;
    fflush(stdin);
    cout << "Enter contact name to search: ";
    getline(cin, input);
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    contact temp;
    temp = book[input];

    if (temp.getName() != "" && isEmpty(temp) != true)
    {
        temp.printContacts();
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
// Shaharyar; Menu banaa na he Jo ke Name and number of contacts and utne numbers input le

int main()
{
    importContacts();

    createContact();

    // contact hi("M. Shaheer Luqman", "03100124127");
    // hi.addNumber("03352904355");
    // hi.addNumber("05845131541");
    // storeContactHash(hi);

    while (1)
    {
        searchContact();
    }
}

void deleteContact(){};
// Hadi; Contact ka naam le aur hashmap se woh contact delete kerde

void missingInformation(){};
// Shaharyar; function bataye ga ke contact mein naam missing ho ya numbers 1 bhi na hoon tou woh insert kerwayega

void invalidContact(){};
// Hadi; dekhega ke agar contact ke number mein agar
// 1. koi aesa charachter ho jo ke number mein nahi hona chahiye lekin ho
// 2. koi number standard size se chota ho
// 3. koi number standard size se baraa ho
// tou uss contact ko flag kere.

void smartSearch(); // Shaheer

void mergeContact(){};
// Hadi; 2 contacts parameter lega and usko aik contact mein save kerke return kerdega

void internationalization(){};
// Shaharyar; agar number se pehle international code na ho tou woh laga de for e.g 03100124127 tou usko +923100124127 kerde. yeh sirf 03XX... wale numbers nahi 021XX.. wale bhi kerna chahiye

void Capitalization(){};
// Hadi; Name ke jitne bhi words hein sab ke pehle letter capital hoone chahiye

void simplifyNumber(){}; // Shaheer

void duplicateContact(){}; // Shaheer

// Preview and Confirm All Changes
void searchAndReplaceContacts(){};