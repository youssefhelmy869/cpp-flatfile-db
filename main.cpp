#include <iostream>
#include <vector>
#include <stdexcept>
#include "database.hpp"

using namespace std;

int main()
{
    try
    {
        // =========================
        // TEST 1: Students table
        // =========================
        database students("students", 3, {"Name", "Age", "Grade"});

        students.insert_recored({"Ali", "16", "A"});
        students.insert_recored({"Sara", "17", "A+"});
        students.insert_recored({"Omar", "15", "B"});
        students.insert_recored({"Mariam", "16", "A"});
        students.insert_recored({"Youssef", "18", "B+"});

        cout << "Students table created successfully.\n";

        // =========================
        // TEST 2: Products table
        // =========================
        database products("products", 3, {"Product", "Price", "Stock"});

        products.insert_recored({"Laptop", "15000", "5"});
        products.insert_recored({"Phone", "8000", "10"});
        products.insert_recored({"Tablet", "6000", "7"});
        products.insert_recored({"Monitor", "4000", "3"});

        cout << "Products table created successfully.\n";

        // =========================
        // TEST 3: Edge case (should throw error)
        // =========================
        cout << "Testing invalid insert...\n";
        students.insert_recored({"OnlyName", "NoAge"}); // ❌ wrong size

        cout << "This line should NOT print.\n";
    }
    catch (const exception &e)
    {
        cout << "ERROR: " << e.what() << endl;
    }

    return 0;
}