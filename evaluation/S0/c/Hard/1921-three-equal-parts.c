// Source: https://leetcode.com/problems/three-equal-parts/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array arr which consists of only zeros and ones, divide the array into three non-empty parts such that all of these parts represent the same binary value.
//
// If it is possible, return any [i, j] with i + 1 < j, such that:
//
//
// 	arr[0], arr[1], ..., arr[i] is the first part,
// 	arr[i + 1], arr[i + 2], ..., arr[j - 1] is the second part, and
// 	arr[j], arr[j + 1], ..., arr[arr.length - 1] is the third part.
// 	All three parts have equal binary values.
//
//
// If it is not possible, return [-1, -1].
//
// Note that the entire part is used when considering what binary value it represents. For example, [1,1,0] represents 6 in decimal, not 3. Also, leading zeros are allowed, so [0,1,1] and [1,1] represent the same value.
//
// Example:
// Input: arr = [1,0,1,0,1]
// Output: [0,3]
//
// Constraints:
// 3 <= arr.length <= 3 * 104
// 	arr[i] is 0 or 1
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* threeEqualParts(int* arr, int arrSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = 2;
    int *res = (int*)malloc(2 * sizeof(int));
    if (!res) return NULL;

    int totalOnes = 0;
    for (int i = 0; i < arrSize; ++i) {
        if (arr[i] == 1) totalOnes++;
    }
    if (totalOnes % 3 != 0) {
        res[0] = -1; res[1] = -1; return res;
    }
    if (totalOnes == 0) {
        res[0] = 0; res[1] = arrSize - 1; return res;
    }

    int onesPerPart = totalOnes / 3;
    int firstStart = -1, firstEnd = -1;
    int secondStart = -1, secondEnd = -1;
    int thirdStart = -1, thirdEnd = -1;
    int oneCount = 0;

    for (int i = 0; i < arrSize; ++i) {
        if (arr[i] == 1) {
            oneCount++;
            if (oneCount == 1) firstStart = i;
            if (oneCount == onesPerPart) firstEnd = i;
            if (oneCount == onesPerPart + 1) secondStart = i;
            if (oneCount == 2 * onesPerPart) secondEnd = i;
            if (oneCount == 2 * onesPerPart + 1) thirdStart = i;
            if (oneCount == 3 * onesPerPart) thirdEnd = i;
        }
    }

    int len = arrSize - thirdStart;
    if (firstEnd + len > secondStart || secondEnd + len > thirdStart) {
        res[0] = -1; res[1] = -1; return res;
    }

    for (int i = 0; i < len; ++i) {
        if (arr[firstStart + i] != arr[secondStart + i] || arr[firstStart + i] != arr[thirdStart + i]) {
            res[0] = -1; res[1] = -1; return res;
        }
    }

    res[0] = firstEnd + len - 1;        
    res[1] = secondEnd + len;
    return res;
}
