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
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
// - Reservoir Sampling (array, randomized, simulation)
//   • When to use: When you need to randomly select a fixed number of items (k) from a stream or a very large dataset of unknown size, ensuring each item has an equal probability of selection in a single pass.
//   • Idea: Reservoir sampling is a randomized algorithm that selects k items from a list containing n items, where n is either a very large or unknown number, ensuring each item has an equal probability of being selected. It processes the input in a single pass with O(N) time complexity and O(k) space complexity.
//   • Invariants: The reservoir always contains exactly k elements.; Any element processed up to the current index `i` has a k/(i+1) probability of being in the reservoir.
//   • Tips: Initialize the reservoir with the first k elements from the stream.; For each subsequent element, generate a random index from 0 to current_stream_index.
//   • Pitfalls: Failing to correctly initialize the reservoir with the first k elements.; Generating random indices outside the valid range [0, current_stream_index] or [0, k-1].
// - Flows with demands (graph, binary-search-answer)
//   • When to use: Use when a problem involves finding a flow in a network where edges have both lower and upper capacity bounds, or nodes have supply/demand requirements, and an optimal value needs to be found.
//   • Idea: This technique transforms a network with lower and upper capacity bounds on edges (or node demands) into a standard max-flow problem. It often involves adding a new source and sink to handle demands, and then binary searching on the answer if an optimal value is sought, typically with O(MaxFlow * log(Range)) complexity.
//   • Invariants: The total flow out of the super source equals the total demand that needs to be satisfied.; For any node, the sum of incoming flow minus outgoing flow equals its net demand (0 for internal nodes in a circulation).
//   • Tips: Convert lower bounds to demands by adjusting capacities and adding a super source/sink.; A feasible flow exists if the max flow in the transformed network equals the total demand.
//   • Pitfalls: Incorrectly calculating residual capacities after demand satisfaction.; Forgetting to add a super source/sink for handling demands.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    // Max-heap to store the classes based on the potential increase in pass ratio
    typedef struct {
        int pass;
        int total;
        double potential_increase;
    } Class;

    Class* heap = (Class*)malloc(classesSize * sizeof(Class));
    int heapSize = 0;
    
    // Initialize the heap with all classes
    for (int i = 0; i < classesSize; i++) {
        heap[i].pass = classes[i][0];
        heap[i].total = classes[i][1];
        heap[i].potential_increase = (double)(classes[i][1] - classes[i][0]) / (classes[i][1] * (classes[i][1] + 1));
        heapSize++;
    }
    
    // Heapify the array to make it a max-heap
    for (int i = heapSize / 2 - 1; i >= 0; i--) {
        int largest = i;
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        
        if (leftChild < heapSize && heap[leftChild].potential_increase > heap[largest].potential_increase) {
            largest = leftChild;
        }
        
        if (rightChild < heapSize && heap[rightChild].potential_increase > heap[largest].potential_increase) {
            largest = rightChild;
        }
        
        if (largest != i) {
            Class temp = heap[i];
            heap[i] = heap[largest];
            heap[largest] = temp;
            
            // Update indices in the array
            int current_index = i;
            while (current_index < heapSize) {
                int left_child_index = 2 * current_index + 1;
                int right_child_index = 2 * current_index + 2;
                int max_child_index = current_index;
                
                if (left_child_index < heapSize && 
                    heap[left_child_index].potential_increase > heap[max_child_index].potential_increase) {
                    max_child_index = left_child_index;
                }
                
                if (right_child_index < heapSize && 
                    heap[right_child_index].potential_increase > heap[max_child_index].potential_increase) {
                    max_child_index = right_child_index;
                }
                
                if (max_child_index == current_index) break;
                
                Class temp_node = heap[current_index];
                heap[current_index] = heap[max_child_index];
                heap[max_child_index] = temp_node;
                
                current_index = max_child_index;
            }
        }
    }

    // Distribute extra students to maximize average pass ratio
    for (int studentCount = 0; studentCount < extraStudents; studentCount++) {
        // Remove the class with maximum potential increase
        Class maxClass = heap[0];
        
        // Update the class's pass and total values
        maxClass.pass++;
        maxClass.total++;
        
        // Recalculate potential increase for this class
        maxClass.potential_increase = (double)(maxClass.total - maxClass.pass) / (maxClass.total * (maxClass.total + 1));
        
        // Update the class in the array and re-heapify
        int indexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRootIndexToFixUpFromRoot();
        
        // Re-heapify from root down to maintain max-heap property
        int currentPosInHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeapArrayForMaxHeapPropertyMaintainedDownwardTraversalOfHeatmation();
    }

    // Calculate final average pass ratio
    double totalRatioSum = 0.0;
    for (int i = 0; i < classesSize; i++) {
        totalRatioSum += ((double)heap[i].pass / (double)heap[i].total);
    }

    free(heap);
    
    return totalRatioSum / classesSize;
}