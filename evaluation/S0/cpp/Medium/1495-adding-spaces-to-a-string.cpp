// Source: https://leetcode.com/problems/adding-spaces-to-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string s and a 0-indexed integer array spaces that describes the indices in the original string where spaces will be added. Each space should be inserted before the character at the given index.
//
//
// 	For example, given s = "EnjoyYourCoffee" and spaces = [5, 9], we place spaces before 'Y' and 'C', which are at indices 5 and 9 respectively. Thus, we obtain "Enjoy Your Coffee".
//
//
// Return the modified string after the spaces have been added.
//
// Example:
// Input: s = "LeetcodeHelpsMeLearn", spaces = [8,13,15]
// Output: "Leetcode Helps Me Learn"
// Explanation: 
// The indices 8, 13, and 15 correspond to the underlined characters in "LeetcodeHelpsMeLearn".
// We then place spaces before those characters.
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consists only of lowercase and uppercase English letters.
// 	1 <= spaces.length <= 3 * 105
// 	0 <= spaces[i] <= s.length - 1
// 	All the values of spaces are strictly increasing.
//

class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
        string result;
        result.reserve(s.length() + spaces.size());
        
        int spaceIndex = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (spaceIndex < spaces.size() && i == spaces[spaceIndex]) {
                result += ' ';
                ++spaceIndex;
            }
            result += s[i];
        }
        
        return result;          
    }
};
