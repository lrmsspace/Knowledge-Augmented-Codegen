// Source: https://leetcode.com/problems/erect-the-fence/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array trees where trees[i] = [xi, yi] represents the location of a tree in the garden.
//
// Fence the entire garden using the minimum length of rope, as it is expensive. The garden is well-fenced only if all the trees are enclosed.
//
// Return the coordinates of trees that are exactly located on the fence perimeter. You may return the answer in any order.
//
// Example:
// Input: trees = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
// Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
// Explanation: All the trees will be on the perimeter of the fence except the tree at [2, 2], which will be inside the fence.
//
// Constraints:
// 1 <= trees.length <= 3000
// 	trees[i].length == 2
// 	0 <= xi, yi <= 100
// 	All the given positions are unique.
//

/**
 * @param {number[][]} trees
 * @return {number[][]}
 */
var outerTrees = function(trees) {
    const cross = (o, a, b) => (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0]);
    trees.sort((a, b) => a[0] - b[0] || a[1] - b[1]);
    const lower = [];
    for (const tree of trees) {
        while (lower.length >= 2 && cross(lower[lower.length - 2], lower[lower.length - 1], tree) < 0) {
            lower.pop();
        }
        lower.push(tree);
    }
    const upper = [];   
    for (let i = trees.length - 1; i >= 0; i--) {
        const tree = trees[i];
        while (upper.length >= 2 && cross(upper[upper.length - 2], upper[upper.length - 1], tree) < 0) {
            upper.pop();
        }
        upper.push(tree);
    }
    upper.pop();
    lower.pop();
    return lower.concat(upper); 
};
