// Source: https://leetcode.com/problems/satisfiability-of-equality-equations/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings equations that represent relationships between variables where each string equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".Here, xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.
//
// Return true if it is possible to assign integers to variable names so as to satisfy all the given equations, or false otherwise.
//
// Example:
// Input: equations = ["a==b","b!=a"]
// Output: false
// Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
// There is no way to assign the variables to satisfy both equations.
//
// Constraints:
// 1 <= equations.length <= 500
// 	equations[i].length == 4
// 	equations[i][0] is a lowercase letter.
// 	equations[i][1] is either '=' or '!'.
// 	equations[i][2] is '='.
// 	equations[i][3] is a lowercase letter.
//

bool equationsPossible(char** equations, int equationsSize) {
    int parent[26];
    for (int i = 0; i < 26; i++) {
        parent[i] = i;
    }

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

    // First pass: process all "==" equations
    for (int i = 0; i < equationsSize; i++) {
        if (equations[i][1] == '=') {
            int var1 = equations[i][0] - 'a';
            int var2 = equations[i][3] - 'a';
            unionSet(var1, var2);
        }
    }

    // Second pass: process all "!=" equations
    for (int i = 0; i < equationsSize; i++) {
        if (equations[i][1] == '!') {
            int var1 = equations[i][0] - 'a';
            int var2 = equations[i][3] - 'a';
            if (find(var1) == find(var2)) {
                return false; // Conflict found
            }
        }
    }

    return true; // No conflicts found      
}
