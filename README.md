<b>Rosu Mihai Cosmin 323CA</b>

<b>Fisierele din arhiva:</b>  
- treap.h - Header-ul folosit pentru implementarea structurii de Treap.  
- treap.c - Implementarea propriu-zisa a structurii de Treap.  
- main_treap.c - Programul care citeste comenzile din teste si apeleaza functiile
corespunzatoare din implementarea Treap-ului.  

- utils.h - Macro folosit pentru a verifica daca s-a alocat in mod corect memoria.  
- linked_list.h - Header-ul folosit pentru implementarea structurii de lista  
- simpla inlantuita, folosita in cadrul implementarii Hashtable-ului.  
- linked_list.c - Implementarea propriu-zisa a listei simplu inlantuite.  
- hashtable.h - Header-ul folosit pentru implementarea Hashtable-ului.  
- hashtable.c - Implementarea propriu-zisa a structurii de Hashtable.  
- main_hashtable.c - Programul care citeste comenzile din teste si apeleaza
functiile corespunzatoare din implementarea Hashtable-ului.  

- test_generator.c - Programul folosit pentru a genera testele de dimensiune mare.  
- in/test1.in - Test in care se verifica functionalitatea operatiilor de add,
remove si modify.  
- in/test2.in - Test in care se verifica diferite scenarii pentru operatia de
modify.  
- in/test3.in - Test in care se verifica diferite scenarii pentru cele trei
operatii.  
- in/test{4, 10, 16, 22}.in - Teste in care se verifica eficienta celor doua
structuri pentru operatia de add folosind 1000/10000/100000/1000000 de numere.  
- in/test{5, 11, 17, 23}.in - Teste in care se verifica eficienta celor doua
structuri pentru operatia de modify (atunci cand se afla un singur numar in
structura) folosind 1000/10000/100000/1000000 de apeluri.  
- in/test{6, 12, 18, 24}.in - Teste in care se verifica eficienta celor doua
structuri pentru operatia de remove (si add-urile necesare) folosind
1000/10000/100000/1000000 de numere.  
- in/test{7, 13, 19, 25}.in - Teste in care se verifica eficienta celor doua
structuri pentru operatiile de add, modify si apoi remove folosind
1000/10000/100000/1000000 de numere.  
- in/test{8, 14, 20, 26}.in - Teste in care se verifica eficienta celor doua
structuri pentru operatia de add (atunci cand in structura s-a mai aflat
aceeasi cantitate de numere) folosind 1000/10000/100000/1000000 de numere.  
- in/test{9, 15, 21, 27}.in - Teste in care se verifica eficienta celor doua
structuri pentru cele trei operatii in diferite cazuri folosind
1000/10000/100000/1000000 de numere.  
- out/* - Rezultatele obtinute la rularea fiecarui algoritm.  

- Makefile - Makefile-ul folosit pentru compilarea celor doua programe. Prezinta
regulile run-p1, run-p2 si run-best, dar si reguli de build, clean si pack.  
- README - Fisier folosit pentru documentarea implementarilor si generarii
testelor.  

<b>Detalii legate de evaluare:</b>  
- In cadrul testelor am folosit o structura simpla: fiecare test are mai multe
randuri si cate o instructiune pe fiecare rand. Aceste instructiuni sunt
compuse dintr-un caracter si zero, unul sau doua numere. Operatiile pot fi:
Add = A number, Remove = R number, Modify = M number1 number2, Find = F number,
Print = P si Stop = S.
- Am mers pe ideea ca toate instructiunile vor fi corecte. O instructiune
incorecta poate fi o comanda neimplementata sau in cazul comenzilor
implementate:  
	-Add unui element deja aflat in structura (cele doua structuri
se comporta diferit in acest caz, Hashtable-ul nu modifica nimic, iar Treap-ul
ajunge sa aiba de doua ori numarul).  
	-Modify dintr-un element in alt element deja existent (acelasi
lucru ca la Add).
- Am implementat si operatia de Find, dar am folosit-o intr-un singur test incat
am implementat-o doar pentru testarea functionalitatii, dar operatia de Print
este mai folositoare.
- Am implementat operatia de Modify ca o combinatie de Remove si Add deoarece
in cazul Hashtable-ului nu aveam alta alternativa (considerand ca operatiile
sunt aplicate pe chei, cazul pe valori ar face ca algoritmii sa produca
rezultate complet diferite), iar in cazul Treap-ului ar fi trebuit sa mut
elementul modificat de la pozitia lui curenta la pozitia corecta si apoi sa
rotatiile pentru proprietatea de Heap, ceea ce e in mare parte ce se intampla
cand se apeleaza Remove si Add.

<b>Cod preluat:</b>  
- <a href="https://ocw.cs.pub.ro/courses/so/laboratoare/resurse/die">utils.h - Din cadrul laboratorului de Structuri de Date din anul 1, semestrul 2.</a>  
- <a href="https://ocw.cs.pub.ro/courses/sd-ca/laboratoare/lab-10">treap.h, treap.c - In cadrul implentarii Treap-ului am folosit scheletul de
laborator de Structuri de Date.</a>  
- <a href="https://ocw.cs.pub.ro/courses/sd-ca/laboratoare/lab-04">linked_list.h, linked_list.c, hashtable.h, hashtable.c - In cadrul implentarii
Hashtable-ului am folosit scheletul de laborator de Structuri de Date.</a>  
