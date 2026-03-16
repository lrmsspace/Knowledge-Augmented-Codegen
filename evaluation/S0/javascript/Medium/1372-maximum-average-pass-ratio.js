// Source: https://leetcode.com/problems/maximum-average-pass-ratio/   |   Difficulty: Medium
//
// Problem Description:
// There is a school that has classes of students and each class will be having a final exam. You are given a 2D integer array classes, where classes[i] = [passi, totali]. You know beforehand that in the ith class, there are totali total students, but only passi number of students will pass the exam.
//
// You are also given an integer extraStudents. There are another extraStudents brilliant students that are guaranteed to pass the exam of any class they are assigned to. You want to assign each of the extraStudents students to a class in a way that maximizes the average pass ratio across all the classes.
//
// The pass ratio of a class is equal to the number of students of the class that will pass the exam divided by the total number of students of the class. The average pass ratio is the sum of pass ratios of all the classes divided by the number of the classes.
//
// Return the maximum possible average pass ratio after assigning the extraStudents students. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
// Output: 0.78333
// Explanation: You can assign the two extra students to the first class. The average pass ratio will be equal to (3/4 + 3/5 + 2/2) / 3 = 0.78333.
//
// Constraints:
// 1 <= classes.length <= 105
// 	classes[i].length == 2
// 	1 <= passi <= totali <= 105
// 	1 <= extraStudents <= 105
//

/**
 * @param {number[][]} classes
 * @param {number} extraStudents
 * @return {number}
 */
var maxAverageRatio = function(classes, extraStudents) {
    const pq = new MaxPriorityQueue({ priority: (item) => item[0] } );
    const getDelta = (pass, total) => {
        const ratio1 = pass / total;
        const ratio2 = (pass + 1) / (total + 1);
        return ratio2 - ratio1;
    };
    for (const [pass, total] of classes) {
        pq.enqueue([getDelta(pass, total), pass, total]);
    }
    for (let i = 0; i < extraStudents; i++) {
        const [delta, pass, total] = pq.dequeue().element;
        pq.enqueue([getDelta(pass + 1, total + 1), pass + 1, total + 1]);
    }
    let totalRatio = 0;
    while (!pq.isEmpty()) {
        const [_, pass, total] = pq.dequeue().element;
        totalRatio += pass / total;
    }
    return totalRatio / classes.length;
}   ;