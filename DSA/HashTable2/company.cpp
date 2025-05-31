#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Company
{
    string name;
    string tax_code;
    string address;
};

Company readCompany(string info)
{
    stringstream stream(info);
    string content;
    Company company;
    getline(stream, content, '|');
    company.name = content;
    getline(stream, content, '|');
    company.tax_code = content;
    getline(stream, content, '|');
    company.address = content;
    return company;
}

vector<Company> readCompanyList(string fileName)
{
    ifstream inFile(fileName);
    if (inFile.eof())
    {
        cout << "File is not found.";
        return {};
    }
    string line;
    vector<Company> companyList;
    getline(inFile, line);
    while (getline(inFile, line))
    {
        Company company = readCompany(line);
        companyList.push_back(company);
    }

    inFile.close();
    return companyList;
}

void printList(vector<Company> companyList)
{
    for (int i = 0; i < companyList.size(); i++)
        cout << companyList[i].name << '|' << companyList[i].tax_code << '|' << companyList[i].address << endl;
}

long long hashString(string companyName)
{
    int size = companyName.size();
    if (size > 20)
    {
        companyName = companyName.substr(size - 20);
        size = companyName.size();
    }

    long long factor = 1, hash = 0, m = 1e9 + 9;
    for (int i = 0; i < size; i++)
    {
        hash = (hash + (companyName[i] * factor) % m) % m;
        factor = (factor * 31) % m;
    }
    return hash;
}

void hashName(vector<Company> companyList)
{
    for (int i = 0; i < companyList.size(); i++)
        cout << hashString(companyList[i].name) << endl;
}

Company *createHashTable(vector<Company> listCompany)
{
    Company *hashTable = new Company[2000];
    for (int i = 0; i < 2000; i++)
    {
        hashTable[i].name = "";
        hashTable[i].tax_code = "";
        hashTable[i].address = "";
    }
    for (Company comp : listCompany)
    {
        int idx = hashString(comp.name)  % 2000;
        int i = 0;
        while (!hashTable[idx].name.empty() && i < 2000)
        {
            idx = (idx + 1) % 2000;
            i++;
        }
        hashTable[idx] = comp;
    }
    return hashTable;
}

void printHash(Company *hashTable)
{
    int idx = 0;
    for (int i = 0; i < 2000; i++)
    {

        if (!hashTable[i].name.empty())
        {
            cout << "Index " << i << ": " << hashTable[i].name << " | "
                 << hashTable[i].tax_code << " | "
                 << hashTable[i].address << endl;
            idx++;
            if (idx >= 5)
                break;
        }
    }
}

void Insert(Company *hashTable, Company company)
{
    int idx = hashString(company.name) % 2000; // Tính chỉ số băm ban đầu
    int i = 0;

    while (!hashTable[idx].name.empty() && i < 2000)
    {
        idx = (idx + 1) % 2000;
        i++;
    }

    if (i == 2000)
    {
        cout << "Error: Hash table is full, cannot insert " << company.name << endl;
    }
    else
    {
        hashTable[idx] = company;
        cout << "Inserted " << company.name << " at index " << idx << endl;
    }
}

Company *Search(Company *hashTable, string companyName)
{
    int idx = hashString(companyName) % 2000;
    int i = 0;

    while (i < 2000)
    {
        if (hashTable[idx].name.empty())
            return NULL;

        if (hashTable[idx].name == companyName)
            return &hashTable[idx];

        idx = (idx + 1) % 2000;
        i++;
    }

    return NULL;
}
int main()
{
    vector<Company> companyList = readCompanyList("MST.txt");
    // printList(companyList);
    // hashName(companyList);
    // cout << "-----------" << endl;
    // cout << hashString("CONG TY CO PHAN THUONG MAI CHAU DUC PHAT");
    Company *hashTable = createHashTable(companyList);
    // Company newCompany = {"CONG TY TNHH MOI", "123456789", "123 Address Street"};
    // Insert(hashTable, newCompany);
    printHash(hashTable);

    // string companyName = "CONG TY CO PHAN THUONG MAI CHAU DUC PHAT";
    // Company *foundCompany = Search(hashTable, companyName);

    // if (foundCompany != NULL)
    // {
    //     cout << "Company found:" << endl;
    //     cout << "Name: " << foundCompany->name << endl;
    //     cout << "Tax Code: " << foundCompany->tax_code << endl;
    //     cout << "Address: " << foundCompany->address << endl;
    // }
    // else

    //     cout << "Company not found." << endl;

    delete[] hashTable;
    return 0;
}