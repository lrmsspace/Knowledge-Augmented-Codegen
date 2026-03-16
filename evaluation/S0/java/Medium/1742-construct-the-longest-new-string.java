// Source: https://leetcode.com/problems/construct-the-longest-new-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given three integers x, y, and z.
//
// You have x strings equal to "AA", y strings equal to "BB", and z strings equal to "AB". You want to choose some (possibly all or none) of these strings and concatenate them in some order to form a new string. This new string must not contain "AAA" or "BBB" as a substring.
//
// Return the maximum possible length of the new string.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: x = 2, y = 5, z = 1
// Output: 12
// Explanation: We can concatenate the strings "BB", "AA", "BB", "AA", "BB", and "AB" in that order. Then, our new string is "BBAABBAABBAB". 
// That string has length 12, and we can show that it is impossible to construct a string of longer length.
//
// Constraints:
// 1 <= x, y, z <= 50
//

class Solution {
    public int longestString(int x, int y, int z) {
        int result = z * 2; // Each "AB" contributes 2 characters

        // After using all "AB" strings, we can add "AA" and "BB" strings
        // without forming "AAA" or "BBB" substrings.
        // We can add min(x, y) pairs of "AA" and "BB".
        int minPairs = Math.min(x, y);
        result += minPairs * 4; // Each pair contributes 4 characters ("AA" + "BB")

        // If there are remaining "AA" or "BB" strings, we can add one more
        // of the remaining type without forming forbidden substrings.
        if (x > minPairs) {
            result += 2; // Add one more "AA"
        } else if (y > minPairs) {
            result += 2; // Add one more "BB"
        }

        return result;          
    }
}
