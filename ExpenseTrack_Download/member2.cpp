#include "member2.h"
#include <iomanip>

void addExpense(Node*& head, const Expense& expense) {
    Node* newNode = new Node{expense, nullptr};

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}

bool deleteExpense(Node*& head, int id) {
    if (head == nullptr) return false;

    if (head->data.id == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data.id != id) {
        current = current->next;
    }

    if (current->next == nullptr) return false;

    Node* temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
}

bool updateExpense(Node* head, int id, double newAmount) {
    if (newAmount <= 0) return false;

    Node* current = head;
    while (current != nullptr) {
        if (current->data.id == id) {
            current->data.amount = newAmount;
            return true;
        }
        current = current->next;
    }
    return false;
}

void displayExpenses(const Node* head) {
    if (head == nullptr) {
        cout << "\nNo expense records found.\n";
        return;
    }

    cout << "\n---------------- EXPENSE RECORDS ----------------\n";
    cout << left << setw(8) << "ID"
         << setw(20) << "Category"
         << right << setw(14) << "Amount (INR)" << '\n';
    cout << "-------------------------------------------------\n";

    const Node* current = head;
    while (current != nullptr) {
        cout << left << setw(8) << current->data.id
             << setw(20) << current->data.category
             << right << setw(14) << fixed << setprecision(2)
             << current->data.amount << '\n';
        current = current->next;
    }
}

double calculateTotalExpenses(const Node* head) {
    double total = 0.0;
    const Node* current = head;

    while (current != nullptr) {
        total += current->data.amount;
        current = current->next;
    }
    return total;
}

int copyExpensesToArray(const Node* head, Expense arr[], int capacity) {
    int count = 0;
    const Node* current = head;

    while (current != nullptr && count < capacity) {
        arr[count++] = current->data;
        current = current->next;
    }
    return count;
}

bool expenseExists(const Node* head, int id) {
    const Node* current = head;
    while (current != nullptr) {
        if (current->data.id == id) return true;
        current = current->next;
    }
    return false;
}

void freeExpenseList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
