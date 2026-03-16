// Source: https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, find two disjoint palindromic subsequences of s such that the product of their lengths is maximized. The two subsequences are disjoint if they do not both pick a character at the same index.
//
// Return the maximum possible product of the lengths of the two palindromic subsequences.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters. A string is palindromic if it reads the same forward and backward.
//
// Example:
// Input: s = "leetcodecom"
// Output: 9
// Explanation: An optimal solution is to choose "ete" for the 1st subsequence and "cdc" for the 2nd subsequence.
// The product of their lengths is: 3 * 3 = 9.
//
// Constraints:
// 2 <= s.length <= 12
// 	s consists of lowercase English letters only.
//

int maxProduct(char* s) {
    int n = strlen(s);
    int maxProd = 0;
    int totalMasks = 1 << n;

    // Function to check if a subsequence is a palindrome
    int isPalindrome(char* str, int len) {
        for (int i = 0; i < len / 2; i++) {
            if (str[i] != str[len - 1 - i]) {
                return 0;
            }
        }
        return 1;
    }

    // Iterate through all possible subsequences using bitmasking
    for (int mask1 = 1; mask1 < totalMasks; mask1++) {
        char subseq1[13];
        int len1 = 0;

        // Build the first subsequence based on mask1
        for (int i = 0; i < n; i++) {
            if (mask1 & (1 << i)) {
                subseq1[len1++] = s[i];
            }
        }
        subseq1[len1] = '\0';

        // Check if the first subsequence is a palindrome
        if (!isPalindrome(subseq1, len1)) {
            continue;
        }

        for (int mask2 = 1; mask2 < totalMasks; mask2++) {
            // Ensure the two masks are disjoint
            if (mask1 & mask2) {
                continue;
            }

            char subseq2[13];
            int len2 = 0;

            // Build the second subsequence based on mask2
            for (int i = 0; i < n; i++) {
                if (mask2 & (1 << i)) {
                    subseq2[len2++] = s[i];
                }
            }
            subseq2[len2] = '\0';

            // Check if the second subsequence is a palindrome
            if (!isPalindrome(subseq2, len2)) {
                continue;
            }

            // Update maximum product
            int product = len1 * len2;
            if (product > maxProd) {
                maxProd = product;
            }
        }
    }

    return maxProd;     
}
