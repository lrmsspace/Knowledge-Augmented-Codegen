// Source: https://leetcode.com/problems/calculate-score-after-performing-instructions/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays, instructions and values, both of size n.
//
// You need to simulate a process based on the following rules:
//
//
// 	You start at the first instruction at index i = 0 with an initial score of 0.
// 	If instructions[i] is "add":
// 	
// 		Add values[i] to your score.
// 		Move to the next instruction (i + 1).
// 	
// 	
// 	If instructions[i] is "jump":
// 	
// 		Move to the instruction at index (i + values[i]) without modifying your score.
// 	
// 	
//
//
// The process ends when you either:
//
//
// 	Go out of bounds (i.e., i < 0 or i >= n), or
// 	Attempt to revisit an instruction that has been previously executed. The revisited instruction is not executed.
//
//
// Return your score at the end of the process.
//
// Example:
// Input: instructions = ["jump","add","add","jump","add","jump"], values = [2,1,3,1,-2,-3]
//
// Output: 1
//
// Explanation:
//
// Simulate the process starting at instruction 0:
//
//
// 	At index 0: Instruction is "jump", move to index 0 + 2 = 2.
// 	At index 2: Instruction is "add", add values[2] = 3 to your score and move to index 3. Your score becomes 3.
// 	At index 3: Instruction is "jump", move to index 3 + 1 = 4.
// 	At index 4: Instruction is "add", add values[4] = -2 to your score and move to index 5. Your score becomes 1.
// 	At index 5: Instruction is "jump", move to index 5 + (-3) = 2.
// 	At index 2: Already visited. The process ends.
//
// Constraints:
// n == instructions.length == values.length
// 	1 <= n <= 105
// 	instructions[i] is either "add" or "jump".
// 	-105 <= values[i] <= 105
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long calculateScore(vector<string>& instructions, vector<int>& values) {
        int n = instructions.size();
        long long score = 0;
        unordered_set<int> visited;
        int i = 0;

        while (i >= 0 && i < n && visited.find(i) == visited.end()) {
            visited.insert(i);
            if (instructions[i] == "add") {
                score += values[i];
                i++;
            } else { // "jump"
                i += values[i];
            }
        }

        return score;           
    }
};
