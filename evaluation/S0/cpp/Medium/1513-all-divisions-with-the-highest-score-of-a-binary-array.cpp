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
public:
    vector<int> maxScoreIndices(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixZeros(n + 1, 0);
        vector<int> suffixOnes(n + 1, 0);

        // Calculate prefix zeros
        for (int i = 1; i <= n; ++i) {
            prefixZeros[i] = prefixZeros[i - 1] + (nums[i - 1] == 0 ? 1 : 0);
        }

        // Calculate suffix ones
        for (int i = n - 1; i >= 0; --i) {
            suffixOnes[i] = suffixOnes[i + 1] + (nums[i] == 1 ? 1 : 0);
        }

        int maxScore = 0;
        vector<int> result;

        // Find maximum score and corresponding indices
        for (int i = 0; i <= n; ++i) {
            int currentScore = prefixZeros[i] + suffixOnes[i];
            if (currentScore > maxScore) {
                maxScore = currentScore;
                result.clear();
                result.push_back(i);
            } else if (currentScore == maxScore) {
                result.push_back(i);
            }
        }

        return result;          
    }
};
