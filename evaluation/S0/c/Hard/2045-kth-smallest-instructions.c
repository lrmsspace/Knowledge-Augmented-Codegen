// Source: https://leetcode.com/problems/kth-smallest-instructions/   |   Difficulty: Hard
//
// Problem Description:
// Bob is standing at cell (0, 0), and he wants to reach destination: (row, column). He can only travel right and down. You are going to help Bob by providing instructions for him to reach destination.
//
// The instructions are represented as a string, where each character is either:
//
//
// 	'H', meaning move horizontally (go right), or
// 	'V', meaning move vertically (go down).
//
//
// Multiple instructions will lead Bob to destination. For example, if destination is (2, 3), both "HHHVV" and "HVHVH" are valid instructions.
//
// However, Bob is very picky. Bob has a lucky number k, and he wants the kth lexicographically smallest instructions that will lead him to destination. k is 1-indexed.
//
// Given an integer array destination and an integer k, return the kth lexicographically smallest instructions that will take Bob to destination.
//
// Example:
// Input: destination = [2,3], k = 1
// Output: "HHHVV"
// Explanation: All the instructions that reach (2, 3) in lexicographic order are as follows:
// ["HHHVV", "HHVHV", "HHVVH", "HVHHV", "HVHVH", "HVVHH", "VHHHV", "VHHVH", "VHVHH", "VVHHH"].
//
// Constraints:
// destination.length == 2
// 	1 <= row, column <= 15
// 	1 <= k <= nCr(row + column, row), where nCr(a, b) denotes a choose b​​​​​.
//

char* kthSmallestPath(int* destination, int destinationSize, int k) {
    int row = destination[0], col = destination[1];
    int total = row + col;
    int **C = (int**)malloc((total + 1) * sizeof(int*));
    for (int i = 0; i <= total; i++) {
        C[i] = (int*)malloc((i + 1) * sizeof(int));
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            if (j == i) {
                C[i][j] = 1;
            } else {
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }
    }
    char *result = (char*)malloc((total + 1) * sizeof(char));
    result[total] = '\0';
    int r = row, c = col;
    for (int i = 0; i < total; i++) {
        if (c == 0) {
            result[i] = 'V';
            r--;
        } else if (r == 0) {
            result[i] = 'H';
            c--;
        } else {
            int count = C[r + c - 1][r];
            if (k <= count) {
                result[i] = 'H';
                c--;
            } else {
                result[i] = 'V';
                k -= count;
                r--;
            }
        }
    }
    for (int i = 0; i <= total; i++) {
        free(C[i]);
    }
    free(C);
    return result;
}
