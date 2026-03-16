// Source: https://leetcode.com/problems/building-boxes/   |   Difficulty: Hard
//
// Problem Description:
// You have a cubic storeroom where the width, length, and height of the room are all equal to n units. You are asked to place n boxes in this room where each box is a cube of unit side length. There are however some rules to placing the boxes:
//
//
// 	You can place the boxes anywhere on the floor.
// 	If box x is placed on top of the box y, then each side of the four vertical sides of the box y must either be adjacent to another box or to a wall.
//
//
// Given an integer n, return the minimum possible number of boxes touching the floor.
//
// Example:
// Input: n = 3
// Output: 3
// Explanation: The figure above is for the placement of the three boxes.
// These boxes are placed in the corner of the room, where the corner is on the left side.
//
// Constraints:
// 1 <= n <= 109
//

class Solution {
public:
    int minimumBoxes(int n) {
        int layer = 0;
        int totalBoxes = 0;
        int boxesOnFloor = 0;
        
        while (true) {
            int boxesInLayer = (layer + 1) * (layer + 2) / 2;
            if (totalBoxes + boxesInLayer > n) break;
            totalBoxes += boxesInLayer;
            boxesOnFloor += (layer + 1);
            layer++;
        }
        
        int rem = n - totalBoxes;
        int side = 1;
        
        while (rem > 0) {
            int boxesInSide = side;
            if (rem >= boxesInSide) {
                boxesOnFloor += 1;
                rem -= boxesInSide;
            } else {
                break;
            }
            side++;
        }
        
        return boxesOnFloor;            
    }
};
