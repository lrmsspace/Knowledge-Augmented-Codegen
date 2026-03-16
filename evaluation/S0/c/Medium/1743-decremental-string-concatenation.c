// Source: https://leetcode.com/problems/decremental-string-concatenation/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array words containing n strings.
//
// Let's define a join operation join(x, y) between two strings x and y as concatenating them into xy. However, if the last character of x is equal to the first character of y, one of them is deleted.
//
// For example join("ab", "ba") = "aba" and join("ab", "cde") = "abcde".
//
// You are to perform n - 1 join operations. Let str0 = words[0]. Starting from i = 1 up to i = n - 1, for the ith operation, you can do one of the following:
//
//
// 	Make stri = join(stri - 1, words[i])
// 	Make stri = join(words[i], stri - 1)
//
//
// Your task is to minimize the length of strn - 1.
//
// Return an integer denoting the minimum possible length of strn - 1.
//
// Example:
// Input: words = ["aa","ab","bc"]
// Output: 4
// Explanation: In this example, we can perform join operations in the following order to minimize the length of str2: 
// str0 = "aa"
// str1 = join(str0, "ab") = "aab"
// str2 = join(str1, "bc") = "aabc" 
// It can be shown that the minimum possible length of str2 is 4.
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 50
// 	Each character in words[i] is an English lowercase letter
//

int minimizeConcatenatedLength(char** words, int wordsSize) {
    int dp[wordsSize][2];
    for (int i = 0; i < wordsSize; i++) {
        int len = strlen(words[i]);
        dp[i][0] = dp[i][1] = len;
    }

    for (int i = 1; i < wordsSize; i++) {
        char* curr = words[i];
        char curr_start = curr[0];
        char curr_end = curr[strlen(curr) - 1];

        for (int j = 0; j < 2; j++) {
            char* prev = words[i - 1];
            char prev_start = prev[0];
            char prev_end = prev[strlen(prev) - 1];

            // Case 1: prev + curr
            dp[i][0] = fmin(dp[i][0], dp[i - 1][j] + strlen(curr) - (prev_end == curr_start ? 1 : 0));

            // Case 2: curr + prev
            dp[i][1] = fmin(dp[i][1], dp[i - 1][j] + strlen(curr) - (curr_end == prev_start ? 1 : 0));
        }
    }

    return fmin(dp[wordsSize - 1][0], dp[wordsSize - 1][1]);        
}
