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
                cin.ignore(); // To ignore the newline character from previous input
                cout << "Enter host name: ";
                getline(cin, host);
                cout << "Enter start time (YYYY-MM-DD HH:MM AM/PM): ";