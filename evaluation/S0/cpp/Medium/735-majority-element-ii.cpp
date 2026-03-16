// Source: https://leetcode.com/problems/majority-element-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
//
// Example:
// Input: nums = [3,2,3]
// Output: [3]
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-109 <= nums[i] <= 109
//
//
//  
// Follow up: Could you solve the problem in linear time and in O(1) space?
//

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int count1 = 0, count2 = 0;
        int candidate1 = 0, candidate2 = 1; // Initialize to different values

        for (int num : nums) {
            if (num == candidate1) {
                count1++;
            } else if (num == candidate2) {
                count2++;
            } else if (count1 == 0) {
                candidate1 = num;
                count1 = 1;
            } else if (count2 == 0) {
                candidate2 = num;
                count2 = 1;
            } else {
                count1--;
                count2--;
            }
        }

        // Verify the candidates
        count1 = 0;
        count2 = 0;
        for (int num : nums) {
            if (num == candidate1) {
                count1++;
            } else if (num == candidate2) {
                count2++;
            }
        }

        vector<int> result;
        int n = nums.size();
        if (count1 > n / 3) {
            result.push_back(candidate1);
        }
        if (count2 > n / 3) {
            result.push_back(candidate2);
        }

        return result;          
    }
};
