// Source: https://leetcode.com/problems/largest-3-same-digit-number-in-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string num representing a large integer. An integer is good if it meets the following conditions:
//
//
// 	It is a substring of num with length 3.
// 	It consists of only one unique digit.
//
//
// Return the maximum good integer as a string or an empty string "" if no such integer exists.
//
// Note:
//
//
// 	A substring is a contiguous sequence of characters within a string.
// 	There may be leading zeroes in num or a good integer.
//
// Example:
// Input: num = "6777133339"
// Output: "777"
// Explanation: There are two distinct good integers: "777" and "333".
// "777" is the largest, so we return "777".
//
// Constraints:
// 3 <= num.length <= 1000
// 	num only consists of digits.
//

class Solution {
public:
    string largestGoodInteger(string num) {
        string res = "";
        for (int i = 0; i < num.size() - 2; ++i) {
            if (num[i] == num[i + 1] && num[i] == num[i + 2]) {
                string candidate = num.substr(i, 3);
                if (candidate > res) {
                    res = candidate;
                }
            }
        }
        return res;         
    }
};
