#include <stdio.h>
#include <stdlib.h>

struct Reservation
{
    int passengerID;
    int trainNumber;
    int seatNumber;
    int age;
    int status;
};

void bookTicket()
{
    struct Reservation r;
    FILE *file;

    printf("\n===== BOOK TICKET =====\n");

    printf("Enter Passenger ID: ");
    scanf("%d", &r.passengerID);

    printf("Enter Train Number: ");
    scanf("%d", &r.trainNumber);

    printf("Enter Seat Number: ");
    scanf("%d", &r.seatNumber);

    printf("Enter Passenger Age: ");
    scanf("%d", &r.age);

    if (r.passengerID <= 0 || r.trainNumber <= 0 ||
        r.seatNumber <= 0 || r.age <= 0 || r.age > 120)
    {
        printf("Invalid input. Please enter valid values.\n");
        return;
    }

    r.status = 1;

    file = fopen("reservations.txt", "a");

    if (file == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    fprintf(file, "%d %d %d %d %d\n",
            r.passengerID, r.trainNumber, r.seatNumber,
            r.age, r.status);

    fclose(file);

    printf("\nTicket booked successfully!\n");
}

void displayTickets()
{
    struct Reservation r;
    FILE *file;
    int found = 0;

    file = fopen("reservations.txt", "r");

    if (file == NULL)
    {
        printf("\nNo reservation records found.\n");
        return;
    }

    printf("\n========== RESERVATIONS ==========\n");
    printf("%-12s %-10s %-7s %-5s %s\n",
           "PassengerID", "TrainNo", "Seat", "Age", "Status");

    while (fscanf(file, "%d %d %d %d %d",
                  &r.passengerID, &r.trainNumber,
                  &r.seatNumber, &r.age, &r.status) == 5)
    {
        if (r.status == 1)
        {
            printf("%-12d %-10d %-7d %-5d Booked\n",
                   r.passengerID, r.trainNumber,
                   r.seatNumber, r.age);
            found = 1;
        }
    }

    if (found == 0)
        printf("No active reservations found.\n");

    fclose(file);
}

void cancelTicket()
{
    struct Reservation r;
    FILE *file;
    FILE *temp;
    int passengerID;
    int found = 0;

    printf("\n===== CANCEL TICKET =====\n");
    printf("Enter Passenger ID to cancel: ");
    scanf("%d", &passengerID);

    if (passengerID <= 0)
    {
        printf("Invalid Passenger ID.\n");
        return;
    }

    file = fopen("reservations.txt", "r");

    if (file == NULL)
    {
        printf("No reservation records found.\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    if (temp == NULL)
    {
        printf("Unable to create temporary file.\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d %d %d %d %d",
                  &r.passengerID, &r.trainNumber,
                  &r.seatNumber, &r.age, &r.status) == 5)
    {
        if (r.passengerID == passengerID && r.status == 1)
        {
            r.status = 0;
            found = 1;
        }

        fprintf(temp, "%d %d %d %d %d\n",
                r.passengerID, r.trainNumber,
                r.seatNumber, r.age, r.status);
    }

    fclose(file);
    fclose(temp);

    if (remove("reservations.txt") != 0)
    {
        printf("Unable to update reservation file.\n");
        remove("temp.txt");
        return;
    }

    if (rename("temp.txt", "reservations.txt") != 0)
    {
        printf("Unable to update reservation file.\n");
        return;
    }

    if (found == 1)
        printf("Ticket cancelled successfully.\n");
    else
        printf("Active reservation not found.\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n===============================\n");
        printf("   RAILWAY RESERVATION SYSTEM\n");
        printf("===============================\n");

        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. Display Reservations\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                bookTicket();
                break;

            case 2:
                cancelTicket();
                break;

            case 3:
                displayTickets();
                break;

            case 4:
                printf("Thank you!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}
