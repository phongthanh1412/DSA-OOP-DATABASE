#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Examinee
{
    string id;
    float math = 0, literature = 0, physics = 0, chemistry = 0, biology = 0, history = 0, geography = 0,
          civic_education = 0, natural_science = 0, social_science = 0, foreign_language = 0;
};

Examinee readExaminee(string lineInfo)
{
    stringstream stream(lineInfo);
    string line;
    Examinee examinee;
    vector<float *> subjectScore{
        &examinee.math,
        &examinee.literature,
        &examinee.physics,
        &examinee.chemistry,
        &examinee.biology,
        &examinee.history,
        &examinee.geography,
        &examinee.civic_education,
        &examinee.natural_science,
        &examinee.social_science,
        &examinee.foreign_language,
    };

    if (getline(stream, line, ','))
        examinee.id = line;
    getline(stream, line, ',');
    for (int i = 0; i < subjectScore.size(); i++)
    {
        if (getline(stream, line, ','))
            *subjectScore[i] = !line.empty() ? stof(line) : 0;
    }
    examinee.natural_science = examinee.physics + examinee.chemistry + examinee.biology;
    examinee.social_science = examinee.history + examinee.geography + examinee.civic_education;
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
    while (getline(ifile, line))
    {
        Examinee examinee = readExaminee(line);
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
        int total = examinee.natural_science + examinee.social_science + examinee.math + examinee.literature + examinee.foreign_language;

        cout << examinee.math << ' ' << examinee.literature << ' ' << examinee.physics << ' ' << examinee.chemistry
             << ' ' << examinee.biology << ' ' << examinee.history << ' ' << examinee.geography << ' ' << examinee.civic_education << ' '
             << examinee.natural_science << ' ' << examinee.social_science << ' ' << examinee.foreign_language << ' ' << total << endl;

        ofile << examinee.id << ' ' << total << endl;
    }
    ofile.close();
}
int main()
{
    vector<Examinee> examnineeList = readExamineeList("data.txt");
    writeTotal(examnineeList, "outFileName.txt");
    return 0;
}