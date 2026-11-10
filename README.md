# Annual Expense and Net Savings Management System

## Project Overview

A four-member C++ Data Structures college project that accepts annual income and
expense records, calculates total expenditure and displays net annual savings.

## Architecture

The entire project is maintained in **one source file**: `main.cpp`.

```
ExpenseTrack/
├── main.cpp       ← single source file (all four modules)
├── README.md
└── .gitignore
```

## Module Assignment

| Member | Module | Data Structure | Algorithms |
|--------|--------|---------------|------------|
| Member 1 | Income & Category Management | Structures, Arrays | — |
| Member 2 | Expense Record Management | Singly Linked List | Insert, Delete, Update, Display |
| Member 3 | Searching & Sorting | Array (temp copy) | Linear Search, Bubble Sort |
| Member 4 | Undo & Annual Report | Stack | — |

## Common Structures (Section 0 — shared, do not modify)

```cpp
struct Expense   { int id; string category; double amount; };
struct Node      { Expense data; Node* next; };
struct AnnualData{ double annualIncome; double totalExpenses; double netSavings; };
```

## Member 3 – Searching & Sorting

### Functions

| Function | Algorithm | Best | Worst |
|----------|-----------|------|-------|
| `searchByID()` | Linear Search | O(1) | O(n) |
| `searchByCategory()` | Linear Search | O(1) | O(n) |
| `bubbleSortByAmount()` | Bubble Sort | O(n) | O(n²) |

### How to Build & Run

```bash
g++ -std=c++17 -Wall -Wextra -o ExpenseTrack main.cpp
./ExpenseTrack
```

## Branch Strategy

| Branch | Purpose |
|--------|---------|
| `main` | Integration branch – stable baseline |
| `feature/member3-search-sort` | Member 3 work (this branch) |

> Do **not** push or merge to `main` without team lead approval.
