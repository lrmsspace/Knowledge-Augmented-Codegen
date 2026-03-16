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

/**
 * @param {string[]} strs
 * @return {number}
 */
var numSimilarGroups = function(strs) {
    const n = strs.length;
    const parent = new Array(n).fill(0).map((_, i) => i);
    const find = (x) => {
        if (parent[x] !== x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    const union = (x, y) => {
        const rootX = find(x);
        const rootY = find(y);
        if (rootX !== rootY) {
            parent[rootY] = rootX;
        }
    }
    const isSimilar = (s1, s2) => {
        let diffCount = 0;
        for (let i = 0; i < s1.length; i++) {
            if (s1[i] !== s2[i]) {
                diffCount++;
                if (diffCount > 2) {
                    return false;
                }
            }
        }
        return diffCount === 0 || diffCount === 2;
    }
    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            if (isSimilar(strs[i], strs[j])) {
                union(i, j);
            }
        }
    }
    const groups = new Set();
    for (let i = 0; i < n; i++) {
        groups.add(find(i));
    }
    return groups.size;
};
