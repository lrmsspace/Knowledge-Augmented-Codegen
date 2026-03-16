// Source: https://leetcode.com/problems/push-dominoes/   |   Difficulty: Medium
//
// Problem Description:
// There are n dominoes in a line, and we place each domino vertically upright. In the beginning, we simultaneously push some of the dominoes either to the left or to the right.
//
// After each second, each domino that is falling to the left pushes the adjacent domino on the left. Similarly, the dominoes falling to the right push their adjacent dominoes standing on the right.
//
// When a vertical domino has dominoes falling on it from both sides, it stays still due to the balance of the forces.
//
// For the purposes of this question, we will consider that a falling domino expends no additional force to a falling or already fallen domino.
//
// You are given a string dominoes representing the initial state where:
//
//
// 	dominoes[i] = 'L', if the ith domino has been pushed to the left,
// 	dominoes[i] = 'R', if the ith domino has been pushed to the right, and
// 	dominoes[i] = '.', if the ith domino has not been pushed.
//
//
// Return a string representing the final state.
//
// Example:
// Input: dominoes = "RR.L"
// Output: "RR.L"
// Explanation: The first domino expends no additional force on the second domino.
//
// Constraints:
// n == dominoes.length
// 	1 <= n <= 105
// 	dominoes[i] is either 'L', 'R', or '.'.
//

char* pushDominoes(char* dominoes) {
    int n = strlen(dominoes);
    int* forces = (int*)calloc(n, sizeof(int));
    int force = 0;

    // Apply forces from right pushes
    for (int i = 0; i < n; i++) {
        if (dominoes[i] == 'R') {
            force = n;
        } else if (dominoes[i] == 'L') {
            force = 0;
        } else {
            force = max(force - 1, 0);
        }
        forces[i] += force;
    }

    // Apply forces from left pushes
    force = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (dominoes[i] == 'L') {
            force = n;
        } else if (dominoes[i] == 'R') {
            force = 0;
        } else {
            force = max(force - 1, 0);
        }
        forces[i] -= force;
    }

    // Build the result based on net forces
    char* result = (char*)malloc((n + 1) * sizeof(char));
    for (int i = 0; i < n; i++) {
        if (forces[i] > 0) {
            result[i] = 'R';
        } else if (forces[i] < 0) {
            result[i] = 'L';
        } else {
            result[i] = '.';
        }
    }
    result[n] = '\0';

    free(forces);
    return result;      
}
