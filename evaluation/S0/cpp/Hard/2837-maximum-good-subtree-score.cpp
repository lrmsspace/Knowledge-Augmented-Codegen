// Source: https://leetcode.com/problems/maximum-good-subtree-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. Each node i has an integer value vals[i], and its parent is given by par[i].
//
// A subset of nodes within the subtree of a node is called good if every digit from 0 to 9 appears at most once in the decimal representation of the values of the selected nodes.
//
// The score of a good subset is the sum of the values of its nodes.
//
// Define an array maxScore of length n, where maxScore[u] represents the maximum possible sum of values of a good subset of nodes that belong to the subtree rooted at node u, including u itself and all its descendants.
//
// Return the sum of all values in maxScore.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: vals = [2,3], par = [-1,0]
//
// Output: 8
//
// Explanation:
//
//
//
//
// 	The subtree rooted at node 0 includes nodes {0, 1}. The subset {2, 3} is good as the digits 2 and 3 appear only once. The score of this subset is 2 + 3 = 5.
// 	The subtree rooted at node 1 includes only node {1}. The subset {3} is good. The score of this subset is 3.
// 	The maxScore array is [5, 3], and the sum of all values in maxScore is 5 + 3 = 8. Thus, the answer is 8.
//
// Constraints:
// 1 <= n == vals.length <= 500
// 	1 <= vals[i] <= 109
// 	par.length == n
// 	par[0] == -1
// 	0 <= par[i] < n for i in [1, n - 1]
// 	The input is generated such that the parent array par represents a valid tree.
//

class Solution {
public:
    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        const int MOD = 1e9 + 7;
        int n = vals.size();
        vector<vector<int>> tree(n);
        for (int i = 1; i < n; i++) {
            tree[par[i]].push_back(i);
        }
        
        vector<int> dp(n, 0);
        
        function<set<int>(int)> dfs = [&](int u) -> set<int> {
            set<int> currDigits;
            int currSum = vals[u];
            int val = vals[u];
            while (val > 0) {
                currDigits.insert(val % 10);
                val /= 10;
            }
            
            for (int v : tree[u]) {
                set<int> childDigits = dfs(v);
                bool canMerge = true;
                for (int d : childDigits) {
                    if (currDigits.count(d)) {
                        canMerge = false;
                        break;
                    }
                }
                if (canMerge) {
                    for (int d : childDigits) {
                        currDigits.insert(d);
                    }
                    currSum += dp[v];
                }
            }
            dp[u] = currSum;
            return currDigits;
        };
        
        dfs(0);
        
        long long result = 0;
        for (int score : dp) {
            result = (result + score) % MOD;
        }
        
        return (int)result;         
    }
};
