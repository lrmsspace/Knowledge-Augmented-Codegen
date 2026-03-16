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

int countKSubsequencesWithMaxBeauty(char* s, int k) {
    const int MOD = 1000000007;
    int freq[26] = {0};
    for (char *p = s; *p; ++p) {
        freq[*p - 'a']++;
    }
    // Sort frequencies in descending order
    qsort(freq, 26, sizeof(int), cmpInt);
    int maxBeautyFreqs[26];
    int maxBeautySize = 0;
    for (int i = 25; i >= 26 - k; --i) {
        maxBeautyFreqs[maxBeautySize++] = freq[i];
    }
    int minFreq = maxBeautyFreqs[maxBeautySize - 1];
    int countMinFreqInMaxBeauty = 0;
    for (int i = 0; i < maxBeautySize; ++i) {
        if (maxBeautyFreqs[i] == minFreq) {
            countMinFreqInMaxBeauty++;
        }
    }
    int countMinFreqInTotal = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] == minFreq) {
            countMinFreqInTotal++;
        }
    }
    // Calculate nCr(countMinFreqInTotal, countMinFreqInMaxBeauty)
    long long numerator = 1;
    long long denominator = 1;
    for (int i = 0; i < countMinFreqInMaxBeauty; ++i) {
        numerator = (numerator * (countMinFreqInTotal - i)) % MOD;
        denominator = (denominator * (i + 1)) % MOD;
    }
    // Fermat's little theorem for modular inverse
    long long denomInv = 1;
    int power = MOD - 2;
    long long base = denominator;
    while (power) {
        if (power & 1) {
            denomInv = (denomInv * base) % MOD;
        }
        base = (base * base) % MOD;
        power >>= 1;
    }
    return (numerator * denomInv) % MOD;        
}
