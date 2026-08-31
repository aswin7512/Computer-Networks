# Algorithm: Lexical Analyzer
1. Start.
2. Read the file path from the user.
3. Open the file in read mode.
4. If the file cannot be opened, display an error message and stop.
5. Read the file character by character until the end of the file.
6. Ignore whitespace characters.
7. If the character is a letter or _:
	- Read the complete word.
	- Check whether it is a keyword.
	- If it is a keyword, display Keyword.
	- Otherwise, display Identifier.
8. If the character is a digit:
	- Read all consecutive digits.
	- Display the token as a Number.
9. If the character is /:
	- Check the next character.
	- If it is *, skip the multi-line comment.
	- If it is /, skip the single-line comment.
	- Otherwise, display / as an Operator.
10. If the character is one of + - * / = % < >, display it as an Operator.
11. If the character is one of ( ) { } [ ] ; ,, display it as a Special Symbol.
12. For any other character, display it as Unknown.
13. Close the file.
14. Stop.
