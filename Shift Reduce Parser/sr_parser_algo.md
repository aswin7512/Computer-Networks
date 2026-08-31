# Algorithm: Shift-Reduce Parser
1. Start.
2. Read the input string containing operands (i), operators (+, *) and parentheses.
3. Initialize an empty stack and set the input pointer to the first symbol.
4. Repeat the following steps until the entire input is processed:
	- Check the top of the stack for a pattern that matches a grammar rule.
	- If i is found, reduce i → E.
	- If E*E is found, reduce E*E → E.
	- If E+E is found, reduce E+E → E.
	- If (E) is found, reduce (E) → E.
	- If no reduction is possible, shift the next input symbol onto the stack.
5. Continue shifting and reducing until all input symbols are processed.
6. If the stack contains only E after processing the entire input, accept the string.
7. Otherwise, reject the string.
8. Display the parsing actions and final result.
9. Stop.
