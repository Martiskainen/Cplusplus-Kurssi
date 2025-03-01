#include <iostream>
#include <vector>

using namespace std;

struct Student
{
    string name_;
    string birth_day_;
};

// Prints the given student and preceding text if such is given.
void print(Student* student, const string& pre_text = "")
{
    cout << pre_text;
    if(student)
    {
        cout << student->name_ << " --- " << student->birth_day_ << endl;
    }
    else
    {
        cout << "None" << endl;
    }
}

// TODO: Write the new functions here
// Function to find the first occurrence of a student with matching name and birthday
Student* find_first_occurrence(const string& name, const string& birth_day, const vector<Student*>& students)
{
    for (Student* student : students)
    {
        if (student && student->name_ == name && student->birth_day_ == birth_day)
        {
            return student;
        }
    }
    return nullptr;
}

// Function to find and print the students that are in both given courses
void find_same(const vector<Student*>& course1, const vector<Student*>& course2)
{
    for (Student* student1 : course1)
    {
        for (Student* student2 : course2)
        {
            if (student1 && student2 && student1->name_ == student2->name_ && student1->birth_day_ == student2->birth_day_
                && student1->name_ != "")
            {
                cout << "* Same student in two courses: " << student1->name_ << " --- " << student1->birth_day_ << endl;
                break;
            }
        }
    }
}

// Function to find and print students who have identical names and birthdays but are different students
void find_identical(const vector<Student*>& course)
{
    for (size_t i = 0; i < course.size(); ++i)
    {
        Student* current_student = course.at(i);
        for (size_t j = i + 1; j < course.size(); ++j)
        {
            Student* other_student = course.at(j);
            if (current_student && other_student && current_student->name_ == other_student->name_ && current_student->birth_day_ == other_student->birth_day_
                && current_student != other_student) // Ensure that they are different students
            {
                cout << "* Identical students in a course: " << current_student->name_ << " --- " << current_student->birth_day_ << endl;
            }
        }
    }
}



// Don't remove! Needed for tests.
#ifndef POINTERS_TEST
#define POINTERS_TEST
// Don't remove! Needed for tests.

// Main function (an example test case)
int main()
{
    // Students
    Student stud1{"Mortti", "2001-01-01"};
    Student stud2{"Vertti", "2002-02-02"};
    Student stud3{"Mortti", "2001-01-01"};

    // Assigning students to courses
    vector<Student*> prog1 = {nullptr, &stud1, &stud2};
    vector<Student*> prog2 = {&stud1, &stud2, nullptr, &stud3};
    vector<Student*> prog3 = {&stud1, &stud3};

    // Different seaches
    cout << "Seaching for same students from two different courses" << endl;
    find_same(prog1, prog2);

    cout << endl << "Searching for identical students from a course" << endl;
    find_identical(prog3);

    cout << endl << "Searching for a certain student from a course" << endl;
    Student* wanted = find_first_occurrence("Mortti", "2001-01-01", prog1);
    print(wanted, "* ");
    wanted = find_first_occurrence("Mortti", "2002-02-02", prog1);
    print(wanted, "* ");

    return 0;
}

// Don't remove! Needed for tests.
#endif //POINTERS_TEST
// Don't remove! Needed for tests.
