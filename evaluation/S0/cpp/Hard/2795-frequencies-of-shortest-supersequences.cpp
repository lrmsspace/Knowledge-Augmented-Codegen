// Source: https://leetcode.com/problems/frequencies-of-shortest-supersequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings words. Find all shortest common supersequences (SCS) of words that are not permutations of each other.
//
// A shortest common supersequence is a string of minimum length that contains each string in words as a subsequence.
//
// Return a 2D array of integers freqs that represent all the SCSs. Each freqs[i] is an array of size 26, representing the frequency of each letter in the lowercase English alphabet for a single SCS. You may return the frequency arrays in any order.
//
// Example:
// Input: words = ["ab","ba"]
//
// Output: [[1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]
//
// Explanation:
//
// The two SCSs are "aba" and "bab". The output is the letter frequencies for each one.
//
// Constraints:
// 1 <= words.length <= 256
// 	words[i].length == 2
// 	All strings in words will altogether be composed of no more than 16 unique lowercase letters.
// 	All strings in words are unique.
//

class Solution {
public:
    vector<vector<int>> supersequences(vector<string>& words) {
        const int ALPHABET_SIZE = 26;
        const int MAX_MASK = 1 << 16;
        const int INF = 1e9;
        
        int n = words.size();
        unordered_map<char, int> charToIndex;
        int charCount = 0;
        
        for (const string& w : words) {
            for (char c : w) {
                if (charToIndex.find(c) == charToIndex.end()) {
                    charToIndex[c] = charCount++;
                }
            }
        }
        
        vector<vector<int>> dp(MAX_MASK, vector<int>(charCount, INF));
        dp[0] = vector<int>(charCount, 0);
        
        for (int mask = 0; mask < (1 << n); ++mask) {
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) continue;
                
                int nextMask = mask | (1 << i);
                string w = words[i];
                
                for (int c = 0; c < charCount; ++c) {
                    dp[nextMask][c] = min(dp[nextMask][c], dp[mask][c]);
                }
                
                dp[nextMask][charToIndex[w[0]]] += 1;
                dp[nextMask][charToIndex[w[1]]] += 1;
            }
        }
        
        vector<vector<int>> result;
        int fullMask = (1 << n) - 1;
        
        unordered_set<string> uniqueFreqs;
        
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (__builtin_popcount(mask) != n) continue;
            
            vector<int> freq(ALPHABET_SIZE, 0);
            for (const auto& [ch, idx] : charToIndex) {
                freq[ch - 'a'] = dp[mask][idx];
            }
            
            string freqKey;
            for (int f : freq) {
                freqKey += to_string(f) + ",";
            }
            
            if (uniqueFreqs.find(freqKey) == uniqueFreqs.end()) {
                uniqueFreqs.insert(freqKey);
                result.push_back(freq);
            }
        }
        
        return result;          
    }
};
