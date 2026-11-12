#ifndef MEMBER3_H
#define MEMBER3_H

#include "shared.h"

int searchByID(const Expense arr[], int count, int id);
int searchByCategory(const Expense arr[], int count,
                     const string& category, Expense results[], int capacity);
void bubbleSortByAmount(Expense arr[], int count, bool ascending);

#endif
