# Annual Expense and Net Savings Management System

A C++ command-line application for tracking expenses for one financial year and
calculating net savings.

## Project files

- `main.cpp` - Main menu and integration of the modules
- `shared.h` - Common data structures
- `member1.cpp` / `member1.h` - Annual income and expense categories
- `member2.cpp` / `member2.h` - Expense records stored in a singly linked list
- `member3.cpp` / `member3.h` - Linear search and bubble sort
- `member4.cpp` / `member4.h` - Undo stack and annual report

## Build

Compile with g++ and C++11 or later:

```sh
g++ -std=c++11 -Wall -Wextra main.cpp member1.cpp member2.cpp member3.cpp member4.cpp -o ExpenseTrack
```

Run on Windows:

```powershell
.\ExpenseTrack.exe
```

Run on Linux or macOS:

```sh
./ExpenseTrack
```

## Use

1. Enter the financial year and annual income.
2. Add expenses using the predefined categories.
3. View, update, or delete expense records.
4. Search by ID or category, or sort records by amount.
5. Undo the latest added expense that still exists.
6. Generate the annual financial report.

## Data structures and algorithms

- Structures and arrays
- Singly linked list
- Linear search
- Bubble sort
- Array-based LIFO stack

Expenses are kept in memory only and are lost when the program exits. Search
and sort operate on temporary copies, leaving the linked-list order unchanged.
The temporary array supports up to 1000 records.
