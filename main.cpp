#include <iostream>
#include "database.hpp"

using namespace std;

int main()
{
    try
    {
        cout << "Creating database...\n";

        database students(
            "StudentsDB",
            4,
            {"Name", "Age", "Grade", "Class"});

        cout << "Database created successfully.\n\n";

        // Insert a large number of records
        cout << "Inserting records...\n";

        for (int i = 1; i <= 50; ++i)
        {
            students.insert_recored({
                "Student_" + to_string(i),
                to_string(10 + (i % 8)),
                string(1, 'A' + (i % 5)),
                "Class_" + to_string((i % 3) + 1)
            });
        }

        cout << "50 records inserted.\n\n";

        // Test random lookups
        cout << "Testing record retrieval...\n";

        for (int i = 1; i <= 10; ++i)
        {
            int idx = (i * 5) % 50 + 1;

            vector<string> rec = students.find_record(idx);

            cout << "Record " << idx << ": ";

            for (auto &v : rec)
            {
                cout << v << " ";
            }

            cout << "\n";
        }

        cout << "\nTesting boundary cases...\n";

        // First record
        vector<string> first = students.find_record(1);

        // Last record
        vector<string> last = students.find_record(50);

        cout << "First record: ";
        for (auto &v : first) cout << v << " ";
        cout << "\n";

        cout << "Last record: ";
        for (auto &v : last) cout << v << " ";
        cout << "\n";

        cout << "\nTesting invalid access...\n";
        students.find_record(999); // should throw

    }
    catch (const exception &e)
    {
        cout << "ERROR: " << e.what() << endl;
    }

    return 0;
}