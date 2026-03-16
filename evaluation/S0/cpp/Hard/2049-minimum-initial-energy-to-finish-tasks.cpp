// Source: https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array tasks where tasks[i] = [actuali, minimumi]:
//
//
// 	actuali is the actual amount of energy you spend to finish the ith task.
// 	minimumi is the minimum amount of energy you require to begin the ith task.
//
//
// For example, if the task is [10, 12] and your current energy is 11, you cannot start this task. However, if your current energy is 13, you can complete this task, and your energy will be 3 after finishing it.
//
// You can finish the tasks in any order you like.
//
// Return the minimum initial amount of energy you will need to finish all the tasks.
//
// Example:
// Input: tasks = [[1,2],[2,4],[4,8]]
// Output: 8
// Explanation:
// Starting with 8 energy, we finish the tasks in the following order:
//     - 3rd task. Now energy = 8 - 4 = 4.
//     - 2nd task. Now energy = 4 - 2 = 2.
//     - 1st task. Now energy = 2 - 1 = 1.
// Notice that even though we have leftover energy, starting with 7 energy does not work because we cannot do the 3rd task.
//
// Constraints:
// 1 <= tasks.length <= 105
// 	1 <= actual​i <= minimumi <= 104
//

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        // Sort tasks by (minimum - actual) in descending order
        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });
        
        long long initialEnergy = 0;
        long long currentEnergy = 0;
        
        for (const auto& task : tasks) {
            int actual = task[0];
            int minimum = task[1];
            
            if (currentEnergy < minimum) {
                initialEnergy += (minimum - currentEnergy);
                currentEnergy = minimum;
            }
            
            currentEnergy -= actual;
        }
        
        return (int)initialEnergy;          
    }
};
