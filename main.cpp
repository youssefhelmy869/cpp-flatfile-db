#include <iostream>
#include "database.hpp"

using namespace std;

int main()
{
    try
    {
        cout << "Creating database...\n";

        database students(
            "Students",
            4,
            {"Name", "Age", "Grade", "Class"});

        cout << "Database created.\n\n";

        // =====================================
        // Insert 1000 records
        // =====================================

        cout << "Inserting records...\n";

        for (int i = 1; i <= 1000; ++i)
        {
            students.insert_recored({"Student_" + to_string(i),
                                     to_string(10 + (i % 9)),
                                     string(1, 'A' + (i % 5)),
                                     "Class_" + to_string((i % 10) + 1)});
        }

        cout << "1000 records inserted.\n\n";

        // =====================================
        // Retrieve records
        // =====================================

        cout << "Testing find_record...\n";

        vector<int> test_ids = {1, 100, 500, 750, 1000};

        for (int id : test_ids)
        {
            vector<string> rec = students.find_record(id);

            cout << "Record " << id << ": ";

            for (string &value : rec)
            {
                cout << value << " ";
            }

            cout << '\n';
        }

        cout << '\n';

        // =====================================
        // Update records
        // =====================================

        cout << "Updating records...\n";

        students.update_record(
            1,
            {"UPDATED_STUDENT",
             "18",
             "A+",
             "Elite_Class"});

        students.update_record(
            500,
            {"MIDPOINT_STUDENT",
             "17",
             "B+",
             "Special_Class"});

        students.update_record(
            1000,
            {"LAST_STUDENT",
             "19",
             "A+",
             "Top_Class"});

        cout << "Updates completed.\n\n";

        // =====================================
        // Verify updates
        // =====================================

        cout << "Verifying updates...\n";

        for (int id : {1, 500, 1000})
        {
            vector<string> rec = students.find_record(id);

            cout << "Record " << id << ": ";

            for (string &value : rec)
            {
                cout << value << " ";
            }

            cout << '\n';
        }

        cout << '\n';

        // =====================================
        // Invalid find test
        // =====================================

        cout << "Testing invalid find...\n";

        try
        {
            students.find_record(2000);
        }
        catch (exception &e)
        {
            cout << "Expected error: "
                 << e.what()
                 << '\n';
        }

        cout << '\n';

        // =====================================
        // Invalid insert test
        // =====================================

        cout << "Testing invalid insert...\n";

        try
        {
            students.insert_recored(
                {"OnlyName",
                 "OnlyAge"});
        }
        catch (exception &e)
        {
            cout << "Expected error: "
                 << e.what()
                 << '\n';
        }

        cout << '\n';

        // =====================================
        // Invalid update test
        // =====================================

        cout << "Testing invalid update...\n";

        try
        {
            students.update_record(
                1500,
                {"Fake",
                 "10",
                 "C",
                 "Class"});
        }
        catch (exception &e)
        {
            cout << "Expected error: "
                 << e.what()
                 << '\n';
        }

        cout << '\n';

        // =====================================
        // Stress retrieval
        // =====================================

        cout << "Running retrieval stress test...\n";

        for (int i = 1; i <= 1000; ++i)
        {
            students.find_record(i);
        }
        cout << "1000 retrievals completed.\n\n";

        cout << "All tests completed successfully.\n";
    }
    catch (exception &e)
    {
        cout << "\nFATAL ERROR:\n";
        cout << e.what() << '\n';
    }

    return 0;
}