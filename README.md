# Context Free Grammar Emulator

<br>

Context-Free Grammar (CFG) is a formal grammar used to describe the syntax or structure of a formal language. 

It consists of four tuples: **(V, T, P, S)**:

- **V**: The collection of **variables** or **non-terminal symbols**.
- **T**: The set of **terminals** (the basic symbols from which strings are formed).
- **P**: The **production rules** that consist of both terminals and non-terminals.
- **S**: The **starting symbol**, from which derivation begins.

<br>

## Formatting Rules for the Input Text File:

- The file must contain **three sections**: variables, the alphabet, and the rules. These sections can be in any order but must follow specific formatting rules and appear only once.
- In the **variables section**, each line should contain a variable. If the variable is the starting variable, it should be written as: `"variable_name,*"`. This section must include exactly one starting variable. Duplicate variables are not allowed.
- In the **alphabet section**, each line should contain a single letter of the alphabet. Duplicate entries are not allowed.
- In the **rules section**, the first position of each line should contain a variable, followed by variables or alphabet letters separated by commas. Example: `"variable_1,letter_1,variable_2,letter_2"`.
- A section begins with `"SectionHeader:"`, where `"SectionHeader"` can be any string. After the data is introduced in the specified format, the last line of the section should contain `"End"`.
- Comments are marked with a `"#"` at the beginning of the line.

<br>

### File Validation Includes:

- Checking if a starting variable exists or if there are multiple starting variables.
- Verifying that no variable is identical to a letter in the alphabet.
- Checking for duplicate entries in the variables.
- Checking for duplicate entries in the alphabet.
- Ensuring that every element in the rules exists either in the variables or in the alphabet.
- Verifying that every rule starts with a variable.
- Preventing infinite loops caused by rules where a variable never gets replaced with a string of letters from the alphabet but only with itself.

<br>

## Example of an input File:

<br>

\#  
\#  
\#  
Vars:  
A,*  
End  
\#  
\#  
\#  
Sigma:  
0  
1  
End  
\#  
\#  
\#  
Rules:  
A,0,A,1  
A,0,1  
End   
\#  
\#  
\#  


