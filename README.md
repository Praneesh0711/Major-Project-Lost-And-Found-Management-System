# Lost & Found Management System
A modular C-based application designed to record, search, match, and manage lost and found items.  
This project was created as part of the **Major Project – Programming in C** course (CSEG1032).

---

## 📖 Overview
The goal of this project is to provide a simple and efficient system to help users:

- Register **lost** items  
- Register **found** items  
- **Search** through item lists  
- Automatically **match** similar lost & found records  
- Generate a **Daily Summary Report**  
- Store all records in persistent **binary files**

The project is completely modular, file-driven, and follows all guidelines from the UPES Project Manual.

---

- src/
  - main.c
  - utils.c
  - lost.c
  - found.c
  - fileops.c
  - match.c
  - report.c

- include/
  - utils.h
  - lost.h
  - found.h
  - fileops.h
  - match.h
  - report.h

- docs/
  - ProjectReport.pdf

- assets/
   - screenshots/

   - sample_input.txt
- README.md



---

## 🧩 Features

### ✔ Add Lost Items  
Users can log lost belongings with detailed information such as category, description, location, and date.

### ✔ Add Found Items  
Allows registering items that have been found on campus.

### ✔ Search Items  
Search based on partial matching of name, description, or category.

### ✔ Automatic Matching  
Uses a simple token-based similarity algorithm to find connections between lost and found records.

### ✔ Daily Report Generation  
Generates `daily_report.txt` containing:
- Total lost items  
- Total found items  
- Matches  
- Summary statistics  

### ✔ Persistent Storage  
All records are saved in:
- `lost.db`
- `found.db`

---

## 🛠️ Requirements

- GCC or any standard C compiler  
- Works on:
  - Windows (MinGW)
  - Linux (GCC)
  - MacOS (Clang)
  - OnlineGDB / Replit / VS Code

No additional libraries required.

---
## 🧠 Implementation Summary

- Uses modular programming

- Implements user-defined structures

- Safe string handling using fgets

- Dynamic memory allocation (malloc, realloc)

- Binary file storage for records

- Token-based text similarity matching

- Clean separation of .h/.c files
## 📄 Documentation

Full project report is available in:
/docs/ProjectReport.pdf



## 🎯 Future Enhancements

- GUI or Web Interface

- Better NLP-based matching algorithm

- QR Code-based tagging system

- Multi-user authentication

- Cloud storage integration


## 🙌 Author

Praneesh Bhatt
B.Tech CSE – UPES
2025
