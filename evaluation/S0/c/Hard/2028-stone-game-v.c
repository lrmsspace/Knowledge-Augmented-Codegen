// Source: https://leetcode.com/problems/stone-game-v/   |   Difficulty: Hard
//
// Problem Description:
// There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.
//
// In each round of the game, Alice divides the row into two non-empty rows (i.e. left row and right row), then Bob calculates the value of each row which is the sum of the values of all the stones in this row. Bob throws away the row which has the maximum value, and Alice's score increases by the value of the remaining row. If the value of the two rows are equal, Bob lets Alice decide which row will be thrown away. The next round starts with the remaining row.
//
// The game ends when there is only one stone remaining. Alice's score is initially zero.
//
// Return the maximum score that Alice can obtain.
//
// Example:
// Input: stoneValue = [6,2,3,4,5,5]
// Output: 18
// Explanation: In the first round, Alice divides the row to [6,2,3], [4,5,5]. The left row has the value 11 and the right row has value 14. Bob throws away the right row and Alice's score is now 11.
// In the second round Alice divides the row to [6], [2,3]. This time Bob throws away the left row and Alice's score becomes 16 (11 + 5).
// The last round Alice has only one choice to divide the row which is [2], [3]. Bob throws away the right row and Alice's score is now 18 (16 + 2). The game ends because only one stone is remaining in the row.
//
// Constraints:
// 1 <= stoneValue.length <= 500
// 	1 <= stoneValue[i] <= 106
//

int stoneGameV(int* stoneValue, int stoneValueSize) {
    int prefixSums[stoneValueSize + 1];
    prefixSums[0] = 0;
    for (int i = 0; i < stoneValueSize; ++i) {
        prefixSums[i + 1] = prefixSums[i] + stoneValue[i];
    }

    int dp[stoneValueSize][stoneValueSize];
    memset(dp, 0, sizeof(dp));

    for (int length = 2; length <= stoneValueSize; ++length) {
        for (int i = 0; i <= stoneValueSize - length; ++i) {
            int j = i + length - 1;
            for (int k = i; k < j; ++k) {
                int leftSum = prefixSums[k + 1] - prefixSums[i];
                int rightSum = prefixSums[j + 1] - prefixSums[k + 1];
                if (leftSum < rightSum) {
                    dp[i][j] = dp[i][k] + leftSum > dp[i][j] ? dp[i][k] + leftSum : dp[i][j];
                } else if (leftSum > rightSum) {
                    dp[i][j] = dp[k + 1][j] + rightSum > dp[i][j] ? dp[k + 1][j] + rightSum : dp[i][j];
                } else {
                    int leftOption = dp[i][k] + leftSum;
                    int rightOption = dp[k + 1][j] + rightSum;
                    int maxOption = leftOption > rightOption ? leftOption : rightOption;
                    dp[i][j] = maxOption > dp[i][j] ? maxOption : dp[i][j];
                }
            }
        }
    }

    return dp[0][stoneValueSize - 1];       
}
