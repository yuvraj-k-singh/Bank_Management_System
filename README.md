# Bank Management System (C Project)

This project is a **console-based Bank Management System** developed entirely in the **C programming language** By Yuvraj Kumar Singh. It is designed to simulate the fundamental operations of a bank, focusing on secure user interaction and robust data persistence using local file storage.

The system allows multiple users to create accounts, log in, and perform core banking functions such as deposits, withdrawals, and reviewing their transaction history. A separate, secure Admin Panel is included for managing the user base, setting system-wide limits, and handling direct account transfers.

---

## 🚀 Features

### 👤 User Panel
- Create New Account
- Secure Login System
- Deposit Money
- Withdraw Money (with minimum withdrawal limit)
- Check Account Balance
- View Transaction History
- Auto-save data on each update

### 🛠 Admin Panel
- Admin Login
- View All Users
- Add Money to User Account
- Delete User
- Transfer Money Between Accounts
- Set Minimum Withdrawal Limit

### 💾 Data Management
- Stores all users in **bankdata.txt**
- Auto-generated transaction history files: `{username}_history.txt`
- Uses C file handling (`fopen`, `fgets`, `fprintf`, `fscanf`)
- Data remains stored after program exit

---

## 📁 Project Structure
```
Bank_Management_System/
│
├── bankdata.txt                # Stores user login and balance info
├── {username}_history.txt      # Auto-created transaction history files
├── main.c                      # Full source code
└── README.md                   # Documentation
```

---

## 🔧 Technologies Used
- C Programming Language
- File Handling
- Modular Functions
- Structured Programming
- Console Based Interface

---

## 🧠 How to Run

### 1️⃣ Clone the Repository
```
git clone https://github.com/yuvraj-k-singh/Bank_Management_System
```

### 2️⃣ Compile
```
gcc main.c -o bank
```

### 3️⃣ Run
```
./bank
```

---

## 👨‍💼 Admin Credentials
```
Username: admin
Password: admin12
```

---

## 📸 Screenshots
(Add screenshots after running your program.)

---

## 🤝 Contributing
Contributions, issues, and feature requests are welcome!

Process:
1. Fork the repository
2. Create a new branch
3. Commit your changes
4. Submit a pull request

---

## 📜 License
This project is open-source and available under the **MIT License**.

---

### ⭐ If you find this project helpful, please give it a star!

