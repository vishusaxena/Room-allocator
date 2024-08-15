#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

class Room {
public:
    int roomNumber;
    string host;
    string startTime;
    string endTime;
    int chairs;


    Room(int roomNumber, int chairs) : roomNumber(roomNumber), chairs(chairs) {}

    void setHost(const string& hostName) {
        host = hostName;
    }

    void setSchedule(const string& start, const string& end) {
        startTime = start;
        endTime = end;
    }

    void updateChairs(int newChairs) {
        chairs = newChairs;
    }

    bool isAvailable(const string& start, const string& end) {
        return (start >= endTime || end <= startTime);
    }

    bool hasEnded(const string& currentTime) {
        return currentTime > endTime;
    }
};

class BookingManager {
private:
    map<int, Room> rooms;

    string getCurrentTime() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %I:%M %p", ltm);
        return string(buffer);
    }

public:
    void addRoom(int roomNumber, int chairs) {
        if (rooms.find(roomNumber) != rooms.end()) {
            cout << "Room number " << roomNumber << " already exists. Please choose a different room number." << endl;
        } else {
            rooms[roomNumber] = Room(roomNumber, chairs);
            cout << "Room added successfully!" << endl;
        }
    }

    bool bookRoom(int roomNumber, const string& host, const string& start, const string& end, int chairs) {
        if (rooms.find(roomNumber) != rooms.end()) {
            Room& room = rooms[roomNumber];
            if (room.isAvailable(start, end)) {
                if (room.host.empty() || room.host == host) {
                    room.setHost(host);
                    room.setSchedule(start, end);
                    room.updateChairs(chairs);
                    logBooking(roomNumber, host, start, end, chairs);
                    cout << "Room booked successfully!" << endl;
                    return true;
                } else {
                    cout << "Room is booked by another host." << endl;
                    return false;
                }
            } else {
                cout << "Room is not available in the requested time slot." << endl;
                return false;
            }
        } else {
            cout << "Room number does not exist." << endl;
            return false;
        }
    }

    void checkRoomStatus(int roomNumber) {
        if (rooms.find(roomNumber) != rooms.end()) {
            Room& room = rooms[roomNumber];
            cout << "\nRoom " << roomNumber << " Status:\n";
            cout << "-----------------------------------\n";
            cout << "Host: " << room.host << "\n";
            cout << "Start Time: " << room.startTime << "\n";
            cout << "End Time: " << room.endTime << "\n";
            cout << "Chairs: " << room.chairs << "\n";
            cout << "-----------------------------------\n";
        } else {
            cout << "Room not found." << endl;
        }
    }

    

private:
    void logBooking(int roomNumber, const string& host, const string& start, const string& end, int chairs) {
        ofstream file("bookings.txt", ios::app);
        if (file.is_open()) {
            file << "Room Number: " << roomNumber << "\n";
            file << "Host: " << host << "\n";
            file << "Start Time: " << start << "\n";
            file << "End Time: " << end << "\n";
            file << "Chairs: " << chairs << "\n";
            file << "-----------------------------------\n";
            file.close();
        } else {
            cout << "Unable to open bookings log file." << endl;
        }
    }
};

void displayMenu() {
    cout << "\nRoom Allotment and Booking System\n";
    cout << "=================================\n";
    cout << "1. Add Room\n";
    cout << "2. Book Room\n";
    cout << "3. Check Room Status\n";
    cout << "4. Exit\n";
    cout << "=================================\n";
    cout << "Enter your choice: ";
}

int main() {
    BookingManager manager;
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int roomNumber, chairs;
                cout << "Enter room number: ";
                cin >> roomNumber;
                cout << "Enter number of chairs: ";
                cin >> chairs;
                manager.addRoom(roomNumber, chairs);
                break;
            }
            case 2: {
                int roomNumber, chairs;
                string host, start, end;
                cout << "Enter room number: ";
                cin >> roomNumber;
                cin.ignore(); 
                cout << "Enter host name: ";
                getline(cin, host);
                cout << "Enter start time (YYYY-MM-DD HH:MM AM/PM): ";
                getline(cin, start);
                cout << "Enter end time (YYYY-MM-DD HH:MM AM/PM): ";
                getline(cin, end);
                cout << "Enter number of chairs required: ";
                cin >> chairs;
                manager.bookRoom(roomNumber, host, start, end, chairs);
                break;
            }
            case 3: {
                int roomNumber;
                cout << "Enter room number: ";
                cin >> roomNumber;
                manager.checkRoomStatus(roomNumber);
                break;
            }
            
            case 4: {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    } while (choice != 4);

    return 0;
}
