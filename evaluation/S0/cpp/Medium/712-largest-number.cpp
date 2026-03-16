// Source: https://leetcode.com/problems/largest-number/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.
//
// Since the result may be very large, so you need to return a string instead of an integer.
//
// Example:
// Input: nums = [10,2]
// Output: "210"
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 109
//

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> strNums;
        for (int num : nums) {
            strNums.push_back(to_string(num));
        }

        sort(strNums.begin(), strNums.end(), [](const string& a, const string& b) {
            return a + b > b + a;
        });

        if (strNums[0] == "0") {
            return "0";
        }

        string result;
        for (const string& str : strNums) {
            result += str;
        }

        return result;          
    }
};
