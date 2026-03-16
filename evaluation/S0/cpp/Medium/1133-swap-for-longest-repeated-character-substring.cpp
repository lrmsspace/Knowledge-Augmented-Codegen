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

class Solution {
public:
    int maxRepOpt1(string text) {
        unordered_map<char, int> charCount;
        for (char c : text) {
            charCount[c]++;
        }

        int maxLength = 0;
        int n = text.size();

        for (int i = 0; i < n; ) {
            char currentChar = text[i];
            int j = i;

            // Find the length of the current block of the same character
            while (j < n && text[j] == currentChar) {
                j++;
            }
            int blockLength = j - i;

            // Check for a possible swap with another block of the same character
            int k = j + 1;
            while (k < n && text[k] == currentChar) {
                k++;
            }
            int nextBlockLength = k - (j + 1);

            // Calculate the maximum length considering a swap
            int totalLength = blockLength + nextBlockLength;
            if (charCount[currentChar] > totalLength) {
                totalLength++; // We can swap one more character
            }

            maxLength = max(maxLength, totalLength);
            i = j; // Move to the next block
        }

        return maxLength;           
    }
};
