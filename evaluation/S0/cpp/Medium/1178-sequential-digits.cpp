// Source: https://leetcode.com/problems/sequential-digits/   |   Difficulty: Medium
//
// Problem Description:
// An integer has sequential digits if and only if each digit in the number is one more than the previous digit.
//
// Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.
//
// Example:
// Input: low = 100, high = 300
// Output: [123,234]
//
// Constraints:
// 10 <= low <= high <= 10^9
//

class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> result;
        string digits = "123456789";

        int nLow = to_string(low).size();
        int nHigh = to_string(high).size();

        for (int length = nLow; length <= nHigh; ++length) {
            for (int start = 0; start <= 9 - length; ++start) {
                int num = stoi(digits.substr(start, length));
                if (num >= low && num <= high) {
                    result.push_back(num);
                }
            }
        }

        return result;          
    }
};
