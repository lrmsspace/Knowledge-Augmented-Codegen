// Source: https://leetcode.com/problems/remove-boxes/   |   Difficulty: Hard
//
// Problem Description:
// You are given several boxes with different colors represented by different positive numbers.
//
// You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (i.e., composed of k boxes, k >= 1), remove them and get k * k points.
//
// Return the maximum points you can get.
//
// Example:
// Input: boxes = [1,3,2,2,2,3,4,3,1]
// Output: 23
// Explanation:
// [1, 3, 2, 2, 2, 3, 4, 3, 1] 
// ----> [1, 3, 3, 4, 3, 1] (3*3=9 points) 
// ----> [1, 3, 3, 3, 1] (1*1=1 points) 
// ----> [1, 1] (3*3=9 points) 
// ----> [] (2*2=4 points)
//
// Constraints:
// 1 <= boxes.length <= 100
// 	1 <= boxes[i] <= 100
//

/**
 * @param {number[]} boxes
 * @return {number}
 */
var removeBoxes = function(boxes) {
    const memo = new Map();
    const dfs = (l, r, k) => {
        if (l > r) return 0;
        const key = `${l},${r},${k}`;
        if (memo.has(key)) return memo.get(key);
        let i = l, count = k;
        while (i + 1 <= r && boxes[i] === boxes[i + 1]) {
            i++;
            count++;
        }
        let maxPoints = (count * count) + dfs(i + 1, r, 0);
        for (let j = i + 1; j <= r; j++) {
            if (boxes[j] === boxes[i]) {
                maxPoints = Math.max(maxPoints, dfs(i + 1, j - 1, 0) + dfs(j, r, count));
            }
        }
        memo.set(key, maxPoints);
        return maxPoints;
    }
    return dfs(0, boxes.length - 1, 0); 
};
