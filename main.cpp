#include <iostream>
#include "database.hpp"

using namespace std;

int main()
{
    vector<string> feilds = {"name", "age", "position", "salary"};
    database workers(true, "workers", 4, feilds);
    vector<string> names = {
        "Liam",
        "Noah",
        "Oliver",
        "Elijah",
        "James",
        "William",
        "Benjamin",
        "Lucas",
        "Henry",
        "Theodore",
        "Jack",
        "Levi",
        "Alexander",
        "Jackson",
        "Mateo",
        "Daniel",
        "Michael",
        "Mason",
        "Sebastian",
        "Ethan",
        "Logan",
        "Owen",
        "Samuel",
        "Jacob",
        "Asher",
        "Aiden",
        "John",
        "Joseph",
        "Wyatt",
        "David",
        "Leo",
        "Luke",
        "Julian",
        "Hudson",
        "Grayson",
        "Matthew",
        "Ezra",
        "Gabriel",
        "Carter",
        "Isaac",
        "Jayden",
        "Luca",
        "Anthony",
        "Dylan",
        "Lincoln",
        "Thomas",
        "Maverick",
        "Elias",
        "Josiah",
        "Charles",
        "Caleb",
        "Christopher",
        "Ezekiel",
        "Miles",
        "Jaxon",
        "Isaiah",
        "Andrew",
        "Joshua",
        "Nathan",
        "Nolan",
        "Adrian",
        "Cameron",
        "Santiago",
        "Eli",
        "Aaron",
        "Ryan",
        "Angel",
        "Cooper",
        "Waylon",
        "Easton",
        "Kai",
        "Christian",
        "Landon",
        "Colton",
        "Roman",
        "Axel",
        "Brooks",
        "Jonathan",
        "Robert",
        "Jameson",
        "Ian",
        "Everett",
        "Greyson",
        "Wesley",
        "Jeremiah",
        "Hunter",
        "Leonardo",
        "Jordan",
        "Jose",
        "Bennett",
        "Silas",
        "Nicholas",
        "Parker",
        "Beau",
        "Weston",
        "Austin",
        "Connor",
        "Carson",
        "Dominic"};
    vector<string> positions = {
        "Manager",
        "Assistant Manager",
        "Team Leader",
        "Supervisor",
        "Coordinator",
        "Administrator",
        "Director",
        "Executive",
        "Analyst",
        "Consultant",
        "Engineer",
        "Senior Engineer",
        "Junior Engineer",
        "Software Developer",
        "Web Developer",
        "Database Administrator",
        "System Administrator",
        "Network Engineer",
        "Project Manager",
        "Product Manager",
        "Accountant",
        "Financial Analyst",
        "Auditor",
        "Sales Representative",
        "Sales Manager",
        "Marketing Specialist",
        "Marketing Manager",
        "Human Resources Officer",
        "Recruiter",
        "Customer Service Representative",
        "Support Specialist",
        "Operations Manager",
        "Business Analyst",
        "Research Assistant",
        "Research Scientist",
        "Data Analyst",
        "Data Scientist",
        "Quality Assurance Engineer",
        "Quality Control Inspector",
        "Technician",
        "Mechanic",
        "Architect",
        "Graphic Designer",
        "UX Designer",
        "UI Designer",
        "Content Writer",
        "Editor",
        "Teacher",
        "Professor",
        "Intern"};
    int i = 0;
    int age = 18;
    int j = 0;

    for (auto &name : names)
    {
        ++i;
        ++age;
        ++j;
        vector<string> values = {name, to_string(age), positions[j], to_string((i * j * age) ^ i)};
        workers.insert_recored(values);
        if (i >= 99)
        {
            i = 0;
        }
        if (age >= 95)
        {
            age = 18;
        }
        if (j >= 49)
        {
            j = 0;
        }
    }

    cout << to_string(workers.find_index("position", "Assistant Manager"));
    
    return 0;
}