#include <stdio.h>
#include <stdlib.h>

#include "task1.h"

secretariat *citeste_secretariat(const char *nume_fisier) {
    FILE* f = fopen(nume_fisier, "r");
    if (f == NULL) {
        return NULL;
    }
    secretariat* s = malloc(sizeof(secretariat));
    fscanf(f, "%d", &s->nr_studenti);
    s->studenti = malloc(s->nr_studenti * sizeof(student));
    for (int i = 0; i < s->nr_studenti; i++) {
        fscanf(f, "%d", &s->studenti[i].id);
        fscanf(f, "%s", s->studenti[i].nume);
        fscanf(f, "%d", &s->studenti[i].an_studiu);
        fscanf(f, "%c", &s->studenti[i].statut);
        fscanf(f, "%f", &s->studenti[i].medie_generala);
    }
    fclose(f);
    return s;
}

void adauga_student(secretariat *s, int id, char *nume, int an_studiu, char statut, float medie_generala) {
    // TODO(student): 1.2
}

void elibereaza_secretariat(secretariat **s) {
    // TODO(student): 1.3
}
