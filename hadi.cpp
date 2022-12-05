#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <tuple>
#include <unordered_map>

//in contact class
tuple<string,string,string,string> getNumbers()
 {
    return make_tuple(cont.getNumber1(), cont.getNumber2(), cont.getNumber3(),cont.getNumber4());
 }

void deleteContact(contact &con)
{
    book.erase(con.getName());

    // for (auto itr = book.begin(); itr != book.end(); ++itr)
    // {
    //     cout << itr->first << '\t' << itr->second << '\n';
    // }

    // delete from file??
}

void mergeContact(contact &c1, contact c2)
{
    int cont1 = c1.getN();
    int cont2 = c2.getN();
    // int count = max(cont1, cont2);

    string num1, num2, num3, num4, num[4];
    // for (int i = 0; i < cont2; i++)
    // {
    //     num[i] = get<i>(c2.getNumbers());
    // }
    num1 = get<0>(c2.getNumbers());
    num2 = get<1>(c2.getNumbers());
    num3 = get<2>(c2.getNumbers());
    num4 = get<3>(c2.getNumbers());

    if (cont1 == 1)
    {
        c1.addNumber(num1);
        c1.addNumber(num2);
        c1.addNumber(num3);
    }
    else if (cont1 == 2)
    {
        c1.addNumber(num1);
        c1.addNumber(num2);
    }
    else if (cont1 == 2)
    {
        c1.addNumber(num1);
    }
    else
        cout << "Cannot add more than 4 numbers" << endl;

    deleteContact(c2);
    // if (cont2 == 1)
    // {
    //     string num1;
    //     num1 = c1.getNumber1();
    // }
    // else if (cont2 == 2)
    // {
    //     string num1, num2;
    //     num1 = c1.getNumber1();
    //     num2 = c1.getNumber2();
    // }
    // else if (cont2 == 3)
    // {
    //     string num1, num2, num3;
    //     num1 = c1.getNumber1();
    //     num2 = c1.getNumber2();
    //     num3 = c1.getNumber3();
    // }
    // else
    // {
    //     string num1, num2, num3, num4;
    //     num1 = c1.getNumber1();
    //     num2 = c1.getNumber2();
    //     num3 = c1.getNumber3();
    //     num4 = c1.getNumber4();
    // }
}


void Capitalization(string &name)
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
