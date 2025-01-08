#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

#include "task1.h"

secretariat *citeste_secretariat(const char *nume_fisier) {
    FILE* f = fopen(nume_fisier, "r");
    if (f == NULL) {
        return NULL;
    }

    // [STUDENTI]
    // 0, Andrei Popescu, 2, b
    // 1, Ioana Ionescu, 1, t

    // [MATERII]
    // 0, PCLP, Radu Bran
    // 1, USO, Maria Sandu

    // [INROLARI]
    // 1, 1, 3.10 3.80 2.10
    // 2, 2, 2.65 1.20 3.00

    secretariat* s = malloc(sizeof(secretariat));

    char line[MAX_LINE];
    int section = -1;

    while(fgets(line, MAX_LINE, f) != NULL) {

        line[strcspn(line, "\r\n")] = 0;

        if (line[0] == '\0') {
            continue;
        }

        if (strcmp(line, "[STUDENTI]") == 0) {
            section = 0;
            continue;
        } else if (strcmp(line, "[MATERII]") == 0) {
            section = 1;
            continue;
        } else if (strcmp(line, "[INROLARI]") == 0) {
            section = 2;
            continue;
        }

        if (section == 0) {
            int temp_id, temp_year;
            s->studenti = realloc(s->studenti, (s->nr_studenti + 1) * sizeof(student));
            student* new_student = &s->studenti[s->nr_studenti++];
            sscanf(line, "%d, %40[^,], %d, %c", &temp_id, new_student->nume, &temp_year, &new_student->statut);
            new_student->id = temp_id;
            new_student->an_studiu = temp_year;
        } else if (section == 1) {
            s->materii = realloc(s->materii, (s->nr_materii + 1) * sizeof(materie));
            materie* new_materie = &s->materii[s->nr_materii++];
            sscanf(line, "%d, %40[^,], %40[^,]", &new_materie->id, new_materie->nume, new_materie->nume_titular);
        } else if (section == 2) {
            s->inrolari = realloc(s->inrolari, (s->nr_inrolari + 1) * sizeof(inrolare));
            inrolare* new_inrolare = &s->inrolari[s->nr_inrolari++];
            sscanf(line, "%d, %d, %f %f %f", &new_inrolare->id_student, &new_inrolare->id_materie, &new_inrolare->note[0], &new_inrolare->note[1], &new_inrolare->note[2]);
        }
    }

    fclose(f);
    return s;
}

void adauga_student(secretariat *s, int id, char *nume, int an_studiu, char statut, float medie_generala) {
    s->nr_studenti++;
    s->studenti = realloc(s->studenti, s->nr_studenti * sizeof(student));
    s->studenti[s->nr_studenti - 1].id = id;
    strcpy(s->studenti[s->nr_studenti - 1].nume, nume);
    s->studenti[s->nr_studenti - 1].an_studiu = an_studiu;
    s->studenti[s->nr_studenti - 1].statut = statut;
    s->studenti[s->nr_studenti - 1].medie_generala = medie_generala;
}

void elibereaza_secretariat(secretariat **s) {
    if (s == NULL || *s == NULL) {
        return;
    }

    free((*s)->studenti);
    free((*s)->materii);
    free((*s)->inrolari);
    free(*s);
    *s = NULL;
}
