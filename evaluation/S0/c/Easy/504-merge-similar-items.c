// Source: https://leetcode.com/problems/merge-similar-items/   |   Difficulty: Easy
//
// Problem Description:
// You are given two 2D integer arrays, items1 and items2, representing two sets of items. Each array items has the following properties:
//
//
// 	items[i] = [valuei, weighti] where valuei represents the value and weighti represents the weight of the ith item.
// 	The value of each item in items is unique.
//
//
// Return a 2D integer array ret where ret[i] = [valuei, weighti], with weighti being the sum of weights of all items with value valuei.
//
// Note: ret should be returned in ascending order by value.
//
// Example:
// Input: items1 = [[1,1],[4,5],[3,8]], items2 = [[3,1],[1,5]]
// Output: [[1,6],[3,9],[4,5]]
// Explanation: 
// The item with value = 1 occurs in items1 with weight = 1 and in items2 with weight = 5, total weight = 1 + 5 = 6.
// The item with value = 3 occurs in items1 with weight = 8 and in items2 with weight = 1, total weight = 8 + 1 = 9.
// The item with value = 4 occurs in items1 with weight = 5, total weight = 5.  
// Therefore, we return [[1,6],[3,9],[4,5]].
//
// Constraints:
// 1 <= items1.length, items2.length <= 1000
// 	items1[i].length == items2[i].length == 2
// 	1 <= valuei, weighti <= 1000
// 	Each valuei in items1 is unique.
// 	Each valuei in items2 is unique.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** mergeSimilarItems(int** items1, int items1Size, int* items1ColSize, int** items2, int items2Size, int* items2ColSize, int* returnSize, int** returnColumnSizes) {
    int weight[1001] = {0};
    for (int i = 0; i < items1Size; i++) {
        weight[items1[i][0]] += items1[i][1];
    }
    for (int i = 0; i < items2Size; i++) {
        weight[items2[i][0]] += items2[i][1];
    }

    int count = 0;
    for (int i = 1; i <= 1000; i++) {
        if (weight[i] > 0) {
            count++;
        }
    }

    int** result = (int**)malloc(sizeof(int*) * count);
    *returnColumnSizes = (int*)malloc(sizeof(int) * count);
    *returnSize = count;

    int index = 0;
    for (int i = 1; i <= 1000; i++) {
        if (weight[i] > 0) {
            result[index] = (int*)malloc(sizeof(int) * 2);
            result[index][0] = i;
            result[index][1] = weight[i];
            (*returnColumnSizes)[index] = 2;
            index++;
        }
    }

    return result;      
}
