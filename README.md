# Splitwise (C++ Console App)

A simple command-line application that mimics the core functionality of Splitwise — helping users manage shared expenses, groups, and balances. Built using C++ with persistent data storage via file I/O.



## 🔑 Main Features
- 👥 User registration and login
- 🧑‍🤝‍🧑 Group creation with member management
- 💸 Expense splitting between group members
- 📊 Balance calculation and summary display
- 💾 Persistent file storage and retrieval



## 👤 Types of Users

### 1. User
- Register and log in
- Create or join groups
- Add and split expenses
- View balance summaries

---

## 🧩 Feature Breakdown

### 🔐 User Registration
- Prompts for a unique username
- Prevents duplicate usernames
- Stores user info in a file

### 🏷️ Group Creation
- Users can create named groups
- Add members to each group
- Group info is stored with members listed

### 💰 Expense Addition
- Users specify group, amount, and payer
- Expense is divided equally among members
- Balances are adjusted and saved

### 📈 Balance Display
- View individual and group balance summaries
- Data retrieved and formatted from saved file

---

## 🛠 Tech Stack
- C++
- File I/O (text-based persistence)
- Console-based interface
- Structured using functions and arrays

---

## 📁 How to Run
1. Clone the repo
2. Compile using any C++ compiler (e.g., `g++ splitwise.cpp -o splitwise`)
3. Run: `./splitwise`
