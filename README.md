# Student Database Management System

## Overview

This project is a C++ implementation of a Student Database Management System as part of the APT Lab 3 exercises. The system provides functionalities to manage student and course data, including adding new students and courses, enrolling students in courses, updating student information, and persisting data to and from a file. The project also includes a simple command-line interface to interact with the database.

## Features

### 1. Student Database (Exercise 3.1)
- **Classes and Data Members:** The project includes classes such as `Student`, `Course`, `Enrollment`, and `StudentDB`, designed to handle student information and course enrollments.
- **Immutable Classes:** Efforts were made to keep classes immutable where possible, following best practices in object-oriented programming.
- **Simple User Interface:** A `SimpleUI` class provides a command-line interface to interact with the student database. The following commands are supported:
  - Add new course
  - List all courses
  - Add new student
  - Add enrollment
  - Print student details
  - Search for a student
  - Update student information

### 2. Data Persistence (Exercise 3.2)
- **Saving Data:** The database contents can be saved to a file in a custom format derived from CSV. This includes courses, students, and enrollments.
- **Loading Data:** The system can also read from a file to restore the database contents, ensuring that all previous data is accurately reloaded.
- **Seamless File I/O:** The file operations are handled through well-defined methods in the respective classes, adhering to the single responsibility principle.

### 3. Obtaining Test Data (Exercise 3.3)
- **External Data Source:** The project connects to a remote server to fetch sample user data in JSON format.
- **Boost Library Usage:** The Boost library's I/O streams and JSON parsing capabilities are utilized to handle network communication and data processing.
- **Automated Data Population:** The system can automatically populate the database with student records fetched from the server, making testing more efficient.

## Technologies Used
- **C++11/14**: The project is written in modern C++ to take advantage of its advanced features like smart pointers, lambdas, and more.
- **Boost Libraries**: Used for handling I/O streams, network communication, and JSON parsing.
- **Object-Oriented Design**: Emphasis on immutability, data encapsulation, and separation of concerns.

## How to Run the Project
1. **Clone the repository**: `git clone <repository-url>`
2. **Build the project**: Use a C++ compiler like `g++` or a build system like CMake.
3. **Run the executable**: Execute the binary to start the command-line interface.
4. **Interact with the system**: Use the provided commands in the UI to manage the database.

## Future Improvements
- **Enhanced UI**: Upgrade the SimpleUI to a more user-friendly graphical interface.
- **Database Support**: Integrate a database management system for persistent data storage.
- **Advanced Search**: Implement more advanced search capabilities with filters and sorting.


