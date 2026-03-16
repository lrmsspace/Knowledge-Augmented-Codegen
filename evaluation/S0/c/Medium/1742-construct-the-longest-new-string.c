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

int longestString(int x, int y, int z) {
    int result = z * 2; // Each "AB" contributes 2 characters

    // Calculate the maximum number of "AA" and "BB" we can use without forming "AAA" or "BBB"
    int max_AA = (y + z + 1) / 2; // Maximum "AA" we can use
    int max_BB = (x + z + 1) / 2; // Maximum "BB" we can use

    // Add the minimum of available and maximum usable "AA" and "BB"
    result += (x < max_AA) ? x * 2 : max_AA * 2;
    result += (y < max_BB) ? y * 2 : max_BB * 2;

    return result;      
}
