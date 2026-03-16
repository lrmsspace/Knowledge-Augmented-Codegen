// Source: https://leetcode.com/problems/most-frequent-ids/   |   Difficulty: Medium
//
// Problem Description:
// The problem involves tracking the frequency of IDs in a collection that changes over time. You have two integer arrays, nums and freq, of equal length n. Each element in nums represents an ID, and the corresponding element in freq indicates how many times that ID should be added to or removed from the collection at each step.
//
//
// 	Addition of IDs: If freq[i] is positive, it means freq[i] IDs with the value nums[i] are added to the collection at step i.
// 	Removal of IDs: If freq[i] is negative, it means -freq[i] IDs with the value nums[i] are removed from the collection at step i.
//
//
// Return an array ans of length n, where ans[i] represents the count of the most frequent ID in the collection after the ith step. If the collection is empty at any step, ans[i] should be 0 for that step.
//
// Example:
// Input: nums = [2,3,2,1], freq = [3,2,-3,1]
//
// Output: [3,3,2,2]
//
// Explanation:
//
// After step 0, we have 3 IDs with the value of 2. So ans[0] = 3.
// After step 1, we have 3 IDs with the value of 2 and 2 IDs with the value of 3. So ans[1] = 3.
// After step 2, we have 2 IDs with the value of 3. So ans[2] = 2.
// After step 3, we have 2 IDs with the value of 3 and 1 ID with the value of 1. So ans[3] = 2.
//
// Constraints:
// 1 <= nums.length == freq.length <= 105
// 	1 <= nums[i] <= 105
// 	-105 <= freq[i] <= 105
// 	freq[i] != 0
// 	The input is generated such that the occurrences of an ID will not be negative in any step.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* mostFrequentIDs(int* nums, int numsSize, int* freq, int freqSize, int* returnSize) {
    // Hash map to store the frequency of each ID
    #define MAX_ID 100000
    long long idCount[MAX_ID + 1] = {0};
    
    // Array to store the result
    long long* result = (long long*)malloc(numsSize * sizeof(long long));
    
    // Variable to keep track of the maximum frequency
    long long maxFreq = 0;
    
    for (int i = 0; i < numsSize; i++) {
        int id = nums[i];
        int change = freq[i];
        
        // Update the frequency of the current ID
        idCount[id] += change;
        
        // If the frequency becomes negative, reset it to zero
        if (idCount[id] < 0) {
            idCount[id] = 0;
        }
        
        // Update the maximum frequency
        if (idCount[id] > maxFreq) {
            maxFreq = idCount[id];
        } else if (change < 0 && idCount[id] + (-change) == maxFreq) {
            // Recalculate maxFreq if the current max ID's count was decreased
            maxFreq = 0;
            for (int j = 1; j <= MAX_ID; j++) {
                if (idCount[j] > maxFreq) {
                    maxFreq = idCount[j];
                }
            }
        }
        
        // Store the current maximum frequency in the result
        result[i] = maxFreq;
    }
    
    *returnSize = numsSize;
    return result;      
}
