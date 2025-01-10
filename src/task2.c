#include "task2.h"

#define BUFFER_FIELD 7
#define BUFFER_TABLE 6
#define MAX_LINE 256
#define MAX_TABLES 256
#define MAX_FIELDS 256

int main(int argc, char *argv[]) {
    char* db = strdup(argv[1]);
    FILE* file = fopen(db, "r");
    if (!file) {
        free(db);
        return 0;
    }

    secretariat* s = citeste_secretariat(db);
    int query_count = 0;
    char query[MAX_LINE];

    if (scanf("%d", &query_count) != 1) {
        free(db);
        return 0;
    }
    getchar();

    char fields[MAX_FIELDS][MAX_FIELDS], tables[MAX_TABLES][MAX_TABLES];
    for (int i = 0; i < query_count; i++) {
        if (fgets(query, sizeof(query), stdin)) {
            query[strcspn(query, "\r\n")] = '\0';
            query[strcspn(query, ";")] = '\0';

            char field_buffer[MAX_LINE] = "";
            char table_buffer[MAX_LINE] = "";

            char* from_keyword = strstr(query, " FROM ");
            if (from_keyword) {
                *from_keyword = '\0';
                snprintf(field_buffer, sizeof(field_buffer), "%s", query + BUFFER_FIELD);
                snprintf(table_buffer, sizeof(table_buffer), "%s", from_keyword + BUFFER_TABLE);

                snprintf(fields[i], sizeof(fields[i]), "%s", field_buffer);
                snprintf(tables[i], sizeof(tables[i]), "%s", table_buffer);

                if (strcmp(tables[i], "studenti") == 0) {
                    if (strcmp(fields[i], "*") == 0) {
                        for (int i = 0; i < s->nr_studenti; i++) {
                            printf("%d %s %d %c %.2f\n",
                                s->studenti[i].id,
                                s->studenti[i].nume,
                                s->studenti[i].an_studiu,
                                s->studenti[i].statut,
                                s->studenti[i].medie_generala);
                        }
                    } else {
                        for (int j = 0; j < s->nr_studenti; j++) {
                            char field_copy[MAX_FIELDS];
                            snprintf(field_copy, sizeof(field_copy), "%s", fields[i]);
                            char* token = strtok(field_copy, " ");
                            int first = 1;
                            while (token) {
                                if (!first) {
                                    printf(" ");
                                }
                                first = 0;
                                if (strstr(token, "id") || strstr(token, " id"))
                                    printf("%d", s->studenti[j].id);
                                if (strstr(token, "nume") || strstr(token, " nume"))
                                    printf("%s", s->studenti[j].nume);
                                if (strstr(token, "an_studiu") || strstr(token, " an_studiu"))
                                    printf("%d", s->studenti[j].an_studiu);
                                if (strstr(token, "statut") || strstr(token, " statut"))
                                    printf("%c", s->studenti[j].statut);
                                if (strstr(token, "medie_generala") || strstr(token, " medie_generala"))
                                    printf("%.2f", s->studenti[j].medie_generala);
                                token = strtok(NULL, " ");
                            }
                            printf("\n");
                        }
                    }
                } else if (strcmp(tables[i], "materii") == 0) {
                    if (strcmp(fields[i], "*") == 0) {
                        for (int j = 0; j < s->nr_materii; j++) {
                            printf("%d %s %s\n",
                                s->materii[j].id,
                                s->materii[j].nume,
                                s->materii[j].nume_titular);
                        }
                    } else {
                        for (int j = 0; j < s->nr_materii; j++) {
                            char field_copy[MAX_FIELDS];
                            snprintf(field_copy, sizeof(field_copy), "%s", fields[i]);
                            char* token = strtok(field_copy, " ");
                            int first = 1;
                            while (token) {
                                if (!first) {
                                    printf(" ");
                                }
                                first = 0;
                                if (strstr(token, "id") || strstr(token, " id"))
                                    printf("%d", s->materii[j].id);
                                if (strstr(token, "nume") || strstr(token, " nume"))
                                    printf("%s", s->materii[j].nume);
                                if (strstr(token, "nume_titular") || strstr(token, " nume_titular"))
                                    printf("%s", s->materii[j].nume_titular);
                                token = strtok(NULL, " ");
                            }
                            printf("\n");
                        }
                    }
                } else if (strcmp(tables[i], "inrolari") == 0) {
                    if (strcmp(fields[i], "*") == 0) {
                        for (int j = 0; j < s->nr_inrolari; j++) {
                            printf("%d %d %.2f %.2f %.2f\n",
                                s->inrolari[j].id_student,
                                s->inrolari[j].id_materie,
                                s->inrolari[j].note[0],
                                s->inrolari[j].note[1],
                                s->inrolari[j].note[2]);
                        }
                    } else {
                        for (int j = 0; j < s->nr_inrolari; j++) {
                            char field_copy[MAX_FIELDS];
                            snprintf(field_copy, sizeof(field_copy), "%s", fields[i]);
                            char* token = strtok(field_copy, " ");
                            int first = 1;
                            while (token) {
                                if (!first) {
                                    printf(" ");
                                }
                                first = 0;
                                if (strstr(token, "id_student") || strstr(token, " id_student"))
                                    printf("%d", s->inrolari[j].id_student);
                                if (strstr(token, "id_materie") || strstr(token, " id_materie"))
                                    printf("%d", s->inrolari[j].id_materie);
                                if (strstr(token, "note") || strstr(token, " note"))
                                    printf("%.2f %.2f %.2f", s->inrolari[j].note[0],
                                    s->inrolari[j].note[1], s->inrolari[j].note[2]);
                                token = strtok(NULL, " ");
                            }
                            printf("\n");
                        }
                    }
                }
            }
        }
    }

    fclose(file);
    free(db);
    elibereaza_secretariat(&s);
    return 0;
}
