// Source: https://leetcode.com/problems/largest-values-from-labels/   |   Difficulty: Medium
//
// Problem Description:
// You are given n item's value and label as two integer arrays values and labels. You are also given two integers numWanted and useLimit.
//
// Your task is to find a subset of items with the maximum sum of their values such that:
//
//
// 	The number of items is at most numWanted.
// 	The number of items with the same label is at most useLimit.
//
//
// Return the maximum sum.
//
// Example:
// Input: values = [5,4,3,2,1], labels = [1,1,2,2,3], numWanted = 3, useLimit = 1
//
// Output: 9
//
// Explanation:
//
// The subset chosen is the first, third, and fifth items with the sum of values 5 + 3 + 1.
//
// Constraints:
// n == values.length == labels.length
// 	1 <= n <= 2 * 104
// 	0 <= values[i], labels[i] <= 2 * 104
// 	1 <= numWanted, useLimit <= n
//

int largestValsFromLabels(int* values, int valuesSize, int* labels, int labelsSize, int numWanted, int useLimit) {
    typedef struct {
        int value;
        int label;
    } Item;

    int compare(const void* a, const void* b) {
        return ((Item*)b)->value - ((Item*)a)->value;
    }

    Item* items = (Item*)malloc(valuesSize * sizeof(Item));
    for (int i = 0; i < valuesSize; i++) {
        items[i].value = values[i];
        items[i].label = labels[i];
    }

    qsort(items, valuesSize, sizeof(Item), compare);

    int* labelCount = (int*)calloc(20001, sizeof(int));
    int totalValue = 0;
    int itemsUsed = 0;

    for (int i = 0; i < valuesSize && itemsUsed < numWanted; i++) {
        if (labelCount[items[i].label] < useLimit) {
            totalValue += items[i].value;
            labelCount[items[i].label]++;
            itemsUsed++;
        }
    }

    free(items);
    free(labelCount);

    return totalValue;      
}
