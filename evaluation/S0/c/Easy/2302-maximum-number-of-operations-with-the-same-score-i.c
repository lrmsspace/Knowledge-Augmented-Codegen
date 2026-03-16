// Source: https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of integers nums. Consider the following operation:
//
//
// 	Delete the first two elements nums and define the score of the operation as the sum of these two elements.
//
//
// You can perform this operation until nums contains fewer than two elements. Additionally, the same score must be achieved in all operations.
//
// Return the maximum number of operations you can perform.
//
// Example:
// Input: nums = [3,2,1,4,5]
//
// Output: 2
//
// Explanation:
//
//
// 	We can perform the first operation with the score 3 + 2 = 5. After this operation, nums = [1,4,5].
// 	We can perform the second operation as its score is 4 + 1 = 5, the same as the previous operation. After this operation, nums = [5].
// 	As there are fewer than two elements, we can't perform more operations.
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 1000
//

int maxOperations(int* nums, int numsSize) {
    int max_ops = 0;
    int freq[2001] = {0}; // Since nums[i] can be at most 1000, the maximum sum can be 2000

    // Count frequency of each number in nums
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    // Check all possible sums from 2 to 2000
    for (int target_sum = 2; target_sum <= 2000; target_sum++) {
        int current_ops = 0;
        int temp_freq[2001];
        memcpy(temp_freq, freq, sizeof(freq));

        for (int num = 1; num <= 1000; num++) {
            int complement = target_sum - num;
            if (complement < 1 || complement > 1000) continue;

            if (num == complement) {
                current_ops += temp_freq[num] / 2;
            } else if (num < complement) {
                current_ops += (temp_freq[num] < temp_freq[complement]) ? temp_freq[num] : temp_freq[complement];
            }
        }

        if (current_ops > max_ops) {
            max_ops = current_ops;
        }
    }

    return max_ops;     
}
