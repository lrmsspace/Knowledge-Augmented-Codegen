// Source: https://leetcode.com/problems/sort-array-by-increasing-frequency/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers nums, sort the array in increasing order based on the frequency of the values. If multiple values have the same frequency, sort them in decreasing order.
//
// Return the sorted array.
//
// Example:
// Input: nums = [1,1,2,2,2,3]
// Output: [3,1,1,2,2,2]
// Explanation: '3' has a frequency of 1, '1' has a frequency of 2, and '2' has a frequency of 3.
//
// Constraints:
// 1 <= nums.length <= 100
// 	-100 <= nums[i] <= 100
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* frequencySort(int* nums, int numsSize, int* returnSize) {
    int freq[201] = {0}; // Frequency array for numbers from -100 to 100
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i] + 100]++;
    }

    // Create an array of pairs (number, frequency)
    typedef struct {
        int num;
        int frequency;
    } NumFreq;

    NumFreq numFreqs[numsSize];
    for (int i = 0; i < numsSize; i++) {
        numFreqs[i].num = nums[i];
        numFreqs[i].frequency = freq[nums[i] + 100];
    }

    // Custom comparator for sorting
    int compare(const void* a, const void* b) {
        NumFreq* nf1 = (NumFreq*)a;
        NumFreq* nf2 = (NumFreq*)b;
        if (nf1->frequency != nf2->frequency) {
            return nf1->frequency - nf2->frequency; // Ascending frequency
        } else {
            return nf2->num - nf1->num; // Descending number
        }
    }

    // Sort the array of pairs
    qsort(numFreqs, numsSize, sizeof(NumFreq), compare);

    // Prepare the result array
    int* result = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        result[i] = numFreqs[i].num;
    }

    *returnSize = numsSize;
    return result;      
}
