# Railway Reservation System

## Project Overview

A simple C language project that simulates a railway reservation system.

The program allows the user to:
- Book a ticket
- Cancel a ticket
- Display active reservations
- Exit the program

## C Concepts Used

- Structure
- Functions
- Variables
- if-else
- switch-case
- do-while loop
- while loop
- File handling
- fopen()
- fprintf()
- fscanf()
- fclose()
- remove()
- rename()

## Data Stored

Each reservation contains:
Passenger ID, Train Number, Seat Number, Age and Status.

Status 1 means booked and status 0 means cancelled.

## Cancellation

For cancellation, the program reads the original file, changes the matching active reservation's status to 0, writes the records to a temporary file, and replaces the original file.

## Run

Compile with:

gcc railway_reservation.c -o railway_reservation

Run on Windows:

railway_reservation.exe

The HTML and CSS files are a simple web demonstration for GitHub Pages. The C file is the main academic project.
