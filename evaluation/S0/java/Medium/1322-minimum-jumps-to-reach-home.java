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
    public int minimumJumps(int[] forbidden, int a, int b, int x) {
        Set<Integer> forbiddenSet = new HashSet<>();
        for (int pos : forbidden) {
            forbiddenSet.add(pos);
        }

        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0, 0}); // position, jumps, lastJumpWasBackward
        Set<String> visited = new HashSet<>();
        visited.add("0,0");

        int upperBound = 6000; // A safe upper limit to avoid infinite jumps

        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int position = current[0];
            int jumps = current[1];
            int lastJumpWasBackward = current[2];

            if (position == x) {
                return jumps;
            }

            // Jump forward
            int forwardPos = position + a;
            if (forwardPos <= upperBound && !forbiddenSet.contains(forwardPos)) {
                String state = forwardPos + ",0";
                if (!visited.contains(state)) {
                    visited.add(state);
                    queue.offer(new int[]{forwardPos, jumps + 1, 0});
                }
            }

            // Jump backward
            if (lastJumpWasBackward == 0) {
                int backwardPos = position - b;
                if (backwardPos >= 0 && !forbiddenSet.contains(backwardPos)) {
                    String state = backwardPos + ",1";
                    if (!visited.contains(state)) {
                        visited.add(state);
                        queue.offer(new int[]{backwardPos, jumps + 1, 1});
                    }
                }
            }
        }

        return -1;          
    }
}
