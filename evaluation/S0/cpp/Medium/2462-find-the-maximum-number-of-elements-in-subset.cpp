// Source: https://leetcode.com/problems/find-the-maximum-number-of-elements-in-subset/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of positive integers nums.
//
// You need to select a subset of nums which satisfies the following condition:
//
//
// 	You can place the selected elements in a 0-indexed array such that it follows the pattern: [x, x2, x4, ..., xk/2, xk, xk/2, ..., x4, x2, x] (Note that k can be be any non-negative power of 2). For example, [2, 4, 16, 4, 2] and [3, 9, 3] follow the pattern while [2, 4, 8, 4, 2] does not.
//
//
// Return the maximum number of elements in a subset that satisfies these conditions.
//
// Example:
// Input: nums = [5,4,1,2,2]
// Output: 3
// Explanation: We can select the subset {4,2,2}, which can be placed in the array as [2,4,2] which follows the pattern and 22 == 4. Hence the answer is 3.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<int, int> countMap;
        for (int num : nums) {
            countMap[num]++;
        }

        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());

        int maxLength = 0;

        for (int num : nums) {
            if (countMap.find(num) == countMap.end()) {
                continue;
            }

            int currentNum = num;
            int currentLength = 0;

            while (countMap.find(currentNum) != countMap.end() && countMap[currentNum] > 0) {
                currentLength++;
                countMap[currentNum]--;
                currentNum *= 2;
            }

            maxLength = max(maxLength, currentLength);
        }

        return maxLength;           
    }
};
