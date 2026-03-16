// Source: https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called valid if x can be rearranged to have word2 as a prefix.
//
// Return the total number of valid substrings of word1.
//
// Example:
// Input: word1 = "bcca", word2 = "abc"
//
// Output: 1
//
// Explanation:
//
// The only valid substring is "bcca" which can be rearranged to "abcc" having "abc" as a prefix.
//
// Constraints:
// 1 <= word1.length <= 105
// 	1 <= word2.length <= 104
// 	word1 and word2 consist only of lowercase English letters.
//

long long validSubstringCount(char* word1, char* word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    if (len1 < len2) return 0;

    int count2[26] = {0};
    for (int i = 0; i < len2; i++) {
        count2[word2[i] - 'a']++;
    }

    int count1[26] = {0};
    long long result = 0;
    int left = 0;

    for (int right = 0; right < len1; right++) {
        count1[word1[right] - 'a']++;

        while (!canFormPrefix(count1, count2)) {
            count1[word1[left] - 'a']--;
            left++;
        }

        result += (right - left + 1);
    }

    return result;      
}
