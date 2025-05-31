#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Company
{
    string name;
    string tax_code;
    string address;
};

Company readCompany(string companyInfo)
{
    stringstream stream(companyInfo);
    string line;
    Company company;
    if (getline(stream, line, '|'))
        company.name = line;
    if (getline(stream, line, '|'))
        company.tax_code = line;
    if (getline(stream, line, '|'))
        company.address = line;
    return company;
}

vector<Company> readCompanyList(string fileName)
{
    fstream ifile;
    ifile.open(fileName, ios::in);
    if (ifile.eof())
    {
        cout << "File is not found.";
        return {};
    }
    string line;
    vector<Company> companyList;
    getline(ifile, line);
    while (getline(ifile, line))
    {
        Company company = readCompany(line);
        companyList.push_back(company);
    }
    ifile.close();
    return companyList;
}

void writeTotal(vector<Company> companyList, string outFileName)
{
    fstream ofile;
    ofile.open(outFileName, ios::out);
    if (ofile.eof())
    {
        cout << "File is not found.";
        return;
    }
    for (Company company : companyList)
    {
        ofile << company.name << '/' << company.tax_code << '/' << company.address << endl;
        cout << company.name << '/' << company.tax_code << '/' << company.address << endl;
    }
    ofile.close();
}
int main()
{
    vector<Company> companyList = readCompanyList("MST.txt");
    writeTotal(companyList, "outputComp.txt");
    return 0;
}