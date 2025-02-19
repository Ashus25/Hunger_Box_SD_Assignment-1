# 🎟️ Movie Ticket Booking System 🎭

## Overview
The **Movie Ticket Booking System** is a C++ application designed to simulate a basic movie ticket booking platform. It allows users to **register, log in, and perform various actions** based on their roles (**Admin or Customer**).  
- **Admins** can manage theaters and movies.  
- **Customers** can book tickets, view bookings, and cancel reservations.

---

## 🚀 Features  

### **User Management**
- ✅ **Registration**: Users can register with a username, password, and role (**Admin or Customer**).
- ✅ **Login/Logout**: Users can log in and log out of the system.
- ✅ **Role-Based Access**:  
  - **Admins** can add theaters and movies.  
  - **Customers** can book and cancel tickets.

### **Theater Management**
- ✅ **Add Theater**: Admins can add theaters with screens and specify seat prices.
- ✅ **View Theaters**: Users can view all available theaters and their screens.

### **Movie Management**
- ✅ **Add Movie**: Admins can add movies with details like **title, genre, language, and duration**.
- ✅ **Search Movies**: Users can search for movies by **title, genre, or location**.

### **Booking Management**
- ✅ **Book Ticket**: Customers can book tickets for a **specific movie, theater, showtime, and seat**.
- ✅ **Cancel Booking**: Customers can cancel bookings and receive a **partial refund** if canceled within **1 hour of the showtime**.
- ✅ **View Bookings**: Customers can view their **booking history**.

### **Payment Processing**
- ✅ **Simulated payment processing** with **random success or failure**.

### **Seat Management**
- ✅ Seats are categorized as **"Standard"** or **"Premium"** with different prices.
- ✅ Seats can be **booked or canceled**, and **availability is checked before booking**.

### **Showtime Management**
- ✅ **Showtimes** are added to screens, and **seats are initialized automatically** for each showtime.

---

## 🛠️ Installation

### **📌 Prerequisites**
- A **C++ compiler** (e.g., GCC, Clang).
- A **terminal or command prompt** to run the program.

### **🔧 Steps to Set Up**
1. Clone or download the **source code** to your local machine.
2. Open a **terminal or command prompt** and navigate to the directory containing the source code.

### **🛠️ Compilation**
Compile the program using a **C++ compiler**. Example using **GCC**:
```bash
g++ -o Movie_Ticket_Booking_Design main.cpp
