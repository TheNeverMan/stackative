Stackative Interpreter README

Installation Guide.

To install Stackative Interpreter:

1. Clone this repo.
2. Go to the stec subfolder from this folder.
3. execute "cmake;make" in terminal.
4. A binary called "stec" should appear.

Stackative Interpreter is called "stec", to interpret a file simply execute interpreter with filename as an argument like this:

./stec /home/user/dir/file.ste

Stackative source code files should have ste filename extension, but of course stec can interpret any plain/text file.

When stec tries to execute illegal command or encounter any error in code, a message will be printed, sample message looks like this:

!: Stack is empty

Error message is composed out of two parts, first it shows which command caused the error and then actual error message. Keep in mind that even when error is encountered this does not mean that code execution will stop, only command that gave error will fail. This means
that even this code will execute:

!!!!!!!!!!!!!!!done!

It tries to remove values from stack even when stack is empty, but you can see that "done" is still printed.

Known bugs:

1. join commands behaves weirdly when joining strings that start with zeros or contain only zeros.
2. truth loops crash program after enough iterations.

TODO:

1. debug mode, in this mode content of stack and other program variables would be printed on screen every instruction execution.
2. hide error messages switch,
3. stop execution on first error switch,
4. shell mode,
