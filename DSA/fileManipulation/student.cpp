#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Examinee
{
    string name, id;
    float math = 0, literature = 0, foreign_language = 0;
};

Examinee readExaminee(fstream& ifile) {
    Examinee examinee;

    getline(ifile, examinee.id, ';');

    getline(ifile, examinee.name, ';');

    ifile >> examinee.math;
    ifile.ignore(1); 

    ifile >> examinee.literature;
    ifile.ignore(1);

    ifile >> examinee.foreign_language;
    ifile.ignore(1); 

    return examinee;
}

vector<Examinee> readExamineeList(string fileName)
{

    vector<Examinee> examineeList;
    fstream ifile;
    ifile.open(fileName, ios::in);
    if (ifile.eof())
    {
        cout << "File is not found.";
        return {};
    }

    string line;
    getline(ifile, line);
    while (!ifile.eof())
    {
        Examinee examinee = readExaminee(ifile);
        examineeList.push_back(examinee);
    }
    ifile.close();
    return examineeList;
}

void writeTotal(vector<Examinee> examineeList, string outFileName)
{

    fstream ofile;
    ofile.open(outFileName, ios::out);
    if (ofile.eof())
    {
        cout << "File is not found.";
        return;
    }

    for (Examinee examinee : examineeList)
    {

        cout << examinee.id << " " << examinee.name << " " << examinee.math << " " << examinee.literature << " "
            << examinee.foreign_language << endl;
        ofile << examinee.id << " " << examinee.name << " " << examinee.math << " " << examinee.literature << " "
            << examinee.foreign_language << endl;
    }
    ofile.close();
}
int main()
{
    vector<Examinee> examnineeList = readExamineeList("input.txt");
    writeTotal(examnineeList, "output.txt");
    return 0;
}