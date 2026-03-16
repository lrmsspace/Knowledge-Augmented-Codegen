// Source: https://leetcode.com/problems/stone-game-vi/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob take turns playing a game, with Alice starting first.
//
// There are n stones in a pile. On each player's turn, they can remove a stone from the pile and receive points based on the stone's value. Alice and Bob may value the stones differently.
//
// You are given two integer arrays of length n, aliceValues and bobValues. Each aliceValues[i] and bobValues[i] represents how Alice and Bob, respectively, value the ith stone.
//
// The winner is the person with the most points after all the stones are chosen. If both players have the same amount of points, the game results in a draw. Both players will play optimally. Both players know the other's values.
//
// Determine the result of the game, and:
//
//
// 	If Alice wins, return 1.
// 	If Bob wins, return -1.
// 	If the game results in a draw, return 0.
//
// Example:
// Input: aliceValues = [1,3], bobValues = [2,1]
// Output: 1
// Explanation:
// If Alice takes stone 1 (0-indexed) first, Alice will receive 3 points.
// Bob can only choose stone 0, and will only receive 2 points.
// Alice wins.
//
// Constraints:
// n == aliceValues.length == bobValues.length
// 	1 <= n <= 105
// 	1 <= aliceValues[i], bobValues[i] <= 100
//

int stoneGameVI(int* aliceValues, int aliceValuesSize, int* bobValues, int bobValuesSize) {
    int n = aliceValuesSize;
    int totalAlice = 0, totalBob = 0;

    // Create an array to hold the stones with their combined values
    int stones[n][3]; // [0]: combined value, [1]: Alice's value, [2]: Bob's value

    for (int i = 0; i < n; i++) {
        stones[i][0] = aliceValues[i] + bobValues[i];
        stones[i][1] = aliceValues[i];
        stones[i][2] = bobValues[i];
    }

    // Sort stones based on combined value in descending order
    qsort(stones, n, sizeof(stones[0]), [](const void* a, const void* b) {
        return ((int*)b)[0] - ((int*)a)[0];
    });

    // Simulate the game
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            // Alice's turn
            totalAlice += stones[i][1];
        } else {
            // Bob's turn
            totalBob += stones[i][2];
        }
    }

    // Determine the result
    if (totalAlice > totalBob) {
        return 1; // Alice wins
    } else if (totalBob > totalAlice) {
        return -1; // Bob wins
    } else {
        return 0; // Draw
    }       
}
