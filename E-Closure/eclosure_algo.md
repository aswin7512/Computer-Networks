# Algorithm: Epsilon Closure of an NFA
1. Start.
2. Read the number of states and store all the states.
3. Read the number of transitions.
4. Read each transition as From, Symbol, To.
5. Use e to represent an epsilon transition.
6. For each state:
	- Reset the visited array.
	- Add the current state to its epsilon closure.
	- Check all transitions from the current state.
	- If an epsilon transition is found, visit the destination state.
	- Repeat this process using DFS until no new epsilon-reachable states are found.
7. Display the epsilon closure of the current state.
8. Repeat the process for all states.
9. Stop.
