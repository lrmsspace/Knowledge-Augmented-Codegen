// Source: https://leetcode.com/problems/most-frequent-prime/   |   Difficulty: Medium
//
// Problem Description:
// You are given a m x n 0-indexed 2D matrix mat. From every cell, you can create numbers in the following way:
//
//
// 	There could be at most 8 paths from the cells namely: east, south-east, south, south-west, west, north-west, north, and north-east.
// 	Select a path from them and append digits in this path to the number being formed by traveling in this direction.
// 	Note that numbers are generated at every step, for example, if the digits along the path are 1, 9, 1, then there will be three numbers generated along the way: 1, 19, 191.
//
//
// Return the most frequent prime number greater than 10 out of all the numbers created by traversing the matrix or -1 if no such prime number exists. If there are multiple prime numbers with the highest frequency, then return the largest among them.
//
// Note: It is invalid to change the direction during the move.
//
// Example:
// Input: mat = [[1,1],[9,9],[1,1]]
// Output: 19
// Explanation: 
// From cell (0,0) there are 3 possible directions and the numbers greater than 10 which can be created in those directions are:
// East: [11], South-East: [19], South: [19,191].
// Numbers greater than 10 created from the cell (0,1) in all possible directions are: [19,191,19,11].
// Numbers greater than 10 created from the cell (1,0) in all possible directions are: [99,91,91,91,91].
// Numbers greater than 10 created from the cell (1,1) in all possible directions are: [91,91,99,91,91].
// Numbers greater than 10 created from the cell (2,0) in all possible directions are: [11,19,191,19].
// Numbers greater than 10 created from the cell (2,1) in all possible directions are: [11,19,19,191].
// The most frequent prime number among all the created numbers is 19.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 6
// 	1 <= mat[i][j] <= 9
//

int mostFrequentPrime(int** mat, int matSize, int* matColSize) {
    #define MAX_NUM 1000000
    bool isPrime[MAX_NUM];
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i < MAX_NUM; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < MAX_NUM; j += i) {
                isPrime[j] = false;
            }
        }
    }

    int directions[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
    int freq[MAX_NUM];
    memset(freq, 0, sizeof(freq));

    for (int i = 0; i < matSize; i++) {
        for (int j = 0; j < matColSize[0]; j++) {
            for (int d = 0; d < 8; d++) {
                int x = i, y = j;
                int num = 0;
                while (x >= 0 && x < matSize && y >= 0 && y < matColSize[0]) {
                    num = num * 10 + mat[x][y];
                    if (num > 10 && isPrime[num]) {
                        freq[num]++;
                    }
                    x += directions[d][0];
                    y += directions[d][1];
                }
            }
        }
    }

    int maxFreq = 0;
    int result = -1;
    for (int num = 11; num < MAX_NUM; num++) {
        if (freq[num] > maxFreq || (freq[num] == maxFreq && num > result)) {
            maxFreq = freq[num];
            result = num;
        }
    }

    return result;
}
