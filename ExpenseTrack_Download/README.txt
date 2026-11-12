ANNUAL EXPENSE & NET SAVINGS MANAGEMENT SYSTEM
Language: C++

FILES
-----
main.cpp       Main menu and integration of all modules
shared.h       Common structures shared by all members
member1.*      Annual income and expense categories (structures, arrays)
member2.*      Expense record management (singly linked list)
member3.*      Searching and sorting (linear search, bubble sort)
member4.*      Undo and annual report (array-based stack)

COMPILE (g++)
----------------
g++ -std=c++11 -Wall -Wextra main.cpp member1.cpp member2.cpp member3.cpp member4.cpp -o ExpenseTrack

RUN
---
Windows: ExpenseTrack.exe
Linux/macOS: ./ExpenseTrack

HOW TO USE
----------
1. Enter financial year and annual income at startup.
2. Add expenses using the predefined categories.
3. View, update, or delete expense records.
4. Search by ID or category.
5. Sort copied expense records by amount.
6. Undo the latest still-existing added expense.
7. Generate the annual financial report.

DS TOPICS
---------
1. Structures and arrays
2. Singly linked list
3. Linear search
4. Bubble sort
5. Stack (LIFO)

DESIGN NOTES
------------
- Expense records are stored in a singly linked list.
- Searching and sorting use temporary copies, so the original list order is unchanged.
- The undo stack stores IDs of added expenses. Undo removes the latest addition
  that still exists in the linked list.
- Manual deletion does not edit the undo stack; stale IDs are skipped by undo.
- Data is stored in memory only and is lost when the program exits.
- This version handles one financial year per program run.
- The temporary search/sort array supports up to 1000 records.
