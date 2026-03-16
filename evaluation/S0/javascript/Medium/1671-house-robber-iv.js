// Source: https://leetcode.com/problems/house-robber-iv/   |   Difficulty: Medium
//
// Problem Description:
// There are several consecutive houses along a street, each of which has some money inside. There is also a robber, who wants to steal money from the homes, but he refuses to steal from adjacent homes.
//
// The capability of the robber is the maximum amount of money he steals from one house of all the houses he robbed.
//
// You are given an integer array nums representing how much money is stashed in each house. More formally, the ith house from the left has nums[i] dollars.
//
// You are also given an integer k, representing the minimum number of houses the robber will steal from. It is always possible to steal at least k houses.
//
// Return the minimum capability of the robber out of all the possible ways to steal at least k houses.
//
// Example:
// Input: nums = [2,3,5,9], k = 2
// Output: 5
// Explanation: 
// There are three ways to rob at least 2 houses:
// - Rob the houses at indices 0 and 2. Capability is max(nums[0], nums[2]) = 5.
// - Rob the houses at indices 0 and 3. Capability is max(nums[0], nums[3]) = 9.
// - Rob the houses at indices 1 and 3. Capability is max(nums[1], nums[3]) = 9.
// Therefore, we return min(5, 9, 9) = 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= (nums.length + 1)/2
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minCapability = function(nums, k) {
    const canRobWithCapability = (capability) => {
        let count = 0;
        let i = 0;
        while (i < nums.length) {
            if (nums[i] <= capability) {
                count++;
                i += 2; // Skip the next house
            } else {
                i++;
            }
        }
        return count >= k;
    };

    let left = Math.min(...nums);
    let right = Math.max(...nums);
    let result = right;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        if (canRobWithCapability(mid)) {
            result = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return result;  
            
};
