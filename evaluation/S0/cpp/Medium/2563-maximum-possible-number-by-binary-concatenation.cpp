// Source: https://leetcode.com/problems/maximum-possible-number-by-binary-concatenation/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums of size 3.
//
// Return the maximum possible number whose binary representation can be formed by concatenating the binary representation of all elements in nums in some order.
//
// Note that the binary representation of any number does not contain leading zeros.
//
// Example:
// Input: nums = [1,2,3]
//
// Output: 30
//
// Explanation:
//
// Concatenate the numbers in the order [3, 1, 2] to get the result "11110", which is the binary representation of 30.
//
// Constraints:
// nums.length == 3
// 	1 <= nums[i] <= 127
//

class Solution {
public:
    int maxGoodNumber(vector<int>& nums) {
        vector<string> binaries;
        for (int num : nums) {
            binaries.push_back(toBinary(num));
        }

        sort(binaries.begin(), binaries.end(), [](const string& a, const string& b) {
            return a + b > b + a;
        });

        string resultBinary;
        for (const string& bin : binaries) {
            resultBinary += bin;
        }

        return binaryToDecimal(resultBinary);           
    }
};
