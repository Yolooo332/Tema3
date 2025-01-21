#include "task3.h"
#define BLOCKS 4

unsigned char* XOR(unsigned char* block, size_t block_size, unsigned char* iv, size_t iv_size) {
    unsigned char* result = malloc(block_size * sizeof(unsigned char));
    if (!result) {
        return NULL;
    }
    for (int i = 0; i < block_size; i++) {
        result[i] = block[i] ^ iv[i % iv_size];
    }
    return result;
}

unsigned char* S_BOX(unsigned char* block, size_t block_size, unsigned char* key, size_t key_size) {
    return XOR(block, block_size, key, key_size);
}

unsigned char* P_BOX(unsigned char* block, size_t block_size) {
    unsigned char* result = malloc(block_size * sizeof(unsigned char));
    if (!result) {
        return NULL;
    }
    for (int i = 0; i < block_size; i++) {
        result[i] = block[(i * (block_size - 1) + 2) % block_size];
    }
    return result;
}

void cripteaza_studenti(secretariat *secretariat, void *key,
    size_t key_len, void *iv, size_t iv_len, char *cale_output) {
    FILE* output = fopen(cale_output, "wb");
    if (output == NULL) {
        return;
    }

    for (int i = 0; i < secretariat->nr_studenti; i++) {
        size_t name_length = strlen(secretariat->studenti[i].nume);
        memset(secretariat->studenti[i].nume + name_length + 1, 0,
        MAX_STUDENT_NAME - name_length - 1);
    }

    size_t students_size = secretariat->nr_studenti * sizeof(student);
    size_t block_size = students_size / BLOCKS;
    if (students_size % BLOCKS != 0) {
        block_size = students_size / BLOCKS + 1;
    }

    unsigned char* students_bytes = (unsigned char*)secretariat->studenti;
    unsigned char** block = malloc(BLOCKS * sizeof(unsigned char*));
    size_t padding = students_size - block_size * 3;
    for (int i = 0; i < BLOCKS; i++) {
        block[i] = malloc(block_size * sizeof(unsigned char));
        for (int j = 0; j < block_size; j++) {
            if (i == 3 && j >= padding) {
                block[i][j] = 0;
            } else {
                block[i][j] = students_bytes[block_size * i + j];
            }
        }
    }

    block[0] = XOR(block[0], block_size, iv, iv_len);
    block[0] = S_BOX(block[0], block_size, key, key_len);
    block[0] = P_BOX(block[0], block_size);

    for (int i = 1; i < BLOCKS; i++) {
        block[i] = XOR(block[i], block_size, block[i - 1], block_size);
        block[i] = S_BOX(block[i], block_size, key, key_len);
        block[i] = P_BOX(block[i], block_size);
    }

    for (int i = 0; i < BLOCKS; i++) {
        fwrite(block[i], sizeof(unsigned char), block_size, output);
        free(block[i]);
    }

    free(block);
    fclose(output);
}
