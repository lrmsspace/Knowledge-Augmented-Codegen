// Source: https://leetcode.com/problems/count-k-subsequences-of-a-string-with-maximum-beauty/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an integer k.
//
// A k-subsequence is a subsequence of s, having length k, and all its characters are unique, i.e., every character occurs once.
//
// Let f(c) denote the number of times the character c occurs in s.
//
// The beauty of a k-subsequence is the sum of f(c) for every character c in the k-subsequence.
//
// For example, consider s = "abbbdd" and k = 2:
//
//
// 	f('a') = 1, f('b') = 3, f('d') = 2
// 	Some k-subsequences of s are:
// 	
// 		"abbbdd" -> "ab" having a beauty of f('a') + f('b') = 4
// 		"abbbdd" -> "ad" having a beauty of f('a') + f('d') = 3
// 		"abbbdd" -> "bd" having a beauty of f('b') + f('d') = 5
// 	
// 	
//
//
// Return an integer denoting the number of k-subsequences whose beauty is the maximum among all k-subsequences. Since the answer may be too large, return it modulo 109 + 7.
//
// A subsequence of a string is a new string formed from the original string by deleting some (possibly none) of the characters without disturbing the relative positions of the remaining characters.
//
// Notes
//
//
// 	f(c) is the number of times a character c occurs in s, not a k-subsequence.
// 	Two k-subsequences are considered different if one is formed by an index that is not present in the other. So, two k-subsequences may form the same string.
//
// Example:
// Input: s = "bcca", k = 2
// Output: 4
// Explanation: From s we have f('a') = 1, f('b') = 1, and f('c') = 2.
// The k-subsequences of s are: 
// bcca having a beauty of f('b') + f('c') = 3 
// bcca having a beauty of f('b') + f('c') = 3 
// bcca having a beauty of f('b') + f('a') = 2 
// bcca having a beauty of f('c') + f('a') = 3
// bcca having a beauty of f('c') + f('a') = 3 
// There are 4 k-subsequences that have the maximum beauty, 3. 
// Hence, the answer is 4.
//
// Constraints:
// 1 <= s.length <= 2 * 105
// 	1 <= k <= s.length
// 	s consists only of lowercase English letters.
//

class Solution {
    public int countKSubsequencesWithMaxBeauty(String s, int k) {
        int MOD = 1_000_000_007;
        int[] freq = new int[26];
        for (char c : s.toCharArray()) {
            freq[c - 'a']++;
        }
        Arrays.sort(freq);
        long res = 1;
        int n = freq.length;
        for (int i = 0; i < k; i++) {
            if (freq[n - 1 - i] != freq[n - k]) {
                res = (res * freq[n - 1 - i]) % MOD;
            } else {
                int count = 0;
                for (int j = 0; j < n; j++) {
                    if (freq[j] == freq[n - k]) {
                        count++;
                    }
                }
                int choose = 0;
                for (int j = n - k; j < n; j++) {
                    if (freq[j] == freq[n - k]) {
                        choose++;
                    }
                }
                res = (res * nCr(count, choose, MOD)) % MOD;
                break;
            }
        }
        return (int) res;           
    }
}
