#ifndef SHARED_H
#define SHARED_H

#include <iostream>
#include <string>

using namespace std;

struct AnnualData {
    int year;
    double income;
    string categories[8];
    int categoryCount;
};

struct Expense {
    int id;
    string category;
    double amount;
};

struct Node {
    Expense data;
    Node* next;
};

#endif
