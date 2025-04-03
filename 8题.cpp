#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct TrainTicket {
    string trainNumber;     // Train identifier
    string destination;     // Destination station
    string departureTime;   // Departure time (HH:MM format)
    string travelTime;      // Travel duration (HH:MM format)
    double price;           // Ticket price

    bool operator<(const TrainTicket& other) const {
        return departureTime > other.departureTime;
    }
};

// Validate time format (HH:MM)
bool isValidTimeFormat(const string& time) {
    if (time.length() != 5 || time[2] != ':') 
        return false;
    
    try {
        int hours = stoi(time.substr(0, 2));
        int minutes = stoi(time.substr(3, 2));
        return (hours >= 0 && hours < 24) && (minutes >= 0 && minutes < 60);
    } catch (...) {
        return false;
    }
}

double getPositiveNumber(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error! Please enter a positive number.\n";
        } else {
            return value;
        }
    }
}

// Input ticket data with validation
void inputTickets(vector<TrainTicket>& tickets) {
    TrainTicket ticket;
    cout << "\nEnter ticket details:\n";
    
    cout << "Train number: ";
    cin >> ticket.trainNumber;
    
    cout << "Destination station: ";
    cin.ignore();
    getline(cin, ticket.destination);
    
    do {
        cout << "Departure time (HH:MM): ";
        cin >> ticket.departureTime;
        if (!isValidTimeFormat(ticket.departureTime)) {
            cout << "Invalid format! Please use HH:MM (24-hour format).\n";
        }
    } while (!isValidTimeFormat(ticket.departureTime));
    
    do {
        cout << "Travel duration (HH:MM): ";
        cin >> ticket.travelTime;
        if (!isValidTimeFormat(ticket.travelTime)) {
            cout << "Invalid format! Please use HH:MM (24-hour format).\n";
        }
    } while (!isValidTimeFormat(ticket.travelTime));
    
    ticket.price = getPositiveNumber("Ticket price: ");
    
    tickets.push_back(ticket);
    cout << "Ticket added successfully!\n";
}

// Display all tickets in a formatted table
void displayAllTickets(const vector<TrainTicket>& tickets) {
    if (tickets.empty()) {
        cout << "No ticket data available.\n";
        return;
    }
    
    cout << "\nTicket List:\n";
    cout << "+----------------+----------------------+----------------+--------------+-------------+\n";
    cout << "| Train Number   | Destination Station  | Departure Time | Travel Time  | Price       |\n";
    cout << "+----------------+----------------------+----------------+--------------+-------------+\n";
    
    for (const auto& ticket : tickets) {
        cout << "| " << left << setw(14) << ticket.trainNumber 
             << " | " << setw(20) << ticket.destination 
             << " | " << setw(14) << ticket.departureTime 
             << " | " << setw(12) << ticket.travelTime
             << " | " << setw(11) << fixed << setprecision(2) << ticket.price << " |\n";
    }
    cout << "+----------------+----------------------+----------------+--------------+-------------+\n";
}

// Calculate and display average ticket price
void calculateAveragePrice(const vector<TrainTicket>& tickets) {
    if (tickets.empty()) {
        cout << "No data available for calculation.\n";
        return;
    }
    
    double sum = 0;
    for (const auto& ticket : tickets) {
        sum += ticket.price;
    }
    cout << "Average ticket price: " << fixed << setprecision(2) << (sum / tickets.size()) << " USD\n";
}

// Find and display cheapest ticket to a destination
void findCheapestToDestination(vector<TrainTicket>& tickets) {
    if (tickets.empty()) {
        cout << "No ticket data available.\n";
        return;
    }
    
    string destination;
    cout << "Enter destination station: ";
    cin.ignore();
    getline(cin, destination);
    
    vector<TrainTicket> filtered;
    copy_if(tickets.begin(), tickets.end(), back_inserter(filtered),
        [&destination](const TrainTicket& t) { return t.destination == destination; });
    
    if (filtered.empty()) {
        cout << "No tickets found for destination '" << destination << "'.\n";
    } else {
        auto cheapest = *min_element(filtered.begin(), filtered.end(),
            [](const TrainTicket& a, const TrainTicket& b) { return a.price < b.price; });
        
        cout << "\nCheapest ticket to '" << destination << "':\n";
        cout << "+----------------+----------------------+----------------+--------------+-------------+\n";
        cout << "| " << left << setw(14) << cheapest.trainNumber 
             << " | " << setw(20) << cheapest.destination 
             << " | " << setw(14) << cheapest.departureTime 
             << " | " << setw(12) << cheapest.travelTime
             << " | " << setw(11) << fixed << setprecision(2) << cheapest.price << " |\n";
        cout << "+----------------+----------------------+----------------+--------------+-------------+\n";
    }
}

void sortByDepartureTime(vector<TrainTicket>& tickets) {
    if (tickets.empty()) {
        cout << "No data available for sorting.\n";
        return;
    }
    
    sort(tickets.begin(), tickets.end());
    cout << "Tickets sorted by departure time (newest first).\n";
}

// Main menu display
void showMenu() {
    cout << "\n=== Train Ticket Management System ===" << endl;
    cout << "1. Enter ticket data" << endl;
    cout << "2. Display all tickets" << endl;
    cout << "3. Calculate average ticket price" << endl;
    cout << "4. Find cheapest ticket to destination" << endl;
    cout << "5. Sort by departure time" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    vector<TrainTicket> tickets;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: inputTickets(tickets); break;
            case 2: displayAllTickets(tickets); break;
            case 3: calculateAveragePrice(tickets); break;
            case 4: findCheapestToDestination(tickets); break;
            case 5: sortByDepartureTime(tickets); break;
            case 6: cout << "Program terminated.\n"; break;
            default: {
                cout << "Invalid choice! Please enter 1-6.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (choice = 6);

    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          }
