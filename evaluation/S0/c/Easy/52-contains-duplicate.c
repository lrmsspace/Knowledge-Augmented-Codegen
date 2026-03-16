// Source: https://leetcode.com/problems/contains-duplicate/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
//
// Example:
// Input: nums = [1,2,3,1]
//
// Output: true
//
// Explanation:
//
// The element 1 occurs at the indices 0 and 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//

bool containsDuplicate(int* nums, int numsSize) {
    // Using a hash table to track seen numbers
    #define TABLE_SIZE 131071  // A large prime number for better distribution
    int hashTable[TABLE_SIZE] = {0};

    for (int i = 0; i < numsSize; i++) {
        // Compute a hash index
        int hashIndex = (nums[i] + 1000000000) % TABLE_SIZE; // Offset to handle negative numbers

        // Linear probing in case of collision
        while (hashTable[hashIndex] != 0) {
            if (hashTable[hashIndex] == nums[i]) {
                return true; // Duplicate found
            }
            hashIndex = (hashIndex + 1) % TABLE_SIZE;
        }

        // Insert the number into the hash table
        hashTable[hashIndex] = nums[i];
    }

    return false; // No duplicates found        
}
