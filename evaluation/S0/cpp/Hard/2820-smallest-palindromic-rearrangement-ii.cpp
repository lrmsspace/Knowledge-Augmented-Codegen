// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a palindromic string s and an integer k.
//
// Return the k-th lexicographically smallest palindromic permutation of s. If there are fewer than k distinct palindromic permutations, return an empty string.
//
// Note: Different rearrangements that yield the same palindromic string are considered identical and are counted once.
//
// Example:
// Input: s = "abba", k = 2
//
// Output: "baab"
//
// Explanation:
//
//
// 	The two distinct palindromic rearrangements of "abba" are "abba" and "baab".
// 	Lexicographically, "abba" comes before "baab". Since k = 2, the output is "baab".
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
// 	s is guaranteed to be palindromic.
// 	1 <= k <= 106
//

class Solution {
public:
    string smallestPalindrome(string s, int k) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }
        
        string half = "";
        char midChar = '\0';
        for (int i = 0; i < 26; i++) {
            if (count[i] % 2 == 1) {
                midChar = 'a' + i;
            }
            half += string(count[i] / 2, 'a' + i);
        }
        
        int n = half.size();
        string result = "";
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 26; j++) {
                if (count[j] / 2 == 0) continue;
                
                count[j] -= 2;
                
                long long permutations = 1;
                int remaining = n - i - 1;
                for (int c : count) {
                    permutations *= factorial(remaining) / factorial(c / 2);
                    remaining -= c / 2;
                }
                
                if (permutations >= k) {
                    result += ('a' + j);
                    break;
                } else {
                    k -= permutations;
                    count[j] += 2;
                }
            }
        }
        
        string palindrome = result;
        if (midChar != '\0') {
            palindrome += midChar;
        }
        reverse(result.begin(), result.end());
        palindrome += result;
        
        return palindrome;          
    }
};
