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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* groupStrings(char** words, int wordsSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = 2;
    int *result = (int*)malloc(2 * sizeof(int));
    if (!result) return NULL;

    int parent[wordsSize];
    int size[wordsSize];
    for (int i = 0; i < wordsSize; ++i) {
        parent[i] = i;
        size[i] = 1;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void union_sets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (size[rootX] < size[rootY]) {
                parent[rootX] = rootY;
                size[rootY] += size[rootX];
            } else {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
            }
        }
    }

    int bitmasks[wordsSize];
    for (int i = 0; i < wordsSize; ++i) {
        int mask = 0;
        for (char *p = words[i]; *p; ++p) {
            mask |= 1 << (*p - 'a');
        }
        bitmasks[i] = mask;
    }

    for (int i = 0; i < wordsSize; ++i) {
        for (int j = i + 1; j < wordsSize; ++j) {
            int diff = bitmasks[i] ^ bitmasks[j];
            if (__builtin_popcount(diff) <= 2) {
                union_sets(i, j);
            }
        }
    }

    int groupCount = 0;
    int maxSize = 0;
    for (int i = 0; i < wordsSize; ++i) {
        if (find(i) == i) {
            groupCount++;
            if (size[i] > maxSize) {
                maxSize = size[i];
            }
        }
    }

    result[0] = groupCount;
    result[1] = maxSize;
    return result;      
}
