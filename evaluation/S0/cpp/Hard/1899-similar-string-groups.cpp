// Source: https://leetcode.com/problems/similar-string-groups/   |   Difficulty: Hard
//
// Problem Description:
// Two strings, X and Y, are considered similar if either they are identical or we can make them equivalent by swapping at most two letters (in distinct positions) within the string X.
//
// For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar, but "star" is not similar to "tars", "rats", or "arts".
//
// Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.  Notice that "tars" and "arts" are in the same group even though they are not similar.  Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.
//
// We are given a list strs of strings where every string in strs is an anagram of every other string in strs. How many groups are there?
//
// Example:
// Input: strs = ["tars","rats","arts","star"]
// Output: 2
//
// Constraints:
// 1 <= strs.length <= 300
// 	1 <= strs[i].length <= 300
// 	strs[i] consists of lowercase letters only.
// 	All words in strs have the same length and are anagrams of each other.
//

class Solution {
public:
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();
        vector<int> parent(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        
        auto isSimilar = [](const string& a, const string& b) {
            int diffCount = 0;
            for (int i = 0; i < a.size(); i++) {
                if (a[i] != b[i]) {
                    diffCount++;
                    if (diffCount > 2) return false;
                }
            }
            return diffCount == 2 || diffCount == 0;
        };
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isSimilar(strs[i], strs[j])) {
                    int rootI = find(i);
                    int rootJ = find(j);
                    if (rootI != rootJ) {
                        parent[rootJ] = rootI;
                    }
                }
            }
        }
        
        unordered_set<int> groups;
        for (int i = 0; i < n; i++) {
            groups.insert(find(i));
        }
        
        return groups.size();           
    }
};
