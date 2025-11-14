#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define PAGE_SIZE 4096

int main() {
    FILE* file = fopen("ctiny.db", "wb"); // wb = write binary
    if (!file) {
        printf("Erro ao criar arquivo tiny.db\n");
        return 1;
    }
 
    uint8_t page0[PAGE_SIZE]; // O arry é criado aqui | unsigned 8-bit integer - 1 byte  
    memset(page0, 0, PAGE_SIZE); // Preenche tudo com zeros

    // --- Campos da página 0 ---
    page0[0] = 'T';              // Magic byte 1
    page0[1] = 'D';              // Magic byte 2
    page0[2] = 1;                // Versão baixa
    page0[3] = 0;                // Versão alta (1 = 0x0001)

    // page_size (4 bytes, little-endian)
    page0[4] = PAGE_SIZE & 0xFF;
    page0[5] = (PAGE_SIZE >> 8) & 0xFF;
    page0[6] = (PAGE_SIZE >> 16) & 0xFF;
    page0[7] = (PAGE_SIZE >> 24) & 0xFF;

    // total_pages = 1
    page0[8]  = 1;
    page0[9]  = 0;
    page0[10] = 0;
    page0[11] = 0;

    // total_records = 0
    page0[12] = 0;
    page0[13] = 0;
    page0[14] = 0;
    page0[15] = 0;

    // Escreve a página 0 no arquivo
    fwrite(page0, PAGE_SIZE, 1, file);

    fclose(file);
    printf("tiny.db criado com página 0!\n");

  

    return 0;
}
