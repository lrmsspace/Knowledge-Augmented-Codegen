// Source: https://leetcode.com/problems/letter-combinations-of-a-phone-number/   |   Difficulty: Medium
//
// Problem Description:
// Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.
//
// A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
//
// Example:
// Input: digits = "23"
// Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
//
// Constraints:
// 0 <= digits.length <= 4
// 	digits[i] is a digit in the range ['2', '9'].
//

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        vector<string> digitToLetters = {
            "",     // 0
            "",     // 1
            "abc",  // 2
            "def",  // 3
            "ghi",  // 4
            "jkl",  // 5
            "mno",  // 6
            "pqrs", // 7
            "tuv",  // 8
            "wxyz"  // 9
        };

        vector<string> result;
        string currentCombination;

        function<void(int)> backtrack = [&](int index) {
            if (index == digits.size()) {
                result.push_back(currentCombination);
                return;
            }

            int digit = digits[index] - '0';
            const string& letters = digitToLetters[digit];

            for (char letter : letters) {
                currentCombination.push_back(letter);
                backtrack(index + 1);
                currentCombination.pop_back();
            }
        };

        backtrack(0);
        return result;          
    }
};
