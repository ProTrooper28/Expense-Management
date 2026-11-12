#ifndef MEMBER4_H
#define MEMBER4_H

#include "shared.h"

const int MAX_UNDO = 100;

void pushUndo(int undoStack[], int& top, int expenseId);
bool undoLastAddition(Node*& head, int undoStack[], int& top);
void generateAnnualReport(const AnnualData& data, const Node* head);

#endif
