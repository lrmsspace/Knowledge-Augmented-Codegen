// Source: https://leetcode.com/problems/add-to-array-form-of-integer/   |   Difficulty: Easy
//
// Problem Description:
// The array-form of an integer num is an array representing its digits in left to right order.
//
//
// 	For example, for num = 1321, the array form is [1,3,2,1].
//
//
// Given num, the array-form of an integer, and an integer k, return the array-form of the integer num + k.
//
// Example:
// Input: num = [1,2,0,0], k = 34
// Output: [1,2,3,4]
// Explanation: 1200 + 34 = 1234
//
// Constraints:
// 1 <= num.length <= 104
// 	0 <= num[i] <= 9
// 	num does not contain any leading zeros except for the zero itself.
// 	1 <= k <= 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* addToArrayForm(int* num, int numSize, int k, int* returnSize) {
    int maxSize = (numSize > 5) ? numSize + 1 : 6;
    int* result = (int*)malloc(maxSize * sizeof(int));
    int carry = 0;
    int i = numSize - 1;
    int j = 0;

    while (i >= 0 || k > 0 || carry > 0) {
        int digitNum = (i >= 0) ? num[i] : 0;
        int digitK = k % 10;

        int sum = digitNum + digitK + carry;
        result[j++] = sum % 10;
        carry = sum / 10;

        if (i >= 0) i--;
        k /= 10;
    }

    // Reverse the result array
    for (int left = 0, right = j - 1; left < right; left++, right--) {
        int temp = result[left];
        result[left] = result[right];
        result[right] = temp;
    }

    *returnSize = j;
    return result;      
}
