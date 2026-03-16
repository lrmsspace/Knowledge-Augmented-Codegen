// Source: https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/   |   Difficulty: Hard
//
// Problem Description:
// Fruits are available at some positions on an infinite x-axis. You are given a 2D integer array fruits where fruits[i] = [positioni, amounti] depicts amounti fruits at the position positioni. fruits is already sorted by positioni in ascending order, and each positioni is unique.
//
// You are also given an integer startPos and an integer k. Initially, you are at the position startPos. From any position, you can either walk to the left or right. It takes one step to move one unit on the x-axis, and you can walk at most k steps in total. For every position you reach, you harvest all the fruits at that position, and the fruits will disappear from that position.
//
// Return the maximum total number of fruits you can harvest.
//
// Example:
// Input: fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
// Output: 9
// Explanation: 
// The optimal way is to:
// - Move right to position 6 and harvest 3 fruits
// - Move right to position 8 and harvest 6 fruits
// You moved 3 steps and harvested 3 + 6 = 9 fruits in total.
//
// Constraints:
// 1 <= fruits.length <= 105
// 	fruits[i].length == 2
// 	0 <= startPos, positioni <= 2 * 105
// 	positioni-1 < positioni for any i > 0 (0-indexed)
// 	1 <= amounti <= 104
// 	0 <= k <= 2 * 105
//

class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        vector<long long> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + fruits[i][1];
        }
        
        int maxFruits = 0;
        
        // Try moving left first
        for (int leftSteps = 0; leftSteps <= k; leftSteps++) {
            int leftPos = startPos - leftSteps;
            int remainingSteps = k - leftSteps;
            int rightPos = startPos + remainingSteps - leftSteps;
            
            // Find the range of positions we can harvest
            int leftIdx = lower_bound(fruits.begin(), fruits.end(), vector<int>{leftPos, 0}) - fruits.begin();
            int rightIdx = upper_bound(fruits.begin(), fruits.end(), vector<int>{rightPos, INT_MAX}) - fruits.begin() - 1;
            
            if (leftIdx <= rightIdx) {
                long long totalFruits = prefixSum[rightIdx + 1] - prefixSum[leftIdx];
                maxFruits = max(maxFruits, (int)totalFruits);
            }
        }
        
        // Try moving right first
        for (int rightSteps = 0; rightSteps <= k; rightSteps++) {
            int rightPos = startPos + rightSteps;
            int remainingSteps = k - rightSteps;
            int leftPos = startPos - (remainingSteps - rightSteps);
            
            // Find the range of positions we can harvest
            int leftIdx = lower_bound(fruits.begin(), fruits.end(), vector<int>{leftPos, 0}) - fruits.begin();
            int rightIdx = upper_bound(fruits.begin(), fruits.end(), vector<int>{rightPos, INT_MAX}) - fruits.begin() - 1;
            
            if (leftIdx <= rightIdx) {
                long long totalFruits = prefixSum[rightIdx + 1] - prefixSum[leftIdx];
                maxFruits = max(maxFruits, (int)totalFruits);
            }
        }
        
        return maxFruits;           
    }
};
