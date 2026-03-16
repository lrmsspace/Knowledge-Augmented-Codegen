// Source: https://leetcode.com/problems/egg-drop-with-2-eggs-and-n-floors/   |   Difficulty: Medium
//
// Problem Description:
// You are given two identical eggs and you have access to a building with n floors labeled from 1 to n.
//
// You know that there exists a floor f where 0 <= f <= n such that any egg dropped at a floor higher than f will break, and any egg dropped at or below floor f will not break.
//
// In each move, you may take an unbroken egg and drop it from any floor x (where 1 <= x <= n). If the egg breaks, you can no longer use it. However, if the egg does not break, you may reuse it in future moves.
//
// Return the minimum number of moves that you need to determine with certainty what the value of f is.
//
// Example:
// Input: n = 2
// Output: 2
// Explanation: We can drop the first egg from floor 1 and the second egg from floor 2.
// If the first egg breaks, we know that f = 0.
// If the second egg breaks but the first egg didn't, we know that f = 1.
// Otherwise, if both eggs survive, we know that f = 2.
//
// Constraints:
// 1 <= n <= 1000
//

class Solution {
public:
    int twoEggDrop(int n) {
        int left = 1, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            int sum = mid * (mid + 1) / 2;
            if (sum < n) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;            
    }
};
