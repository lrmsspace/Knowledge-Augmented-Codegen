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
// Helpful references (internal KB):
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
// - Josephus Problem (number, simulation, recursion)
//   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
//   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
//   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
//   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
//   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* survivedRobotsHealths(int* positions, int positionsSize, int* healths, int healthsSize, char* directions, int* returnSize) {
    typedef struct {
        int index;
        int position;
        int health;
        char direction;
    } Robot;

    Robot* robots = (Robot*)malloc(positionsSize * sizeof(Robot));
    for (int i = 0; i < positionsSize; i++) {
        robots[i].index = i;
        robots[i].position = positions[i];
        robots[i].health = healths[i];
        robots[i].direction = directions[i];
    }

    // Sort robots by position
    int cmp(const void* a, const void* b) {
        Robot* r1 = (Robot*)a;
        Robot* r2 = (Robot*)b;
        return r1->position - r2->position;
    }
    qsort(robots, positionsSize, sizeof(Robot), cmp);

    int* resultHealths = (int*)malloc(positionsSize * sizeof(int));
    for (int i = 0; i < positionsSize; i++) {
        resultHealths[i] = -1; // -1 indicates robot is destroyed
    }

    int* stack = (int*)malloc(positionsSize * sizeof(int));
    int top = -1;

    for (int i = 0; i < positionsSize; i++) {
        if (robots[i].direction == 'R') {
            stack[++top] = i; // Push index onto stack
        } else { // direction 'L'
            while (top >= 0 && robots[stack[top]].health > 0 && robots[i].health > 0) {
                if (robots[stack[top]].health > robots[i].health) {
                    robots[stack[top]].health--;
                    robots[i].health = 0; // Destroy current robot
                } else if (robots[stack[top]].health < robots[i].health) {
                    robots[i].health--;
                    robots[stack[top]].health = 0; // Destroy robot on stack
                    top--; // Pop from stack
                } else { // Equal health
                    robots[stack[top]].health = 0; // Destroy both
                    robots[i].health = 0;
                    top--; // Pop from stack
                }
            }
            if (robots[i].health > 0) {
                resultHealths[robots[i].index] = robots[i].health; // Survived
            }
        }
    }

    // Remaining robots in stack survive
    while (top >= 0) {
        int idx = stack[top--];
        if (robots[idx].health > 0) {
            resultHealths[robots[idx].index] = robots[idx].health; // Survived
        }
    }
    free(stack);
    free(robots);
    // Prepare final result
    int survivorCount = 0;
    for (int i = 0; i < positionsSize; i++) {
        if (resultHealths[i] != -1) {
            survivorCount++;
        }
    }
    int* finalResult = (int*)malloc(survivorCount * sizeof(int));
    int j = 0;
    for (int i = 0; i < positionsSize; i++) {
        if (resultHealths[i] != -1) {
            finalResult[j++] = resultHealths[i];
        }
    }
    free(resultHealths);
    *returnSize = survivorCount;
    return finalResult; 
}
