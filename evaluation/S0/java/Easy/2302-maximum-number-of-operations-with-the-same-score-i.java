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

class Solution {
    public int maxOperations(int[] nums) {
        int n = nums.length;
        int maxOperations = 0;

        for (int targetSum = 2; targetSum <= 2000; targetSum++) {
            boolean[] used = new boolean[n];
            int currentOperations = 0;

            for (int i = 0; i < n; i++) {
                if (used[i]) continue;

                for (int j = i + 1; j < n; j++) {
                    if (!used[j] && nums[i] + nums[j] == targetSum) {
                        used[i] = true;
                        used[j] = true;
                        currentOperations++;
                        break;
                    }
                }
            }

            maxOperations = Math.max(maxOperations, currentOperations);
        }

        return maxOperations;           
    }
}
