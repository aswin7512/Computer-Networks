# Algorithm: Intermediate Code Generation
1. Start.
2. Read the infix expression.
3. Initialize an empty stack for operators.
4. Convert the infix expression into postfix form:
	- If the character is an operand, add it to the postfix expression.
	- If it is (, push it onto the stack.
	- If it is ), pop operators until ( is found.
	- If it is an operator, pop operators with higher or equal precedence, then push the current operator.
5. Pop all remaining operators from the stack and add them to the postfix expression.
6. Initialize a stack for operands and temporary variables.
7. Scan the postfix expression from left to right:
	- If the character is an operand, push it onto the operand stack.
	- If it is an operator:
		* Pop the second operand.
		* Pop the first operand.
		* Create a new temporary variable (t1, t2, etc.).
		* Generate the three-address statement: temp = operand1 operator operand2.
		* Push the temporary variable back onto the stack.
8. Display all the generated three-address code statements.
9. Stop.
