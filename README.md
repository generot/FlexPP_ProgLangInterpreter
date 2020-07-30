# FlexPP_ProgLangInterpreter
This is an interpreter for my own programming language going by the name Flex++. It has originally been 
created for a Discord bot, but now it is also available as a standalone interpreter. As of now, it is not
completely bug-free, but overall it can be used to its full potential. The interpreter itself uses a hand-written
lexer and recursive-descent parser to tokenize and parse the Flex++ code. Refer to the documentation below to
learn more about the Flex++ language.<br><br>

**USAGE**: fppi.exe |src_code_dir|<br>

**DOCUMENTATION**<br>
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
<code>
    begin<br>
        set a=3<br>
        set b=9<br>
        a=b<br>
    end<br>
</code>
is NOT a valid Flex++ program and WILL NOT be interpreted correctly.<br>

The correct usage is:
<code>
    begin<br>
        set a = 3<br>
        set b = 9<br>
        a = b<br>
    end<br>
</code>

"begin" and "end" are used to denote the beggining and the end of a block<br><br>
For example:<br>
<code>
    begin<br>
    ...<br>
    end<br>
</code>

Variables are declared using the "set" keyword. For the interpreter, every variable is of type "double",
therefore only numerical expressions can be evaluated by the interpreter<br>
For example:<br>

<code>
    set var = 3<br>
    set a = 3\*4+var<br>
    set var = 3/(var-2)+3<br>
</code>

Because of the limitations of the current lexer, numerical expressions should always be written without any
whitespace inbetween the members, therefore:<br>

<code>
    set smth = 90 + 4<br>
    set incorrect = 3 + 4 + 9 \* 3 / smth<br>
</code>

is NOT allowed.<br>

As of now, a Flex++ program as a whole is a single block and every "if" and "while" statement
also has to be followed by a block.<br><br>
For example:<br>

<code>
    if: var >= a begin<br>
    ...<br>
    end<br>
</code>

<code>
    while: var < a begin<br>
    ...<br>
    end<br>
</code>

Assignment is done in the most common way across programming languages:<br>
<code>
    |var_name| = |value|<br>
</code>

The keywords "print" and "printc" are used respectively for printing a numeric value and a character.<br>
For example:<br>

<code>
    set space = 32<br>
    print space<br>
    printc space<br>
    print space<br>
</code>

Output: 32 32<br>
Explanation: 32 is the ASCII value of a 'space' character, therefore 'print space' prints 32 and 'printc space' prints a space character.<br>

The argument we give to the "print/printc" keyword can be followed by the "eol"(End of line) keyword. It basically prints a newline character<br>
For example:
<code>
    set space = 32<br>
    print space eol<br>
    print space eol<br>
</code>
Output:<br>
32<br>
32<br><br>

You can refer to test_prog.txt to see how a Flex++ program looks.<br>




