#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// Entity Structs
struct Student {
    int id;
    string name;
    string password;
    map<string, string> files; // File name and content
    map<string, string> attendance; // Date and status (Present/Absent)
    map<string, int> marks; // Subject and marks
};

struct Teacher {
    int id;
    string name;
    string password;
    map<int, string> uploadedFiles; // File ID and content
    map<int, map<string, string> > studentAttendance; // Student ID and attendance (Fixed `>>` issue)
    map<int, map<string, int> > studentMarks; // Student ID and marks (Fixed `>>` issue)
};

struct Administrator {
    int id;
    string name;
    string password;
};

// Global Vectors for Entities
vector<Student> students;
vector<Teacher> teachers;
Administrator admin = {1, "Admin", "admin123"};

// Function Prototypes
void adminMenu();
void studentMenu(int studentId);
void teacherMenu(int teacherId);
void login();

// Utility Functions
Student* findStudentById(int id) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].id == id) return &students[i];
    }
    return NULL; // Using NULL instead of nullptr for older compilers
}

Teacher* findTeacherById(int id) {
    for (size_t i = 0; i < teachers.size(); i++) {
        if (teachers[i].id == id) return &teachers[i];
    }
    return NULL;
}

// Admin Functions
void addStudent() {
    Student s;
    cout << "Enter Student ID: ";
    cin >> s.id;
    cin.ignore();
    cout << "Enter Student Name: ";
    getline(cin, s.name);
    cout << "Set Student Password: ";
    getline(cin, s.password);
    students.push_back(s);
    cout << "Student added successfully!\n";
}

void addTeacher() {
    Teacher t;
    cout << "Enter Teacher ID: ";
    cin >> t.id;
    cin.ignore();
    cout << "Enter Teacher Name: ";
    getline(cin, t.name);
    cout << "Set Teacher Password: ";
    getline(cin, t.password);
    teachers.push_back(t);
    cout << "Teacher added successfully!\n";
}

void changePassword() {
    string newPassword;
    cout << "Enter new admin password: ";
    cin >> newPassword;
    admin.password = newPassword;
    cout << "Password changed successfully!\n";
}

void adminMenu() {
    int choice;
    do {
        cout << "\nAdministrator Menu\n";
        cout << "1. Add Student\n";
        cout << "2. Add Teacher\n";
        cout << "3. Change Password\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                addTeacher();
                break;
            case 3:
                changePassword();
                break;
            case 4:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}

// Student Functions
void viewFiles(int studentId) {
    Student* s = findStudentById(studentId);
    if (s != NULL && !s->files.empty()) {
        cout << "\nFiles:\n";
        for (map<string, string>::iterator it = s->files.begin(); it != s->files.end(); ++it) {
            cout << "File Name: " << it->first << ", Content: " << it->second << endl;
        }
    } else {
        cout << "No files found.\n";
    }
}

void viewAttendance(int studentId) {
    Student* s = findStudentById(studentId);
    if (s != NULL && !s->attendance.empty()) {
        cout << "\nAttendance:\n";
        for (map<string, string>::iterator it = s->attendance.begin(); it != s->attendance.end(); ++it) {
            cout << "Date: " << it->first << ", Status: " << it->second << endl;
        }
    } else {
        cout << "No attendance records found.\n";
    }
}

void viewMarks(int studentId) {
    Student* s = findStudentById(studentId);
    if (s != NULL && !s->marks.empty()) {
        cout << "\nMarks:\n";
        for (map<string, int>::iterator it = s->marks.begin(); it != s->marks.end(); ++it) {
            cout << "Subject: " << it->first << ", Marks: " << it->second << endl;
        }
    } else {
        cout << "No marks found.\n";
    }
}

void studentMenu(int studentId) {
    int choice;
    do {
        cout << "\nStudent Menu\n";
        cout << "1. View Files\n";
        cout << "2. View Attendance\n";
        cout << "3. View Marks\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewFiles(studentId);
                break;
            case 2:
                viewAttendance(studentId);
                break;
            case 3:
                viewMarks(studentId);
                break;
            case 4:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}

// Teacher Functions
void takeAttendance(int teacherId) {
    Teacher* t = findTeacherById(teacherId);
    int studentId;
    string date, status;
    cout << "Enter Student ID: ";
    cin >> studentId;
    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> date;
    cout << "Enter Status (Present/Absent): ";
    cin >> status;
    t->studentAttendance[studentId][date] = status;
    cout << "Attendance recorded successfully!\n";
}

void uploadFiles(int teacherId) {
    Teacher* t = findTeacherById(teacherId);
    int fileId;
    string content;
    cout << "Enter File ID: ";
    cin >> fileId;
    cin.ignore();
    cout << "Enter File Content: ";
    getline(cin, content);
    t->uploadedFiles[fileId] = content;
    cout << "File uploaded successfully!\n";
}

void uploadMarks(int teacherId) {
    Teacher* t = findTeacherById(teacherId);
    int studentId;
    string subject;
    int marks;
    cout << "Enter Student ID: ";
    cin >> studentId;
    cin.ignore();
    cout << "Enter Subject: ";
    getline(cin, subject);
    cout << "Enter Marks: ";
    cin >> marks;
    t->studentMarks[studentId][subject] = marks;
    cout << "Marks uploaded successfully!\n";
}

void teacherMenu(int teacherId) {
    int choice;
    do {
        cout << "\nTeacher Menu\n";
        cout << "1. Take Attendance\n";
        cout << "2. Upload Files\n";
        cout << "3. Upload Marks\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                takeAttendance(teacherId);
                break;
            case 2:
                uploadFiles(teacherId);
                break;
            case 3:
                uploadMarks(teacherId);
                break;
            case 4:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}

// Login Function
void login() {
    int userType;
    cout << "\nLogin\n";
    cout << "1. Administrator\n";
    cout << "2. Teacher\n";
    cout << "3. Student\n";
    cout << "Enter user type: ";
    cin >> userType;

    int id;
    string password;
    switch (userType) {
        case 1:
            cout << "Enter Admin ID: ";
            cin >> id;
            cout << "Enter Password: ";
            cin >> password;
            if (id == admin.id && password == admin.password) {
                adminMenu();
            } else {
                cout << "Invalid admin credentials!\n";
            }
            break;
        case 2:
            cout << "Enter Teacher ID: ";
            cin >> id;
            cout << "Enter Password: ";
            cin >> password;
            if (Teacher* t = findTeacherById(id)) {
                if (t->password == password) {
                    teacherMenu(id);
                } else {
                    cout << "Invalid password!\n";
                }
            } else {
                cout << "Teacher not found!\n";
            }
            break;
        case 3:
            cout << "Enter Student ID: ";
            cin >> id;
            cout << "Enter Password: ";
            cin >> password;
            if (Student* s = findStudentById(id)) {
                if (s->password == password) {
                    studentMenu(id);
                } else {
                    cout << "Invalid password!\n";
                }
            } else {
                cout << "Student not found!\n";
            }
            break;
        default:
            cout << "Invalid user type!\n";
    }
}

int main() {
    while (true) {
        login();
    }
    return 0;
}

