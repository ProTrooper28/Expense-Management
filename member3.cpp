#include "member3.h"
#include <cctype>
#include <utility>

static string toLowerText(const string& value) {
    string result = value;
    for (char& ch : result) {
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return result;
}

int searchByID(const Expense arr[], int count, int id) {
    for (int i = 0; i < count; ++i) {
        if (arr[i].id == id) return i;
    }
    return -1;
}

int searchByCategory(const Expense arr[], int count,
                     const string& category, Expense results[], int capacity) {
    int matches = 0;
    const string target = toLowerText(category);

    for (int i = 0; i < count && matches < capacity; ++i) {
        if (toLowerText(arr[i].category) == target) {
            results[matches++] = arr[i];
        }
    }
    return matches;
}

void bubbleSortByAmount(Expense arr[], int count, bool ascending) {
    for (int i = 0; i < count - 1; ++i) {
        bool swapped = false;

        for (int j = 0; j < count - i - 1; ++j) {
            bool shouldSwap = ascending
                ? arr[j].amount > arr[j + 1].amount
                : arr[j].amount < arr[j + 1].amount;

            if (shouldSwap) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}
