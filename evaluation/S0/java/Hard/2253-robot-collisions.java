// Source: https://leetcode.com/problems/robot-collisions/   |   Difficulty: Hard
//
// Problem Description:
// There are n 1-indexed robots, each having a position on a line, health, and movement direction.
//
// You are given 0-indexed integer arrays positions, healths, and a string directions (directions[i] is either 'L' for left or 'R' for right). All integers in positions are unique.
//
// All robots start moving on the line simultaneously at the same speed in their given directions. If two robots ever share the same position while moving, they will collide.
//
// If two robots collide, the robot with lower health is removed from the line, and the health of the other robot decreases by one. The surviving robot continues in the same direction it was going. If both robots have the same health, they are both removed from the line.
//
// Your task is to determine the health of the robots that survive the collisions, in the same order that the robots were given, i.e. final health of robot 1 (if survived), final health of robot 2 (if survived), and so on. If there are no survivors, return an empty array.
//
// Return an array containing the health of the remaining robots (in the order they were given in the input), after no further collisions can occur.
//
// Note: The positions may be unsorted.
//
// Example:
// Input: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions = "RRRRR"
// Output: [2,17,9,15,10]
// Explanation: No collision occurs in this example, since all robots are moving in the same direction. So, the health of the robots in order from the first robot is returned, [2, 17, 9, 15, 10].
//
// Constraints:
// 1 <= positions.length == healths.length == directions.length == n <= 105
// 	1 <= positions[i], healths[i] <= 109
// 	directions[i] == 'L' or directions[i] == 'R'
// 	All values in positions are distinct
//

class Solution {
    public List<Integer> survivedRobotsHealths(int[] positions, int[] healths, String directions) {
        int n = positions.length;
        Integer[] indices = new Integer[n];
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }
        Arrays.sort(indices, Comparator.comparingInt(i -> positions[i]));

        Deque<Integer> stack = new ArrayDeque<>();
        for (int idx : indices) {
            char dir = directions.charAt(idx);
            int health = healths[idx];

            if (dir == 'R') {
                stack.push(idx);
            } else {
                while (!stack.isEmpty() && health > 0) {
                    int topIdx = stack.peek();
                    if (healths[topIdx] < health) {
                        health--;
                        healths[topIdx] = 0;
                        stack.pop();
                    } else if (healths[topIdx] == health) {
                        healths[topIdx] = 0;
                        health = 0;
                        stack.pop();
                    } else {
                        healths[topIdx]--;
                        health = 0;
                    }
                }
                healths[idx] = health;
            }
        }

        List<Integer> result = new ArrayList<>();
        for (int h : healths) {
            if (h > 0) {
                result.add(h);
            }
        }
        return result;          
    }
}
