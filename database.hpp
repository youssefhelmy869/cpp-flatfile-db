#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>

using namespace std;

inline int liner_search(string value, vector<string> values)
{
    // returns the index of the value in the array if it is not in the vector then retrun - 1
    int index = -1;
    for (int i = 0; i < values.size(); ++i)
    {
        if (values[i] == value)
        {
            index = i;
            return index;
        }
    }
    return index;
}
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
            cout << "creating database\n";
            this->feild_names = feild_names;
            database_name = idatabase_name;
            number_of_feilds = inumber_of_feilds;
            string filename = database_name + ".txt";

            file.open(filename, ios::out | ios::in | ios::trunc);
            this->filename = filename;
            file << "--------------------------" << database_name << "--------------------------\n";

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

            cout << "database created succssefully\n";
        }
        else

        {
            if (idatabase_name.substr(idatabase_name.size() - 4) != ".txt")
            {
                throw invalid_argument("input does not contain a proper file name");
            }
            filename = idatabase_name;
            database_name = idatabase_name.substr(0, idatabase_name.size() - 4);
            file.open(filename, ios::in | ios::out);
            if (!file)
            {
                throw runtime_error("Could not open database file");
            }
            string feilds_line;
            getline(file, feilds_line);
            getline(file, feilds_line);
            // split string feild into vector [feild_names] using |
            string word;
            for (char ch : feilds_line)
            {
                if (ch == '|')
                {
                    if (word != "index")
                    {
                        this->feild_names.push_back(word);
                    }
                    word = "";
                }
                else if (ch != ' ')
                // feild names should not contain spaces
                {
                    word = word + ch;
                }
            }
            this->feild_names.push_back(word);
            // get the records from the file
            string line;

            while (getline(file, line))
            {
                if (line.empty())
                {
                    continue;
                }
                vector<string> values;
                string value;
                for (char ch : line)
                {
                    if (ch == '|')
                    {
                        values.push_back(value);
                        value = "";
                    }
                    else
                    {
                        value = value + ch;
                    }
                }
                values.push_back(value);
                record *temp = new record(values.size() - 1);
                int record_index = stoi(values[0]);
                vector<string> values_without_index;
                for (int i = 1; i < values.size(); ++i)
                {
                    values_without_index.push_back(values[i]);
                }
                temp->add_data(values_without_index, record_index);
                this->records.push_back(temp);
                ;
            }
            this->number_of_feilds = this->feild_names.size();
            this->next_av_index = records.size() + 1;
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
        if (values.size() != number_of_feilds - 1)
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

    int find_index(string feild_name, string value)
    {

        // if the value is not found -1 is returned
        int return_index = -1;
        // find the feild_name index that corrosponds to the index of the value in the vector in records

        int feild_name_index = liner_search(feild_name, this->feild_names);
        if (feild_name_index == -1)
        {
            throw invalid_argument("this feild name does not exsisit in the database");
        }
        // adding 1 to the feild_name_index because the feild names vector does not account for the index colum so adding one will make it
        // corrospond to the actual vector in each record
        ++feild_name_index;
        cout << "[find index] feild name found index is " << feild_name_index << "\n";
        value = remove_spaces(value);
        for (record *rec : records)
        {
            vector<string> records_values = rec->export_record();
            if (remove_spaces(records_values[feild_name_index]) == value)
            {
                return stoi(records_values[0]);
            }
        }
        if (return_index == -1)
        {
            cout << "[find_index] value was not found \n";
        }
        return return_index;
    }
    vector<int> find_all_index(string feild_name, string value)
    {
        // returns all the indexes that contain the value in a vector
        vector<int> indexes;
        int feild_name_index = liner_search(feild_name, this->feild_names);
        if (feild_name_index == -1)
        {
            throw invalid_argument("this feild does not exsit in the database");
        }
        // adding 1 to the feild_name_index because the feild names vector does not account for the index colum so adding one will make it
        // corrospond to the actual vector in each record
        ++feild_name_index;
        value = remove_spaces(value);
        for (record *rec : this->records)
        {
            vector<string> record_values = rec->export_record();
            if (remove_spaces(record_values[feild_name_index]) == value)
            {
                indexes.push_back(stoi(record_values[0]));
            }
        }
        if (indexes.empty())
        {
            cout << "[find_all_index] value was not found \n";
        }
        return indexes;
    }

private:
    // each record has a physical index which is [index] and the index is equal to index = position in records + 1
    vector<record *> records;
    fstream file;
    string filename;
    string database_name;
    int number_of_feilds;
    int next_av_index = 1;
    // next avalible index
    vector<string> feild_names;
    void update_file()
    {
        file.close();
        file.open(filename, ios::out | ios::trunc | ios::in);
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
    inline string remove_spaces(string value)
    {
        value.erase(remove(value.begin(), value.end(), ' '), value.end());
        return value;
    }
};