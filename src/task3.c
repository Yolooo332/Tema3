#include "task3.h"

#define BLOCK_SIZE 16

// void split_into_blocks_and_pad(char **studenti, int numar_studenti, unsigned char blocks[][BLOCK_SIZE], int *num_blocks) {
//     int total_len = 0;
//     for (int i = 0; i < numar_studenti; i++) {
//         total_len += strlen(studenti[i]);
//     }

//     *num_blocks = (total_len + BLOCK_SIZE - 1) / BLOCK_SIZE;
//     int current_block = 0, current_pos = 0;

//     for (int i = 0; i < numar_studenti; i++) {
//         int len = strlen(studenti[i]);
//         for (int j = 0; j < len; j++) {
//             blocks[current_block][current_pos++] = studenti[i][j];
//             if (current_pos == BLOCK_SIZE) {
//                 current_block++;
//                 current_pos = 0;
//             }
//         }
//     }

//     while (current_pos < BLOCK_SIZE) {
//         blocks[current_block][current_pos++] = 0x00;
//     }
// }

// void XOR(unsigned char *block, unsigned char *iv, size_t len) {
//     for (size_t i = 0; i < len; i++) {
//         block[i] ^= iv[i];
//     }
// }

// void S_BOX(unsigned char *block, void *key) {
//     for (int i = 0; i < BLOCK_SIZE; i++) {
//         block[i] = (block[i] + ((unsigned char *)key)[i % key_len]) % 256;
//     }
// }

// void P_BOX(unsigned char *block) {
//     // Dummy P_BOX implementation
//     unsigned char temp[BLOCK_SIZE];
//     for (int i = 0; i < BLOCK_SIZE; i++) {
//         temp[i] = block[(i * 3) % BLOCK_SIZE];
//     }
//     memcpy(block, temp, BLOCK_SIZE);
// }

void cripteaza_studenti(secretariat *secretariat, void *key, size_t key_len,
                        void *iv, size_t iv_len, char *cale_output) {
    // int num_blocks;
    // unsigned char blocks[100][BLOCK_SIZE];

    // split_into_blocks_and_pad(secretariat->studenti, secretariat->nr_studenti, blocks, &num_blocks);

    // XOR(blocks[0], iv, BLOCK_SIZE);
    // S_BOX(blocks[0], key);
    // P_BOX(blocks[0]);

    // for (int i = 1; i < num_blocks; i++) {
    //     XOR(blocks[i], blocks[i - 1], BLOCK_SIZE);
    //     S_BOX(blocks[i], key);
    //     P_BOX(blocks[i]);
    // }

    // FILE *output_file = fopen(cale_output, "wb");
    // if (output_file == NULL) {
    //     return;
    // }

    // for (int i = 0; i < num_blocks; i++) {
    //     fwrite(blocks[i], 1, BLOCK_SIZE, output_file);
    // }

    // fclose(output_file);
}
