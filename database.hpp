#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

class database
{
public:
    database(string idatabase_name, int inumber_of_feilds, vector<string> feild_names)
    {
        if (inumber_of_feilds != feild_names.size())
        {
            throw invalid_argument("number of feilds are not consistent");
        }
        this->feild_names = feild_names;
        database_name = idatabase_name;
        number_of_feilds = inumber_of_feilds;
        string filename = database_name + ".txt";
        ofstream file(filename);
        if (!file)
        {
            throw runtime_error("Could not create database file");
        }
        string first_row = "index"; // is the names of each feild
        for (string &field : feild_names)
        {
            first_row = first_row + " | " + field;
        }
        file << first_row << "\n";
    }
    

private:
    string database_name;
    int number_of_feilds;
    int index = 1;
    vector<string> feild_names;
};