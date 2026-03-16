// Source: https://leetcode.com/problems/longest-duplicate-substring/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, consider all duplicated substrings: (contiguous) substrings of s that occur 2 or more times. The occurrences may overlap.
//
// Return any duplicated substring that has the longest possible length. If s does not have a duplicated substring, the answer is "".
//
// Example:
// Input: s = "banana"
// Output: "ana"
//
// Constraints:
// 2 <= s.length <= 3 * 104
// 	s consists of lowercase English letters.
//

class Solution {
public:
    string longestDupSubstring(string s) {
        int n = s.length();
        int left = 1, right = n - 1;
        string result = "";
        
        const long long mod = (1LL << 61) - 1;
        const long long base = 131;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            unordered_set<long long> hashes;
            long long hash = 0;
            long long power = 1;
            
            for (int i = 0; i < mid; i++) {
                hash = (hash * base + s[i]) % mod;
                if (i < mid - 1) power = (power * base) % mod;
            }
            hashes.insert(hash);
            bool found = false;
            string candidate = "";
            
            for (int i = mid; i < n; i++) {
                hash = (hash - s[i - mid] * power % mod + mod) % mod;
                hash = (hash * base + s[i]) % mod;
                
                if (hashes.count(hash)) {
                    found = true;
                    candidate = s.substr(i - mid + 1, mid);
                    break;
                }
                hashes.insert(hash);
            }
            
            if (found) {
                result = candidate;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;          
    }
};
