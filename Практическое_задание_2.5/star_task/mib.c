#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_NOF_MIB 64

typedef enum scs {
    scs15or60 = 0,
    scs30or120 = 1
} scs_e;

// заполнить и выставить сколько бит занимает поле
// https://www.sharetechnote.com/html/5G/5G_Mib_Sib.html MIB ::= SEQUENCE
/*
MIB ::= SEQUENCE {
    systemFrameNumber                   BIT STRING (SIZE (6)), => 6 bits
    subCarrierSpacingCommon             ENUMERATED {scs15or60, scs30or120}, => 1 bit
    ssb-SubcarrierOffset                INTEGER (0..15), => 4 bits
    dmrs-TypeA-Position                 ENUMERATED {pos2, pos3},  => 1 bit
    pdcch-ConfigSIB1                    INTEGER (0..255), => 8 bits
    cellBarred                          ENUMERATED {barred, notBarred},  => 1 bit
    intraFreqReselection                ENUMERATED {allowed, notAllowed}, => 1 bit
    spare                               BIT STRING (SIZE (1)) => 1 bit

} 
MIB (Master Information Block) — это основной информационный блок, который передается
базовой станцией (gNB) в сети 5G. Он является частью системной информации, которую
пользовательское устройство (UE) должно декодировать для подключения к сети. MIB передается
по физическому каналу PBCH (Physical Broadcast Channel) и содержит ключевые параметры,
необходимые для начального доступа к сети.
*/
typedef struct MIB {
    unsigned char systemFrameNumber : 6;      // BIT STRING
    unsigned char subCarrierSpacingCommon: 1; // scs15or60 or scs30or120
    unsigned char ssb_SubcarrierOffset: 4;    // 0..15
    unsigned char dmrs_TypeA_Position: 1;     // pos2 or pos3
    unsigned char pdcch_ConfigSIB1: 8;        // 0..255
    unsigned char cellBarred: 1;              // barred or notBarred
    unsigned char intraFreqReselection: 1;    // allowed or notAllowed
    unsigned char spare: 1;                   // BIT STRING
} MIB_t; // 4 байта

// alignment до 4 байт (9 бит пустые)
// файл весит 260 байт, что кратно 4(и не кратно 3), поэтому будем считать, что в файле каждый MIB занимает 4 байта

typedef struct MIB_LIST {
    int nof_mibs;
    MIB_t mib[MAX_NOF_MIB];
} MIB_LIST_t;

void print_bits(int value, int numBits) {
    for (int i = numBits - 1; i >= 0; i--)
        printf("%d", (value >> i) & 1);
}

void print_MIB_t(MIB_t mib_t) {
    printf("systemFrameNumber: ");
    print_bits(mib_t.systemFrameNumber, 6);
    puts("");
    
    printf("subCarrierSpacingCommon: %s\n", mib_t.subCarrierSpacingCommon ? "scs30or120" : "scs15or60");
    printf("ssb_SubcarrierOffset: %u\n", mib_t.ssb_SubcarrierOffset);
    printf("dmrs_TypeA_Position: %s\n", mib_t.dmrs_TypeA_Position ? "pos3" : "pos2");
    printf("pdcch_ConfigSIB1: %u\n", mib_t.pdcch_ConfigSIB1);
    printf("cellBarred: %s\n", mib_t.cellBarred ? "barred" : "notBarred");
    printf("intraFreqReselection: %s\n", mib_t.intraFreqReselection ? "notAllowed" : "allowed");
    printf("spare: %u\n", mib_t.spare);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./mib bin_file\n");
        exit(1);
    }

    MIB_LIST_t mib_list;
    
    // считать из бинарного файла байты и выяснить значения полей структуры
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Error reading file\n");
        exit(1);
    }
    
    MIB_t current_MIB_t;
    int i = 0;
    while (i < MAX_NOF_MIB - 1 && fread(&mib_list.mib[i], sizeof(MIB_t), 1, file) > 0) {
        i++;
    }
    mib_list.nof_mibs = i + 1;

    for (int i = 0; i < mib_list.nof_mibs; i++){
        print_MIB_t(mib_list.mib[i]);
        puts("");
    }

    printf("%d\n", mib_list.nof_mibs);
}