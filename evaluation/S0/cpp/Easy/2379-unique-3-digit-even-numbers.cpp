// Source: https://leetcode.com/problems/unique-3-digit-even-numbers/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of digits called digits. Your task is to determine the number of distinct three-digit even numbers that can be formed using these digits.
//
// Note: Each copy of a digit can only be used once per number, and there may not be leading zeros.
//
// Example:
// Input: digits = [1,2,3,4]
//
// Output: 12
//
// Explanation: The 12 distinct 3-digit even numbers that can be formed are 124, 132, 134, 142, 214, 234, 312, 314, 324, 342, 412, and 432. Note that 222 cannot be formed because there is only 1 copy of the digit 2.
//
// Constraints:
// 3 <= digits.length <= 10
// 	0 <= digits[i] <= 9
//

class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        unordered_set<int> unique_numbers;
        int n = digits.size();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    // Check for distinct indices and leading zero
                    if (i != j && j != k && i != k && digits[i] != 0 && digits[k] % 2 == 0) {
                        int number = digits[i] * 100 + digits[j] * 10 + digits[k];
                        unique_numbers.insert(number);
                    }
                }
            }
        }

        return unique_numbers.size();           
    }
};
