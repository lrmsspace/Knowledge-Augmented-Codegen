// Source: https://leetcode.com/problems/sort-array-by-parity-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers nums, half of the integers in nums are odd, and the other half are even.
//
// Sort the array so that whenever nums[i] is odd, i is odd, and whenever nums[i] is even, i is even.
//
// Return any answer array that satisfies this condition.
//
// Example:
// Input: nums = [4,2,5,7]
// Output: [4,5,2,7]
// Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.
//
// Constraints:
// 2 <= nums.length <= 2 * 104
// 	nums.length is even.
// 	Half of the integers in nums are even.
// 	0 <= nums[i] <= 1000
//
//
//  
// Follow Up: Could you solve it in-place?
//

class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        int evenIndex = 0;
        int oddIndex = 1;

        for (int num : nums) {
            if (num % 2 == 0) {
                result[evenIndex] = num;
                evenIndex += 2;
            } else {
                result[oddIndex] = num;
                oddIndex += 2;
            }
        }

        return result;          
    }
};
