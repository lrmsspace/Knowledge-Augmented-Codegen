// Source: https://leetcode.com/problems/circular-array-loop/   |   Difficulty: Medium
//
// Problem Description:
// You are playing a game involving a circular array of non-zero integers nums. Each nums[i] denotes the number of indices forward/backward you must move if you are located at index i:
//
//
// 	If nums[i] is positive, move nums[i] steps forward, and
// 	If nums[i] is negative, move nums[i] steps backward.
//
//
// Since the array is circular, you may assume that moving forward from the last element puts you on the first element, and moving backwards from the first element puts you on the last element.
//
// A cycle in the array consists of a sequence of indices seq of length k where:
//
//
// 	Following the movement rules above results in the repeating index sequence seq[0] -> seq[1] -> ... -> seq[k - 1] -> seq[0] -> ...
// 	Every nums[seq[j]] is either all positive or all negative.
// 	k > 1
//
//
// Return true if there is a cycle in nums, or false otherwise.
//
// Example:
// Input: nums = [2,-1,1,2,2]
// Output: true
// Explanation: The graph shows how the indices are connected. White nodes are jumping forward, while red is jumping backward.
// We can see the cycle 0 --> 2 --> 3 --> 0 --> ..., and all of its nodes are white (jumping in the same direction).
//
// Constraints:
// 1 <= nums.length <= 5000
// 	-1000 <= nums[i] <= 1000
// 	nums[i] != 0
//
//
//  
// Follow up: Could you solve it in O(n) time complexity and O(1) extra space complexity?
//

class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();

        auto nextIndex = [&](int current) {
            return ((current + nums[current]) % n + n) % n; // ensure non-negative
        };

        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) continue; // already visited

            int slow = i, fast = i;
            bool isForward = nums[i] > 0;

            while (true) {
                slow = nextIndex(slow);
                if (nums[slow] == 0 || (nums[slow] > 0) != isForward) break;

                fast = nextIndex(fast);
                if (nums[fast] == 0 || (nums[fast] > 0) != isForward) break;
                fast = nextIndex(fast);
                if (nums[fast] == 0 || (nums[fast] > 0) != isForward) break;

                if (slow == fast) {
                    if (slow == nextIndex(slow)) break; // single-element loop
                    return true;
                }
            }

            // Mark all nodes in the current traversal as visited
            int marker = i;
            int val = nums[i];
            while (nums[marker] != 0 && (nums[marker] > 0) == isForward) {
                int temp = marker;
                marker = nextIndex(marker);
                nums[temp] = 0; // mark as visited
            }
        }

        return false;           
    }
};
