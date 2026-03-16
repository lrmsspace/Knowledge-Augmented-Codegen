// Source: https://leetcode.com/problems/ambiguous-coordinates/   |   Difficulty: Medium
//
// Problem Description:
// We had some 2-dimensional coordinates, like "(1, 3)" or "(2, 0.5)". Then, we removed all commas, decimal points, and spaces and ended up with the string s.
//
//
// 	For example, "(1, 3)" becomes s = "(13)" and "(2, 0.5)" becomes s = "(205)".
//
//
// Return a list of strings representing all possibilities for what our original coordinates could have been.
//
// Our original representation never had extraneous zeroes, so we never started with numbers like "00", "0.0", "0.00", "1.0", "001", "00.01", or any other number that can be represented with fewer digits. Also, a decimal point within a number never occurs without at least one digit occurring before it, so we never started with numbers like ".1".
//
// The final answer list can be returned in any order. All coordinates in the final answer have exactly one space between them (occurring after the comma.)
//
// Example:
// Input: s = "(123)"
// Output: ["(1, 2.3)","(1, 23)","(1.2, 3)","(12, 3)"]
//
// Constraints:
// 4 <= s.length <= 12
// 	s[0] == '(' and s[s.length - 1] == ')'.
// 	The rest of s are digits.
//

class Solution {
public:
    vector<string> ambiguousCoordinates(string s) {
        vector<string> result;
        int n = s.size();
        
        for (int i = 2; i < n - 1; ++i) {
            string left = s.substr(1, i - 1);
            string right = s.substr(i, n - i - 1);
            
            vector<string> leftParts = generateParts(left);
            vector<string> rightParts = generateParts(right);
            
            for (const string& l : leftParts) {
                for (const string& r : rightParts) {
                    result.push_back("(" + l + ", " + r + ")");
                }
            }
        }
        
        return result;          
    }
};
