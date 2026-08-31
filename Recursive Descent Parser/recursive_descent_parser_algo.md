# Algorithm: Recursive Descent Parser
1. Start.
2. Read the input expression.
3. Initialize the input position to 0.
4. Skip any spaces in the expression.
5. Parse the expression using the following rules:
	- Expression: Parse a term, followed by zero or more + and terms.
	- Term: Parse a factor, followed by zero or more * and factors.
	- Factor: Accept an identifier, number, or expression inside parentheses.
6. While parsing a factor:
	- If it is a letter, read the complete identifier.
	- If it is a digit, read the complete number.
	- If it is (, parse the expression inside it and check for the matching ).
	- Otherwise, report an invalid expression.
7. Continue parsing according to the grammar until the expression ends.
8. Skip any remaining spaces.
9. If the end of the input is reached, display Valid expression.
10. Otherwise, display Invalid expression.
11. Stop.
