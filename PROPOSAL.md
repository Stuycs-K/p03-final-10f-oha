# Final Project Proposal

## Group Members:

Adam Oh

# Intentions:

The goal is to make a simple text editor. The functions I aim to for sure implement is to open text files, add and delete characters, move cursor with arrows, and close and saving to the file.

# Intended usage:

The intended use of the program is to be able to edit text documents within the terminal, similar to vim.

# Technical Details:

It will allocate memory to store text buffers.

It will navigate allocated memory to move the cursor and add and remove characters.

It will work with files to open, edit, save and close the file you are editing, using read to open and write to save and close the file.

It will use signals to detect when a command is being used, something like ctrl + s to save or ctrl + q to quit.

It will use fork and exec to make use of user input.

# Intended pacing:

Day 1-2: basic opening and closing files and scrolling and moving cursor
Day 3-4: editing functions (deletion and inserting)
Day 5: File saving

Week 2: add more functions with signals, polish and debug
