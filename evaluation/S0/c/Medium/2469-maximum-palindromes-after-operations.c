// Source: https://leetcode.com/problems/maximum-palindromes-after-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string array words having length n and containing 0-indexed strings.
//
// You are allowed to perform the following operation any number of times (including zero):
//
//
// 	Choose integers i, j, x, and y such that 0 <= i, j < n, 0 <= x < words[i].length, 0 <= y < words[j].length, and swap the characters words[i][x] and words[j][y].
//
//
// Return an integer denoting the maximum number of palindromes words can contain, after performing some operations.
//
// Note: i and j may be equal during an operation.
//
// Example:
// Input: words = ["abbb","ba","aa"]
// Output: 3
// Explanation: In this example, one way to get the maximum number of palindromes is:
// Choose i = 0, j = 1, x = 0, y = 0, so we swap words[0][0] and words[1][0]. words becomes ["bbbb","aa","aa"].
// All strings in words are now palindromes.
// Hence, the maximum number of palindromes achievable is 3.
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 100
// 	words[i] consists only of lowercase English letters.
//

int maxPalindromesAfterOperations(char** words, int wordsSize) {
    int oddCount = 0;
    for (int i = 0; i < wordsSize; i++) {
        int charCount[26] = {0};
        for (int j = 0; words[i][j] != '\0'; j++) {
            charCount[words[i][j] - 'a']++;
        }
        int localOddCount = 0;
        for (int k = 0; k < 26; k++) {
            if (charCount[k] % 2 != 0) {
                localOddCount++;
            }
        }
        if (localOddCount % 2 != 0) {
            oddCount++;
        }
    }
    return wordsSize - (oddCount > 0 ? oddCount - 1 : 0);       
}
