#include "member1.h"
#include "member2.h"
#include "member3.h"
#include "member4.h"

#include <iomanip>
#include <limits>

const int MAX_RECORDS = 1000;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. " << prompt;
        clearInput();
    }
    return value;
}

double readPositiveAmount(const string& prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value) || value <= 0) {
        cout << "Enter an amount greater than zero: ";
        clearInput();
    }
    return value;
}

string chooseCategory(const AnnualData& annual) {
    displayCategories(annual);
    int choice = readInt("Choose category number: ");

    while (choice < 1 || choice > annual.categoryCount) {
        cout << "Invalid category choice.\n";
        choice = readInt("Choose category number: ");
    }
    return annual.categories[choice - 1];
}

void printOneExpense(const Expense& expense) {
    cout << "ID: " << expense.id
         << " | Category: " << expense.category
         << " | Amount: INR " << fixed << setprecision(2)
         << expense.amount << '\n';
}

int main() {
    AnnualData annual{};
    Node* head = nullptr;

    int undoStack[MAX_UNDO];
    int top = -1;
    int nextID = 1;

    inputAnnualData(annual);

    int choice;
    do {
        cout << "\n============================================\n";
        cout << "       ANNUAL EXPENSE TRACKER SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Add expense\n";
        cout << "2. View all expenses\n";
        cout << "3. Delete expense\n";
        cout << "4. Update expense amount\n";
        cout << "5. Search expense by ID\n";
        cout << "6. Search expenses by category\n";
        cout << "7. Sort expenses by amount\n";
        cout << "8. Undo last expense addition\n";
        cout << "9. Generate annual report\n";
        cout << "10. View expense categories\n";
        cout << "0. Exit\n";

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: {
                Expense expense{};
                expense.id = nextID++;
                expense.category = chooseCategory(annual);
                expense.amount = readPositiveAmount("Enter expense amount (INR): ");

                addExpense(head, expense);
                pushUndo(undoStack, top, expense.id);

                cout << "Expense added successfully. Assigned ID: "
                     << expense.id << '\n';
                break;
            }

            case 2:
                displayExpenses(head);
                break;

            case 3: {
                int id = readInt("Enter expense ID to delete: ");
                if (deleteExpense(head, id)) {
                    cout << "Expense deleted successfully.\n";
                } else {
                    cout << "Expense ID not found.\n";
                }
                break;
            }

            case 4: {
                int id = readInt("Enter expense ID to update: ");
                double amount = readPositiveAmount("Enter new amount (INR): ");
                if (updateExpense(head, id, amount)) {
                    cout << "Expense updated successfully.\n";
                } else {
                    cout << "Expense ID not found. No update made.\n";
                }
                break;
            }

            case 5: {
                Expense records[MAX_RECORDS];
                int count = copyExpensesToArray(head, records, MAX_RECORDS);
                int id = readInt("Enter expense ID to search: ");
                int index = searchByID(records, count, id);

                if (index != -1) {
                    printOneExpense(records[index]);
                } else {
                    cout << "Expense not found.\n";
                }
                break;
            }

            case 6: {
                Expense records[MAX_RECORDS];
                Expense results[MAX_RECORDS];
                int count = copyExpensesToArray(head, records, MAX_RECORDS);
                string category = chooseCategory(annual);

                int matches = searchByCategory(
                    records, count, category, results, MAX_RECORDS
                );

                if (matches == 0) {
                    cout << "No expenses found in this category.\n";
                } else {
                    cout << "\nMatching expenses:\n";
                    for (int i = 0; i < matches; ++i) {
                        printOneExpense(results[i]);
                    }
                }
                break;
            }

            case 7: {
                Expense records[MAX_RECORDS];
                int count = copyExpensesToArray(head, records, MAX_RECORDS);

                if (count == 0) {
                    cout << "No expenses available to sort.\n";
                    break;
                }

                int order = readInt(
                    "1. Ascending (lowest to highest)\n"
                    "2. Descending (highest to lowest)\n"
                    "Choose order: "
                );

                while (order != 1 && order != 2) {
                    cout << "Invalid choice. Enter 1 or 2.\n";
                    order = readInt("Choose order: ");
                }

                bubbleSortByAmount(records, count, order == 1);

                cout << "\nSorted expenses:\n";
                for (int i = 0; i < count; ++i) {
                    printOneExpense(records[i]);
                }
                break;
            }

            case 8:
                if (undoLastAddition(head, undoStack, top)) {
                    cout << "Last added expense undone successfully.\n";
                } else {
                    cout << "No valid expense addition available to undo.\n";
                }
                break;

            case 9:
                generateAnnualReport(annual, head);
                break;

            case 10:
                displayCategories(annual);
                break;

            case 0:
                cout << "Exiting Expense Tracker. Goodbye!\n";
                break;

            default:
                cout << "Invalid menu choice. Try again.\n";
        }

    } while (choice != 0);

    freeExpenseList(head);
    return 0;
}
