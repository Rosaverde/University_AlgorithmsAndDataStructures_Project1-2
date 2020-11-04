# University_AlgorithmsAndDataStructures_Project1-2
\
Write a day planner.\
\
Each list item contains a date (day, month, year), time and note. Write the following functions:

1. function that prints the contents of the list,
2. function deleting the list,
3. function displaying all notes for a given day,
4. the function "add_beginning", which adds an element to the beginning of the list (the function takes a pointer to the beginning of the list and a data record as arguments).

Use the above functions in a program that:

1. loads data from the console to the schedule until the record with the date (0, 0, 0) is loaded - do not add the last note to the list,
2. shows the contents of the list,
3. displays notes for a given day (loaded from the console),
4. clears the list

Data should be added to the list using the function add_on_beginning (items on the list should be in the reverse order than in the file).

Program:
1. finds the first note (in terms of earliest hour) of a certain day and moves it to the top of the list
2. Print a list (using the print function)
3. Returns the number of notes older than this note (if there are no notes for a given day, return 0)
4. removes the remaining notes from that day from the list (if any)
5. Print a list (using the print function)
