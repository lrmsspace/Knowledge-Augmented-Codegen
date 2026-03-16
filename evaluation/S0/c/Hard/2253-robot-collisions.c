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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* survivedRobotsHealths(int* positions, int positionsSize, int* healths, int healthsSize, char* directions, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = 0;
    if (positionsSize <= 0 || positionsSize != healthsSize || positionsSize != (int)strlen(directions)) {
        return NULL;
    }

    typedef struct {
        int index;
        int position;
        int health;
        char direction;
    } Robot;

    Robot *robots = (Robot*)malloc(positionsSize * sizeof(Robot));
    if (!robots) return NULL;

    for (int i = 0; i < positionsSize; ++i) {
        robots[i].index = i;
        robots[i].position = positions[i];
        robots[i].health = healths[i];
        robots[i].direction = directions[i];
    }

    /* Sort robots by position */
    int cmpRobot(const void *a, const void *b) {
        Robot *ra = (Robot*)a;
        Robot *rb = (Robot*)b;
        return ra->position - rb->position;
    }
    qsort(robots, positionsSize, sizeof(Robot), cmpRobot);

    int *alive = (int*)calloc(positionsSize, sizeof(int));
    if (!alive) {
        free(robots);
        return NULL;
    }

    int *stack = (int*)malloc(positionsSize * sizeof(int));
    if (!stack) {
        free(robots);
        free(alive);
        return NULL;
    }
    int top = -1;

    for (int i = 0; i < positionsSize; ++i) {
        Robot *curr = &robots[i];
        if (curr->direction == 'R') {
            stack[++top] = i; /* push index onto stack */
        } else {
            while (top >= 0) {
                Robot *other = &robots[stack[top]];
                if (other->health < curr->health) {
                    curr->health--;
                    other->health = 0;
                    top--; /* pop from stack */
                } else if (other->health > curr->health) {
                    other->health--;
                    curr->health = 0;
                    break;
                } else {
                    other->health = 0;
                    curr->health = 0;
                    top--; /* pop from stack */
                    break;
                }
            }
        }
    }

    for (int i = 0; i < positionsSize; ++i) {  
        if (robots[i].health > 0) {
            alive[robots[i].index] = robots[i].health;
            (*returnSize)++;
        }
    }
    int *result = (int*)malloc((*returnSize) * sizeof(int));
    if (!result) {
        free(robots);
        free(alive);
        free(stack);
        return NULL;
    }
    int idx = 0;
    for (int i = 0; i < positionsSize; ++i) {
        if (alive[i] > 0) {
            result[idx++] = alive[i];
        }
    }
    free(robots);
    free(alive);
    free(stack);
    return result;     
}
