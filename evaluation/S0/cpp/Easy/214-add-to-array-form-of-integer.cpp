// Source: https://leetcode.com/problems/add-to-array-form-of-integer/   |   Difficulty: Easy
//
// Problem Description:
// The array-form of an integer num is an array representing its digits in left to right order.
//
//
// 	For example, for num = 1321, the array form is [1,3,2,1].
//
//
// Given num, the array-form of an integer, and an integer k, return the array-form of the integer num + k.
//
// Example:
// Input: num = [1,2,0,0], k = 34
// Output: [1,2,3,4]
// Explanation: 1200 + 34 = 1234
//
// Constraints:
// 1 <= num.length <= 104
// 	0 <= num[i] <= 9
// 	num does not contain any leading zeros except for the zero itself.
// 	1 <= k <= 104
//

class Solution {
public:
    vector<int> addToArrayForm(vector<int>& num, int k) {
        vector<int> result;
        int n = num.size();
        int carry = 0;

        for (int i = n - 1; i >= 0 || k > 0 || carry > 0; --i) {
            int digitNum = (i >= 0) ? num[i] : 0;
            int digitK = k % 10;
            k /= 10;

            int sum = digitNum + digitK + carry;
            carry = sum / 10;
            result.push_back(sum % 10);
        }

        reverse(result.begin(), result.end());
        return result;          
    }
};
