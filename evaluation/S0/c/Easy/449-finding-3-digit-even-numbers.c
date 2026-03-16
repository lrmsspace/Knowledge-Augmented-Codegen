// Source: https://leetcode.com/problems/finding-3-digit-even-numbers/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array digits, where each element is a digit. The array may contain duplicates.
//
// You need to find all the unique integers that follow the given requirements:
//
//
// 	The integer consists of the concatenation of three elements from digits in any arbitrary order.
// 	The integer does not have leading zeros.
// 	The integer is even.
//
//
// For example, if the given digits were [1, 2, 3], integers 132 and 312 follow the requirements.
//
// Return a sorted array of the unique integers.
//
// Example:
// Input: digits = [2,1,3,0]
// Output: [102,120,130,132,210,230,302,310,312,320]
// Explanation: All the possible integers that follow the requirements are in the output array. 
// Notice that there are no odd integers or integers with leading zeros.
//
// Constraints:
// 3 <= digits.length <= 100
// 	0 <= digits[i] <= 9
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findEvenNumbers(int* digits, int digitsSize, int* returnSize) {
    int count[10] = {0};
    for (int i = 0; i < digitsSize; i++) {
        count[digits[i]]++;
    }

    int* result = (int*)malloc(900 * sizeof(int));
    int idx = 0;

    for (int i = 100; i <= 998; i += 2) {
        int hundreds = i / 100;
        int tens = (i / 10) % 10;
        int units = i % 10;

        count[hundreds]--;
        count[tens]--;
        count[units]--;

        if (count[hundreds] >= 0 && count[tens] >= 0 && count[units] >= 0) {
            result[idx++] = i;
        }

        count[hundreds]++;
        count[tens]++;
        count[units]++;
    }

    *returnSize = idx;
    return result;      
}
