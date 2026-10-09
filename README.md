# Course Management System

A console-based **Course Management System** developed in C++ to
practice Object-Oriented Programming, data structures, dynamic memory
management, and file handling.

## Features

### Student

-   Register as a student
-   Log in using ID and password
-   Enroll in courses
-   View enrolled courses
-   View grades
-   Log out

### Instructor

-   Register as an instructor
-   Log in using ID and password
-   Create courses
-   View their courses
-   Add students to their courses
-   View student grades
-   Log out

### Admin

-   Add students
-   Remove students
-   Add instructors
-   Remove instructors
-   Add courses
-   Remove courses
-   Add new admins
-   Log out

## Object-Oriented Programming

The project uses:

-   **Inheritance** --- `Student`, `Instructor`, and `Admin` inherit
    from `User`.
-   **Polymorphism** --- virtual `displayMenu()` and dynamic casting are
    used to work with different user types.
-   **Encapsulation** --- class data is kept private/protected and
    accessed through member functions.
-   **Abstract Class** --- `User` contains the pure virtual function
    `displayMenu()`.
-   **Constructors and Destructors**
-   **Dynamic Memory Allocation**

## Data Structure

The project implements a custom **Doubly Linked List** through
`CustomStudentList`.

It supports:

-   Adding students to the front or back
-   Searching by student ID
-   Searching by student name
-   Removing students
-   Displaying students from front to back
-   Displaying students from back to front

## File Handling

The system saves and loads data using:

-   `users.txt` --- stores student, instructor, and admin information.
-   `courses.txt` --- stores course information.

Data is loaded when the `SystemManager` is created and saved when the
program exits through the `SystemManager` destructor.

> The data files are local files. They are not required to be uploaded
> to GitHub, so your locally created data can remain on your computer.

## Limits

The current implementation uses fixed-size arrays:

-   Maximum **100 users**
-   Maximum **30 courses**
-   Maximum **100 students/grades per course**
-   Maximum **10 courses per student**

## Default Test Admin

A test Admin account is created when the program starts:

  Field      Value
  ---------- ---------------------
  ID         `1000`
  Name       `Admin`
  Email      `admin@example.com`
  Password   `1234`

This account is provided for testing the Admin features.

Once logged in as Admin, you can add additional Admin accounts from the
Admin menu.

## How to Run

1.  Clone or download the repository.
2.  Open the `.cpp` file in a C++ IDE such as Visual Studio Code,
    Code::Blocks, or Visual Studio.
3.  Compile the program using a C++ compiler.
4.  Run the program.
5.  Use the test Admin account above or register as a
    Student/Instructor.

## Technologies

-   C++
-   Object-Oriented Programming (OOP)
-   Doubly Linked List
-   File Handling
-   Dynamic Memory Allocation
-   Inheritance and Polymorphism

## Project Structure

The current project is implemented in a single C++ source file.

Main classes:

-   `Node`
-   `CustomStudentList`
-   `User`
-   `Student`
-   `Instructor`
-   `Admin`
-   `Course`
-   `SystemManager`

## Project Purpose

This project was created as a practical C++ project to apply OOP
concepts, custom data structures, file handling, inheritance,
polymorphism, and basic user/course management in one system.
