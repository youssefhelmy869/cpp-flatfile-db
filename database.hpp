#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;
struct record
{
    string *values = nullptr;
    int number_of_feilds;
    // first value in each must be the index
    // index 0 of the values array is the index of the recored
    record(int number_of_feilds)
    {
        this->number_of_feilds = number_of_feilds + 1;

        values = new string[this->number_of_feilds];
    }
    record(const record &) = delete;
    record &operator=(const record &) = delete;
    record(record &&) = delete;
    record &operator=(record &&) = delete;
    ~record()
    {
        delete[] values;
    }
    void add_data(vector<string> data, int record_index)
    {
        if (data.size() + 1 != number_of_feilds)
        {
            throw invalid_argument("when adding data to record number of feild was found inconsistent");
        }
        values[0] = to_string(record_index);
        int i = 1;
        for (string value : data)
        {
            values[i] = value;
            ++i;
        }
    }
    int get_record_index()
    {
        return stoi(values[0]);
    }
    vector<string> export_record()
    {
        vector<string> temp;
        for (int i = 0; i < number_of_feilds; ++i)
        {
            temp.push_back(values[i]);
        }
        return temp;
    }
};
class database
{
    // database must be consistent with 
    // . index = position in vector + 1 
    // . these varaible must always be stored
    //      - filename 
    //      - database name
    //      - number of feilds
    //      - feild names
    //      - the vector that contains the records
    // each records index value is just used to make finding a record to be 0(1) not as a primary key
public:
    
    database(bool new_database, string idatabase_name, int inumber_of_feilds = 0, vector<string> feild_names = {})
    {
        // if the new_database = false then the idatabase show be the file name

        if (inumber_of_feilds != feild_names.size())
        {
            throw invalid_argument("number of feilds are not consistent");
        }
        if (new_database == true)
        {
            this->feild_names = feild_names;
            database_name = idatabase_name;
            number_of_feilds = inumber_of_feilds;
            string filename = database_name + ".txt";

            file.open(filename, ios::out | ios::trunc);
            this->filename = filename;

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
        else
        {
            //code to extract data from old file 
        }
    }

    database(const database &) = delete;
    database &operator=(const database &) = delete;
    database(database &&) = delete;
    database &operator=(database &&) = delete;
    void insert_recored(vector<string> values)
    {
        if (values.size() != number_of_feilds)
        {
            throw invalid_argument("number of feilds are inconsistent");
        }
        string new_line = " " + to_string(next_av_index);

        for (auto &value : values)
        {
            new_line = new_line + " | " + value;
        }
        file << new_line << "\n";
        record *temp = new record(number_of_feilds);
        temp->add_data(values, next_av_index);
        records.push_back(temp);

        ++next_av_index;
    }

    vector<string> find_record(int index)
    {
        record *target_record = nullptr;
        if (index < 1 || index > records.size())
        {
            throw invalid_argument("when looking for a record the index was found to be greater than the total number of records");
        }
        target_record = records[index - 1];

        return target_record->export_record();
    }

    ~database()
    {
        for (record *rec : records)
        {
            delete rec;
        }

        file.close();
    }

    void update_record(int index, vector<string> values)
    {
        // values vector is excpected without the index value;
        if (index < 1 || index > records.size())
        {
            throw invalid_argument("index does not match any record in the database");
        }
        if (values.size() != number_of_feilds-1)
        {
            throw invalid_argument("number of feilds in does not match database");
        }
        record *target_record = records[index - 1];
        target_record->add_data(values, index);
        update_file();
    }
    void delete_record(int index)
    {
        if (index < 1 || index > records.size())
        {
            throw invalid_argument("when trying to delete a record the index inputed was inconsistent");
        }
        delete records[index - 1];
        records.erase(records.begin() + (index - 1));
        update_file();
    }

private:
    // each record has a physical index which is [index] and the index is equal to index = position in records + 1
    vector<record *> records;
    ofstream file;
    string filename;
    string database_name;
    int number_of_feilds;
    int next_av_index = 1;
    // next avalible index
    vector<string> feild_names;
    void update_file()
    {
        file.close();
        file.open(filename, ios::out | ios::trunc);
        file << "--------------------------" << database_name << "--------------------------\n";
        // make sure all the elments in the vector has the index as their posistion after a deleter or a change
        next_av_index = 1;
        for (auto &rec : records)
        {
            rec->values[0] = to_string(next_av_index);
            ++next_av_index;
        }
        string feild_names;
        for (string &name : this->feild_names)
        {
            feild_names = feild_names + name + " | ";
        }
        file << "index | " << feild_names << '\n';
        for (record *rec : records)
        {
            string new_line = "";
            vector<string> data = rec->export_record();
            for (string value : data)
            {
                new_line = new_line + " | " + value;
            }
            file << new_line << "\n";
        }
    }
};