#include <iostream>
#include <thread>
#include <aclapi.h>
#include <fstream>
#include <list>
#include <string.h>
#include <bits/stdc++.h>
#include <windows.h>
#include <mutex>
#include <stdlib.h>

using namespace std;

// Files Name
static const string MANAGERS_FILE_NAME = "data/managers_file.txt";
static const string CUSTOMERS_FILE_NAME = "data/customers_file.txt";
static const string ORDERS_FILE_NAME = "data/orders_file.txt";
static const string PRODUCTS_FILE_NAME = "data/products_file.txt";
static const string CATEGORIES_FILE_NAME = "data/categories_file.txt";
static const string LIST_APPETIZER = "Appetizer";
static const string LIST_DRINKS = "Drinks";
static const string LIST_FAST_FOOD = "Fast Food";
static const string LIST_PERSIAN_FOOD = "Persian Food";
static const string LIST_DESERS = "Desers";

const int LIST_ARRAY_SIZE = 5;

std::mutex mtx;

static const string LISTS_DETAIL[LIST_ARRAY_SIZE][2] =
    {
        {LIST_APPETIZER, "1"},
        {LIST_DRINKS, "2"},
        {LIST_FAST_FOOD, "3"},
        {LIST_PERSIAN_FOOD, "4"},
        {LIST_DESERS, "5"}};

// Main Colors
static const string COLOR_STYLE = "0x70";

class Login;

// Enums Type
enum PERSON_TYPE
{
    MANAGER,
    CUSTOMER
};

enum COLORS
{
    RED,
    BLUE,
    BLACK,
    WHITE,
    GREEN
};

enum ORDERED_BY
{
    TIME,
    PRICE
};
// System logic functions

void go(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord);
}

// use to get x position
int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(
            GetStdHandle(STD_OUTPUT_HANDLE),
            &csbi))
        return -1;
    return csbi.dwCursorPosition.X;
}

// use to get y position
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(
            GetStdHandle(STD_OUTPUT_HANDLE),
            &csbi))
        return -1;
    return csbi.dwCursorPosition.Y;
}

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void clear()
{
    system("cls");
    system("color F3");
    for (int i = 0; i <= 119; i++)
    {
        go(i, 0);
        cout << char(219);
    }
    for (int i = 1; i < 30; i++)
    {
        go(0, i);
        cout << char(219);
        go(119, i);
        cout << char(219);
    }
    go(1, 1);
    SetConsoleTextAttribute(h, 0xF0);
}

// generate data model id
string generateId(int digit)
{
    srand(time(0));
    int tavan = 1;
    for (int i = 1; i <= digit; i++)
    {
        tavan *= 10;
    }
    return to_string(rand() % tavan);
}

list<string> stringToListW(string input)
{
    list<string> words;

    stringstream stream(input);

    string word;
    while (stream >> word)
    {
        words.push_back(word);
    }
    return words;
}

string readLine()
{
    string input;
    if (cin.peek() == '\n')
        cin.ignore();
    getline(cin, input);
    return input;
}

// this function called to check if input is number or not ; this function used for show invalid inputs
bool is_number(string s)
{
    std::string::iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

// Data Models
struct Person
{
private:
    string username;
    string password;
    string id;
    string name;
    string phoneNumber;

public:
    void print()
    {
        SetConsoleTextAttribute(h, 0xFD);
        go(15, wherey());
        cout << "--------------------------------------------------------------------------------------\n";
        go(15, wherey());
        cout << "Username : " << username << "\t||\t"
             << "Name : " << name << "     || \t"
             << "Phone Number : " << phoneNumber << "\n";
        go(15, wherey());
        cout << "--------------------------------------------------------------------------------------\n";
        SetConsoleTextAttribute(h, 0xF0);
        go(1, wherey());
    }
    void setUsername(string _username)
    {
        username = _username;
    }
    string getUsername()
    {
        return username;
    }
    void setPassword(string _password)
    {
        password = _password;
    }
    string getPassword()
    {
        return password;
    }
    void setId(string _id)
    {
        id = _id;
    }
    string getId()
    {
        return id;
    }
    void setName(string _name)
    {
        name = _name;
    }
    string getName()
    {
        return name;
    }
    void setPhone(string _phone)
    {
        phoneNumber = _phone;
    }
    string getPhone() { return phoneNumber; }
};

struct Order
{
private:
    string id;
    string parentId;
    list<string> productsId;
    list<int> productsCount;
    long price;
    int time;
    bool isPaid;
    bool isReady;

public:
    bool hasProduct = false;

    void setId(string _id)
    {
        id = _id;
    }

    string getId()
    {
        return id;
    }

    void setParentId(string _parentId)
    {
        parentId = _parentId;
    }

    string getParentId() { return parentId; }

    void setProductsId(string ids)
    {
        productsId = stringToListW(ids);
    }
    list<string> getProductsId() { return productsId; }

    string getProductsIdString()
    {
        string ids = "";

        list<string>::iterator it = productsId.begin();
        while (it != productsId.end())
        {
            ids += *it + " ";

            it++;
        }
        return ids;
    }

    void setProductsCount(string _counts)
    {
        list<string> counts = stringToListW(_counts);
        list<string>::iterator it = counts.begin();
        while (it != counts.end())
        {
            productsCount.push_back(stoi(*it));
            if (!hasProduct)
                hasProduct = true;
            it++;
        }
    }

    list<int> getProductsCount() { return productsCount; }

    string getProductsCString()
    {
        string counts = "";

        list<int>::iterator it = productsCount.begin();
        while (it != productsCount.end())
        {
            counts += to_string(*it) + " ";
            it++;
        }
        return counts;
    }

    void setPrice(string _price)
    {
        price = stoi(_price);
    }

    void setPrice(long _price)
    {
        price = _price;
    }

    int getPrice()
    {
        return price;
    }

    void setTime(string _time)
    {
        time = stoi(_time);
    }

    void setTime(int _time)
    {
        time = _time;
    }

    int getTime()
    {
        return time;
    }

    void setPaid(int condition)
    {
        if (condition == 0)
            isPaid = false;
        else if (condition == 1)
            isPaid = true;
    }

    bool getPaid() { return isPaid; }

    void setReady(int condition)
    {
        if (condition == 0)
            isReady = false;
        else if (condition == 1)
            isReady = true;
    }

    bool getReady()
    {
        return isReady;
    }

    void addProduct(string id, int count)
    {
        list<string>::iterator it = productsId.begin();
        list<int>::iterator itC = productsCount.begin();
        bool isExist = false;
        while (it != productsId.end())
        {
            if (id == *it)
            {
                isExist = true;
                break;
            }
            it++;
            itC++;
        }

        if (isExist)
        {
            productsCount.insert(itC, *itC + count);
            productsCount.erase(itC);
        }
        else
        {
            productsId.push_back(id);
            productsCount.push_back(count);
        }
        if (!hasProduct)
            hasProduct = true;
    }

    void removeProduct(string id, int count)
    {

        list<string>::iterator it = productsId.begin();
        list<int>::iterator itC = productsCount.begin();

        while (it != productsId.end())
        {
            if (*it == id)
            {
                if (count >= *itC)
                {
                    productsId.erase(it);
                    productsCount.erase(itC);
                    break;
                }
                else
                {
                    productsCount.insert(itC, *itC - count);
                    productsCount.erase(itC);
                    break;
                }
            }
            it++;
            itC++;
        }
    }
};

struct Product
{
private:
    string name;
    long price;
    string id;
    string parentId;
    string information;
    int time;

public:
    void setName(string _name)
    {
        name = _name;
    }

    string getName() { return name; }

    void setPrice(string _price)
    {
        price = stoi(_price);
    }

    long getPrice()
    {
        return price;
    }

    void setId(string _id) { id = _id; }
    string getId() { return id; }

    void setParentId(string _id) { parentId = _id; }
    string getParentId() { return parentId; }

    void setTime(string _time)
    {
        time = stoi(_time);
    }
    int getTime() { return time; }

    string getInfo()
    {
        return information;
    }
    void setInfo(string info)
    {
        information = info;
    }
};

struct List
{
    list<Product> products;
    string name;
    string id;

public:
    void setName(string _name) { name = _name; }
    string getName() { return name; }

    void setId(string _id) { id = _id; }
    string getId() { return id; }

    void setProducts(list<Product> _products) { products = _products; }

    list<Product> getProducts() { return products; }
};

class FileManager
{
public:
    Person isPersonExist(string username, string password, PERSON_TYPE type)
    {
        ifstream *file;
        switch (type)
        {
        case MANAGER:
            file = new ifstream(MANAGERS_FILE_NAME);
            break;
        case CUSTOMER:
            file = new ifstream(CUSTOMERS_FILE_NAME);
            break;

        default:
            break;
        }

        string line;
        Person person;
        long pointer = 0;
        bool founded = false;
        bool userF = false;

        while (getline(*file, line))
        {

            switch (pointer)
            {
            case 0:
                if (line == username)
                {
                    userF = true;
                }
                else
                {
                    userF = false;
                }
                break;
            case 1:
                if (line == password && userF)
                {
                    userF = true;
                }
                else
                {
                    userF = false;
                }
                break;
            case 2:
                person.setId(line);
                break;
            case 3:
                person.setName(line);
                break;
            case 4:
                person.setPhone(line);
                break;
            case 5:
                if (line == "NEXT")
                {
                    if (userF)
                    {
                        founded = true;
                    }
                    else
                    {
                        founded = false;
                        pointer = -1;
                    }
                }
                break;
            default:
                break;
            }

            if (founded)
            {
                if (userF)
                {
                    person.setUsername(username);
                    person.setPassword(password);
                }
                break;
            }

            pointer++;
        }
        return person;
    }

    Person getPerson(string id)
    {
        ifstream customers_file(CUSTOMERS_FILE_NAME);
        string line;
        string all[5];
        int pointer = 0;
        bool founded = false;
        bool nextT = false;

        while (getline(customers_file, line))
        {
            if (line == id)
            {
                founded = true;
            }
            else if (line == "NEXT")
            {
                if (founded)
                {
                    break;
                }
                else
                {
                    pointer = 0;
                    nextT = true;
                }
            }
            if (!nextT)
            {
                all[pointer] = line;
                pointer++;
            }
            else
                nextT = false;
        }

        Person person;
        if (founded)
        {
            person.setUsername(all[0]);
            person.setPassword(all[1]);
            person.setId(all[2]);
            person.setName(all[3]);
            person.setPhone(all[4]);
        }
        return person;
    }

    void addNewPerson(Person p, PERSON_TYPE type)
    {

        ofstream *file;
        if (type == CUSTOMER)
        {
            file = new ofstream(CUSTOMERS_FILE_NAME, ios::app);
        }
        else if (type == MANAGER)
        {
            file = new ofstream(MANAGERS_FILE_NAME, ios::app);
        }
        *file << p.getUsername() << '\n'
              << p.getPassword() << '\n'
              << p.getId() << '\n'
              << p.getName() << '\n'
              << p.getPhone() << '\n'
              << "NEXT\n";

        file->close();
    }

    void updateManager(Person manager, Person p)
    {
        ifstream manager_file_if(MANAGERS_FILE_NAME);
        string line;
        string all = "";
        bool founded;
        int pointer = 0;

        while (getline(manager_file_if, line))
        {
            switch (pointer)
            {
            case 0:
                if (line == manager.getUsername())
                {
                    founded = true;
                    line = p.getUsername();
                }
                else
                {
                    founded = false;
                    pointer = 0;
                }
                break;
            case 1:
                if (founded)
                {
                    line = p.getPassword();
                }
                break;
            case 2:
                if (founded)
                    line = p.getId();
                break;
            case 3:
                if (founded)
                    line = p.getName();
                break;
            case 4:
                if (founded)
                    line = p.getPhone();
                break;
            default:
                break;
            }

            all += line + "\n";
            if (founded)
                pointer++;
        }
        ofstream manager_file_of(MANAGERS_FILE_NAME);
        manager_file_of << all;
        manager_file_of.close();
    }

    void deleteProduct(string id)
    {
        ifstream product_file_if(PRODUCTS_FILE_NAME);
        string line;
        string all = "", add = "";
        bool founded;

        while (getline(product_file_if, line))
        {
            if (line == id)
                founded = true;
            add += line + '\n';
            if (line == "NEXT")
            {
                if (founded == false)
                    all += add;
                else
                    founded = false;
                add = "";
            }
        }
        ofstream product_file_of(PRODUCTS_FILE_NAME);
        product_file_of << all;
        product_file_of.close();
    }

    void addProduct(Product p)
    {

        ofstream file(PRODUCTS_FILE_NAME, ios::app);

        file << p.getParentId() << '\n'
             << p.getId() << '\n'
             << p.getName() << '\n'
             << p.getPrice() << '\n'
             << p.getTime() << '\n'
             << p.getInfo() << '\n'
             << "NEXT\n";

        file.close();
    }

    void updateProduct(Product p, string id, int i)
    {
        ifstream product_file_if(PRODUCTS_FILE_NAME);
        string line;
        string all = "";
        bool founded;
        int pointer = 0;

        while (getline(product_file_if, line))
        {
            switch (pointer)
            {
            case 0:
                if (line == id)
                {
                    founded = true;
                }
                else
                {
                    founded = false;
                    pointer = 0;
                }
                break;
            case 1:
                if (founded && i == 1)
                    line = p.getName();
                break;
            case 2:
                if (founded && i == 2)
                    line = to_string(p.getPrice());
                break;
            case 3:
                if (founded && i == 3)
                    line = to_string(p.getTime());
                break;
            case 4:
                if (founded && i == 4)
                    line = p.getInfo();
                break;
            default:
                break;
            }

            all += line + "\n";
            if (founded)
                pointer++;
        }
        ofstream product_file_of(PRODUCTS_FILE_NAME);
        product_file_of << all;
        product_file_of.close();
    }

    list<Order> getOrders(string parentId)
    {
        ifstream orders_file(ORDERS_FILE_NAME);
        string line;
        int pointer = 0;
        bool putIn = false;
        list<Order> orders;
        Order *order;
        while (getline(orders_file, line))
        {
            switch (pointer)
            {
            case 0:
                if (line == parentId || parentId == "TRUE")
                {
                    putIn = true;
                    order = new Order();
                    order->setParentId(line);
                }
                break;
            case 1:
                if (putIn)
                    order->setId(line);
                break;
            case 2:
                if (putIn)
                    order->setProductsId(line);
                break;
            case 3:
                if (putIn)
                    order->setProductsCount(line);
                break;
            case 4:
                if (putIn)
                    order->setPrice(line);
                break;
            case 5:
                if (putIn)
                    order->setTime(line);
                break;
            case 6:
                if (putIn)
                    order->setReady(stoi(line));
                break;
            case 7:
                if (putIn)
                    order->setPaid(stoi(line));
                break;
            case 8:
                if (line == "NEXT" && putIn)
                {
                    orders.push_back(*order);
                    putIn = false;
                }
                pointer = -1;
                break;
            default:
                break;
            }
            pointer++;
        }

        return orders;
    }

    Order getOrder(string orderId)
    {
        ifstream order_file(ORDERS_FILE_NAME);
        string line;
        string details[7];
        string lastLine;
        int foundedLine = 0;
        while (getline(order_file, line))
        {
            if (foundedLine > 0 && foundedLine <= 7)
            {
                if (foundedLine == 7)
                {
                    break;
                }
                details[foundedLine] = line;
                foundedLine++;
            }
            else if (line == orderId)
            {
                details[0] = lastLine;
                details[1] = line;
                foundedLine = 2;
            }
            else
            {
                lastLine = line;
            }
        }
        Order order;

        if (foundedLine > 2)
        {
            order.setParentId(details[0]);
            order.setId(details[1]);
            order.setProductsId(details[2]);
            order.setProductsCount(details[3]);
            order.setPrice(details[4]);
            order.setTime(details[5]);
            order.setReady(stoi(details[6]));
            order.setPaid(stoi(details[7]));
        }
        return order;
    }

    list<List> getPList()
    {
        list<List> lists;
        List *listP;
        for (int i = 0; i < LIST_ARRAY_SIZE; i++)
        {
            listP = new List();
            listP->setName(LISTS_DETAIL[i][0]);
            listP->setId(LISTS_DETAIL[i][1]);
            listP->setProducts(getProducts(listP->getId()));
            list<Product>::iterator it = listP->getProducts().begin();
            lists.push_back(*listP);
        }
        return lists;
    }

    list<Product> getProducts(string code)
    {
        ifstream products_file(PRODUCTS_FILE_NAME);

        list<Product> products;
        Product *product;

        string all[6];
        string line;
        int pointer = 0;
        bool putIn = false;
        while (getline(products_file, line))
        {
            if (line == code)
            {
                putIn = true;
            }
            if (putIn)
            {
                if (line == "NEXT")
                {
                    product = new Product();
                    product->setParentId(all[0]);
                    product->setId(all[1]);
                    product->setName(all[2]);
                    product->setPrice(all[3]);
                    product->setTime(all[4]);
                    product->setInfo(all[5]);
                    products.push_back(*product);
                    pointer = 0;
                    putIn = false;
                }
                else
                {
                    all[pointer] = line;
                    pointer++;
                }
            }
        }

        return products;
    };

    list<Product> getProducWIds(list<string> ids)
    {
        list<string>::iterator it;
        ifstream products_file(PRODUCTS_FILE_NAME);

        list<Product> products;
        Product *product;

        string line;

        int pointer = -1;
        bool founded = false;

        while (getline(products_file, line))
        {
            pointer++;
            switch (pointer)
            {
            case 0:
                product = new Product();
                product->setParentId(line);
                break;
            case 1:
                it = ids.begin();
                while (it != ids.end())
                {
                    if (line == *it)
                    {
                        founded = true;
                        product->setId(line);
                        break;
                    }
                    it++;
                }
                break;
            case 2:
                if (founded)
                    product->setName(line);
                break;
            case 3:
                if (founded)
                    product->setPrice(line);

                break;
            case 4:
                if (founded)
                    product->setTime(line);
                break;
            case 5:
                product->setInfo(line);
                break;
            case 6:
                if (line == "NEXT")
                {
                    if (founded)
                    {
                        products.push_back(*product);
                        founded = false;
                    }
                    pointer = -1;
                }
                break;

            default:
                break;
            }
        }

        it = ids.begin();
        list<Product> orderedProducts;
        while (it != ids.end())
        {
            list<Product>::iterator itP = products.begin();
            while (itP != products.end())
            {
                if (itP->getId() == *it)
                    break;
                itP++;
            }
            orderedProducts.push_back(*itP);
            it++;
        }
        return orderedProducts;
    }

    void changeOrderDetail(Order order)
    {
        ifstream order_file_if(ORDERS_FILE_NAME);
        string line;
        string all = "";
        bool founded;
        int pointer = 0;

        while (getline(order_file_if, line))
        {
            switch (pointer)
            {
            case 0:
                if (line == order.getParentId())
                {
                    founded = true;
                }
                else
                {
                    founded = false;
                    pointer = 0;
                }
                break;

            case 1:
                if (!(line == order.getId() && founded))
                {
                    founded = false;
                    pointer = 0;
                }
                break;
            case 2:
                if (founded)
                    line = order.getProductsIdString();
                break;
            case 3:
                if (founded)
                    line = order.getProductsCString();
                break;
            case 4:
                if (founded)
                    line = to_string(order.getPrice());
                break;
            case 5:
                if (founded)
                    line = to_string(order.getTime());
                break;
            case 6:
                if (founded)
                    line = to_string(order.getReady());
                break;
            case 7:
                if (founded)
                {
                    line = to_string(order.getPaid());
                }

                break;
            default:
                break;
            }

            all += line + "\n";
            if (founded)
                pointer++;
        }
        ofstream order_file_of(ORDERS_FILE_NAME);
        order_file_of << all;
        order_file_of.close();
    }

    void addOrder(Order order)
    {
        if (order.hasProduct)
        {
            ofstream order_file(ORDERS_FILE_NAME, ios::app);
            order_file << order.getParentId() << "\n"
                       << order.getId() << "\n";
            string productsId = "";
            list<string> ids = order.getProductsId();
            go(1, wherey() + 1);
            cout << productsId.size() << endl;
            go(1, wherey());

            list<string>::iterator itId = ids.begin();

            while (itId != ids.end())
            {
                productsId += *itId + " ";
                itId++;
            }
            string productsCount = "";
            list<int> counts = order.getProductsCount();
            list<int>::iterator itCount = counts.begin();

            while (itCount != counts.end())
            {
                productsCount += to_string(*itCount) + " ";
                itCount++;
            }
            order_file << productsId << "\n"
                       << productsCount << "\n"
                       << order.getPrice() << "\n"
                       << order.getTime() << "\n"
                       << order.getReady() << "\n"
                       << order.getPaid() << "\n"
                       << "NEXT\n";
            order_file.close();
        }
    }

    void removeOrder(string id)
    {
        ifstream order_file_if(ORDERS_FILE_NAME);
        string line;
        string all = "", add = "";
        bool founded;

        while (getline(order_file_if, line))
        {
            if (line == id)
                founded = true;
            add += line + '\n';
            if (line == "NEXT")
            {
                if (founded == false)
                    all += add;
                else
                    founded = false;
                add = "";
            }
        }
        ofstream order_file_of(ORDERS_FILE_NAME);
        order_file_of << all;
        order_file_of.close();
    }
};

// global variables
FileManager fileManager;

// Check Files When code run in new system
class SystemInstalled
{
    FileManager fileManager;

    void checkFilesExist()
    {
        ifstream chefs_file(MANAGERS_FILE_NAME);
        ifstream customers_file(CUSTOMERS_FILE_NAME);
        ifstream orders_file(ORDERS_FILE_NAME);
        ifstream products_file(PRODUCTS_FILE_NAME);
        if (!chefs_file.good())
            createManagerFile();
        if (!customers_file.good())
            createCustomersFile();
        if (!orders_file.good())
            createOrderFile();
        if (!products_file.good())
            createProductsFile();
    }
    void createManagerFile()
    {
        ofstream chefs_file(MANAGERS_FILE_NAME);
        // Add me and morteza account as an chef
        chefs_file << "KIANMEHR\n12345678\n13\nKian\n09351231231\nNEXT\nMORTEZA\n87654321\n21\nMorteza\n093261272172\nNEXT\n";
        chefs_file.close();
    }
    void createCustomersFile()
    {
        ofstream customers_file(CUSTOMERS_FILE_NAME);
        // Add Baghery as an customer
        customers_file << "BAGHERI\n1379\n312\nBagheri\n09245654842\nNEXT\n";
        customers_file.close();
    }
    void createOrderFile()
    {
        ofstream orders_file(ORDERS_FILE_NAME);
        orders_file.close();
    }
    void createProductsFile()
    {
        ofstream products_file(PRODUCTS_FILE_NAME);
        products_file.close();
    }

public:
    void checkFiles()
    {
        checkFilesExist();
    }
};

class Customer
{
private:
    Person customer;
    Order *cart;
    bool firstTime = true;
    list<List> lProducts;
    list<Order> orders;
    bool paiedOption = false;
    bool backOS = false;
    int ordersC = 0;

    void getOrders()
    {
        orders = fileManager.getOrders(customer.getId());
    }

    void setUpList()
    {
        lProducts = fileManager.getPList();
    }

    // check if exit any order which didn't paid . add paid option
    list<Order> ordersNP;

    int paidOption()
    {
        ordersNP.clear();
        list<Order>::iterator it = orders.begin();

        while (it != orders.end())
        {
            if (!it->getPaid())
                ordersNP.push_back(*it);
            it++;
        }
        if (ordersNP.size() > 0)
        {
            cout << "3-Bill Payment\n\n";
            go(1, wherey());
            paiedOption = true;
            return 1;
        }
        else
        {
            paiedOption = false;
            return 0;
        }
    }

    void paidUi()
    {
        clear();
        cout << "=========================================Payment Of Orders=========================================\n\n";
        go(1, wherey());
        list<Order>::iterator it = ordersNP.begin();

        while (it != ordersNP.end())
        {

            cout << "Order Id : " << it->getId() << ":------->"
                 << "Price : " << it->getPrice() << " Toman"
                 << "\t" << it->getParentId();
            go(1, wherey() + 1);
            cout << "----------------------------------------------------------------------\n";
            go(1, wherey());
            it++;
        }
        cout << "Enter the order ID to pay for it\n";
        go(1, wherey());
        cout << "8-Back\n";
        go(1, wherey());
        string input;
        cin >> input;
        go(1, wherey());
        if (is_number(input))
        {
            if (stoi(input) != 8)
            {
                it = ordersNP.begin();
                bool founded = false;
                while (it != ordersNP.end())
                {
                    if (it->getId() == input)
                    {
                        founded = true;
                        break;
                    }
                    it++;
                }
                if (founded)
                {
                    clear();
                    cout << "Put customer cart number \n";
                    go(1, wherey());
                    string cartNumber;
                    cin >> cartNumber;
                    go(1, wherey());
                    cout << "Put customer cart password \n";
                    go(1, wherey());
                    string cartPass;
                    cin >> cartPass;
                    go(1, wherey());
                    it->setPaid(1);

                    fileManager.changeOrderDetail(*it);
                    clear();

                    cout << " Operation has successfully end . "
                         << it->getPrice() << " was deducted from customer bank account.\n";
                    go(1, wherey());
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    setUpUi();
                }
                else
                {
                    clear();
                    cout << "INVALID INPUT TRY AGAIN \n";
                    go(1, wherey());
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    paidUi();
                }
            }
            else
            {
                setUpUi();
            }
        }
        else
        {
            clear();
            cout << "INVALID INPUT TRY AGAIN \n";
            go(1, wherey());
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            paidUi();
        }
    }

    // Check if exist any order add regiter option
    bool registerOOption(int n)
    {
        if (cart->hasProduct)
        {
            cout << n << "-"
                 << "Register Order\n\n";
            go(1, wherey());
            return true;
        }
        return false;
    }

    void removePFC()
    {
        cout << "\n\n";
        go(1, wherey());
        string input[2];
        cout << "Enter Product ID (8-Back): ";
        cin >> input[0];
        go(1, wherey());
        if (is_number(input[0]))
            if (input[0] != "8")
            {
                cout << "Enter Product Count(8-Back): ";
                cin >> input[1];
                go(1, wherey());
                if (is_number(input[1]))
                {
                    if (input[1] != "8")
                    {

                        cart->removeProduct(input[0], stoi(input[1]));

                        clear();

                        cout << "Product Removed !!! ";
                        this_thread::sleep_for(chrono::milliseconds(1000));
                        if (cart->getProductsId().size() != 0)
                        {
                            registerUi();
                        }
                        else
                        {
                            cart->hasProduct = false;
                            setUpUi();
                        }
                    }
                    else
                    {
                        registerUi();
                    }
                }
                else
                {
                    clear();
                    cout << "INVALID INPUT TRY AGAIN";
                    go(1, wherey() + 1);
                    this_thread::sleep_for(chrono::milliseconds(1000));
                }
            }
            else
            {
                registerUi();
            }
    }

    void registerUi()
    {
        clear();
        cout << "Selected Products : \n\n";
        go(1, wherey());
        list<Product> products = fileManager.getProducWIds(cart->getProductsId());
        list<Product>::iterator it = products.begin();
        list<int> productsCount = cart->getProductsCount();
        list<int>::iterator itCount = productsCount.begin();
        long totalTime = 0;
        long totalPrice = 0;
        long totalCount = 0;
        cout << "ID\t\tName\t\tPrice\t\tTime\t\tCount\t\tTotal Price";
        while (it != products.end())
        {
            go(1, wherey() + 1);
            cout << "----------------------------------------------------------------------------------------------\n";
            go(1, wherey());
            cout << it->getId();
            go(16, wherey());
            cout << it->getName();
            go(32, wherey());
            long price = (it->getPrice()) * (*itCount);
            cout << it->getPrice();
            go(48, wherey());
            cout << it->getTime();
            go(64, wherey());
            cout << *itCount;
            totalCount += *itCount;
            go(80, wherey());
            cout << price;
            go(1, wherey() + 1);
            cout << "----------------------------------------------------------------------------------------------\n";
            go(1, wherey());
            if (it->getTime() > totalTime)
                totalTime = it->getTime();
            totalPrice += price;
            it++;
            itCount++;
        }
        go(1, wherey() + 1);
        cout << "----------------------------------------------------------------------------------------------\n";
        go(1, wherey());
        cout << "Total Price : " << totalPrice << "\t"
             << "Total Time : " << totalTime << "\t"
             << "Total Count : " << totalCount;
        go(1, wherey() + 1);
        cout << "----------------------------------------------------------------------------------------------\n";
        go(1, wherey() + 1);

        cout << "1-Remove Product ";
        go(1, wherey() + 2);
        cout << "2-Add Product";
        go(1, wherey() + 2);
        cout << "3-Order";
        go(1, wherey() + 2);
        cout << "8-Back\n\n";
        go(1, wherey());
        cart->setTime(totalTime);
        cart->setPrice(totalPrice);
        string input;
        cin >> input;
        go(1, wherey());

        if (!is_number(input))
            input = "100";

        switch (stoi(input))
        {
        case 1:
            removePFC();
            break;
        case 2:
            setUpPUi(1);
            break;
        case 3:
            if (customer.getId() == "")
                customer.setId(generateId(5));
            cart->setParentId(customer.getId());
            cart->setId(generateId(3));
            fileManager.addOrder(*cart);
            cart = new Order();
            clear();
            cout << "Order successfully registered !!!";
            this_thread::sleep_for(chrono::milliseconds(1000));
            setUpUi();

            break;
        case 8:
            setUpUi();
            break;
        default:
            clear();
            cout << "INVALID INPUT TRY AGAIN";
            go(1, wherey() + 1);
            this_thread::sleep_for(chrono::milliseconds(1000));
            registerUi();
            break;
        }
    }

    void createSubscriptionUi()
    {
        Person person;
        clear();
        cout << "Username : ";
        person.setUsername(readLine());
        go(1, wherey());
        cout << "Password: ";
        person.setPassword(readLine());
        go(1, wherey());
        cout << "Phone Number : ";
        person.setPhone(readLine());
        go(1, wherey());
        cout << "Name : ";
        person.setName(readLine());
        if (customer.getId() != "")
            person.setId(customer.getId());
        else
            person.setId(generateId(5));

        fileManager.addNewPerson(person, CUSTOMER);
        clear();
        cout << "Subscription created successfully ! ! !";
        customer = person;
        this_thread::sleep_for(chrono::milliseconds(1000));
        firstTime = false;
        setUpUi();
    }

    void cancelOrderUi()
    {
        clear();
        cout << "Enter Order ID : ";
        string input;
        cin >> input;
        if (is_number(input))
        {
            Order order = fileManager.getOrder(input);
            if (order.hasProduct)
            {
                if (!order.getReady())
                {
                    fileManager.removeOrder(order.getId());
                    clear();
                    cout << "Order Removed !!!";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    ordersConditionUi();
                }
                else
                {
                    cout << "The order is ready, you can not change it !!!";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    cancelOrderUi();
                }
            }
            else
            {
                go(1, wherey());
                cout << "INVALID ID TRAY AGAIN !!!";
                this_thread::sleep_for(chrono::milliseconds(1000));
                cancelOrderUi();
            }
        }
        else
        {
            go(1, wherey());
            cout << "INVALID INPUT TRAY AGAIN !!!";
            this_thread::sleep_for(chrono::milliseconds(1000));
            cancelOrderUi();
        }
    }

    void ordersConditionUi()
    {
        clear();
        cout << "=====================<< All Orders >>=====================\n\n";
        go(1, wherey());
        cout << "Order ID\t\tTotal Time\t\tTime left ";
        list<Order>::iterator it = orders.begin();
        bool orderExist = false;
        while (it != orders.end())
        {
            go(1, wherey() + 1);
            cout << "----------------------------------------------------------\n";
            go(1, wherey());
            cout << it->getId();
            go(24, wherey());
            cout << it->getTime();
            go(1, wherey() + 1);
            cout << "----------------------------------------------------------\n";
            go(1, wherey());
            it++;
        }
        go(1, wherey() + 1);
        cout << "1-Cancel the order";
        go(1, wherey() + 2);
        cout << "8-Back\n\n";
        go(1, wherey());
        string input;
        cin >> input;

        if (!is_number(input))
            input = "100";
        switch (stoi(input))
        {
        case 1:
            cancelOrderUi();
            break;
        case 8:
            setUpUi();
            return;
            break;

        default:
            clear();
            go(1, wherey() + 2);
            cout << "INVALID INPUT\n\n";
            go(1, wherey());
            this_thread::sleep_for(chrono::milliseconds(500));
            break;
        }
    }

    int setUpUi()
    {
        clear();
        printOrders();
        bool selected = true;
        while (true)
        {
            string input;

            cout << "Options : ";
            go(1, wherey() + 2);
            cout << "1-Menu";
            go(1, wherey() + 2);
            cout << "2-Create Subscription";
            if (!firstTime)
            {
                cout << "(Unavailable)";
            }
            cout << "\n\n";
            go(1, wherey());
            int paidOExist = paidOption();

            bool registerOExist = registerOOption(3 + paidOExist);
            if (ordersC > 0)
            {
                cout << "5-Order";
                if (ordersC > 1)
                    cout << "s";
                cout << "Condition\n\n";
                go(1, wherey());
            }
            cout << "8-Back";
            go(1, wherey() + 2);
            SetConsoleTextAttribute(h, 0xF4);
            cout << "0-Exit\n\n";
            SetConsoleTextAttribute(h, 0xF0);
            go(1, wherey());

            cin >> input;
            go(1, wherey());
            if (!is_number(input))
                input = "100";
            switch (stoi(input))
            {
            case 1:
                setUpPUi(1);
                selected = true;
                break;
            case 2:
                if (firstTime)
                {
                    createSubscriptionUi();
                    selected = true;
                }
                else
                {
                    go(1, wherey() + 1);
                    cout << "Unavailable Input (You Have Account)\n\n";
                    go(1, wherey());
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    selected = false;
                }
                break;
            case 3:
                if (paidOExist == 1)
                {
                    paidUi();
                    selected = true;
                }
                else if (registerOExist)
                {
                    registerUi();
                    selected = true;
                }
                break;

            case 4:
                if (paidOExist == 1 && registerOExist)
                {
                    registerUi();
                    selected = true;
                }
                else
                {
                    go(1, wherey() + 1);
                    cout << "INVALID INPUT TRY AGAIN \n";
                    go(1, wherey());
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    selected = false;
                }
                break;
            case 5:
                ordersConditionUi();
                break;
            case 0:
                if (!paiedOption)
                    return 0;
                else
                {
                    go(1, wherey() + 1);
                    cout << "You did not pay your bill . First pay it and then leave resturant or we call police :) !!! \n";
                    go(1, wherey());
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    selected = false;
                }
                break;
            case 8:
                selected = true;
                backOS = true;
                break;
            default:
                go(1, wherey() + 1);
                cout << "INVALID INPUT TRY AGAIN \n";
                go(1, wherey());
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                selected = false;
                break;
            }
            if (selected)
                break;
        }
        if (backOS)
        {
            return 1;
        }
        else
            return 0;
    }

    void setUpPUi(int tryN)
    {
        if (tryN == 1)
            setProductsList();
        clear();
        cout << "Select One of these list :";
        go(1, wherey() + 2);
        cout << "1-" << LIST_APPETIZER;
        go(1, wherey() + 2);
        cout << "2-" << LIST_DRINKS;
        go(1, wherey() + 2);
        cout << "3-" << LIST_FAST_FOOD;
        go(1, wherey() + 2);
        cout << "4-" << LIST_PERSIAN_FOOD;
        go(1, wherey() + 2);
        cout << "5-" << LIST_DESERS;
        go(1, wherey() + 2);
        cout << "8-Back\n\n";
        go(1, wherey());

        string input;

        cin >> input;
        go(1, wherey());

        switch (stoi(input))
        {
        case 1:
            setListUi(PRICE, LIST_APPETIZER);
            break;
        case 2:
            setListUi(PRICE, LIST_DRINKS);
            break;
        case 3:
            setListUi(PRICE, LIST_DRINKS);
            break;
        case 4:
            setListUi(PRICE, LIST_PERSIAN_FOOD);
            break;
        case 5:
            setListUi(PRICE, LIST_DESERS);
            break;
        case 8:
            clear();
            setUpUi();
            break;
        default:
            clear();
            go(1, wherey() + 1);
            cout << " INVALID INPUT TRY AGAIN\n";
            go(1, wherey());
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            setUpPUi(2);
            break;
        }
    }

    void setListUi(ORDERED_BY type, string name)
    {
        clear();
        list<List>::iterator it = lProducts.begin();

        while (it != lProducts.end())
        {
            if (it->getName() == name)
            {
                break;
            }
            it++;
        }
        cout << "============================================<<" << it->getName() << ">>============================================\n\n";
        go(1, wherey());
        list<Product> products = it->getProducts();
        products = orderProductsList(products, type);
        list<Product>::iterator itP = products.begin();
        cout << "ID\t\tName\t\tPrice\t\tTime\t\tInfo\n";
        go(1, wherey());
        while (itP != products.end())
        {
            cout << "--------------------------------------------------------------------------------------------------\n";
            go(1, wherey());

            cout << itP->getId();
            go(16, wherey());
            cout << itP->getName();
            go(32, wherey());
            cout << itP->getPrice();
            go(48, wherey());
            cout << itP->getTime();
            go(64, wherey());
            cout << itP->getInfo();
            go(1, wherey() + 1);
            cout << "--------------------------------------------------------------------------------------------------\n";
            go(1, wherey());
            itP++;
        }
        checkSelectP(name, products);
    }

    list<Product> orderProductsList(list<Product> products, ORDERED_BY type)
    {
        list<Product> newProducts;
        list<Product>::iterator itN = products.begin();
        while (itN != products.end())
        {
            list<Product>::iterator it = products.begin();
            list<Product>::iterator itMax;
            long max = -1;
            while (it != products.end())
            {
                long c = (type == PRICE) ? it->getPrice() : it->getTime();
                if (c >= max)
                {
                    bool exist = false;
                    if (newProducts.size() > 0)
                    {
                        list<Product>::iterator itT = newProducts.begin();
                        while (itT != newProducts.end())
                        {
                            if (itT->getId() == it->getId())
                            {
                                exist = true;
                                break;
                            }
                            itT++;
                        }
                    }
                    if (!exist)
                    {
                        if (type == PRICE)
                            max = it->getPrice();
                        else if (type == TIME)
                            max = it->getTime();
                        itMax = it;
                    }
                }
                it++;
            }
            newProducts.push_back(*itMax);
            itN++;
        }

        return newProducts;
    }

    // get  product code from customer and then check if that id exist or not ;
    void checkSelectP(string name, list<Product> products)
    {
        go(1, wherey() + 1);
        cout << "To add food in your order just enter product ID";
        go(1, wherey() + 1);
        cout << "(8-Back)(Change the order of products : 1-Price 2-Time )\n";
        go(1, wherey());
        string input;
        cin >> input;
        go(1, wherey());

        if (input == "1" || input == "2")
        {
            setListUi(((input == "1") ? PRICE : TIME), name);
            return;
        }

        if (is_number(input))
        {
            int inputN = stoi(input);
            if (inputN == 8)
            {
                setUpPUi(1);
                return;
            }
            else
            {
                list<Product>::iterator itP = products.begin();
                bool founded = false;
                while (itP != products.end())
                {
                    if (itP->getId() == input)
                    {
                        founded = true;
                        break;
                    }
                    itP++;
                }
                if (founded)
                {
                    getCountSP(*itP, name);
                }
                else
                {
                    go(1, wherey() + 1);
                    cout << "INVALID INPUT TRY AGAIN \n";
                    go(1, wherey());
                    checkSelectP(name, products);
                }
            }
        }
        else
        {
            go(1, wherey() + 1);
            cout << "INVALID INPUT TRY AGAIN \n";
            go(1, wherey());
            checkSelectP(name, products);
        }
    }

    // after customer select product. this function called and get count of that product
    void getCountSP(Product product, string name)
    {
        clear();

        cout << "How many of this food do you want?";
        go(1, wherey() + 1);
        cout << "8-Back\n";
        go(1, wherey());
        cout << product.getName()
             << "-->>count : ";
        string input;
        cin >> input;
        go(1, wherey());

        if (is_number(input))
        {
            int nInput = stoi(input);
            if (nInput != 8)
            {
                cart->addProduct(product.getId(), nInput);
                go(1, wherey());
                cout << "You added "
                     << input << " Of "
                     << product.getName() << " In your order ";
                std::this_thread::sleep_for(std::chrono::milliseconds(150));
                setListUi(PRICE, name);
            }
            else
            {
                setListUi(PRICE, name);
            }
        }
        else
        {
            clear();
            cout << "INVALID INPUT TRY AGAIN";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            getCountSP(product, name);
        }
    }

    // get Products from file Manager
    void setProductsList()
    {
        lProducts = fileManager.getPList();
    }

    // this function called if user has account and this function get all orders
    void printOrders()
    {
        cout << "======================================================Orders======================================================\n";
        go(1, wherey());
        getOrders();
        ordersC = 0;
        list<Order>::iterator it = orders.begin();
        bool orderExist = false;
        while (it != orders.end())
        {
            go(1, wherey());
            cout << "------------------------------------------------------------------------------------------------------------------\n";
            go(1, wherey());
            cout
                << "Order Id : " << it->getId() << " || "
                << "Price : " << it->getPrice() << " || "
                << "Time : " << it->getTime() << " minutes"
                << " || "
                << "Condition : "
                << ((it->getReady()) ? "Ready !!" : "Baking")
                << " || ";

            cout << "Payment Condition : "
                 << ((it->getPaid()) ? "Paid $$" : "Unpaid");
            go(1, wherey() + 1);
            cout << "------------------------------------------------------------------------------------------------------------------\n";
            go(1, wherey());
            it++;
            orderExist = true;
            ordersC++;
        }
        if (!orderExist)
        {
            go(1, wherey() + 1);
            cout << "                                            << Order Dosen't Exist >>                                               \n";
        }
        go(1, wherey() + 1);
        cout << "==================================================================================================================\n\n";
        go(1, wherey());
    }

public:
    Customer(Person _customer)
    {
        customer = _customer;

        _customer.print();
        if (customer.getUsername() != "")
            firstTime = false;

        cart = new Order();
    }

    int setUpUiP()
    {
        return setUpUi();
    }
};

class Manager
{
private:
    Person manager;
    bool backOS = false;

    list<Order> getAllOrders()
    {
        list<Order> orders = fileManager.getOrders("TRUE");
        return orders;
    }

    void removeOrderUi()
    {
        clear();
        cout << "Order ID to remove order\n";
        go(1, wherey());
        cout << "or\n";
        go(1, wherey());
        cout << "Customer ID to remove customer orders\n";
        go(1, wherey());
        cout << "(8-Back)\n";
        go(1, wherey());
        string input;
        cin >> input;
        go(1, wherey());
        if (stoi(input) == 8)
            setUpUi();
        fileManager.removeOrder(input);
        clear();
        cout << "Order removed sucssefully";

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

        setUpUi();
    }
    // change order condition ui :: call this when change order conditon option selected
    void changeOrderCUi()
    {
        clear();
        string id;
        cout << "Enter Order ID :(8-Back) ";
        cin >> id;
        if (is_number(id))
        {
            if (stoi(id) == 8)
            {
                ordersUi();
                return;
            }
            Order order = fileManager.getOrder(id);
            string input;
            if (order.hasProduct)
            {
                go(1, wherey());
                cout << "Baking Condition :(8-Back)(0-Backing 1-Ready) ";
                cin >> input;
                if (is_number(input))
                {
                    if (stoi(input) == 8)
                    {
                        ordersUi();
                        return;
                    }
                    else
                    {
                        order.setReady(stoi(input));
                        go(1, wherey());
                        cout << "Paid Condition :(8-Back)(0-unPaid 1-Paid) ";
                        cin >> input;
                        if (stoi(input) == 8)
                        {
                            changeOrderCUi();
                            return;
                        }
                        else
                        {
                            order.setPaid(stoi(input));
                            fileManager.changeOrderDetail(order);
                            clear();
                            cout << "Order Condition Chagnes !!!";
                            this_thread::sleep_for(chrono::milliseconds(1000));
                            ordersUi();
                            return;
                        }
                    }
                }
                else
                {
                    clear();
                    cout << "INVALID INPUT !!!";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    changeOrderCUi();
                }
            }
            else
            {
                clear();
                cout << "INVALID Order ID!!!";
                this_thread::sleep_for(chrono::milliseconds(1000));
                changeOrderCUi();
            }
        }
        else
        {
            clear();
            cout << "INVALID INPUT !!!";
            this_thread::sleep_for(chrono::milliseconds(1000));
            changeOrderCUi();
        }
    }

    // orders option ui
    void ordersUi()
    {
        clear();
        manager.print();
        cout << "1-Show all orders\n\n";
        go(1, wherey());
        cout << "2-Change product order\n\n";
        go(1, wherey());
        cout << "3-Remove order\n\n";
        go(1, wherey());
        cout << "8-Back\n\n";
        go(1, wherey());
        string input;
        cin >> input;

        if (!is_number(input))
            input = "100";
        switch (stoi(input))
        {
        case 1:
            printOrders(false);
            break;
        case 2:
            changeOrderCUi();
            break;
        case 3:
            removeOrderUi();
            break;
        case 8:
            setUpUi();
            break;
        default:
            break;
        }
    }

    list<Product> getAllProduct()
    {
        list<Product> products;
        for (int i = 0; i < LIST_ARRAY_SIZE; i++)
        {
            products.splice(products.end(), fileManager.getProducts(LISTS_DETAIL[i][1]));
        }
        return products;
    }

    void showAllProduct()
    {
        clear();
        cout << "=================================================<<"
             << "All products"
             << ">>=================================================\n\n";
        go(1, wherey());
        list<Product> products = getAllProduct();
        list<Product>::iterator itP = products.begin();
        cout << "Parent ID\t\tID\t\tName\t\tPrice\t\tTime\t\tInfo\n";
        go(1, wherey());
        while (itP != products.end())
        {
            cout << "------------------------------------------------------------------------------------------------------------\n";
            go(1, wherey());
            cout << itP->getParentId();
            go(24, wherey());
            cout << itP->getId();
            go(40, wherey());
            cout << itP->getName();
            go(56, wherey());
            cout << itP->getPrice();
            go(72, wherey());
            cout << itP->getTime();
            go(88, wherey());
            cout << itP->getInfo();
            go(1, wherey() + 1);
            cout << "------------------------------------------------------------------------------------------------------------\n";
            go(1, wherey());
            itP++;
        }

        cout << "8-Back\n\n";
        go(1, wherey());
        string input;
        cin >> input;

        if (!is_number(input))
            input = "100";
        if (stoi(input) == 8)
            setUpUi();
    }

    void addNewManagerUi()
    {
        stoi(to_string('8'));
        string input;
        Person p;
        clear();
        manager.print();

        cout << "Set username: ";
        cin >> input;
        p.setUsername(input);
        go(1, wherey() + 1);
        cout << "Set password: ";
        cin >> input;
        p.setPassword(input);
        go(1, wherey() + 1);
        cout << "Set name: ";
        input = readLine();
        p.setName(input);
        go(1, wherey() + 1);
        cout << "Set phone number: ";
        cin >> input;
        go(1, wherey());
        p.setPhone(input);
        p.setId(generateId(5));
        fileManager.addNewPerson(p, MANAGER);

        clear();
        cout << p.getUsername() << "'s manager account created sucssefully";

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

        setUpUi();
    }

    void updateManagerUi()
    {
        Person p;
        clear();
        manager.print();
        cout << "1-Change username\n\n";
        go(1, wherey());
        cout << "2-Change password\n\n";
        go(1, wherey());
        cout << "3-Change name\n\n";
        go(1, wherey());
        cout << "4-Change phone number\n\n";
        go(1, wherey());
        cout << "8-Back\n\n";
        go(1, wherey());
        string input, input1;
        cin >> input;

        clear();
        manager.print();

        if (!is_number(input))
            input = "100";
        if (stoi(input) == 8)
            managerSUi();
        for (int i = 1; i <= 4; i++)
        {
            switch (i)
            {
            case 1:
                if (stoi(input) == i)
                {
                    cout << "Set your new username: ";
                    cin >> input1;
                    p.setUsername(input1);
                }
                else
                    p.setUsername(manager.getUsername());
                break;
            case 2:
                if (stoi(input) == i)
                {
                    cout << "Set your new password: ";
                    cin >> input1;
                    p.setPassword(input1);
                }
                else
                    p.setPassword(manager.getPassword());

                break;
            case 3:
                if (stoi(input) == i)
                {
                    cout << "Set your new name: ";
                    input1 = readLine();
                    p.setName(input1);
                }
                else
                    p.setName(manager.getName());
                break;
            case 4:
                if (stoi(input) == i)
                {
                    cout << "Set your new phone number: ";
                    cin >> input1;
                    p.setPhone(input1);
                }
                else
                    p.setPhone(manager.getPhone());

                break;
            default:
                break;
            }
        }
        p.setId(manager.getId());
        fileManager.updateManager(manager, p);
        manager = p;
        clear();
        cout << "Your information changed sucssefully";

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

        setUpUi();
    }

    void deleteProductUi()
    {
        clear();
        manager.print();
        cout << "Product ID or name:(8-Back) ";
        string input;
        input = readLine();
        if (input == "8")
            setUpUi();
        fileManager.deleteProduct(input);
        clear();
        cout << "Product deleted sucssefully";

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

        setUpUi();
    }

    void updateProductUi()
    {
        Product p;
        clear();
        manager.print();
        cout << "1-Change product name\n\n";
        go(1, wherey());
        cout << "2-Change product price\n\n";
        go(1, wherey());
        cout << "3-Change product time\n\n";
        go(1, wherey());
        cout << "4-Change information\n\n";
        go(1, wherey());
        cout << "8-Back\n\n";
        go(1, wherey());
        string input, id, New;
        cin >> input;

        clear();
        manager.print();
        cout << "Product ID: ";
        cin >> id;
        go(1, wherey());
        p.setId(id);

        if (!is_number(input))
            input = "100";
        if (stoi(input) == 8)
            productSUi();
        for (int i = 1; i <= 4; i++)
        {
            switch (i)
            {
            case 1:
                if (stoi(input) == i)
                {
                    cout << "Set product new name: ";
                    New = readLine();
                    p.setName(New);
                }
                break;
            case 2:

                if (stoi(input) == i)
                {
                    cout << "Set product new price: ";
                    cin >> New;
                    p.setPrice(New);
                }
                break;
            case 3:

                if (stoi(input) == i)
                {
                    cout << "Set product new waiting time: ";
                    cin >> New;
                    p.setTime(New);
                }
                break;
            case 4:
                if (stoi(input) == i)
                {
                    cout << "Set product new information: ";
                    New = readLine();
                    p.setInfo(New);
                }
                break;
            default:
                break;
            }
        }

        fileManager.updateProduct(p, id, stoi(input));
        clear();
        cout << "Product data changed sucssefully";

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

        setUpUi();
    }

    void addProductUi()
    {
        string input;
        Product p;
        clear();
        manager.print();
        cout << "Lists:\n";
        go(1, wherey());

        for (int i = 0; i < LIST_ARRAY_SIZE; i++)
        {
            cout << LISTS_DETAIL[i][0]
                 << " ID -->="
                 << LISTS_DETAIL[i][1]
                 << "\n";
            go(1, wherey());
        }
        go(1, wherey() + 1);
        cout << "Set product list ID: ";
        cin >> input;
        p.setParentId(input);
        go(1, wherey() + 1);
        cout << "Set product name: ";
        input = readLine();
        p.setName(input);
        go(1, wherey() + 1);
        cout << "Set product price: ";
        cin >> input;
        p.setPrice(input);
        go(1, wherey() + 1);
        cout << "Set product time: ";
        cin >> input;
        p.setTime(input);
        go(1, wherey() + 1);
        cout << "Set product information: ";
        input = readLine();
        p.setInfo(input);

        p.setId(generateId(3));
        fileManager.addProduct(p);

        clear();
        cout << "Product added sucssefully";

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

        setUpUi();
    }

    void managerSUi()
    {
        clear();
        manager.print();
        cout << "1-Change your information\n\n";
        go(1, wherey());
        cout << "2-Add new manager\n\n";
        go(1, wherey());
        cout << "8-Back\n\n";
        go(1, wherey());
        string input;
        cin >> input;

        if (!is_number(input))
            input = "100";
        switch (stoi(input))
        {
        case 1:
            updateManagerUi();
            break;
        case 2:
            addNewManagerUi();
            break;
        case 8:
            setUpUi();
            break;
        default:
            break;
        }
    }

    void productSUi()
    {
        clear();
        manager.print();
        cout << "1-See products\n\n";
        go(1, wherey());
        cout << "2-Change producs data\n\n";
        go(1, wherey());
        cout << "3-Add new product\n\n";
        go(1, wherey());
        cout << "4-Delete product\n\n";
        go(1, wherey());
        cout << "8-Back\n\n";
        go(1, wherey());
        string input;
        cin >> input;

        if (!is_number(input))
            input = "100";
        switch (stoi(input))
        {
        case 1:
            showAllProduct();
            break;
        case 2:
            updateProductUi();
            break;
        case 3:
            addProductUi();
            break;
        case 4:
            deleteProductUi();
            break;
        case 8:
            setUpUi();
            break;
        default:
            break;
        }
    }

    int setUpUi()
    {
        clear();
        manager.print();
        cout << "1-Orders\n\n";
        go(1, wherey());
        cout << "2-Products\n\n";
        go(1, wherey());
        cout << "3-Managers setting\n\n";
        go(1, wherey());
        cout << "8-Back\n\n";
        go(1, wherey());
        SetConsoleTextAttribute(h, 0xF4);
        cout << "0-Exit\n\n";
        SetConsoleTextAttribute(h, 0xF0);
        go(1, wherey());

        string input;
        cin >> input;
        if (!is_number(input))
        {
            input = "100";
        }
        switch (stoi(input))
        {
        case 1:
            ordersUi();
            break;

        case 2:
            productSUi();
            break;

        case 3:
            managerSUi();
            break;

        case 8:
            backOS = true;
            break;

        case 0:
            break;

        default:
            clear();
            cout << "INVALID INPUT TRY AGAIN !!!";
            this_thread::sleep_for(chrono::milliseconds(1000));
            setUpUi();
            break;
        }
        if (backOS)
            return 1;
        else
            return 0;
    }

    list<Order> orderedByPay(list<Order> orders, bool orderedBy)
    {
        list<Order>::iterator it = orders.begin();
        list<Order> newSO;
        while (it != orders.end())
        {
            if (it->getPaid() == orderedBy)
                newSO.push_back(*it);
            else
                newSO.push_front(*it);
            it++;
        }
        return newSO;
    }

    // This function used to print all orders
    void printOrders(bool orderedBy)
    {
        clear();
        cout << "======================================================Orders======================================================\n\n";
        go(1, wherey());
        list<Order> orders = getAllOrders();
        orders = orderedByPay(orders, orderedBy);
        cout << "Customer Name\t\tID\t\tPrice\t\tTime\t\tCondition\t\tPayment Condition\n";

        list<Order>::iterator it = orders.begin();
        bool orderExist = false;
        Person *person;
        while (it != orders.end())
        {
            go(1, wherey() + 1);
            cout << "------------------------------------------------------------------------------------------------------------------\n";
            go(1, wherey());

            person = new Person();
            *person = fileManager.getPerson(it->getParentId());
            if (person->getName() != "")
                cout << person->getName();
            else
                cout << "Without Subsc... ";
            go(24, wherey());
            cout << it->getId();
            go(40, wherey());
            cout << it->getPrice();
            go(56, wherey());
            cout << it->getTime();
            go(72, wherey());
            cout << ((it->getReady()) ? "Ready !!" : "Baking");
            go(96, wherey());
            cout << ((it->getPaid()) ? "Paid $$" : "Unpaid");
            go(1, wherey() + 1);
            cout << "------------------------------------------------------------------------------------------------------------------\n";
            go(1, wherey());
            it++;
            orderExist = true;
        }
        if (!orderExist)
        {

            go(1, wherey() + 1);
            cout << "                                            << Order Dosen't Exist >>                                               \n";
        }
        go(1, wherey() + 1);
        cout << "==================================================================================================================\n";
        go(1, wherey());

        while (true)
        {
            go(1, wherey() + 2);
            cout << "1-Order By ";
            cout << ((orderedBy) ? "paid" : "unPaid");
            go(1, wherey() + 2);
            cout << "8-Back\n\n";
            go(1, wherey());
            string input;
            cin >> input;
            if (!is_number(input))
                input = "100";

            if (stoi(input) == 8)
            {
                ordersUi();
                break;
            }
            else if (stoi(input) == 1)
            {
                printOrders(!orderedBy);
                break;
            }
            else
            {
                go(1, wherey() + 2);
                cout << "INVALID INPUT\n\n";
                go(1, wherey());
                this_thread::sleep_for(chrono::milliseconds(500));
            }
        }
    }

public:
    Manager(Person _manager)
    {
        manager = _manager;
        clear();
    }

    int setUpUiP()
    {
        return setUpUi();
    }
};

class Login
{
private:
    void mainUi()
    {
        clear();

        string input;
        go(5, wherey() + 1);
        SetConsoleTextAttribute(h, 0xF2);
        cout << "Login as a : \n\n";
        SetConsoleTextAttribute(h, 0xF0);
        go(9, wherey());
        cout << "1-Manager\n\n";
        go(9, wherey());
        cout << "2-Customer\n\n";
        go(9, wherey());
        SetConsoleTextAttribute(h, 0xF4);
        cout << "0-Exit\n\n";
        SetConsoleTextAttribute(h, 0xF0);
        go(9, wherey());
        cin >> input;
        if (!is_number(input))
            input = "100";
        switch (stoi(input))
        {
        case 1:
            managerUi();
            break;
        case 2:
            customerUi();
            break;
        case 0:
            return;
            break;
        default:
            clear();
            cout << "INVALID INPUT!!!";

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            mainUi();
            break;
        }
    }

    void managerUi()
    {
        string username;
        string password;
        clear();

        cout << "Username : ";
        cin >> username;
        cout << endl;
        go(1, wherey());
        cout << "Password : ";
        cin >> password;

        loginAsManager(fileManager.isPersonExist(username, password, MANAGER));
    }

    void customerUi()
    {
        clear();
        cout << "Do you have subscription ?\n";
        go(1, wherey());
        cout << "1-Yes\n";
        go(1, wherey());
        cout << "2-No\n";
        go(1, wherey());
        cout << "8-Back\n";
        go(1, wherey());
        int n;
        cin >> n;
        if (n == 8)
        {
            mainUi();
        }
        else if (n == 1)
        {
            string username;
            string password;
            clear();

            cout << "Username : ";
            cin >> username;
            go(1, wherey() + 1);
            cout << "Password : ";
            cin >> password;
            loginAsCustomer(fileManager.isPersonExist(username, password, CUSTOMER));
        }
        else if (n == 2)
        {
            Person person;
            Customer customer(person);
            if (customer.setUpUiP() == 1)
            {
                setUpPage();
            }
        }
        else
        {
            wrongInformation(CUSTOMER);
        }
    }
    void wrongInformation(PERSON_TYPE type)
    {
        int invalidT = 0;
        while (true)
        {
            if (invalidT == 0)
            {
                clear();
                cout << "We can't find account with this information !!!";
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            }
            else if (invalidT == 3)
            {
                mainUi();
                break;
            }
            clear();
            cout << "Want to try again ?\n";
            go(1, wherey());
            cout << "1-Yes\n";
            go(1, wherey());
            cout << "8-Back\n";
            go(1, wherey());
            long n;
            cin >> n;
            if (n == 8)
            {
                mainUi();
                break;
            }
            else if (n == 1)
            {
                if (type == MANAGER)
                    managerUi();
                else if (type == CUSTOMER)
                    customerUi();
                break;
            }
            else
            {
                clear();
                cout << "INVALID INPUT!!!";

                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            invalidT++;
        }
    }

    void loginAsManager(Person person)
    {
        if (person.getUsername() != "")
        {
            Manager manager(person);
            if (manager.setUpUiP() == 1)
            {
                setUpPage();
            }
        }
        else
        {
            wrongInformation(MANAGER);
        }
    }

    void loginAsCustomer(Person person)
    {
        if (person.getUsername() != "")
        {
            Customer customer(person);
            if (customer.setUpUiP() == 1)
            {
                setUpPage();
            }
        }
        else
        {
            clear();
            cout << "We can't find Customer with this information !!!";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            clear();
            customerUi();
        }
    }

public:
    // this function called when wants to load login page
    void setUpPage()
    {
        mainUi();
    }
};

int main()
{
    HWND console = GetConsoleWindow();
    RECT r;
    // GetWindowRect(console, &r);
    // MoveWindow(console, r.left, r.top, 896, 726, TRUE);

    SystemInstalled systemC;
    systemC.checkFiles();
    Login login;
    login.setUpPage();

    return 0;
}

/*
customers :
-- username --
-- password --
-- id --
-- name --
-- phone number --

manager :

-- username --
-- password --
-- id --
-- name --
-- phone number --

orders :

-- customer id --
-- id --
-- products ids --
-- products count --
-- price --
-- time --
-- condition --
-- isPaied --

product :
-- list id --
-- id --
-- name --
-- price --
-- time --
-- information --
*/
