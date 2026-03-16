// Source: https://leetcode.com/problems/sort-the-jumbled-numbers/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array mapping which represents the mapping rule of a shuffled decimal system. mapping[i] = j means digit i should be mapped to digit j in this system.
//
// The mapped value of an integer is the new integer obtained by replacing each occurrence of digit i in the integer with mapping[i] for all 0 <= i <= 9.
//
// You are also given another integer array nums. Return the array nums sorted in non-decreasing order based on the mapped values of its elements.
//
// Example:
// Input: mapping = [8,9,4,0,2,1,3,5,7,6], nums = [991,338,38]
// Output: [338,38,991]
// Explanation: 
// Map the number 991 as follows:
// 1. mapping[9] = 6, so all occurrences of the digit 9 will become 6.
// 2. mapping[1] = 9, so all occurrences of the digit 1 will become 9.
// Therefore, the mapped value of 991 is 669.
// 338 maps to 007, or 7 after removing the leading zeros.
// 38 maps to 07, which is also 7 after removing leading zeros.
// Since 338 and 38 share the same mapped value, they should remain in the same relative order, so 338 comes before 38.
// Thus, the sorted array is [338,38,991].
//
// Constraints:
// mapping.length == 10
// 	0 <= mapping[i] <= 9
// 	All the values of mapping[i] are unique.
// 	1 <= nums.length <= 3 * 104
// 	0 <= nums[i] < 109
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortJumbled(int* mapping, int mappingSize, int* nums, int numsSize, int* returnSize) {
    // Helper function to compute the mapped value of a number
    int mapNumber(int num, int* mapping) {
        if (num == 0) {
            return mapping[0];
        }
        int mappedValue = 0;
        int multiplier = 1;
        while (num > 0) {
            int digit = num % 10;
            mappedValue += mapping[digit] * multiplier;
            multiplier *= 10;
            num /= 10;
        }
        return mappedValue;
    }

    // Create an array of pairs (mapped value, original index)
    typedef struct {
        int mappedValue;
        int originalIndex;
    } MappedPair;

    MappedPair* mappedPairs = (MappedPair*)malloc(numsSize * sizeof(MappedPair));
    for (int i = 0; i < numsSize; i++) {
        mappedPairs[i].mappedValue = mapNumber(nums[i], mapping);
        mappedPairs[i].originalIndex = i;
    }

    // Sort the pairs based on mapped values, maintaining relative order for equal values
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = 0; j < numsSize - i - 1; j++) {
            if (mappedPairs[j].mappedValue > mappedPairs[j + 1].mappedValue) {
                MappedPair temp = mappedPairs[j];
                mappedPairs[j] = mappedPairs[j + 1];
                mappedPairs[j + 1] = temp;
            }
        }
    }

    // Create the result array based on sorted order
    int* result = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        result[i] = nums[mappedPairs[i].originalIndex];
    }

    free(mappedPairs);
    *returnSize = numsSize;
    return result;      
}
