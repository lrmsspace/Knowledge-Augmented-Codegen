// Source: https://leetcode.com/problems/find-substring-with-given-hash-value/   |   Difficulty: Hard
//
// Problem Description:
// The hash of a 0-indexed string s of length k, given integers p and m, is computed using the following function:
//
//
// 	hash(s, p, m) = (val(s[0]) * p0 + val(s[1]) * p1 + ... + val(s[k-1]) * pk-1) mod m.
//
//
// Where val(s[i]) represents the index of s[i] in the alphabet from val('a') = 1 to val('z') = 26.
//
// You are given a string s and the integers power, modulo, k, and hashValue. Return sub, the first substring of s of length k such that hash(sub, power, modulo) == hashValue.
//
// The test cases will be generated such that an answer always exists.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "leetcode", power = 7, modulo = 20, k = 2, hashValue = 0
// Output: "ee"
// Explanation: The hash of "ee" can be computed to be hash("ee", 7, 20) = (5 * 1 + 5 * 7) mod 20 = 40 mod 20 = 0. 
// "ee" is the first substring of length 2 with hashValue 0. Hence, we return "ee".
//
// Constraints:
// 1 <= k <= s.length <= 2 * 104
// 	1 <= power, modulo <= 109
// 	0 <= hashValue < modulo
// 	s consists of lowercase English letters only.
// 	The test cases are generated such that an answer always exists.
//

class Solution {
public:
    string subStrHash(string s, int power, int modulo, int k, int hashValue) {
        long long currentHash = 0;
        long long powerK = 1;  // power^k % modulo
        
        // Precompute power^k % modulo
        for (int i = 0; i < k; i++) {
            if (i > 0) powerK = (powerK * power) % modulo;
        }
        
        int n = s.length();
        string result = "";
        
        // Compute hash for the last k-length substring
        for (int i = n - k; i < n; i++) {
            currentHash = (currentHash * power + (s[i] - 'a' + 1)) % modulo;
        }
        
        if (currentHash == hashValue) {
            result = s.substr(n - k, k);
        }
        
        // Rolling hash backwards
        for (int i = n - k - 1; i >= 0; i--) {
            // Remove last character and add new character at the front
            currentHash = (currentHash - ((s[i + k] - 'a' + 1) * powerK) % modulo + modulo) % modulo;
            currentHash = (currentHash * power + (s[i] - 'a' + 1)) % modulo;
            
            if (currentHash == hashValue) {
                result = s.substr(i, k);
            }
        }
        
        return result;          
    }
};
