Stackative-21A
Commands List

How to read this?

[instruction character] - [full instruction name] - [description]

Full list:

! - Print - pops top value from stack and prints it to screen.
? - User Input - asks user for input and pushes it on stack.
@ - Length of Stack - pushes number representing legth of stack on stack.
; - Separator - separates data.
$ - ASCII Convert - pops top value of the stack, if that value is one char string pushes its ASCII code, if it is number pushes an char with ASCII code equal to that number and if it is more that one char strings pushes its length.
# - Program End - ends program instantly.
. - Boolean Test - pops top value of the stack, if it is number other than zero pushes 1 on stack, if it is string or 0 pushes 0 on stack.
: - Duplicate - duplicates top stack value.
, - Delete - pops top value of the stack.
& - Data Handler - at first use pops to value of the stack and stores it, then when used again pushes that value on the stack, then when used again pops value and stores it etc.
() - Truth Loop - code in brackets is executed only and as long as top value of the stack is not 0 or string. Condition is checked at the end and beginning of loop.
[] - For Loop - removes top value of the stack and executes code this many times (if popped value is string code gets executed 0 times), however code in brackets is always executed one more time.
{} - Code Block - code in brackets gets executed only when commands like "=", "<" or ">" give correct result.
= - If - compares two highest values on the stack, if they are equal executes code in "{}", both values need to have same type (string, number) for If to pass.
> - Greather Than - compares two highest values on the stack, if top value on the stack is smaller than second one executes code in "{}", both values need to have same type (string, number) for If to pass.
< - Smaller Than - compares two highest values on the stack, if top value on the stack is bigger than second one executes code in "{}", both values need to have same type (string, number) for If to pass.
~ - Converter - used to convert types of stack values from number to string and from string to number, but data is autoconverted anyways, this command has no use.
+ - Addition - pops two top values of the stack, adds them and pushes result on stack, both values need to be numbers.
/ - Division - pops two top values of the stack, divides second value by highest value from stack and pushes result on stack, both values need to be numbers.
- - Subtraction - pops two top values of the stack, substracts highest value from second value from stack and pushes result on stack, both values need to be numbers.
* - Multiplication - pops two top values of the stack, multiplies them and pushes result on stack, both values need to be numbers.
% - Modulo - pops two top values of the stack and pushes result of modulo of second value by highest value on stack, both values need to be numbers.
| - Split - if top value on stack is string, pops it and split to one char strings and pushes them on stack in original order.
_ - Negate - if top value on stack is number, pops it and pushes negation of it on stack.
" - Comment - code in quotation is not executed
' - Random Number - creates random number using C++ rand() and pushes it on stack.
\ - Special - makes next instruction interpreted as data, used to put instruction characters on stack (\!! will print "!").
^ - Join - pops two top values of the stack and joins them as they were strings (top value is appended to second value) and pushes result on stack.
