#include "task2.h"

#define BUFFER_FIELD 7
#define BUFFER_TABLE 6
#define BUFFER_CONDITION 4
#define BUFFER_VALUE 5
#define BUFFER_EQUAL 1
#define BUFFER_DELETE_FROM 11
#define BUFFER_DELETE_FROM_WHERE 12
#define MAX_LINE 256
#define MAX_TABLES 256
#define MAX_FIELDS 256
#define NMAX 100
#define NUMBER_OF_GRADES 3

void recalculate_media_generala(secretariat* s) {
    for (int i = 0; i < s->nr_studenti; i++) {
        float total = 0.0f;
        int count = 0;
        for (int j = 0; j < s->nr_inrolari; j++) {
            if (s->inrolari[j].id_student == s->studenti[i].id) {
                for (int k = 0; k < 3; k++) {
                    if (s->inrolari[j].note[k] != -1.00 || s->inrolari[j].note[k] != -1) {
                        total += s->inrolari[j].note[k];
                    }
                }
                count++;
            }
        }
        if (count > 0) {
            s->studenti[i].medie_generala = (float)total / (float)count;
        } else {
            s->studenti[i].medie_generala = 0.0f;
        }
        if (s->studenti[i].medie_generala == 0.0) {
            s->studenti[i].medie_generala = -1.0f;
        }
    }
}
int evaluate_conditions(char* condition, void* s_void, const char* table) {
    if (strlen(condition) == 0) {
        return 1;
    }

    char condition_copy[MAX_LINE];
    snprintf(condition_copy, sizeof(condition_copy), "%s", condition);

    char* remaining_conditions = condition_copy;
    while (remaining_conditions) {
        char* and_pos = strstr(remaining_conditions, " AND ");
        char token[MAX_LINE];

        if (and_pos) {
            long token_length = and_pos - remaining_conditions;
            snprintf(token, token_length + BUFFER_EQUAL, "%.*s", (int)token_length, remaining_conditions);
            token[token_length] = '\0';
            remaining_conditions = and_pos + BUFFER_VALUE;
        } else {
            snprintf(token, sizeof(token), "%s", remaining_conditions);
            remaining_conditions = NULL;
        }

        char* field = strtok(token, " ");
        char* operator = strtok(NULL, " ");
        char* value = strtok(NULL, "");

        if (!value) {
            value = operator;
            operator = field + strlen(field) + BUFFER_EQUAL;
            while (*operator == ' ') operator++;
            char* end_operator = operator;
            while (*end_operator && *end_operator != ' ') end_operator++;
            *end_operator = '\0';
            value = end_operator + BUFFER_EQUAL;
            while (*value == ' ') value++;
        }

        if (strcmp(table, "studenti") == 0) {
            student* s = (student*)s_void;
            int val = atoi(value);
            if (strcmp(field, "id") == 0) {
                if (strcmp(operator, "=") == 0 && s->id != val) {
                    return 0;
                } else if (strcmp(operator, ">") == 0 && s->id <= val) {
                    return 0;
                } else if (strcmp(operator, "<") == 0 && s->id >= val) {
                    return 0;
                } else if (strcmp(operator, ">=") == 0 && s->id < val) {
                    return 0;
                } else if (strcmp(operator, "<=") == 0 && s->id > val) {
                    return 0;
                } else if (strcmp(operator, "!=") == 0 && s->id == val) {
                    return 0;
                }
            }
            if (strcmp(field, "nume") == 0) {
                if (strcmp(operator, "=") == 0 && strcmp(s->nume, value) != 0) {
                    return 0;
                } else if (strcmp(operator, "!=") == 0 && strcmp(s->nume, value) == 0) {
                    return 0;
                }
            }
            if (strcmp(field, "an_studiu") == 0) {
                int val = atoi(value);
                if (strcmp(operator, "=") == 0 && s->an_studiu != val) {
                    return 0;
                } else if (strcmp(operator, ">") == 0 && s->an_studiu <= val) {
                    return 0;
                } else if (strcmp(operator, "<") == 0 && s->an_studiu >= val) {
                    return 0;
                } else if (strcmp(operator, ">=") == 0 && s->an_studiu < val) {
                    return 0;
                } else if (strcmp(operator, "<=") == 0 && s->an_studiu > val) {
                    return 0;
                } else if (strcmp(operator, "!=") == 0 && s->an_studiu == val) {
                    return 0;
                }
            }
            if (strcmp(field, "statut") == 0) {
                if (strcmp(operator, "=") == 0 && s->statut != value[0]) {
                    return 0;
                } else if (strcmp(operator, "!=") == 0 && s->statut == value[0]) {
                    return 0;
                }
            }
            if (strcmp(field, "medie_generala") == 0) {
                float val_float = (float)atof(value);
                if (strcmp(operator, "=") == 0 && s->medie_generala != val_float) {
                    return 0;
                } else if (strcmp(operator, ">") == 0 && s->medie_generala <= val_float) {
                    return 0;
                } else if (strcmp(operator, "<") == 0 && s->medie_generala >= val_float) {
                    return 0;
                } else if (strcmp(operator, ">=") == 0 && s->medie_generala < val_float) {
                    return 0;
                } else if (strcmp(operator, "<=") == 0 && s->medie_generala > val_float) {
                    return 0;
                } else if (strcmp(operator, "!=") == 0 && s->medie_generala == val_float) {
                    return 0;
                }
            }
        } else if (strcmp(table, "materii") == 0) {
            materie* s = (materie*)s_void;
            int val = atoi(value);
            if (strcmp(field, "id") == 0) {
                if (strcmp(operator, "=") == 0 && s->id != val) {
                    return 0;
                } else if (strcmp(operator, ">") == 0 && s->id <= val) {
                    return 0;
                } else if (strcmp(operator, "<") == 0 && s->id >= val) {
                    return 0;
                } else if (strcmp(operator, ">=") == 0 && s->id < val) {
                    return 0;
                } else if (strcmp(operator, "<=") == 0 && s->id > val) {
                    return 0;
                } else if (strcmp(operator, "!=") == 0 && s->id == val) {
                    return 0;
                }
            }
            if (strcmp(field, "nume") == 0) {
                if (strcmp(operator, "=") == 0 && strcmp(s->nume, value) != 0) {
                    return 0;
                } else if (strcmp(operator, "!=") == 0 && strcmp(s->nume, value) == 0) {
                    return 0;
                }
            }
            if (strcmp(field, "nume_titular") == 0) {
                if (strcmp(operator, "=") == 0 && strcmp(s->nume_titular, value) != 0) {
                    return 0;
                } else if (strcmp(operator, "!=") == 0 && strcmp(s->nume_titular, value) == 0) {
                    return 0;
                }
            }
        } else if (strcmp(table, "inrolari") == 0) {
            inrolare* s = (inrolare*)s_void;
            int val = atoi(value);
            if (strcmp(field, "id_student") == 0) {
                if (strcmp(operator, "=") == 0 && s->id_student != val) {
                    return 0;
                } else if (strcmp(operator, ">") == 0 && s->id_student <= val) {
                    return 0;
                } else if (strcmp(operator, "<") == 0 && s->id_student >= val) {
                    return 0;
                } else if (strcmp(operator, ">=") == 0 && s->id_student < val) {
                    return 0;
                } else if (strcmp(operator, "<=") == 0 && s->id_student > val) {
                    return 0;
                } else if (strcmp(operator, "!=") == 0 && s->id_student == val) {
                    return 0;
                }
            } else if (strcmp(field, "id_materie") == 0) {
                int val = atoi(value);
                if (strcmp(operator, "=") == 0 && s->id_materie != val) {
                    return 0;
                } else if (strcmp(operator, ">") == 0 && s->id_materie <= val) {
                    return 0;
                } else if (strcmp(operator, "<") == 0 && s->id_materie >= val) {
                    return 0;
                } else if (strcmp(operator, ">=") == 0 && s->id_materie < val) {
                    return 0;
                } else if (strcmp(operator, "<=") == 0 && s->id_materie > val) {
                    return 0;
                } else if (strcmp(operator, "!=") == 0 && s->id_materie == val) {
                    return 0;
                }
            } else if (strcmp(field, "note") == 0) {
                float val_float = (float)atof(value);
                for (int i = 0; i < NUMBER_OF_GRADES; i++) {
                    if (strcmp(operator, "=") == 0 && s->note[i] != val_float) {
                        return 0;
                    } else if (strcmp(operator, ">") == 0 && s->note[i] <= val_float) {
                        return 0;
                    } else if (strcmp(operator, "<") == 0 && s->note[i] >= val_float) {
                        return 0;
                    } else if (strcmp(operator, ">=") == 0 && s->note[i] < val_float) {
                        return 0;
                    } else if (strcmp(operator, "<=") == 0 && s->note[i] > val_float) {
                        return 0;
                    } else if (strcmp(operator, "!=") == 0 && s->note[i] == val_float) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
void update_field(void* s_void, const char* table, const char* field, const char* value) {
    int val = atoi(value);
    float val_float = (float)atof(value);

    char stripped_value[MAX_LINE];
    if (value[0] == '"' && value[strlen(value) - 1] == '"') {
        strncpy(stripped_value, value + 1, strlen(value) - 2);
        stripped_value[strlen(value) - 2] = '\0';
    } else {
        strncpy(stripped_value, value, sizeof(stripped_value));
        stripped_value[sizeof(stripped_value) - 1] = '\0';
    }

    if (strcmp(table, "studenti") == 0) {
        student* s = (student*)s_void;
        if (strcmp(field, "id ") == 0) {
            s->id = val;
        } else if (strcmp(field, "nume ") == 0) {
            snprintf(s->nume, sizeof(s->nume), "%s", stripped_value);
        } else if (strcmp(field, "an_studiu ") == 0) {
            s->an_studiu = val;
        } else if (strcmp(field, "statut ") == 0) {
            s->statut = value[0];
        } else if (strcmp(field, "medie_generala ") == 0) {
            s->medie_generala = val_float;
        }
    } else if (strcmp(table, "materii") == 0) {
        materie* s = (materie*)s_void;
        if (strcmp(field, "id ") == 0) {
            s->id = val;
        } else if (strcmp(field, "nume ") == 0) {
            snprintf(s->nume, sizeof(s->nume), "%s", stripped_value);
        } else if (strcmp(field, "nume_titular ") == 0) {
            snprintf(s->nume_titular, sizeof(s->nume_titular), "%s", stripped_value);
        }
    } else if (strcmp(table, "inrolari") == 0) {
        inrolare* s = (inrolare*)s_void;
        if (strcmp(field, "id_student ") == 0) {
            s->id_student = val;
        } else if (strcmp(field, "id_materie ") == 0) {
            s->id_materie = val;
        } else if (strcmp(field, "note ") == 0) {
            sscanf(value, "%f %f %f", &s->note[0], &s->note[1], &s->note[2]);
        }
    }
}
void delete_record(void* s_void, const char* table) {
    if (strcmp(table, "studenti") == 0) {
        student* s = (student*)s_void;
        s->id = -1;
        s->nume[0] = '\0';
        s->an_studiu = -1;
        s->statut = '\0';
        s->medie_generala = -1.0f;
    } else if (strcmp(table, "materii") == 0) {
        materie* s = (materie*)s_void;
        s->id = -1;
        s->nume[0] = '\0';
        s->nume_titular[0] = '\0';
    } else if (strcmp(table, "inrolari") == 0) {
        inrolare* s = (inrolare*)s_void;
        s->id_student = -1;
        s->id_materie = -1;
        for (int i = 0; i < NUMBER_OF_GRADES; i++) {
            s->note[i] = -1;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }

    char* db = strdup(argv[1]);
    FILE* file = fopen(db, "r");
    if (!file) {
        free(db);
        return 0;
    }

    secretariat* s = citeste_secretariat(db);
    int query_count = 0;
    char query[MAX_TABLES] = {0};

    if (scanf("%d", &query_count) != 1) {
        free(db);
        return 0;
    }
    getchar();

    char fields[NMAX][NMAX], tables[NMAX][NMAX], conditions[NMAX][NMAX], values[NMAX][NMAX];
    for (int i = 0; i < query_count; i++) {
        if (fgets(query, sizeof(query), stdin)) {
            query[strcspn(query, "\r\n")] = '\0';
            query[strcspn(query, ";")] = '\0';

            char field_buffer[MAX_FIELDS] = {0};
            char table_buffer[MAX_TABLES] = {0};
            char condition_buffer[MAX_LINE] = {0};
            char value_buffer[MAX_LINE] = {0};

            if (strncmp(query, "SELECT", BUFFER_TABLE) == 0) {
                char* from_keyword = strstr(query, " FROM ");
                if (from_keyword) {
                    *from_keyword = '\0';
                    snprintf(field_buffer, sizeof(field_buffer), "%s", query + BUFFER_FIELD);

                    char* where_keyword = strstr(from_keyword + BUFFER_TABLE, " WHERE ");
                    if (where_keyword) {
                        *where_keyword = '\0';
                        snprintf(table_buffer, sizeof(table_buffer), "%s", from_keyword + BUFFER_TABLE);
                        snprintf(condition_buffer, sizeof(condition_buffer), "%s", where_keyword + BUFFER_FIELD);
                    } else {
                        snprintf(table_buffer, sizeof(table_buffer), "%s", from_keyword + BUFFER_TABLE);
                    }

                    snprintf(fields[i], sizeof(fields[i]), "%s", field_buffer);
                    snprintf(tables[i], sizeof(tables[i]), "%s", table_buffer);
                    snprintf(conditions[i], sizeof(conditions[i]), "%s", condition_buffer);

                    if (strcmp(tables[i], "studenti") == 0) {
                        if (strcmp(fields[i], "*") == 0) {
                            for (int j = 0; j < s->nr_studenti; j++) {
                                if (strlen(condition_buffer) == 0 ||
                                    evaluate_conditions(condition_buffer, &s->studenti[j], "studenti")) {
                                    if (s->studenti[j].id != -1 || s->studenti[j].nume[0] != '\0' ||
                                        s->studenti[j].an_studiu != -1 || s->studenti[j].statut != '\0' ||
                                        s->studenti[j].medie_generala != -1) {
                                        printf("%d %s %d %c %.2f\n",
                                            s->studenti[j].id,
                                            s->studenti[j].nume,
                                            s->studenti[j].an_studiu,
                                            s->studenti[j].statut,
                                            s->studenti[j].medie_generala);
                                    }
                                }
                            }
                        } else {
                            for (int j = 0; j < s->nr_studenti; j++) {
                                if (strlen(condition_buffer) == 0 ||
                                    evaluate_conditions(condition_buffer, &s->studenti[j], "studenti")) {
                                    char field_copy[NMAX];
                                    snprintf(field_copy, sizeof(field_copy), "%s", fields[i]);
                                    char* token = strtok(field_copy, " ");
                                    int first = 1;
                                    while (token) {
                                        if (!first) {
                                            if (s->studenti[j].id != -1 || s->studenti[j].nume[0] != '\0' ||
                                                s->studenti[j].an_studiu != -1 || s->studenti[j].statut != '\0' ||
                                                s->studenti[j].medie_generala != -1) {
                                                printf(" ");
                                            }
                                        }
                                        first = 0;
                                        if (strstr(token, "id") || strstr(token, " id"))
                                            if (s->studenti[j].id != -1)
                                                printf("%d", s->studenti[j].id);
                                        if (strstr(token, "nume") || strstr(token, " nume"))
                                            if (s->studenti[j].nume[0] != '\0')
                                                printf("%s", s->studenti[j].nume);
                                        if (strstr(token, "an_studiu") || strstr(token, " an_studiu"))
                                            if (s->studenti[j].an_studiu != -1)
                                                printf("%d", s->studenti[j].an_studiu);
                                        if (strstr(token, "statut") || strstr(token, " statut"))
                                            if (s->studenti[j].statut != '\0')
                                                printf("%c", s->studenti[j].statut);
                                        if (strstr(token, "medie_generala") || strstr(token, " medie_generala"))
                                            if (s->studenti[j].medie_generala != -1 ||
                                                s->studenti[j].medie_generala != -1.00)
                                                printf("%.2f", s->studenti[j].medie_generala);
                                        token = strtok(NULL, " ");
                                    }
                                    if (s->studenti[j].id != -1 || s->studenti[j].nume[0] != '\0' ||
                                        s->studenti[j].an_studiu != -1 || s->studenti[j].statut != '\0' ||
                                        s->studenti[j].medie_generala != -1) {
                                        printf("\n");
                                    }
                                }
                            }
                        }
                    } else if (strcmp(tables[i], "materii") == 0) {
                        if (strcmp(fields[i], "*") == 0) {
                            for (int j = 0; j < s->nr_materii; j++) {
                                if (strlen(condition_buffer) == 0 ||
                                    evaluate_conditions(condition_buffer, &s->materii[j], "materii")) {
                                    if (s->materii[j].id != -1 || s->materii[j].nume[0] != '\0' ||
                                        s->materii[j].nume_titular[0] != '\0') {
                                        printf("%d %s %s\n",
                                            s->materii[j].id,
                                            s->materii[j].nume,
                                            s->materii[j].nume_titular);
                                    }
                                }
                            }
                        } else {
                            for (int j = 0; j < s->nr_materii; j++) {
                                if (strlen(condition_buffer) == 0 ||
                                    evaluate_conditions(condition_buffer, &s->materii[j], "materii")) {
                                    char field_copy[NMAX];
                                    snprintf(field_copy, sizeof(field_copy), "%s", fields[i]);
                                    char* token = strtok(field_copy, " ");
                                    int first = 1;
                                    while (token) {
                                        if (!first) {
                                            if (s->materii[j].id != -1 || s->materii[j].nume[0] != '\0' ||
                                                s->materii[j].nume_titular[0] != '\0') {
                                                printf(" ");
                                            }
                                        }
                                        first = 0;
                                        if (strcmp(token, "id") == 0)
                                            if (s->materii[j].id != -1)
                                                printf("%d", s->materii[j].id);
                                        if (strcmp(token, "nume") == 0)
                                            if (s->materii[j].nume[0] != '\0')
                                                printf("%s", s->materii[j].nume);
                                        if (strcmp(token, "nume_titular") == 0)
                                            if (s->materii[j].nume_titular[0] != '\0')
                                                printf("%s", s->materii[j].nume_titular);
                                        token = strtok(NULL, " ");
                                    }
                                    if (s->materii[j].id != -1 || s->materii[j].nume[0] != '\0' ||
                                        s->materii[j].nume_titular[0] != '\0') {
                                        printf("\n");
                                    }
                                }
                            }
                        }
                    } else if (strcmp(tables[i], "inrolari") == 0) {
                        if (strcmp(fields[i], "*") == 0) {
                            for (int j = 0; j < s->nr_inrolari; j++) {
                                if (strlen(condition_buffer) == 0 ||
                                    evaluate_conditions(condition_buffer, &s->inrolari[j], "inrolari")) {
                                    if (s->inrolari[j].id_student != -1 || s->inrolari[j].id_materie != -1 ||
                                        s->inrolari[j].note[0] != -1 || s->inrolari[j].note[1] != -1 ||
                                        s->inrolari[j].note[2] != -1) {
                                        printf("%d %d %.2f %.2f %.2f\n",
                                            s->inrolari[j].id_student,
                                            s->inrolari[j].id_materie,
                                            s->inrolari[j].note[0],
                                            s->inrolari[j].note[1],
                                            s->inrolari[j].note[2]);
                                    }
                                }
                            }
                        } else {
                            for (int j = 0; j < s->nr_inrolari; j++) {
                                if (strlen(condition_buffer) == 0 ||
                                    evaluate_conditions(condition_buffer, &s->inrolari[j], "inrolari")) {
                                    char field_copy[NMAX];
                                    snprintf(field_copy, sizeof(field_copy), "%s", fields[i]);
                                    char* token = strtok(field_copy, " ");
                                    int first = 1;
                                    while (token) {
                                        if (!first) {
                                            if (s->inrolari[j].id_student != -1 || s->inrolari[j].id_materie != -1 ||
                                                s->inrolari[j].note[0] != -1 || s->inrolari[j].note[1] != -1 ||
                                                s->inrolari[j].note[2] != -1) {
                                                printf(" ");
                                            }
                                        }
                                        first = 0;
                                        if (strstr(token, "id_student") || strstr(token, " id_student"))
                                            if (s->inrolari[j].id_student != -1)
                                                printf("%d", s->inrolari[j].id_student);
                                        if (strstr(token, "id_materie") || strstr(token, " id_materie"))
                                            if (s->inrolari[j].id_materie != -1)
                                                printf("%d", s->inrolari[j].id_materie);
                                        if (strstr(token, "note") || strstr(token, " note"))
                                            if (s->inrolari[j].note[0] != -1 &&
                                                s->inrolari[j].note[1] != -1 && s->inrolari[j].note[2] != -1)
                                                printf("%.2f %.2f %.2f",
                                                    s->inrolari[j].note[0],
                                                    s->inrolari[j].note[1],
                                                    s->inrolari[j].note[2]);
                                        token = strtok(NULL, " ");
                                    }
                                    if (s->inrolari[j].id_student != -1 || s->inrolari[j].id_materie != -1 ||
                                        s->inrolari[j].note[0] != -1 || s->inrolari[j].note[1] != -1 ||
                                        s->inrolari[j].note[2] != -1) {
                                        printf("\n");
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (strncmp(query, "UPDATE", BUFFER_TABLE) == 0) {
                char* set_keyword = strstr(query, " SET ");
                if (set_keyword) {
                    *set_keyword = '\0';
                    snprintf(table_buffer, sizeof(table_buffer), "%s", query + BUFFER_FIELD);

                    char* where_keyword = strstr(set_keyword + BUFFER_VALUE, " WHERE ");
                    if (where_keyword) {
                        *where_keyword = '\0';
                        snprintf(field_buffer, sizeof(field_buffer), "%s", set_keyword + BUFFER_VALUE);
                        snprintf(condition_buffer, sizeof(condition_buffer), "%s", where_keyword + BUFFER_FIELD);
                    } else {
                        snprintf(field_buffer, sizeof(field_buffer), "%s", set_keyword + BUFFER_VALUE);
                    }

                    char* equal_sign = strchr(field_buffer, '=');
                    if (equal_sign) {
                        *equal_sign = '\0';
                        snprintf(value_buffer, sizeof(value_buffer), "%s", equal_sign + BUFFER_EQUAL);

                        while (isspace((unsigned char)*value_buffer)) {
                            memmove(value_buffer, value_buffer + BUFFER_EQUAL, strlen(value_buffer));
                        }
                    }

                    snprintf(fields[i], sizeof(fields[i]), "%s", field_buffer);
                    snprintf(tables[i], sizeof(tables[i]), "%s", table_buffer);
                    snprintf(conditions[i], sizeof(conditions[i]), "%s", condition_buffer);
                    snprintf(values[i], sizeof(values[i]), "%s", value_buffer);

                    if (strcmp(tables[i], "studenti") == 0) {
                        for (int j = 0; j < s->nr_studenti; j++) {
                            if (strlen(condition_buffer) == 0 ||
                                evaluate_conditions(condition_buffer, &s->studenti[j], "studenti")) {
                                update_field(&s->studenti[j], "studenti", fields[i], values[i]);
                            }
                        }
                    } else if (strcmp(tables[i], "materii") == 0) {
                        for (int j = 0; j < s->nr_materii; j++) {
                            if (strlen(condition_buffer) == 0 ||
                                evaluate_conditions(condition_buffer, &s->materii[j], "materii")) {
                                update_field(&s->materii[j], "materii", fields[i], values[i]);
                            }
                        }
                    } else if (strcmp(tables[i], "inrolari") == 0) {
                        for (int j = 0; j < s->nr_inrolari; j++) {
                            if (strlen(condition_buffer) == 0 ||
                                evaluate_conditions(condition_buffer, &s->inrolari[j], "inrolari")) {
                                update_field(&s->inrolari[j], "inrolari", fields[i], values[i]);
                                recalculate_media_generala(s);
                            }
                        }
                    }
                }
            } else if (strncmp(query, "DELETE FROM", BUFFER_DELETE_FROM) == 0) {
                char* where_keyword = strstr(query, " WHERE ");
                if (where_keyword) {
                    *where_keyword = '\0';
                    snprintf(table_buffer, sizeof(table_buffer), "%s", query + BUFFER_DELETE_FROM_WHERE);
                    snprintf(condition_buffer, sizeof(condition_buffer), "%s", where_keyword + BUFFER_FIELD);
                } else {
                    snprintf(table_buffer, sizeof(table_buffer), "%s", query + BUFFER_DELETE_FROM_WHERE);
                }

                snprintf(tables[i], sizeof(tables[i]), "%s", table_buffer);
                snprintf(conditions[i], sizeof(conditions[i]), "%s", condition_buffer);

                if (strcmp(tables[i], "studenti") == 0) {
                    for (int j = 0; j < s->nr_studenti; j++) {
                        if (strlen(condition_buffer) == 0 ||
                            evaluate_conditions(condition_buffer, &s->studenti[j], "studenti")) {
                            delete_record(&s->studenti[j], "studenti");
                        }
                    }
                } else if (strcmp(tables[i], "materii") == 0) {
                    for (int j = 0; j < s->nr_materii; j++) {
                        if (strlen(condition_buffer) == 0 ||
                            evaluate_conditions(condition_buffer, &s->materii[j], "materii")) {
                            delete_record(&s->materii[j], "materii");
                        }
                    }
                } else if (strcmp(tables[i], "inrolari") == 0) {
                    for (int j = 0; j < s->nr_inrolari; j++) {
                        if (strlen(condition_buffer) == 0 ||
                            evaluate_conditions(condition_buffer, &s->inrolari[j], "inrolari")) {
                            delete_record(&s->inrolari[j], "inrolari");
                            recalculate_media_generala(s);
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
