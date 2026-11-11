// ============================================================
//  Annual Expense and Net Savings Management System
//  File   : main.cpp
//  Course : C++ Data Structures – College Project
//  Team   : 4 Members
//
//  Section order
//  -------------
//  0. Includes & Common Structures    (shared by all)
//  1. Member 1 – Income & Category Management
//  2. Member 2 – Expense Record Management (Linked List)
//  3. Member 3 – Searching & Sorting          ← THIS MEMBER
//  4. Member 4 – Undo Stack & Annual Report
//  5. main()   – Entry Point & Menu
// ============================================================

#include <iostream>
#include <string>
#include <cctype>  
using namespace std;

struct Expense
{
    int    id;           
    string category;     
    double amount;      
};


//   A node in the Singly Linked List maintained by Member 2.
struct Node
{
    Expense data;        
    Node*   next;        
};

//   Top-level record used by Member 4's annual report.

struct AnnualData
{
    double annualIncome;     
    double totalExpenses;   
    double netSavings;       
};

// ============================================================
// SECTION 1 – MEMBER 1: INCOME & CATEGORY MANAGEMENT
// Data Structures used: Structures, Arrays
// [Member 1 code will be inserted here]

// ============================================================
// END OF SECTION 1
// ============================================================


// ============================================================
// SECTION 2 – MEMBER 2: EXPENSE RECORD MANAGEMENT
// Data Structure used: Singly Linked List
//
// REQUIRED interface that Member 3 depends on:
//
//   int copyExpensesToArray(const Node* head,
//                           Expense arr[],
//                           int capacity);
//
// Member 3 calls this function to obtain a plain array copy
// of the linked-list data.  Implement it here.
// ============================================================


// ============================================================
// SECTION 2 – MEMBER 2: EXPENSE RECORD MANAGEMENT
// Data Structure: Singly Linked List
// ============================================================

// Check whether an expense ID already exists.
bool expenseIdExists(const Node* head, int id)
{
    const Node* current = head;

    while (current != nullptr)
    {
        if (current->data.id == id)
            return true;

        current = current->next;
    }

    return false;
}

// Insert a new expense at the end.
bool addExpense(Node*& head, int id,
                const string& category, double amount)
{
    if (id <= 0 || category.empty() || amount < 0 ||
        expenseIdExists(head, id))
        return false;

    Node* newNode = new Node;
    newNode->data.id = id;
    newNode->data.category = category;
    newNode->data.amount = amount;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
        return true;
    }

    Node* current = head;

    while (current->next != nullptr)
        current = current->next;

    current->next = newNode;
    return true;
}

// Delete an expense using its ID.
bool deleteExpense(Node*& head, int id)
{
    if (head == nullptr)
        return false;

    if (head->data.id == id)
    {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
        return true;
    }

    Node* current = head;

    while (current->next != nullptr &&
           current->next->data.id != id)
        current = current->next;

    if (current->next == nullptr)
        return false;

    Node* toDelete = current->next;
    current->next = toDelete->next;
    delete toDelete;

    return true;
}

// Update an existing expense.
bool updateExpense(Node* head, int id,
                   const string& newCategory,
                   double newAmount)
{
    if (newCategory.empty() || newAmount < 0)
        return false;

    Node* current = head;

    while (current != nullptr)
    {
        if (current->data.id == id)
        {
            current->data.category = newCategory;
            current->data.amount = newAmount;
            return true;
        }

        current = current->next;
    }

    return false;
}

// Display all expenses.
void displayExpenses(const Node* head)
{
    if (head == nullptr)
    {
        cout << "No expense records found.\n";
        return;
    }

    cout << "\n---------- EXPENSE RECORDS ----------\n";
    cout << "ID\tCategory\tAmount\n";

    const Node* current = head;

    while (current != nullptr)
    {
        cout << current->data.id << "\t"
             << current->data.category << "\t\t"
             << current->data.amount << '\n';

        current = current->next;
    }

    cout << "-------------------------------------\n";
}

// Copy linked-list records into an array for Member 3.
int copyExpensesToArray(const Node* head,
                        Expense arr[], int capacity)
{
    if (arr == nullptr || capacity <= 0)
        return 0;

    int count = 0;
    const Node* current = head;

    while (current != nullptr && count < capacity)
    {
        arr[count] = current->data;
        count++;
        current = current->next;
    }

    return count;
}

// Free all dynamically allocated nodes.
void clearExpenses(Node*& head)
{
    while (head != nullptr)
    {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

// ============================================================
// END OF MEMBER 2 SECTION
// ============================================================


// ============================================================
// END OF SECTION 2
// ============================================================


// ============================================================
// SECTION 3 – MEMBER 3: SEARCHING & SORTING
// Data Structures used: Array (temporary copy from Member 2)
// Algorithms : Linear Search, Bubble Sort
// Author     : Member 3

static string toLowerString(const string& s)
{
    string result = s;
    for (int i = 0; i < (int)result.size(); i++)
    {
        // Cast to unsigned char before tolower() to avoid UB on
        // systems where char is signed and the value is > 127.
        result[i] = (char)tolower((unsigned char)result[i]);
    }
    return result;
}



int searchByID(const Expense arr[], int count, int id)
{
    if (arr == nullptr || count <= 0)
        return -1;

    for (int i = 0; i < count; i++)
    {
        if (arr[i].id == id)   
            return i;          
    }

    return -1;    
}

int searchByCategory(const Expense arr[], int count,
                     const string& category,
                     Expense results[], int capacity)
{
    if (arr == nullptr || count <= 0 || capacity <= 0)
        return 0;

    string searchLower = toLowerString(category);

    int matchCount = 0;  

    for (int i = 0; i < count; i++)
    {
        string recordLower = toLowerString(arr[i].category);

        if (recordLower == searchLower)
        {
            results[matchCount] = arr[i];
            matchCount++;

            if (matchCount >= capacity)
                break;
        }
    }

    return matchCount;
}

void bubbleSortByAmount(Expense arr[], int count, bool ascending)
{
    if (arr == nullptr || count <= 1)
        return;

    for (int pass = 0; pass < count - 1; pass++)
    {
        bool swapped = false;   
        
        for (int j = 0; j < count - 1 - pass; j++)
        {
            bool outOfOrder;

            if (ascending)
            {
                outOfOrder = (arr[j].amount > arr[j + 1].amount);
            }
            else
            {
                outOfOrder = (arr[j].amount < arr[j + 1].amount);
            }

            if (outOfOrder)
            {
                Expense temp  = arr[j];
                arr[j]        = arr[j + 1];
                arr[j + 1]    = temp;

                swapped = true;   
            }
        }
        if (!swapped)
            break;
    }
}


// ============================================================
// SECTION 4 – MEMBER 4: UNDO STACK & ANNUAL REPORT
// Data Structure used: Stack
//
// TODO (Member 4): Implement undo functionality using a Stack
// and generate the annual financial report here.
// Do NOT modify any other section.
// ============================================================

// [Member 4 code will be inserted here]

// ============================================================
// END OF SECTION 4
// ============================================================


// ============================================================
// SECTION 5 – main() : ENTRY POINT & MENU
// ============================================================

int main()
{
    cout << "=== Annual Expense & Net Savings Management System ===\n\n";

    // --- Member 3 test data ---
    const int N = 5;
    Expense src[N] = {
        {101, "Food",      350.00},
        {102, "Rent",     1200.00},
        {103, "Food",      180.50},
        {104, "Transport",  75.25},
        {105, "Rent",      950.00}
    };

    int pass = 0, fail = 0;
    #define CHECK(label, cond) do { if(cond){cout<<"[PASS] "<<label<<"\n";pass++;}else{cout<<"[FAIL] "<<label<<"\n";fail++;} } while(0)

    cout << "-- searchByID --\n";
    CHECK("found  id=103 at index 2",    searchByID(src, N, 103) == 2);
    CHECK("miss   id=999 returns -1",    searchByID(src, N, 999) == -1);
    CHECK("empty  array returns -1",     searchByID(src, 0, 101) == -1);

    cout << "-- searchByCategory --\n";
    Expense res[N];
    int found = searchByCategory(src, N, "Food", res, N);
    CHECK("Food: 2 matches",            found == 2);
    CHECK("Food: first id=101",         found >= 1 && res[0].id == 101);
    CHECK("RENT case-insensitive: 2",   searchByCategory(src, N, "RENT", res, N) == 2);
    CHECK("Utilities: 0 matches",       searchByCategory(src, N, "Utilities", res, N) == 0);
    CHECK("empty source: 0",            searchByCategory(src, 0, "Food", res, N) == 0);

    cout << "-- bubbleSortByAmount ascending --\n";
    Expense asc[N];
    for(int i = 0; i < N; i++) asc[i] = src[i];
    bubbleSortByAmount(asc, N, true);
    CHECK("asc[0] = 75.25  (id=104)",   asc[0].amount == 75.25  && asc[0].id == 104);
    CHECK("asc[4] = 1200.00 (id=102)",  asc[4].amount == 1200.00 && asc[4].id == 102);

    cout << "-- bubbleSortByAmount descending --\n";
    Expense dsc[N];
    for(int i = 0; i < N; i++) dsc[i] = src[i];
    bubbleSortByAmount(dsc, N, false);
    CHECK("dsc[0] = 1200.00 (id=102)",  dsc[0].amount == 1200.00 && dsc[0].id == 102);
    CHECK("dsc[4] = 75.25  (id=104)",   dsc[4].amount == 75.25  && dsc[4].id == 104);

    cout << "-- edge cases --\n";
    Expense one[1] = {{7, "Misc", 500.00}};
    bubbleSortByAmount(one, 1, true);
    CHECK("single-element sort: unchanged", one[0].id == 7 && one[0].amount == 500.00);

    #undef CHECK
    cout << "\nResult: " << pass << " passed, " << fail << " failed\n";
    return 0;
}

// ============================================================
// END OF main.cpp
// ============================================================
