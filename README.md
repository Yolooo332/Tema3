*Funcționalități Principale - TASK 1.1, 1.2, 1.3*

1. Citirea Datelor - `citeste_secretariat`

Această funcție citește datele dintr-un fișier text și le stochează în structura secretariat. Deschide fișierul și inițializează o structura secretariat. Parcurge fișierul linie cu linie, identificând secțiunile [STUDENTI], [MATERII] și [INROLARI]. Pentru fiecare secțiune, alocă dinamic memorie pentru a stoca noile intrări și utilizează realloc pentru a extinde tablourile dinamice. Pentru înrolări, actualizează media generală a studenților după citirea notelor.

2. Adăugarea unui Student - `adauga_student`

Această funcție permite adăugarea unui nou student în structura secretariat. Incrementează numărul de studenți și alocă mai multă memorie folosind realloc. Completează informațiile studentului cu parametrii furnizați.

3. Eliberarea Memoriei - `elibereaza_secretariat`

Această funcție eliberează memoria alocată pentru a preveni scurgerile de memorie.

Eliberează memoria alocată pentru studenți, materii (inclusiv numele acestora alocate dinamic) și înrolări.

Actualizează pointerul principal pentru a preveni accesarea unei memorii eliberate.

*Functionalitati Principale - TASK 2*

1. Recalcularea Mediei Generale - `recalculate_media_generala`

Această funcție parcurge lista de studenți și calculează media generală pentru fiecare student în funcție de notele din înrolări. Se iterează prin lista de studenți. Se verifică toate înrolările asociate fiecărui student. Se adună notele valide și se calculează media aritmetică. Media este rotunjită și actualizată în structura student.

2. Evaluarea Condițiilor - `evaluate_conditions`

Această funcție evaluează expresii condiționale pentru filtrarea datelor din tabelele studenti, materii și inrolari. Se analizează condițiile primite ca parametru. Se extrag câmpurile, operatorii și valorile. Se compară valorile cu datele existente în structuri. Returnează 1 dacă înregistrarea respectă condiția, altfel 0.

3. Actualizarea Câmpurilor - `update_field`

Permite modificarea valorilor unui câmp într-un tabel specificat. Se identifică tabela și se verifică validitatea câmpului. Se actualizează valoarea corespunzătoare în structura selectată. Dacă modificarea afectează notele unui student, se recalculează media generală.

4. Ștergerea Înregistrărilor - `delete_record`

Șterge înregistrările din studenti, materii sau inrolari prin marcarea acestora ca invalide. Se compară fiecare element cu condiția specificată. Se resetează valorile elementului. Pentru inrolari, recalcularea mediei generale este declanșată după ștergere.

5. Logica implementarii - `main`

Programul verifică dacă a fost furnizat un argument pentru numele fișierului de intrare. Dacă nu există argumente, programul se oprește imediat. Se alocă memorie pentru numele fișierului și se încearcă deschiderea acestuia. Dacă fișierul nu poate fi deschis, programul eliberează memoria și se încheie. Funcția citeste_secretariat() este apelată pentru a încărca datele despre studenți, materii și înrolări din fișierul specificat. Programul citește un număr întreg care reprezintă numărul de interogări de procesat. Functia `getchar();` elimină caracterele rămase în buffer, cum ar fi newline `\n`. Se declară variabile pentru a stoca interogările și componentele acestora (câmpuri, tabele, condiții, valori). Se verifică dacă interogarea începe cu SELECT. Se extrag tabelul (FROM) și condițiile (WHERE). Se afișează rezultatele în funcție de condiții folosind evaluate_conditions(). Se identifică tabela, câmpul de modificat și valoarea nouă. Se verifică condițiile (WHERE). Se actualizează datele utilizând update_field(). Dacă sunt modificate notele unui student, se recalculează media cu recalculate_media_generala(). Se identifică tabela și condiția WHERE. Se marchează înregistrările ca fiind șterse utilizând delete_record(). Dacă sunt șterse înrolări, recalculate_media_generala() este apelată pentru actualizarea mediilor studenților. Fișierul de intrare este închis. Memoria alocată pentru db este eliberată. Structura secretariat este eliberată pentru a preveni scurgeri de memorie.

*Functionalitati Principale - TASK 3*

Programul implementează un algoritm simplu de criptare pe blocuri (CBC), incluzând trei etape principale:
1. XOR - Operație între blocurile de date și un vector de inițializare (IV) sau alte blocuri anterioare.
2. S_BOX - Substituție a datelor folosind o cheie dată.
3. P_BOX - Permutarea datelor din bloc pentru a redistribui valorile.

`Functia XOR`: Primește un bloc de date și îl XOR-ează cu un vector de inițializare (IV). Este utilizată pentru a introduce variabilitate în criptare.
`Functia S_BOX`: Aplică o substituție pe fiecare octet din bloc folosind o cheie specificată. Ajută la obfuscare și îngreunează decriptarea fără cheie.
`Functia P_BOX`: Aplică o permutare pe blocul de date pentru a redistribui valorile și a mări complexitatea criptării.

`Functia cripteaza_studenti`:
Această funcție criptează lista de studenți și salvează rezultatul într-un fișier binar. Se completează numele studenților pentru a avea o lungime fixă. Se calculează dimensiunea blocurilor pentru a împărți datele în BLOCKS părți egale. Se alocă memoria necesară pentru fiecare bloc. Se adaugă padding la ultimul bloc dacă este necesar. Se aplică XOR, S_BOX, P_BOX pe primul bloc folosind IV-ul. Fiecare bloc următor este XOR-ează cu cel anterior înainte de aplicarea S_BOX și P_BOX. Blocurile criptate sunt scrise într-un fișier binar. Se eliberează memoria utilizată.
