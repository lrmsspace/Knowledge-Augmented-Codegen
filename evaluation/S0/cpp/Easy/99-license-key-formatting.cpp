// Source: https://leetcode.com/problems/license-key-formatting/   |   Difficulty: Easy
//
// Problem Description:
// You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.
//
// We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.
//
// Return the reformatted license key.
//
// Example:
// Input: s = "5F3Z-2e-9-w", k = 4
// Output: "5F3Z-2E9W"
// Explanation: The string s has been split into two parts, each part has 4 characters.
// Note that the two extra dashes are not needed and can be removed.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of English letters, digits, and dashes '-'.
// 	1 <= k <= 104
//

class Solution {
public:
    string licenseKeyFormatting(string s, int k) {
        string res;
        int count = 0;

        // Traverse the string in reverse
        for (int i = s.length() - 1; i >= 0; --i) {
            char c = s[i];
            if (c == '-') {
                continue; // Skip dashes
            }

            // Convert to uppercase and add to result
            res.push_back(toupper(c));
            count++;

            // Insert dash after every k characters
            if (count == k) {
                res.push_back('-');
                count = 0;
            }
        }

        // Remove trailing dash if present
        if (!res.empty() && res.back() == '-') {
            res.pop_back();
        }

        // Reverse the result to get the correct order
        reverse(res.begin(), res.end());
        return res;         
    }
};
