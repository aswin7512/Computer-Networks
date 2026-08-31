# Algorithm: Constant Propagation
1. Start.
2. Read the number of statements.
3. Read each statement in the form x = y + z or x = 10.
4. Separate each statement into:
	- Left-hand side (LHS)
	- First operand
	- Second operand
	- Operator
5. Remove unnecessary spaces from the operands.
6. Check each statement one by one.
7. Replace an operand with its known constant value if that variable was previously assigned a constant.
8. If both operands are constants, perform the given operation (+, -, *, or /).
9. Store the calculated result as a constant so it can be used in later statements.
10. If the operands are not both constants, display the statement without changing it.
11. Display the statements after constant propagation.
12. Stop.
