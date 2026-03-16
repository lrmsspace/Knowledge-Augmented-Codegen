// Source: https://leetcode.com/problems/verbal-arithmetic-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// Given an equation, represented by words on the left side and the result on the right side.
//
// You need to check if the equation is solvable under the following rules:
//
//
// 	Each character is decoded as one digit (0 - 9).
// 	No two characters can map to the same digit.
// 	Each words[i] and result are decoded as one number without leading zeros.
// 	Sum of numbers on the left side (words) will equal to the number on the right side (result).
//
//
// Return true if the equation is solvable, otherwise return false.
//
// Example:
// Input: words = ["SEND","MORE"], result = "MONEY"
// Output: true
// Explanation: Map 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8, 'Y'->'2'
// Such that: "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652
//
// Constraints:
// 2 <= words.length <= 5
// 	1 <= words[i].length, result.length <= 7
// 	words[i], result contain only uppercase English letters.
// 	The number of different characters used in the expression is at most 10.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
private:
    map<char, int> mapping;
    set<int> used;
    set<char> chars;
    set<char> leadingChars;
    vector<string> words;
    string result;
    
    long long charToNumber(const string& s) {
        long long num = 0;
        for (char c : s) {
            num = num * 10 + mapping[c];
        }
        return num;
    }
    
    bool backtrack(vector<char>& charList, int index) {
        // Base case: all characters have been mapped
        if (index == charList.size()) {
            // Check if the equation is valid
            long long sum = 0;
            for (const auto& word : words) {
                sum += charToNumber(word);
            }
            return sum == charToNumber(result);
        }
        
        char c = charList[index];
        
        // Try each digit for the current character
        for (int digit = 0; digit <= 9; digit++) {
            // Skip if this digit is already used
            if (used.count(digit)) {
                continue;
            }
            
            // Skip if this character is a leading character and digit is 0
            if (leadingChars.count(c) && digit == 0) {
                continue;
            }
            
            // Assign the digit to the character
            mapping[c] = digit;
            used.insert(digit);
            
            // Recursively try to map the next character
            if (backtrack(charList, index + 1)) {
                return true;
            }
            
            // Backtrack
            used.erase(digit);
            mapping.erase(c);
        }
        
        return false;
    }
    
public:
    bool isSolvable(vector<string>& words, string result) {
        this->words = words;
        this->result = result;
        
        // Collect all unique characters
        for (const auto& word : words) {
            for (char c : word) {
                chars.insert(c);
            }
        }
        for (char c : result) {
            chars.insert(c);
        }
        
        // Collect leading characters (cannot be 0)
        for (const auto& word : words) {
            if (word.length() > 0) {
                leadingChars.insert(word[0]);
            }
        }
        if (result.length() > 0) {
            leadingChars.insert(result[0]);
        }
        
        // If more than 10 unique characters, it's impossible
        if (chars.size() > 10) {
            return false;
        }
        
        // Convert set to vector for easier indexing in backtracking
        vector<char> charList(chars.begin(), chars.end());
        
        // Use backtracking to find a valid mapping
        return backtrack(charList, 0);
    }
};
