// Source: https://leetcode.com/problems/assign-elements-to-groups-with-constraints/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array groups, where groups[i] represents the size of the ith group. You are also given an integer array elements.
//
// Your task is to assign one element to each group based on the following rules:
//
//
// 	An element at index j can be assigned to a group i if groups[i] is divisible by elements[j].
// 	If there are multiple elements that can be assigned, assign the element with the smallest index j.
// 	If no element satisfies the condition for a group, assign -1 to that group.
//
//
// Return an integer array assigned, where assigned[i] is the index of the element chosen for group i, or -1 if no suitable element exists.
//
// Note: An element may be assigned to more than one group.
//
// Example:
// Input: groups = [8,4,3,2,4], elements = [4,2]
//
// Output: [0,0,-1,1,0]
//
// Explanation:
//
//
// 	elements[0] = 4 is assigned to groups 0, 1, and 4.
// 	elements[1] = 2 is assigned to group 3.
// 	Group 2 cannot be assigned any element.
//
// Constraints:
// 1 <= groups.length <= 105
// 	1 <= elements.length <= 105
// 	1 <= groups[i] <= 105
// 	1 <= elements[i] <= 105
//

class Solution {
    public int[] assignElements(int[] groups, int[] elements) {
        int maxGroupSize = 0;
        for (int group : groups) {
            maxGroupSize = Math.max(maxGroupSize, group);
        }

        int[] elementIndexForDivisor = new int[maxGroupSize + 1];
        Arrays.fill(elementIndexForDivisor, -1);

        for (int j = 0; j < elements.length; j++) {
            int element = elements[j];
            for (int multiple = element; multiple <= maxGroupSize; multiple += element) {
                if (elementIndexForDivisor[multiple] == -1) {
                    elementIndexForDivisor[multiple] = j;
                }
            }
        }

        int[] assigned = new int[groups.length];
        for (int i = 0; i < groups.length; i++) {
            assigned[i] = elementIndexForDivisor[groups[i]];
        }

        return assigned;            
    }
}
