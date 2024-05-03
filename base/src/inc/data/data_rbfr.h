#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum 
{
    RBFR_SIZE_8_E, /* 8 packets */
} tRBFR_SIZE_E;

bool Rbfr_new_B(uint32_t *rbfrDescriptor_pU32, tRBFR_SIZE_E bufferSize_E);
bool Rbfr_write_B(uint32_t rbfrDescriptor_U32, uint8_t packetData_U08);
bool Rbfr_read_B(uint32_t rbfrDescriptor_U32, uint8_t *packetData_pU08);