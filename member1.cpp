#include "member1.h"
#include <limits>

void inputAnnualData(AnnualData& data) {
    data.categories[0] = "Food";
    data.categories[1] = "Rent";
    data.categories[2] = "Transport";
    data.categories[3] = "Education";
    data.categories[4] = "Healthcare";
    data.categories[5] = "Shopping";
    data.categories[6] = "Entertainment";
    data.categories[7] = "Others";
    data.categoryCount = 8;

    cout << "\n===== ANNUAL INFORMATION =====\n";

    cout << "Enter financial year (e.g. 2026): ";
    while (!(cin >> data.year) || data.year < 1900 || data.year > 3000) {
        cout << "Invalid year. Enter a valid year: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter annual income (INR): ";
    while (!(cin >> data.income) || data.income < 0) {
        cout << "Invalid income. Enter a non-negative amount: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void displayCategories(const AnnualData& data) {
    cout << "\nAvailable expense categories:\n";
    for (int i = 0; i < data.categoryCount; ++i) {
        cout << i + 1 << ". " << data.categories[i] << '\n';
    }
}
