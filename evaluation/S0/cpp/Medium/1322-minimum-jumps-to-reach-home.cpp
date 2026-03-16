// Source: https://leetcode.com/problems/minimum-jumps-to-reach-home/   |   Difficulty: Medium
//
// Problem Description:
// A certain bug's home is on the x-axis at position x. Help them get there from position 0.
//
// The bug jumps according to the following rules:
//
//
// 	It can jump exactly a positions forward (to the right).
// 	It can jump exactly b positions backward (to the left).
// 	It cannot jump backward twice in a row.
// 	It cannot jump to any forbidden positions.
//
//
// The bug may jump forward beyond its home, but it cannot jump to positions numbered with negative integers.
//
// Given an array of integers forbidden, where forbidden[i] means that the bug cannot jump to the position forbidden[i], and integers a, b, and x, return the minimum number of jumps needed for the bug to reach its home. If there is no possible sequence of jumps that lands the bug on position x, return -1.
//
// Example:
// Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
// Output: 3
// Explanation: 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.
//
// Constraints:
// 1 <= forbidden.length <= 1000
// 	1 <= a, b, forbidden[i] <= 2000
// 	0 <= x <= 2000
// 	All the elements in forbidden are distinct.
// 	Position x is not forbidden.
//

class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        unordered_set<int> forbiddenSet(forbidden.begin(), forbidden.end());
        queue<tuple<int, int, bool>> q; // position, jumps, canJumpBack
        q.emplace(0, 0, true);
        unordered_set<string> visited;
        visited.insert("0_1"); // position 0, can jump back

        int upperLimit = 6000; // To prevent infinite jumps beyond x

        while (!q.empty()) {
            auto [pos, jumps, canJumpBack] = q.front();
            q.pop();

            if (pos == x) {
                return jumps;
            }

            // Jump forward
            int forwardPos = pos + a;
            if (forwardPos <= upperLimit && forbiddenSet.find(forwardPos) == forbiddenSet.end()) {
                string state = to_string(forwardPos) + "_1"; // can jump back after forward jump
                if (visited.find(state) == visited.end()) {
                    visited.insert(state);
                    q.emplace(forwardPos, jumps + 1, true);
                }
            }

            // Jump backward
            if (canJumpBack) {
                int backwardPos = pos - b;
                if (backwardPos >= 0 && forbiddenSet.find(backwardPos) == forbiddenSet.end()) {
                    string state = to_string(backwardPos) + "_0"; // cannot jump back again
                    if (visited.find(state) == visited.end()) {
                        visited.insert(state);
                        q.emplace(backwardPos, jumps + 1, false);
                    }
                }
            }
        }

        return -1; // Not reachable         
    }
};
