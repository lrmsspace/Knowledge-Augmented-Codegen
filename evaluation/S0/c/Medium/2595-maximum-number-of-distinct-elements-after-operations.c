// Source: https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// You are allowed to perform the following operation on each element of the array at most once:
//
//
// 	Add an integer in the range [-k, k] to the element.
//
//
// Return the maximum possible number of distinct elements in nums after performing the operations.
//
// Example:
// Input: nums = [1,2,2,3,3,4], k = 2
//
// Output: 6
//
// Explanation:
//
// nums changes to [-1, 0, 1, 2, 3, 4] after performing operations on the first four elements.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	0 <= k <= 109
//

int maxDistinctElements(int* nums, int numsSize, int k) {
    // Use a hash set to track distinct elements
    #define TABLE_SIZE 131071  // A large prime number for hash table size
    int hashTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = 0;
    }

    int distinctCount = 0;

    for (int i = 0; i < numsSize; i++) {
        int original = nums[i];
        int found = 0;

        // Try to find a distinct value in the range [original - k, original + k]
        for (int delta = -k; delta <= k; delta++) {
            int candidate = original + delta;
            int hashIndex = (candidate % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;

            // Linear probing for collision resolution
            while (hashTable[hashIndex] != 0) {
                if (hashTable[hashIndex] == candidate) {
                    break; // Candidate already exists
                }
                hashIndex = (hashIndex + 1) % TABLE_SIZE;
            }

            if (hashTable[hashIndex] == 0) {
                // Found a new distinct value
                hashTable[hashIndex] = candidate;
                distinctCount++;
                found = 1;
                break;
            }
        }
    }

    return distinctCount;       
}
