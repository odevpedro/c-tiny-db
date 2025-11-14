#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define PAGE_SIZE 4096
#define BITMAP_SIZE 16   // 16 bytes = 128 bits = 128 slots de registro
#define REG_SIZE 36      // cada registro tem 36 bytes

void create_page0(FILE* file) {
    uint8_t page0[PAGE_SIZE];
    memset(page0, 0, PAGE_SIZE);

    // Magic number
    page0[0] = 'T';
    page0[1] = 'D';

    // Versão 1.0
    page0[2] = 1;
    page0[3] = 0;

    // page_size (4096) em 4 bytes
    page0[4] = PAGE_SIZE & 0xFF;
    page0[5] = (PAGE_SIZE >> 8) & 0xFF;
    page0[6] = (PAGE_SIZE >> 16) & 0xFF;
    page0[7] = (PAGE_SIZE >> 24) & 0xFF;

    // total_pages = 2  (Página 0 + Página 1)
    page0[8] = 2;
    page0[9] = 0;
    page0[10] = 0;
    page0[11] = 0;

    // total_records = 0
    page0[12] = 0;
    page0[13] = 0;
    page0[14] = 0;
    page0[15] = 0;

    fwrite(page0, PAGE_SIZE, 1, file);
}

void create_page1(FILE* file) {
    uint8_t page1[PAGE_SIZE];
    memset(page1, 0, PAGE_SIZE);

    // page_type = 'D' (Data Page)
    page1[0] = 'D';

    // num_records = 0 (2 bytes)
    page1[1] = 0;
    page1[2] = 0;

    // bitmap já está zerado pelo memset (16 bytes a partir do offset 3)

    // resto da página = slots de registros (todos zerados)

    fwrite(page1, PAGE_SIZE, 1, file);
}

int main() {
    FILE* file = fopen("ctiny.db", "wb");
    if (!file) {
        printf("Erro ao criar tiny.db\n");
        return 1;
    }

    create_page0(file);
    create_page1(file);

    fclose(file);
    printf("tiny.db criado com Página 0 e Página 1!\n");
    return 0;
}
