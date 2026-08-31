# Algorithm: Operator Precedence Parser
1. Start.
2. Read the input expression.
3. Tokenize the expression:
	- Convert operands such as a, b, id into id.
	- Keep operators such as +, -, *, /, ^, ( and ).
	- Add $ at the end of the input.
4. Initialize the stack and push $ onto it.
5. Set the input pointer to the first token.
6. Compare the top symbol of the stack with the current input symbol using the operator precedence table.
7. If the precedence relation is < or =:
	- Perform Shift.
	- Push the current input symbol onto the stack.
	- Move the input pointer to the next symbol.
8. If the precedence relation is >:
	- Perform Reduce.
	- Pop symbols from the stack until a < precedence relation is found.
9. If the stack top and input symbol are both $:
	- Accept the expression.
10. If no valid precedence relation exists:
	- Display Error.
	- Reject the expression.
11. Display whether the expression is VALID or INVALID.
12. Stop.
