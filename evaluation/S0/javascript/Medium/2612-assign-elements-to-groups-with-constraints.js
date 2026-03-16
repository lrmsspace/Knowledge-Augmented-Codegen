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

/**
 * @param {number[]} groups
 * @param {number[]} elements
 * @return {number[]}
 */
var assignElements = function(groups, elements) {
    const assigned = [];
    for (let i = 0; i < groups.length; i++) {
        let assignedIndex = -1;
        for (let j = 0; j < elements.length; j++) {
            if (groups[i] % elements[j] === 0) {
                assignedIndex = j;
                break;
            }
        }
        assigned.push(assignedIndex);
    }
    return assigned;
};
