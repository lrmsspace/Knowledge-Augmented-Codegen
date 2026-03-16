// Source: https://leetcode.com/problems/maximum-total-beauty-of-the-gardens/   |   Difficulty: Hard
//
// Problem Description:
// Alice is a caretaker of n gardens and she wants to plant flowers to maximize the total beauty of all her gardens.
//
// You are given a 0-indexed integer array flowers of size n, where flowers[i] is the number of flowers already planted in the ith garden. Flowers that are already planted cannot be removed. You are then given another integer newFlowers, which is the maximum number of flowers that Alice can additionally plant. You are also given the integers target, full, and partial.
//
// A garden is considered complete if it has at least target flowers. The total beauty of the gardens is then determined as the sum of the following:
//
//
// 	The number of complete gardens multiplied by full.
// 	The minimum number of flowers in any of the incomplete gardens multiplied by partial. If there are no incomplete gardens, then this value will be 0.
//
//
// Return the maximum total beauty that Alice can obtain after planting at most newFlowers flowers.
//
// Example:
// Input: flowers = [1,3,1,1], newFlowers = 7, target = 6, full = 12, partial = 1
// Output: 14
// Explanation: Alice can plant
// - 2 flowers in the 0th garden
// - 3 flowers in the 1st garden
// - 1 flower in the 2nd garden
// - 1 flower in the 3rd garden
// The gardens will then be [3,6,2,2]. She planted a total of 2 + 3 + 1 + 1 = 7 flowers.
// There is 1 garden that is complete.
// The minimum number of flowers in the incomplete gardens is 2.
// Thus, the total beauty is 1 * 12 + 2 * 1 = 12 + 2 = 14.
// No other way of planting flowers can obtain a total beauty higher than 14.
//
// Constraints:
// 1 <= flowers.length <= 105
// 	1 <= flowers[i], target <= 105
// 	1 <= newFlowers <= 1010
// 	1 <= full, partial <= 105
//

class Solution {
public:
    long long maximumBeauty(vector<int>& flowers, long long newFlowers, int target, int full, int partial) {
        int n = flowers.size();
        vector<long long> need(n, 0);
        long long totalNeed = 0;
        
        for (int i = 0; i < n; i++) {
            if (flowers[i] < target) {
                need[i] = target - flowers[i];
                totalNeed += need[i];
            }
        }
        
        sort(flowers.begin(), flowers.end());
        
        long long maxBeauty = 0;
        
        for (int complete = 0; complete <= n; complete++) {
            if (complete > 0) {
                int idx = n - complete;
                if (flowers[idx] < target) {
                    long long req = target - flowers[idx];
                    if (newFlowers < req) break;
                    newFlowers -= req;
                    totalNeed -= req;
                }
            }
            
            long long minIncomplete = 0;
            if (complete < n) {
                long long left = 0, right = target - 1;
                
                while (left <= right) {
                    long long mid = left + (right - left) / 2;
                    long long needed = 0;
                    
                    for (int i = 0; i < n - complete; i++) {
                        if (flowers[i] < mid) {
                            needed += mid - flowers[i];
                        }
                    }
                    
                    if (needed <= newFlowers) {
                        minIncomplete = mid;
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
            }
            
            long long currentBeauty = (long long)complete * full + minIncomplete * partial;
            maxBeauty = max(maxBeauty, currentBeauty);
        }
        
        return maxBeauty;           
    }
};
