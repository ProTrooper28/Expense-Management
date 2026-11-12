#include "member4.h"
#include "member2.h"
#include <iomanip>

void pushUndo(int undoStack[], int& top, int expenseId) {
    // If full, discard the oldest undo entry and retain the latest 99.
    if (top == MAX_UNDO - 1) {
        for (int i = 0; i < MAX_UNDO - 1; ++i) {
            undoStack[i] = undoStack[i + 1];
        }
        --top;
    }
    undoStack[++top] = expenseId;
}

bool undoLastAddition(Node*& head, int undoStack[], int& top) {
    // Skip IDs that may already have been manually deleted.
    while (top >= 0) {
        int id = undoStack[top--];
        if (deleteExpense(head, id)) {
            return true;
        }
    }
    return false;
}

void generateAnnualReport(const AnnualData& data, const Node* head) {
    double totalExpenses = calculateTotalExpenses(head);
    double savings = data.income - totalExpenses;

    cout << "\n========== ANNUAL FINANCIAL REPORT ==========\n";
    cout << "Financial year       : " << data.year << '\n';
    cout << fixed << setprecision(2);
    cout << "Annual income        : INR " << data.income << '\n';
    cout << "Total expenses       : INR " << totalExpenses << '\n';
    cout << "Net savings          : INR " << savings << '\n';

    if (data.income > 0) {
        double percentage = (savings / data.income) * 100.0;
        cout << "Savings percentage   : " << percentage << "%\n";
    } else {
        cout << "Savings percentage   : Not applicable (income is zero)\n";
    }

    if (savings < 0) {
        cout << "Status               : Expenses exceed income\n";
    } else {
        cout << "Status               : Income covers expenses\n";
    }
    cout << "=============================================\n";
}
