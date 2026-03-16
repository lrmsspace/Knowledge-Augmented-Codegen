// Source: https://leetcode.com/problems/groups-of-strings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of strings words. Each string consists of lowercase English letters only. No letter occurs more than once in any string of words.
//
// Two strings s1 and s2 are said to be connected if the set of letters of s2 can be obtained from the set of letters of s1 by any one of the following operations:
//
//
// 	Adding exactly one letter to the set of the letters of s1.
// 	Deleting exactly one letter from the set of the letters of s1.
// 	Replacing exactly one letter from the set of the letters of s1 with any letter, including itself.
//
//
// The array words can be divided into one or more non-intersecting groups. A string belongs to a group if any one of the following is true:
//
//
// 	It is connected to at least one other string of the group.
// 	It is the only string present in the group.
//
//
// Note that the strings in words should be grouped in such a manner that a string belonging to a group cannot be connected to a string present in any other group. It can be proved that such an arrangement is always unique.
//
// Return an array ans of size 2 where:
//
//
// 	ans[0] is the maximum number of groups words can be divided into, and
// 	ans[1] is the size of the largest group.
//
// Example:
// Input: words = ["a","b","ab","cde"]
// Output: [2,3]
// Explanation:
// - words[0] can be used to obtain words[1] (by replacing 'a' with 'b'), and words[2] (by adding 'b'). So words[0] is connected to words[1] and words[2].
// - words[1] can be used to obtain words[0] (by replacing 'b' with 'a'), and words[2] (by adding 'a'). So words[1] is connected to words[0] and words[2].
// - words[2] can be used to obtain words[0] (by deleting 'b'), and words[1] (by deleting 'a'). So words[2] is connected to words[0] and words[1].
// - words[3] is not connected to any string in words.
// Thus, words can be divided into 2 groups ["a","b","ab"] and ["cde"]. The size of the largest group is 3.
//
// Constraints:
// 1 <= words.length <= 2 * 104
// 	1 <= words[i].length <= 26
// 	words[i] consists of lowercase English letters only.
// 	No letter occurs more than once in words[i].
//

class Solution {
public:
    vector<int> groupStrings(vector<string>& words) {
        const int N = words.size();
        vector<int> parent(N);
        vector<int> size(N, 1);
        
        for (int i = 0; i < N; i++) {
            parent[i] = i;
        }
        
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        
        auto unionSets = [&](int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
            }
        };
        
        unordered_map<int, int> bitmaskToIndex;
        
        for (int i = 0; i < N; i++) {
            int bitmask = 0;
            for (char c : words[i]) {
                bitmask |= (1 << (c - 'a'));
            }
            
            // Check for same bitmask
            if (bitmaskToIndex.count(bitmask)) {
                unionSets(i, bitmaskToIndex[bitmask]);
            } else {
                bitmaskToIndex[bitmask] = i;
            }
            
            // Check for adding/removing one letter
            for (int j = 0; j < 26; j++) {
                int modifiedMask = bitmask ^ (1 << j);
                if (bitmaskToIndex.count(modifiedMask)) {
                    unionSets(i, bitmaskToIndex[modifiedMask]);
                }
            }
            
            // Check for replacing one letter
            for (int j = 0; j < 26; j++) {
                if (bitmask & (1 << j)) {
                    for (int k = 0; k < 26; k++) {
                        if (!(bitmask & (1 << k))) {
                            int replacedMask = bitmask ^ (1 << j) ^ (1 << k);
                            if (bitmaskToIndex.count(replacedMask)) {
                                unionSets(i, bitmaskToIndex[replacedMask]);
                            }
                        }
                    }
                }
            }
        }
        
        unordered_map<int, int> groupCount;
        for (int i = 0; i < N; i++) {
            int root = find(i);
            groupCount[root]++;
        }
        
        int maxSize = 0;
        for (const auto& entry : groupCount) {
            maxSize = max(maxSize, entry.second);
        }
        
        return {(int)groupCount.size(), maxSize};
    }
};
