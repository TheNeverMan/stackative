Stackative-21A

In Stackative instructions are interpreted one after another. Every instruction is exacly 1 sign. There are 30 instructions:
"! ? @ # $ % ^ & * ( ) _ + { } [ ] - = ; : " \ | : ~ ' / . , < >"
Anything that is not a valid instruction will be put on top of stack, so program:

Hello

will just put "Hello" on stack. "!" command takes top value from stack, removes it and dumps it to screen, so program:

Hello!

will print "Hello" to screen and leave stack empty. Spaces are not separators so this program:

Hello World!

will print "Hello World" to screen. Same applies to numbers and both:

1233243!    -> "1233243" printed on screen
H3ll0!      -> "H3ll0" printed on screen
