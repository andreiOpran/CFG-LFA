# Emulator CFG

<br>

## Reguli de formatare al fisierului text de input:

 - fisierul trebuie sa contina 3 sectiuni: variabile, alfabetul si regulile, introduse in orice ordine dar trebuie sa urmeze anumite formatari.
 - pentru sectiunea de variabile, fiecare rand va fi ocupat de catre o variabila, iar in cazul in care variabila este cea de start se va scrie astfel: "nume_variabila,*". In sectiunea de variabile trebuie sa exista fix o variabila de start. Nu pot exista dubluri.
 - pentru sectiunea alfabetului, pe fiecare rand se va regasi o litera a alfabetului. Nu pot exista dubluri.
 - pentru sectiunea de reguli, pe prima pozitie se va regasi o variabila, iar dupa aceasta, separate prin virgula vor fi variabile sau litere din alfabet. Exemplu: "variabila_1,litera_1,variabila_2,litera_2".
 - o sectiune incepe cu "HeaderSectiune:" unde "HeaderSectiune" poate fi orice sir, si dupa ce se introduc datele conform formatarii de mai sus, pe ultima linie se introduce "End".  
 - comentariile sunt semnalate prin "#" la inceputul liniei.  
 - variabilele, alfabetul si regulile pot fi introduse in orice ordine, dar pot fi introduse o singura data.  

<br>

### Validarea fisierului consta in:

- verificare existenta variabila start sau daca exista mai multe variabile de start
- verificare daca exista o variabila care este egala cu o litera din alfabet
- verificare dubluri in variabile
- verificare dubluri in alfabet
- verificare daca fiecare element din reguli exista in variabile sau in sigma
- verificare daca exista reguli care nu incep cu o variabila
- prevenirea unui loop infinit cauzat reguli in care o variabila nu ajunge sa fie niciodata schimbata cu un sir de litere din alfabet, ci doar cu ea insasi.

<br>

## Exemplu fisier de input:

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


