#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 5
#define MAX_SEATS 10

// Structure to represent a user
struct User {
    char username[50];
    char password[50];
};

// Structure to represent a bus
struct Bus {
    int id;
    char name[50];
    char source[50];
    char destination[50];
    char departureTime[10];
    int seatsAvailable;
};

// Initialize an array of users
struct User user_database[] = {
    {"keith", "keith123"},
    {"rogers", "chumba12"},
    {"user3", "password3"}
};

// Initialize an array of buses
struct Bus buses[MAX_BUSES];

// Structure to represent a reservation
struct Reservation {
    int busID;
    int numSeats;
    char username[50];
};

// Function to display the menu
void displayMenu() {
    printf("\nBus Reservation System Menu\n");
    printf("1. View Bus Schedules\n");
    printf("2. Check Seat Availability\n");
    printf("3. Make a Reservation\n");
    printf("4. Exit\n");
}

// Function to view bus schedules
void viewBusSchedules() {
    printf("\nAvailable Bus Schedules:\n");
    for (int i = 0; i < MAX_BUSES; i++) {
        if (buses[i].id != -1) {
            printf("Bus ID: %d\n", buses[i].id);
            printf("Name: %s\n", buses[i].name);
            printf("Source: %s\n", buses[i].source);
            printf("Destination: %s\n", buses[i].destination);
            printf("Departure Time: %s\n", buses[i].departureTime);
            printf("Available Seats: %d\n", buses[i].seatsAvailable);
            printf("\n");
        }
    }
}

// Function to check seat availability
void checkSeatAvailability() {
    int busID;
    printf("\nEnter Bus ID: ");
    scanf("%d", &busID);

    for (int i = 0; i < MAX_BUSES; i++) {
        if (buses[i].id == busID) {
            printf("Available Seats on Bus %d: %d\n", busID, buses[i].seatsAvailable);
            return;
        }
    }

    printf("Bus with ID %d not found.\n");
}

// Function to make a reservation
void makeReservation() {
    int busID, numSeats;
    char username[50];

    printf("\nEnter your username: ");
    scanf("%s", username);

    int found = 0;

    for (int i = 0; i < sizeof(user_database) / sizeof(user_database[0]); i++) {
        if (strcmp(username, user_database[i].username) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("User not found. Please register or check your username.\n");
        return;
    }

    printf("Enter Bus ID: ");
    scanf("%d", &busID);

    for (int i = 0; i < MAX_BUSES; i++) {
        if (buses[i].id == busID) {
            printf("Available Seats on Bus %d: %d\n", busID, buses[i].seatsAvailable);
            printf("Enter the number of seats to reserve: ");
            scanf("%d", &numSeats);

            if (numSeats > 0 && numSeats <= buses[i].seatsAvailable) {
                buses[i].seatsAvailable -= numSeats;
                printf("%d seat(s) reserved on Bus %d.\n", numSeats, busID);

                // Generate a receipt
                printf("Receipt:\n");
                printf("User: %s\n", username);
                printf("Bus Name: %s\n", buses[i].name);
                printf("Reserved Seats: %d\n", numSeats);

                // Payment process (you can implement a payment gateway here)

                printf("Thank you, you have successfully booked a seat or seats.\n");
            } else {
                printf("Invalid number of seats or insufficient availability.\n");
            }
            return;
        }
    }

    printf("Bus with ID %d not found.\n");
}

int main() {
    // Initialize buses
    for (int i = 0; i < MAX_BUSES; i++) {
        buses[i].id = -1;
        buses[i].seatsAvailable = 0;
    }

    // Add sample bus data
    buses[0].id = 1;
    strcpy(buses[0].name, "Bus A");
    strcpy(buses[0].source, "City 1");
    strcpy(buses[0].destination, "City 2");
    strcpy(buses[0].departureTime, "09:00 AM");
    buses[0].seatsAvailable = MAX_SEATS;

    buses[1].id = 2;
    strcpy(buses[1].name, "Bus B");
    strcpy(buses[1].source, "City 2");
    strcpy(buses[1].destination, "City 3");
    strcpy(buses[1].departureTime, "10:00 AM");
    buses[1].seatsAvailable = MAX_SEATS;

    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewBusSchedules();
                break;
            case 2:
                checkSeatAvailability();
                break;
            case 3:
                makeReservation();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (choice != 4);

    return 0;
}
