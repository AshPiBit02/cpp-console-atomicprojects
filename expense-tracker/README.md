# 💰 Expense & Inflow Tracker (C++)

A **console-based personal finance tracker** built using **C++**, designed to record, store, and summarize daily expenses and income using file handling and OOP concepts.

---

## ✨ Features

* Add expenses with predefined categories
* Add income (inflows) with source details
* View expenses in a formatted table
* View inflow summary with total amount
* Secure option to erase all stored data
* Persistent storage using text files

---

## 🛠️ Technologies Used

* **Language:** C++
* **Concepts & Libraries:**

  * Object-Oriented Programming (Inheritance)
  * File Handling (`fstream`)
  * STL (`vector`, `string`)
  * Formatting & Parsing (`iomanip`, `stringstream`)

---

## 📂 Files Used

* `main.cpp` – source code
* `expense_file.txt` – expense records
* `inflow_file.txt` – inflow records

---

## ▶️ How to Run

```bash
g++ main.cpp -o tracker
./tracker
```

---

## 📌 Notes

* Data is saved automatically to text files
* Erasing all data requires a security code
* Designed for learning and personal use
