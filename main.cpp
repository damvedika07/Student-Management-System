#include <iostream>
#include <fstream>
using namespace std;

class Student {
public:
   int id;
    char name[50];
    int age;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Age: ";
        cin >> age;
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nAge: " << age << endl;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::app | ios::binary);
    s.input();
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Student Added Successfully!\n";
}

void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }
    file.close();
}

void deleteStudent(int id) {
    Student s;
    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    cout << "Student Deleted Successfully!\n";
}

void updateStudent(int id) {
    Student s;
    fstream file("students.dat", ios::in | ios::out | ios::binary);

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "Enter new details:\n";
            s.input();

            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));
            cout << "Student Updated!\n";
            return;
        }
    }

    file.close();
    cout << "Student Not Found!\n";
}

int main() {
    int choice, id;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Delete Student\n";
        cout << "4. Update Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3:
                cout << "Enter ID to delete: ";
                cin >> id;
                deleteStudent(id);
                break;
            case 4:
                cout << "Enter ID to update: ";
                cin >> id;
                updateStudent(id);
                break;
        }
    } while(choice != 5);

    return 0;
}