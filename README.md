# Context Free Grammar Emulator

<br>

Designed to produce random sentences based on a specified Context-Free Grammar, this C++ project reads and
processes grammar rules from a file, then applies them iteratively to generate valid strings. It uses randomness
(Mersenne Twister algorithm) to select applicable rules, ensuring varied sentence outputs. Error handling is included
to prevent infinite loops, and the program ends processing if it detects excessive rule applications.


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


