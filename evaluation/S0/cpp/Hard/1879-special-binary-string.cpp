// Source: https://leetcode.com/problems/special-binary-string/   |   Difficulty: Hard
//
// Problem Description:
// Special binary strings are binary strings with the following two properties:
//
//
// 	The number of 0's is equal to the number of 1's.
// 	Every prefix of the binary string has at least as many 1's as 0's.
//
//
// You are given a special binary string s.
//
// A move consists of choosing two consecutive, non-empty, special substrings of s, and swapping them. Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.
//
// Return the lexicographically largest resulting string possible after applying the mentioned operations on the string.
//
// Example:
// Input: s = "11011000"
// Output: "11100100"
// Explanation: The strings "10" [occuring at s[1]] and "1100" [at s[3]] are swapped.
// This is the lexicographically largest string possible after some number of swaps.
//
// Constraints:
// 1 <= s.length <= 50
// 	s[i] is either '0' or '1'.
// 	s is a special binary string.
//

class Solution {
public:
    string makeLargestSpecial(string s) {
        vector<string> specials;
        int count = 0, last = 0;
        
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') count++;
            else count--;
            
            if (count == 0) {
                // Found a special substring from last to i
                string inner = s.substr(last + 1, i - last - 1);
                string special = "1" + makeLargestSpecial(inner) + "0";
                specials.push_back(special);
                last = i + 1;
            }
        }
        
        // Sort the special substrings in descending order
        sort(specials.begin(), specials.end(), greater<string>());
        
        // Concatenate the sorted special substrings
        string result;
        for (const string& sp : specials) {
            result += sp;
        }
        
        return result;          
    }
};
