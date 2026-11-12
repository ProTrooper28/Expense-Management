#ifndef MEMBER2_H
#define MEMBER2_H

#include "shared.h"

void addExpense(Node*& head, const Expense& expense);
bool deleteExpense(Node*& head, int id);
bool updateExpense(Node* head, int id, double newAmount);
void displayExpenses(const Node* head);
double calculateTotalExpenses(const Node* head);
int copyExpensesToArray(const Node* head, Expense arr[], int capacity);
bool expenseExists(const Node* head, int id);
void freeExpenseList(Node*& head);

#endif
