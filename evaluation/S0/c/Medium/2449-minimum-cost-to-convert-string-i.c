// Source: https://leetcode.com/problems/minimum-cost-to-convert-string-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English letters. You are also given two 0-indexed character arrays original and changed, and an integer array cost, where cost[i] represents the cost of changing the character original[i] to the character changed[i].
//
// You start with the string source. In one operation, you can pick a character x from the string and change it to the character y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y.
//
// Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.
//
// Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].
//
// Example:
// Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
// Output: 28
// Explanation: To convert the string "abcd" to string "acbe":
// - Change value at index 1 from 'b' to 'c' at a cost of 5.
// - Change value at index 2 from 'c' to 'e' at a cost of 1.
// - Change value at index 2 from 'e' to 'b' at a cost of 2.
// - Change value at index 3 from 'd' to 'e' at a cost of 20.
// The total cost incurred is 5 + 1 + 2 + 20 = 28.
// It can be shown that this is the minimum possible cost.
//
// Constraints:
// 1 <= source.length == target.length <= 105
// 	source, target consist of lowercase English letters.
// 	1 <= cost.length == original.length == changed.length <= 2000
// 	original[i], changed[i] are lowercase English letters.
// 	1 <= cost[i] <= 106
// 	original[i] != changed[i]
//

long long minimumCost(char* source, char* target, char* original, int originalSize, char* changed, int changedSize, int* cost, int costSize) {
    int n = strlen(source);
    long long totalCost = 0;

    // Create a cost mapping for character transformations
    int transformationCost[26][26];
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            transformationCost[i][j] = -1; // -1 indicates no direct transformation
        }
    }

    for (int i = 0; i < originalSize; i++) {
        int from = original[i] - 'a';
        int to = changed[i] - 'a';
        if (transformationCost[from][to] == -1 || transformationCost[from][to] > cost[i]) {
            transformationCost[from][to] = cost[i];
        }
    }
    // Use Floyd-Warshall algorithm to find the minimum cost for all character transformations
    for (int k = 0; k < 26; k++) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                if (transformationCost[i][k] != -1 && transformationCost[k][j] != -1) {
                    long long newCost = (long long)transformationCost[i][k] + (long long)transformationCost[k][j];
                    if (transformationCost[i][j] == -1 || transformationCost[i][j] > newCost) {
                        transformationCost[i][j] = (int)newCost;
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (source[i] == target[i]) {
            continue;
        }
        int from = source[i] - 'a';
        int to = target[i] - 'a';
        if (transformationCost[from][to] == -1) {
            return -1;
        }
        totalCost += transformationCost[from][to];
    }

    return totalCost;
}