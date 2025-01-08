#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define NAME_MAX 40
#define ROUND_PRECISION 100
#define ROUND_PRECISION_FLOAT 100.0f
#define ROUND_HALF_FLOAT 0.5f
#define ROUND_HALF 0.5

#include "task1.h"

float round_two(float valoare) {
    return ((float)((int)(valoare * ROUND_PRECISION + ROUND_HALF_FLOAT))) / ROUND_PRECISION_FLOAT;
}

secretariat *citeste_secretariat(const char *nume_fisier) {
    FILE* f = fopen(nume_fisier, "r");
    if (f == NULL) {
        return NULL;
    }

    secretariat* s = malloc(sizeof(secretariat));

    char line[MAX_LINE];
    int section = -1;

    while (fgets(line, MAX_LINE, f) != NULL) {
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
            int temp_id = 0, temp_year = 0;
            s->studenti = realloc(s->studenti, (s->nr_studenti + 1) * sizeof(student));
            if (!s->studenti) {
                fclose(f);
                free(s);
                return NULL;
            }
            student* new_student = &s->studenti[s->nr_studenti++];
            sscanf(line, "%d, %40[^,], %d, %c", &temp_id, new_student->nume, &temp_year, &new_student->statut);
            new_student->id = temp_id;
            new_student->an_studiu = temp_year;
            new_student->medie_generala = 0;
        } else if (section == 1) {
            char temp_name[NAME_MAX], temp_titular[NAME_MAX];
            s->materii = realloc(s->materii, (s->nr_materii + 1) * sizeof(materie));
            if (!s->materii) {
                fclose(f);
                free(s->studenti);
                free(s);
                return NULL;
            }
            materie* new_materie = &s->materii[s->nr_materii++];
            sscanf(line, "%d, %40[^,], %40[^,]", &new_materie->id, temp_name, temp_titular);
            new_materie->nume = strdup(temp_name);
            new_materie->nume_titular = strdup(temp_titular);
        } else if (section == 2) {
            s->inrolari = realloc(s->inrolari, (s->nr_inrolari + 1) * sizeof(inrolare));
            if (!s->inrolari) {
                fclose(f);
                free(s->studenti);
                free(s->materii);
                free(s);
                return NULL;
            }
            inrolare* new_inrolare = &s->inrolari[s->nr_inrolari++];
            sscanf(line, "%d, %d, %f %f %f",
            &new_inrolare->id_student, &new_inrolare->id_materie,
            &new_inrolare->note[0], &new_inrolare->note[1], &new_inrolare->note[2]);

            int* numar_materii = malloc(s->nr_studenti * sizeof(int));
            for (int i = 0; i < s->nr_inrolari; i++) {
                numar_materii[s->inrolari[i].id_student]++;
            }
            for (int i = 0; i < s->nr_inrolari; i++) {
                inrolare *inr = &s->inrolari[i];
                for (int j = 0; j < s->nr_studenti; j++) {
                    if (s->studenti[j].id == inr->id_student) {
                        s->studenti[j].medie_generala = inr->note[0] + inr->note[1] + inr->note[2];
                        break;
                    }
                }
            }
            for (int i = 0; i < s->nr_studenti; i++) {
                if (numar_materii[i] > 0) {
                    s->studenti[i].medie_generala /= (float)(numar_materii[i]);
                    s->studenti[i].medie_generala = round_two(s->studenti[i].medie_generala);
                }
            }
        }
    }

    fclose(f);
    return s;
}

void adauga_student(secretariat *s, int id, char *nume, int an_studiu, char statut, float medie_generala) {
    s->nr_studenti++;
    s->studenti = realloc(s->studenti, s->nr_studenti * sizeof(student));
    s->studenti[s->nr_studenti - 1].id = id;
    snprintf(s->studenti[s->nr_studenti - 1].nume, NAME_MAX, "%s", nume);
    s->studenti[s->nr_studenti - 1].an_studiu = an_studiu;
    s->studenti[s->nr_studenti - 1].statut = statut;
    s->studenti[s->nr_studenti - 1].medie_generala = medie_generala;
}

void elibereaza_secretariat(secretariat **s) {
    if (s == NULL || *s == NULL) {
        return;
    }

    free((*s)->studenti);

    if ((*s)->materii) {
        for (int i = 0; i < (*s)->nr_materii; i++) {
            free((*s)->materii[i].nume);
            free((*s)->materii[i].nume_titular);
        }
        free((*s)->materii);
    }

    free((*s)->inrolari);

    free(*s);
    *s = NULL;
}
