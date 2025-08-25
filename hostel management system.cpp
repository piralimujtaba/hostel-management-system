#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <fstream>
using namespace std;

// Base class Person
class Person {
protected:
    string name;
    string contact;
    int id;
public:
    Person(string n, string c, int i) : name(n), contact(c), id(i) {}
    virtual void display() const = 0; // Pure virtual function for abstraction
    string getName() const { return name; }
    string getContact() const { return contact; }
    int getId() const { return id; }
    virtual ~Person() {}
};

// Derived class: Student
class Student : public Person {
    int roomNumber;
public:
    Student(string n, string c, int i) : Person(n, c, i), roomNumber(-1) {}
    void display() const override {
        cout << "Student Name: " << name << ", Contact: " << contact << ", ID: " << id;
        if (roomNumber != -1) {
            cout << ", Room Number: " << roomNumber;
        }
        cout << endl;
    }
    int getRoomNumber() const { return roomNumber; }
    void setRoomNumber(int rn) { roomNumber = rn; }
};

// Derived class: Staff
class Staff : public Person {
    string role;
public:
    Staff(string n, string c, int i, string r) : Person(n, c, i), role(r) {}
    void display() const override {
        cout << "Staff Name: " << name << ", Contact: " << contact << ", ID: " << id << ", Role: " << role << endl;
    }
    string getRole() const { return role; }
};

// Room class
class Room {
    int roomNumber;
    bool isOccupied;
    Student* occupant;
public:
    Room(int rn) : roomNumber(rn), isOccupied(false), occupant(nullptr) {}
    void allocateRoom(Student* s) {
        isOccupied = true;
        occupant = s;
        s->setRoomNumber(roomNumber);
    }
    void deallocateRoom() {
        isOccupied = false;
        if (occupant != nullptr) {
            occupant->setRoomNumber(-1);
        }
        occupant = nullptr;
    }
    void display() const {
        cout << "Room Number: " << roomNumber << ", Occupied: " << (isOccupied ? "Yes" : "No") << endl;
        if (isOccupied && occupant != nullptr) {
            cout << "Occupant: " << occupant->getName() << endl;
        }
    }
    int getRoomNumber() const { return roomNumber; }
    bool getIsOccupied() const { return isOccupied; }
};

// Notice class for communication and maintenance requests
class Notice {
    string message;
    string sender;
    string recipient;
    bool isMaintenanceRequest;
public:
    Notice(string m, string s, string r, bool isMR = false)
        : message(m), sender(s), recipient(r), isMaintenanceRequest(isMR) {}
    void display() const {
        cout << "Notice: " << message << ", From: " << sender << ", To: " << recipient;
        if (isMaintenanceRequest) {
            cout << " (Maintenance Request)";
        }
        cout << endl;
    }
    string getMessage() const { return message; }
    string getSender() const { return sender; }
    string getRecipient() const { return recipient; }
    bool getIsMaintenanceRequest() const { return isMaintenanceRequest; }
};

// Visitor class
class Visitor {
    string name;
    string contact;
    string visitReason;
    int studentId;
    time_t visitTime;
public:
    Visitor(string n, string c, string v, int sId)
        : name(n), contact(c), visitReason(v), studentId(sId) {
        time(&visitTime); // Record the current time
    }
    void display() const {
        cout << "Visitor Name: " << name << ", Contact: " << contact << ", Reason: " << visitReason
            << ", Visiting Student ID: " << studentId << ", Visit Time: " << (&visitTime);
    }
    string getName() const { return name; }
    string getContact() const { return contact; }
    string getVisitReason() const { return visitReason; }
    int getStudentId() const { return studentId; }
};

// FeeManager class
class FeeManager {
    map<int, double> fees; // Map of student ID and fee amount
    map<int, double> paidFees; // Map of student ID and paid fee amount
public:
    void addFee(int studentId, double amount) {
        fees[studentId] += amount;
        if (paidFees.find(studentId) == paidFees.end()) {
            paidFees[studentId] = 0; // Initialize paid fees for the student
        }
    }
    void payFee(int studentId, double amount) {
        paidFees[studentId] += amount;
    }
    void displayFees() const {
        cout << "Fees:\n";
        for (const auto& fee : fees) {
            cout << "Student ID: " << fee.first << ", Amount Due: $" << (fee.second - paidFees.at(fee.first))
                << ", Total Amount: $" << fee.second << ", Paid: $" << paidFees.at(fee.first) << endl;
        }
    }
    double getTotalFees() const {
        double total = 0;
        for (const auto& fee : fees) {
            total += fee.second;
        }
        return total;
    }
    void displayOverdueFees() const {
        cout << "Overdue Fees:\n";
        for (const auto& fee : fees) {
            if (fee.second > paidFees.at(fee.first)) {
                cout << "Student ID: " << fee.first << ", Amount Overdue: $" << (fee.second - paidFees.at(fee.first)) << endl;
            }
        }
    }
};

// Attendance class for attendance tracking
class Attendance {
    map<int, int> attendance; // Map of student ID and number of days attended
    map<int, int> leaveRequests; // Map of student ID and number of leave days
public:
    void markAttendance(int studentId) {
        attendance[studentId]++;
    }
    void requestLeave(int studentId, int days) {
        leaveRequests[studentId] += days;
    }
    void displayAttendance() const {
        cout << "Attendance:\n";
        for (const auto& att : attendance) {
            cout << "Student ID: " << att.first << ", Days Attended: " << att.second << endl;
        }
    }
};

// Mess class for managing meal times
class Mess {
    vector<string> mealTimes; // Meal times schedule
public:
    void addMealTime(const string& time) {
        mealTimes.push_back(time);
    }
    void displayMealTimes() const {
        cout << "Meal Times:\n";
        for (const auto& time : mealTimes) {
            cout << time << endl;
        }
    }
};

// Hostel class
class Hostel {
    vector<Student> students;
    vector<Staff> staff;
    vector<Room> rooms;
    vector<Notice> notices;
    vector<Visitor> visitors;
    FeeManager feeManager;
    Attendance attendance;
    Mess mess;
public:
    Hostel(int numRooms) {
        for (int i = 1; i <= numRooms; ++i) {
            rooms.emplace_back(i);
        }
    }
    void addStudent(const Student& s) {
        students.push_back(s);
    }
    void addStaff(const Staff& s) {
        staff.push_back(s);
    }
    void allocateRoom(int studentId, int roomNumber) {
        for (auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber && !room.getIsOccupied()) {
                for (auto& student : students) {
                    if (student.getId() == studentId) {
                        room.allocateRoom(&student);
                        return;
                    }
                }
            }
        }
        cout << "Room allocation failed.\n";
    }
    void deallocateRoom(int roomNumber) {
        for (auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber && room.getIsOccupied()) {
                room.deallocateRoom();
                return;
            }
        }
        cout << "Room deallocation failed.\n";
    }
    void addNotice(const Notice& notice) {
        notices.push_back(notice);
    }
    void addVisitor(const Visitor& visitor) {
        visitors.push_back(visitor);
    }
    void addFee(int studentId, double amount) {
        feeManager.addFee(studentId, amount);
    }
    void payFee(int studentId, double amount) {
        feeManager.payFee(studentId, amount);
    }
    void markAttendance(int studentId) {
        attendance.markAttendance(studentId);
    }
    void requestLeave(int studentId, int days) {
        attendance.requestLeave(studentId, days);
    }
    void addMealTime(const string& time) {
        mess.addMealTime(time);
    }
    void display() const {
        cout << "\n--- Hostel Details ---\n";
        cout << "\nStudents:\n";
        for (const auto& student : students) {
            student.display();
        }
        cout << "\nStaff:\n";
        for (const auto& member : staff) {
            member.display();
        }
        cout << "\nRooms:\n";
        for (const auto& room : rooms) {
            room.display();
        }
        cout << "\nNotices:\n";
        for (const auto& notice : notices) {
            notice.display();
        }
        cout << "\nVisitors:\n";
        for (const auto& visitor : visitors) {
            visitor.display();
        }
        cout << endl;
        feeManager.displayFees();
        cout << endl;
        attendance.displayAttendance();
        cout << endl;
        mess.displayMealTimes();
    }
    bool studentExists(int studentId) const {
        for (const auto& student : students) {
            if (student.getId() == studentId) {
                return true;
            }
        }
        return false;
    }

    bool isRoomOccupied(int roomNumber) const {
        for (const auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber && room.getIsOccupied()) {
                return true;
            }
        }
        return false;
    }
};

// Main function
int main() {
    cout << "\t\t\t----------------------------------------" << endl;
    cout << "\t\t\t|                                      |" << endl;
    cout << "\t\t\t|       Hostel management system       |" << endl;
    cout << "\t\t\t|                                      |" << endl;
    cout << "\t\t\t----------------------------------------" << endl;
    Hostel hostel(10);

    // Adding some initial data
    hostel.addStudent(Student("Ali", "1234567890", 1));
    hostel.addStudent(Student("Musaid", "0987654321", 2));
    hostel.addStaff(Staff("Mr. Ahsan", "1122334455", 1, "Warden"));

    int choice;
    while (true) {
        cout << "\nHostel Management System\n";
        cout << "1. Allocate Room\n";
        cout << "2. Deallocate Room\n";
        cout << "3. Add Notice\n";
        cout << "4. Add Visitor\n";
        cout << "5. Add Fee\n";
        cout << "6. Pay Fee\n";
        cout << "7. Mark Attendance\n";
        cout << "8. Register Student\n";
        cout << "9. Register Staff\n";
        cout << "10. Add Meal Time\n";
        cout << "11. Display All\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        int studentId, roomNumber, days;
        double amount;
        string name, message, sender, recipient, contact, visitReason, time, role;

        switch (choice) {
        case 1:
            cout << "Enter student ID and room number to allocate: ";
            cin >> studentId >> roomNumber;
            // Check if the student ID exists
            if (!hostel.studentExists(studentId)) {
                cout << "Error: Student ID does not exist.\n";
            }
            else if (hostel.isRoomOccupied(roomNumber)) {
                cout << "Error: Room is already occupied.\n";
            }
            else {
                hostel.allocateRoom(studentId, roomNumber);
                cout << "Room is allocated.\n";
            }
            break;
        case 2:
            cout << "Enter room number to deallocate: ";
            cin >> roomNumber;
            hostel.deallocateRoom(roomNumber);
            cout << "Room is deallocated.\n";
            break;
        case 3:
            cout << "Enter notice message, sender, recipient (maintenance request? 1 for yes, 0 for no): ";
            cin.ignore();
            getline(cin, message);
            cin >> sender >> recipient >> days;
            hostel.addNotice(Notice(message, sender, recipient, days));
            break;
        case 4:
            cout << "Enter visitor name, contact, reason, and student ID being visited: ";
            cin.ignore();
            getline(cin, name);
            cin >> contact >> visitReason >> studentId;
            hostel.addVisitor(Visitor(name, contact, visitReason, studentId));
            break;
        case 5:
            cout << "Enter student ID and fee amount to add: ";
            cin >> studentId >> amount;
            hostel.addFee(studentId, amount);
            break;
        case 6:
            cout << "Enter student ID and fee amount to pay: ";
            cin >> studentId >> amount;
            hostel.payFee(studentId, amount);
            break;
        case 7:
            cout << "Enter student ID to mark attendance: ";
            cin >> studentId;
            hostel.markAttendance(studentId);
            break;
        case 8:
            cout << "Enter student name, contact, ID, and room number: ";
            cin.ignore();
            getline(cin, name);
            cin >> contact >> studentId >> roomNumber;
            hostel.addStudent(Student(name, contact, studentId));
            cout << "Student registered successfully.\n";
            break;
        case 9:
            cout << "Enter staff name, contact, ID, and role: ";
            cin.ignore();
            getline(cin, name);
            cin >> contact >> studentId >> role;
            hostel.addStaff(Staff(name, contact, studentId, role));
            cout << "Staff registered successfully.\n";
            break;
        case 10:
            cout << "Enter meal time: ";
            cin.ignore();
            getline(cin, time);
            hostel.addMealTime(time);
            break;
        case 11:
            hostel.display();
            break;
        case 0:
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

