// Source: https://leetcode.com/problems/minimum-cost-good-caption/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string caption of length n. A good caption is a string where every character appears in groups of at least 3 consecutive occurrences.
//
// For example:
//
//
// 	"aaabbb" and "aaaaccc" are good captions.
// 	"aabbb" and "ccccd" are not good captions.
//
//
// You can perform the following operation any number of times:
//
// Choose an index i (where 0 <= i < n) and change the character at that index to either:
//
//
// 	The character immediately before it in the alphabet (if caption[i] != 'a').
// 	The character immediately after it in the alphabet (if caption[i] != 'z').
//
//
// Your task is to convert the given caption into a good caption using the minimum number of operations, and return it. If there are multiple possible good captions, return the lexicographically smallest one among them. If it is impossible to create a good caption, return an empty string "".
//
// Example:
// Input: caption = "cdcd"
//
// Output: "cccc"
//
// Explanation:
//
// It can be shown that the given caption cannot be transformed into a good caption with fewer than 2 operations. The possible good captions that can be created using exactly 2 operations are:
//
//
// 	"dddd": Change caption[0] and caption[2] to their next character 'd'.
// 	"cccc": Change caption[1] and caption[3] to their previous character 'c'.
//
//
// Since "cccc" is lexicographically smaller than "dddd", return "cccc".
//
// Constraints:
// 1 <= caption.length <= 5 * 104
// 	caption consists only of lowercase English letters.
//

class Solution {
public:
    string minCostGoodCaption(string caption) {
        int n = caption.size();
        const int ALPHABET_SIZE = 26;
        const int INF = 1e9;
        
        // dp[i][j][k]: minimum cost to make caption[0..i] good,
        // where caption[i] is changed to character 'a' + j,
        // and k is the count of consecutive characters at position i
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(ALPHABET_SIZE, vector<int>(4, INF)));
        vector<vector<vector<int>>> parent(n, vector<vector<int>>(ALPHABET_SIZE, vector<int>(4, -1)));
        
        // Initialize dp for the first character
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            dp[0][j][1] = abs(caption[0] - ('a' + j));
        }
        
        // Fill dp table
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                int cost = abs(caption[i] - ('a' + j));
                
                for (int k = 1; k <= 3; k++) {
                    // Continue the same character
                    if (k < 3) {
                        if (dp[i-1][j][k] + cost < dp[i][j][k+1]) {
                            dp[i][j][k+1] = dp[i-1][j][k] + cost;
                            parent[i][j][k+1] = j * 10 + k; // encode parent state
                        }
                    }
                    
                    // Change to a different character
                    for (int p = 0; p < ALPHABET_SIZE; p++) {
                        if (p != j) {
                            if (dp[i-1][p][3] + cost < dp[i][j][1]) {
                                dp[i][j][1] = dp[i-1][p][3] + cost;
                                parent[i][j][1] = p * 10 + 3; // encode parent state
                            }
                        }
                    }
                }
            }
        }
        
        // Find the minimum cost in the last position with valid ending
        int minCost = INF;
        int endChar = -1;
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (dp[n-1][j][3] < minCost) {
                minCost = dp[n-1][j][3];
                endChar = j;
            }
        }
        if (minCost == INF) {
            return ""; // Impossible to form a good caption
        }
        
        // Reconstruct the good caption
        string result(n, 'a');
        int currChar = endChar;
        int currCount = 3;
        for (int i = n - 1; i >= 0; i--) {
            result[i] = 'a' + currChar;
            int parentState = parent[i][currChar][currCount];
            currChar = parentState / 10;
            currCount = parentState % 10;
        }
        
        return result;
    }
};
