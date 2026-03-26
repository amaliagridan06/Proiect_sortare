Proiect_sortare: Compararea algoritmilor de sortare studiati
Student:Gridan Amalia-Maria

Descriere:
Acest proiect face un experiment pentru a studia cei mai utilizati algoritmi de sortare. Obiectivul este să vedem cât timp le ia să sorteze diferite seturi de date și să aflăm cât de bine funcționează fiecare în diverse situații (caz mediu,cel mai bun caz și cel mai rău caz).

Algoritmi Implementați:
Am decis să folosesc următorii algoritmi:
-Bubble Sort - ușor de înțeles,dar nu prea eficient pentru liste mari;
-Insertion Sort - foarte rapid pe liste mici sau care sunt aproape ordonate.
-Merge Sort (Interclasare) - Stabil;
-Quick Sort - cel mai rapid în general,dar ar putea să nu se descurce bine cu datele care sunt deja sortate.
-Radix Sort - un algoritm care nu compară,excelent pentru numere naturale.

Metodologie de Testare:
Conform cerințelor,am testat algoritmii pe câteva tipuri diferite de date:
 -Random: numere create aleatoriu;
-Sorted: listă deja ordonată crescător;
-Reverse: listă ordonată descrescător;
-Almost Sorted: listă aproape ordonată;
-Plate: liste cu valori repetate.

Concluzii Experimentale:
După ce am terminat testele,am observat că
sortarea prin inserție este mai eficientă decât sortarea rapidă pentru liste foarte mici și pentru cele care sunt aproape sortate;
sortarea rapidă își pierde din viteză atunci când datele sunt deja sortate (deoarece alege pivotul din ultima poziție).
Sortarea radix este cea mai constantă, timpul necesar pentru a o rula depinde de câte cifre are un număr,nu de cum sunt aranjate elementele.
