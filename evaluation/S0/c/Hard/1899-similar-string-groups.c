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

int numSimilarGroups(char** strs, int strsSize) {
    int *parent = (int*)malloc(strsSize * sizeof(int));
    for (int i = 0; i < strsSize; ++i) parent[i] = i;

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void union_set(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) parent[rootY] = rootX;
    }

    int is_similar(const char *a, const char *b) {
        int diff[2], count = 0;
        for (int i = 0; a[i]; ++i) {
            if (a[i] != b[i]) {
                if (count >= 2) return 0;
                diff[count++] = i;
            }
        }
        return (count == 0 || (count == 2 && a[diff[0]] == b[diff[1]] && a[diff[1]] == b[diff[0]]));
    }

    for (int i = 0; i < strsSize; ++i) {
        for (int j = i + 1; j < strsSize; ++j) {
            if (is_similar(strs[i], strs[j])) {
                union_set(i, j);
            }
        }
    }

    int groups = 0;
    for (int i = 0; i < strsSize; ++i) {
        if (parent[i] == i) groups++;
    }

    free(parent);
    return groups;      
}
