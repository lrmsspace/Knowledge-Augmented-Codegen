// Source: https://leetcode.com/problems/find-subtree-sizes-after-changes/   |   Difficulty: Medium
//
// Problem Description:
// You are given a tree rooted at node 0 that consists of n nodes numbered from 0 to n - 1. The tree is represented by an array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.
//
// You are also given a string s of length n, where s[i] is the character assigned to node i.
//
// We make the following changes on the tree one time simultaneously for all nodes x from 1 to n - 1:
//
//
// 	Find the closest node y to node x such that y is an ancestor of x, and s[x] == s[y].
// 	If node y does not exist, do nothing.
// 	Otherwise, remove the edge between x and its current parent and make node y the new parent of x by adding an edge between them.
//
//
// Return an array answer of size n where answer[i] is the size of the subtree rooted at node i in the final tree.
//
// Example:
// Input: parent = [-1,0,0,1,1,1], s = "abaabc"
//
// Output: [6,3,1,1,1,1]
//
// Explanation:
//
// The parent of node 3 will change from node 1 to node 0.
//
// Constraints:
// n == parent.length == s.length
// 	1 <= n <= 105
// 	0 <= parent[i] <= n - 1 for all i >= 1.
// 	parent[0] == -1
// 	parent represents a valid tree.
// 	s consists only of lowercase English letters.
//

class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> tree(n);
        for (int i = 1; i < n; ++i) {
            tree[parent[i]].push_back(i);
        }

        vector<int> answer(n, 0);
        vector<unordered_map<char, int>> charCount(n);

        function<void(int)> dfs = [&](int node) {
            charCount[node][s[node]] = node;
            answer[node] = 1;

            for (int child : tree[node]) {
                dfs(child);

                if (charCount[child].size() > charCount[node].size()) {
                    swap(charCount[node], charCount[child]);
                }

                for (const auto& [ch, idx] : charCount[child]) {
                    if (charCount[node].count(ch)) {
                        int ancestorIdx = charCount[node][ch];
                        answer[ancestorIdx] += answer[idx];
                    } else {
                        charCount[node][ch] = idx;
                    }
                }
            }
        };

        dfs(0);
        return answer;          
    }
};
