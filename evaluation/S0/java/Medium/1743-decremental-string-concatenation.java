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

class Solution {
    public int minimizeConcatenatedLength(String[] words) {
        int n = words.length;
        int[][] dp = new int[n][26];
        
        // Initialize dp for the first word
        String firstWord = words[0];
        int firstLen = firstWord.length();
        int firstStart = firstWord.charAt(0) - 'a';
        int firstEnd = firstWord.charAt(firstLen - 1) - 'a';
        for (int c = 0; c < 26; c++) {
            dp[0][c] = Integer.MAX_VALUE;
        }
        dp[0][firstEnd] = firstLen;
        
        // Fill dp table
        for (int i = 1; i < n; i++) {
            String word = words[i];
            int len = word.length();
            int start = word.charAt(0) - 'a';
            int end = word.charAt(len - 1) - 'a';
            
            for (int c = 0; c < 26; c++) {
                if (dp[i - 1][c] == Integer.MAX_VALUE) continue;
                
                // Option 1: join previous string with current word
                int newLen1 = dp[i - 1][c] + len - (c == start ? 1 : 0);
                dp[i][end] = Math.min(dp[i][end], newLen1);
                
                // Option 2: join current word with previous string
                int newLen2 = dp[i - 1][c] + len - (c == end ? 1 : 0);
                dp[i][start] = Math.min(dp[i][start], newLen2);
            }
        }
        
        // Find the minimum length in the last row of dp
        int minLength = Integer.MAX_VALUE;
        for (int c = 0; c < 26; c++) {
            minLength = Math.min(minLength, dp[n - 1][c]);
        }
        
        return minLength;           
    }
}
