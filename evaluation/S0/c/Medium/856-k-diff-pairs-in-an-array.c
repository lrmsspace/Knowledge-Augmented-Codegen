// Source: https://leetcode.com/problems/k-diff-pairs-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.
//
// A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:
//
//
// 	0 <= i, j < nums.length
// 	i != j
// 	|nums[i] - nums[j]| == k
//
//
// Notice that |val| denotes the absolute value of val.
//
// Example:
// Input: nums = [3,1,4,1,5], k = 2
// Output: 2
// Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
// Although we have two 1s in the input, we should only return the number of unique pairs.
//
// Constraints:
// 1 <= nums.length <= 104
// 	-107 <= nums[i] <= 107
// 	0 <= k <= 107
//

int findPairs(int* nums, int numsSize, int k) {
    if (k < 0) {
        return 0;
    }

    // Using a hash map to count occurrences of each number
    #define HASH_SIZE 20011
    int hash[HASH_SIZE] = {0};
    int offset = 10000000; // To handle negative numbers

    for (int i = 0; i < numsSize; i++) {
        hash[(nums[i] + offset) % HASH_SIZE]++;
    }

    int count = 0;

    if (k == 0) {
        // Count numbers that appear more than once
        for (int i = 0; i < HASH_SIZE; i++) {
            if (hash[i] > 1) {
                count++;
            }
        }
    } else {
        // Count unique pairs with difference k
        for (int i = 0; i < HASH_SIZE; i++) {
            if (hash[i] > 0) {
                int target = (i + k) % HASH_SIZE;
                if (target >= 0 && target < HASH_SIZE && hash[target] > 0) {
                    count++;
                }
            }
        }
    }

    return count;       
}
