# Linked-List-Line-Editor
School Project. Search, edit, and create organized strings using linked list data structures

Program displays use of:
-linked lists to organize strings
-building utility functions to edit, remove, search and reorganize nodes of data


Program runs through the command window and accepts the following commands:

quit
-terminates the program. Information does not save to a file.

insert n [string]
-n is the line number and [string] is the information you wish to add.

insertEnd [string]
-adds a string to the end of the document. This is the most straight forward way to add to a doc. Strings over 80 characters long will be added to a new line.

edit n [string]
-will navigate to the line n and replace that line with your [string]

print
-prints the contents of the entire doc

search [string]
-will return all lines containing the given [string] of characters
