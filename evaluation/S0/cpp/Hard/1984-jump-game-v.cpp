// Source: https://leetcode.com/problems/jump-game-v/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers arr and an integer d. In one step you can jump from index i to index:
//
//
// 	i + x where: i + x < arr.length and  0 < x <= d.
// 	i - x where: i - x >= 0 and  0 < x <= d.
//
//
// In addition, you can only jump from index i to index j if arr[i] > arr[j] and arr[i] > arr[k] for all indices k between i and j (More formally min(i, j) < k < max(i, j)).
//
// You can choose any index of the array and start jumping. Return the maximum number of indices you can visit.
//
// Notice that you can not jump outside of the array at any time.
//
// Example:
// Input: arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
// Output: 4
// Explanation: You can start at index 10. You can jump 10 --> 8 --> 6 --> 7 as shown.
// Note that if you start at index 6 you can only jump to index 7. You cannot jump to index 5 because 13 > 9. You cannot jump to index 4 because index 5 is between index 4 and 6 and 13 > 9.
// Similarly You cannot jump from index 3 to index 2 or index 1.
//
// Constraints:
// 1 <= arr.length <= 1000
// 	1 <= arr[i] <= 105
// 	1 <= d <= arr.length
//

class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> dp(n, 1);
        
        // Indices sorted by their values in arr
        vector<int> indices(n);
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return arr[a] < arr[b];
        });
        
        for (int idx : indices) {
            // Jump left
            for (int j = idx - 1; j >= max(0, idx - d); j--) {
                if (arr[j] < arr[idx]) {
                    dp[idx] = max(dp[idx], dp[j] + 1);
                } else {
                    break;
                }
            }
            // Jump right
            for (int j = idx + 1; j <= min(n - 1, idx + d); j++) {
                if (arr[j] < arr[idx]) {
                    dp[idx] = max(dp[idx], dp[j] + 1);
                } else {
                    break;
                }
            }
        }
        
        return *max_element(dp.begin(), dp.end());          
    }
};
