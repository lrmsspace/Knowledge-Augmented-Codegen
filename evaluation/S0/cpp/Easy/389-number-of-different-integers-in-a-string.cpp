// Source: https://leetcode.com/problems/number-of-different-integers-in-a-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string word that consists of digits and lowercase English letters.
//
// You will replace every non-digit character with a space. For example, "a123bc34d8ef34" will become " 123  34 8  34". Notice that you are left with some integers that are separated by at least one space: "123", "34", "8", and "34".
//
// Return the number of different integers after performing the replacement operations on word.
//
// Two integers are considered different if their decimal representations without any leading zeros are different.
//
// Example:
// Input: word = "a123bc34d8ef34"
// Output: 3
// Explanation: The three different integers are "123", "34", and "8". Notice that "34" is only counted once.
//
// Constraints:
// 1 <= word.length <= 1000
// 	word consists of digits and lowercase English letters.
//

class Solution {
public:
    int numDifferentIntegers(string word) {
        unordered_set<string> uniqueIntegers;
        string currentNumber;

        for (char c : word) {
            if (isdigit(c)) {
                currentNumber += c;
            } else {
                if (!currentNumber.empty()) {
                    // Remove leading zeros
                    size_t nonZeroPos = currentNumber.find_first_not_of('0');
                    if (nonZeroPos == string::npos) {
                        uniqueIntegers.insert("0");
                    } else {
                        uniqueIntegers.insert(currentNumber.substr(nonZeroPos));
                    }
                    currentNumber.clear();
                }
            }
        }

        // Check for any remaining number at the end of the string
        if (!currentNumber.empty()) {
            size_t nonZeroPos = currentNumber.find_first_not_of('0');
            if (nonZeroPos == string::npos) {
                uniqueIntegers.insert("0");
            } else {
                uniqueIntegers.insert(currentNumber.substr(nonZeroPos));
            }
        }

        return uniqueIntegers.size();           
    }
};
