// Source: https://leetcode.com/problems/find-the-shortest-superstring/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of strings words, return the smallest string that contains each string in words as a substring. If there are multiple valid strings of the smallest length, return any of them.
//
// You may assume that no string in words is a substring of another string in words.
//
// Example:
// Input: words = ["alex","loves","leetcode"]
// Output: "alexlovesleetcode"
// Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
//
// Constraints:
// 1 <= words.length <= 12
// 	1 <= words[i].length <= 20
// 	words[i] consists of lowercase English letters.
// 	All the strings of words are unique.
//

class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        int n = words.size();
        vector<vector<int>> overlap(n, vector<int>(n, 0));
        
        // Precompute overlaps
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    int maxOverlap = min(words[i].size(), words[j].size());
                    for (int k = maxOverlap; k >= 0; k--) {
                        if (words[i].substr(words[i].size() - k) == words[j].substr(0, k)) {
                            overlap[i][j] = k;
                            break;
                        }
                    }
                }
            }
        }
        
        // DP to find the maximum overlap path
        int N = 1 << n;
        vector<vector<int>> dp(N, vector<int>(n, 0));
        vector<vector<int>> parent(N, vector<int>(n, -1));
        
        for (int mask = 1; mask < N; mask++) {
            for (int u = 0; u < n; u++) {
                if (!(mask & (1 << u))) continue;
                int prevMask = mask ^ (1 << u);
                if (prevMask == 0) continue;
                
                for (int v = 0; v < n; v++) {
                    if (!(prevMask & (1 << v))) continue;
                    int val = dp[prevMask][v] + overlap[v][u];
                    if (val > dp[mask][u]) {
                        dp[mask][u] = val;
                        parent[mask][u] = v;
                    }
                }
            }
        }
        
        // Reconstruct the path
        int maxLen = -1, last = -1;
        for (int i = 0; i < n; i++) {
            if (dp[N - 1][i] > maxLen) {
                maxLen = dp[N - 1][i];
                last = i;
            }
        }
        
        vector<int> path;
        int mask = N - 1;
        while (last != -1) {
            path.push_back(last);
            int temp = parent[mask][last];
            mask ^= (1 << last);
            last = temp;
        }
        reverse(path.begin(), path.end());
        
        // Build     
        string result = words[path[0]];
        for (int i = 1; i < path.size(); i++) {
            int o = overlap[path[i - 1]][path[i]];
            result += words[path[i]].substr(o);
        }
        return result;       
    }
};
