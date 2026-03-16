// Source: https://leetcode.com/problems/smallest-string-with-swaps/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.
//
// You can swap the characters at any pair of indices in the given pairs any number of times.
//
// Return the lexicographically smallest string that s can be changed to after using the swaps.
//
// Example:
// Input: s = "dcab", pairs = [[0,3],[1,2]]
// Output: "bacd"
// Explaination: 
// Swap s[0] and s[3], s = "bcad"
// Swap s[1] and s[2], s = "bacd"
//
// Constraints:
// 1 <= s.length <= 10^5
// 	0 <= pairs.length <= 10^5
// 	0 <= pairs[i][0], pairs[i][1] < s.length
// 	s only contains lower case English letters.
//

char* smallestStringWithSwaps(char* s, int** pairs, int pairsSize, int* pairsColSize) {
    int n = strlen(s);
    int parent[n];
    for (int i = 0; i < n; i++) parent[i] = i;

    // Find function with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union function
    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootY] = rootX;
        }
    }

    // Union all pairs
    for (int i = 0; i < pairsSize; i++) {
        unionSet(pairs[i][0], pairs[i][1]);
    }

    // Group indices by their root parent
    #define MAX_GROUPS 100000
    int* groups[MAX_GROUPS];
    int groupSizes[MAX_GROUPS];
    for (int i = 0; i < MAX_GROUPS; i++) {
        groups[i] = malloc(n * sizeof(int));
        groupSizes[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int root = find(i);
        groups[root][groupSizes[root]++] = i;
    }

    // Create result array
    char* result = malloc((n + 1) * sizeof(char));
    result[n] = '\0';

    // For each group, sort the characters and place them in result
    for (int i = 0; i < MAX_GROUPS; i++) {
        if (groupSizes[i] > 0) {
            int size = groupSizes[i];
            char chars[size];
            for (int j = 0; j < size; j++) {
                chars[j] = s[groups[i][j]];
            }
            qsort(chars, size, sizeof(char), (int (*)(const void*, const void*))strcmp);

            for (int j = 0; j < size; j++) {
                result[groups[i][j]] = chars[j];
            }
        }
        free(groups[i]);
    }

    return result;      
}
