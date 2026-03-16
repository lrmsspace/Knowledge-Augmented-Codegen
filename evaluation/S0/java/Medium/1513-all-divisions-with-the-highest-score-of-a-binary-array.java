// Source: https://leetcode.com/problems/all-divisions-with-the-highest-score-of-a-binary-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed binary array nums of length n. nums can be divided at index i (where 0 <= i <= n) into two arrays (possibly empty) numsleft and numsright:
//
//
// 	numsleft has all the elements of nums between index 0 and i - 1 (inclusive), while numsright has all the elements of nums between index i and n - 1 (inclusive).
// 	If i == 0, numsleft is empty, while numsright has all the elements of nums.
// 	If i == n, numsleft has all the elements of nums, while numsright is empty.
//
//
// The division score of an index i is the sum of the number of 0's in numsleft and the number of 1's in numsright.
//
// Return all distinct indices that have the highest possible division score. You may return the answer in any order.
//
// Example:
// Input: nums = [0,0,1,0]
// Output: [2,4]
// Explanation: Division at index
// - 0: numsleft is []. numsright is [0,0,1,0]. The score is 0 + 1 = 1.
// - 1: numsleft is [0]. numsright is [0,1,0]. The score is 1 + 1 = 2.
// - 2: numsleft is [0,0]. numsright is [1,0]. The score is 2 + 1 = 3.
// - 3: numsleft is [0,0,1]. numsright is [0]. The score is 2 + 0 = 2.
// - 4: numsleft is [0,0,1,0]. numsright is []. The score is 3 + 0 = 3.
// Indices 2 and 4 both have the highest possible division score 3.
// Note the answer [4,2] would also be accepted.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	nums[i] is either 0 or 1.
//

class Solution {
    public List<Integer> maxScoreIndices(int[] nums) {
        int n = nums.length;
        int totalOnes = 0;

        // Count total number of 1's in the array
        for (int num : nums) {
            if (num == 1) {
                totalOnes++;
            }
        }

        List<Integer> result = new ArrayList<>();
        int maxScore = -1;
        int currentZeros = 0;
        int currentOnes = totalOnes;

        // Iterate through all possible division points
        for (int i = 0; i <= n; i++) {
            int currentScore = currentZeros + currentOnes;

            // Update maxScore and result list if needed
            if (currentScore > maxScore) {
                maxScore = currentScore;
                result.clear();
                result.add(i);
            } else if (currentScore == maxScore) {
                result.add(i);
            }

            // Update counts for next division point
            if (i < n) {
                if (nums[i] == 0) {
                    currentZeros++;
                } else {
                    currentOnes--;
                }
            }
        }

        return result;          
    }
}
