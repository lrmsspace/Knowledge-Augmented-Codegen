// Source: https://leetcode.com/problems/swap-for-longest-repeated-character-substring/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string text. You can swap two of the characters in the text.
//
// Return the length of the longest substring with repeated characters.
//
// Example:
// Input: text = "ababa"
// Output: 3
// Explanation: We can swap the first 'b' with the last 'a', or the last 'b' with the first 'a'. Then, the longest repeated character substring is "aaa" with length 3.
//
// Constraints:
// 1 <= text.length <= 2 * 104
// 	text consist of lowercase English characters only.
//

int maxRepOpt1(char* text) {
    int count[26] = {0};
    int n = strlen(text);
    for (int i = 0; i < n; i++) {
        count[text[i] - 'a']++;
    }

    int maxLen = 0;
    for (int i = 0; i < n; ) {
        char currentChar = text[i];
        int j = i;
        while (j < n && text[j] == currentChar) {
            j++;
        }
        int left = i;
        int right = j;

        // Check for the case without swap
        maxLen = fmax(maxLen, right - left);

        // Check for the case with one swap
        if (right < n) {
            int k = right + 1;
            while (k < n && text[k] == currentChar) {
                k++;
            }
            int totalLength = (right - left) + (k - right - 1 < count[currentChar - 'a'] ? (k - right - 1) : (count[currentChar - 'a'] - (right - left)));
            maxLen = fmax(maxLen, totalLength);
        }

        i = j;
    }

    return maxLen;      
}
