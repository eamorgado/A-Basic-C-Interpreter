# A-Basic-C-Interpreter
A basic C interpreter for the first project of Laboratório de Programação (CC2013) 2018-2019 FCUP
This program is designed to take user instructions and execute them.
The instructions are simple/basic:

    goto <label>;----jumps execution to block with given label
    
    label <namelabel>;----creates a code label
    
    print(<info>);----displays var information or expression result
    
    read(<var>);---creates/updates a var
        Note that on the read, once you input the value do not give <;> but <\n>
    open <file>;--changes interpreter mode and reads from file 
    
    quit;--terminates execution and exits the interpreter
    
    <var>=<exp>;---creates/updates a var with the value of <exp>
    <var>+=<exp>;---adds the value of <exp> to <var> and updates <var>
    <var>-=<exp>;---subtracts the value of <exp> to <var> ,updates <var>
    <var>/=<exp>;---divides the value of <var> by <exp> and updates <var>
    <var>*=<exp>;---multiplies the value of <var> by <exp>, updates <var>
    <var>%=<exp>;---performs mod division between <var> and <exp>


This implementation has several files:

    Structures.h--representation of data
    
    ParserExpression.(h/c)--descendent recursive parser for <exp>
    
    LinkedListHashVar.(h/c)--list of variables in an index of Hashtable<var>
    HashTableVar.(h/c)--HashTable to store <var>, supported by LinkedList
    
    LinkedListHashLabel.(h/c)--list of labels in an index of Hahtable<label>
    HashTableLabel.(h/c)--HashTable to store <label>, supported by LinkedList
    
    LinkedListProgramSequence.(h/c)--list of <process> to store execution sequence
    
    CInterpreter.(h/c)--the actual interpreter, contains the main code of
        parsing a command and executing it 

    Shell(File/Interactive).(h/c)--the two modes of the interpreter, reading 
        from a given file (.txt/.text) and reading from real-time commands, each
        one of them implements an REPL (Read-Execute-Print-Loop) system, where
        the parsing and execution of a command read is done by CInterpreter
    
    Main.(h/c)--initialiser for this program, depending on the lauching method
        it picks one of the Shell(<>).c files:
            ./Main <file>.<text/txt> -->ShellFile
            ./Main -->ShellInteractive
