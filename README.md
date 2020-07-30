# FlexPP_ProgLangInterpreter
This is an interpreter for my own programming language going by the name Flex++. It has originally been 
created for a Discord bot, but now it is also available as a standalone interpreter. As of now, it is not
completely bug-free, but overall it can be used to its full potential. The interpreter itself uses a hand-written
lexer and recursive-descent parser to tokenize and parse the Flex++ code. Refer to the documentation below to
learn more about the Flex++ language.<br><br>

**USAGE**: fppi.exe |src_code_dir|<br>

**DOCUMENTATION**:<br>
As of version Flex++20(following the C++ standard naming) the language has 8 keywords:<br>
    -"begin"<br>
    -"end"<br>
    -"print"<br>
    -"printc"<br>
    -"eol"<br>
    -"set"<br>
    -"if"<br>
    -"while"<br>

It should be noted that it is obligatory for a Flex++ program source code to have some kind of whitespace in front of<br>
everything that is not a numerical expression.<br>
For example:<br>
~~~
    begin
        set a=3
        set b=9
        a=b
    end
~~~
<br>
is **NOT** a valid Flex++ program and **WILL NOT** be interpreted correctly.<br>

The correct usage is:
~~~
    begin
        set a = 3
        set b = 9
        a = b
    end
~~~
<br>
"begin" and "end" are used to denote the beggining and the end of a block<br><br>
For example:<br>

~~~
    begin
    ...
    end
~~~
<br>

Variables are declared using the "set" keyword. For the interpreter, every variable is of type "double",
therefore only numerical expressions can be evaluated by the interpreter<br>
For example:<br>

~~~
    set var = 3
    set a = 3*4+var
    set var = 3/(var-2)+3
~~~
<br>
Because of the limitations of the current lexer, numerical expressions should always be written without any
whitespace inbetween the members, therefore:<br>

~~~
    set smth = 90 + 4
    set incorrect = 3 + 4 + 9 * 3 / smth
~~~

<br>
is **NOT** allowed.<br>

As of now, a Flex++ program as a whole is a single block and every "if" and "while" statement
also has to be followed by a block.<br><br>
For example:<br>

~~~
    if: var >= a begin
    ...
    end
~~~
<br>

~~~
    while: var < a begin
    ...
    end
~~~
<br>

Assignment is done in the most common way across programming languages:<br>
~~~
    |var_name| = |value|
~~~

The keywords "print" and "printc" are used respectively for printing a numeric value and a character.<br>
For example:<br>

~~~
    set space = 32
    print space
    printc space
    print space
~~~
<br>

~~~
Output: 32 32
~~~
<br>

Explanation: 32 is the ASCII value of a 'space' character, therefore 'print space' prints 32 and 'printc space' prints a space character.<br>

The argument we give to the "print/printc" keyword can be followed by the "eol"(End of line) keyword. It basically prints a newline character<br>
For example:
~~~
    set space = 32
    print space eol
    print space eol
~~~
<br>

~~~
Output:
32
32
~~~
<br>

You can refer to test_prog.txt to see how a Flex++ program looks.<br>

**IMPORTANT**: Mathematical expressions using variables are resolved with the help of a preprocessor-like algorithm,
meaning that the following source code:<br>
~~~
set a = -4
set b = 3*a
~~~
...is invalid as it will produce the following expression: <code>3*-4</code><br>
This expression will **NOT** be correctly parsed by the interpreter. To avoid this issue, you may put the variable in front of the other
parts of the expression: <code>set b = a\*3</code><br>
...which will produce the following expression: <code>-4\*3</code><br>
This expression **WILL BE** correctly parsed by the interpreter.<br>

Another option is to put the variable into parentheses in the expression itself.<br>
For example:<br>
~~~
set a = -4
set b = 3*(a)
~~~
<br>

This **WILL PRODUCE** the correct mathematical expression as well: <code>3*(-4)</code><br>...which will be parsed correctly.

