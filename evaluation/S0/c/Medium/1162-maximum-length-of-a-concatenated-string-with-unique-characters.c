// Source: https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings arr. A string s is formed by the concatenation of a subsequence of arr that has unique characters.
//
// Return the maximum possible length of s.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: arr = ["un","iq","ue"]
// Output: 4
// Explanation: All the valid concatenations are:
// - ""
// - "un"
// - "iq"
// - "ue"
// - "uniq" ("un" + "iq")
// - "ique" ("iq" + "ue")
// Maximum length is 4.
//
// Constraints:
// 1 <= arr.length <= 16
// 	1 <= arr[i].length <= 26
// 	arr[i] contains only lowercase English letters.
//

int maxLength(char** arr, int arrSize) {
    int maxLen = 0;

    void backtrack(int index, int currentMask, int currentLen) {
        if (index == arrSize) {
            if (currentLen > maxLen) {
                maxLen = currentLen;
            }
            return;
        }

        // Option 1: Skip the current string
        backtrack(index + 1, currentMask, currentLen);

        // Option 2: Include the current string if it has unique characters
        int strMask = 0;
        int strLen = 0;
        for (int i = 0; arr[index][i] != '\0'; i++) {
            int charBit = 1 << (arr[index][i] - 'a');
            if ((strMask & charBit) != 0) {
                // Duplicate character found in the string itself
                strLen = -1;
                break;
            }
            strMask |= charBit;
            strLen++;
        }

        if (strLen != -1 && (currentMask & strMask) == 0) {
            backtrack(index + 1, currentMask | strMask, currentLen + strLen);
        }
    }

    backtrack(0, 0, 0);
    return maxLen;      
}
