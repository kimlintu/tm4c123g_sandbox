#include <stddef.h>
#include <stdbool.h>

#include "data_rbfr.h"

#define RBFR_NR_SIZE8_BUFFERS_U08 (uint8_t)(1)

typedef struct 
{
    uint8_t *const data_pU08;
    uint16_t       writeIndex_U16;
    uint16_t       readIndex_U16;
} tRBFR_BUFFER_STR;

static uint8_t rbfr_size8_packetBuffers_aaU08[RBFR_NR_SIZE8_BUFFERS_U08][8];
static uint8_t rbfr_size8_nextDescriptor_U08;                                          /* Next available descriptor               */
static tRBFR_BUFFER_STR rbfr_size8_packetBuffer_aSTR[RBFR_NR_SIZE8_BUFFERS_U08] = 
{
    {
        .data_pU08      = &rbfr_size8_packetBuffers_aaU08[0][0],
        .writeIndex_U16 = 0,
        .readIndex_U16  = 0
    }
};

/*
 * Retrieves a new ring buffer. This functions returns two values. A descriptor
 * that can be used with the API in order to perform operations on the buffer,
 * and a boolean value that says if a ring buffer could be retrieved succesfully.
 * 
 * @param rbfrDescriptor_pU32: Pointer to the descriptor that should be returned
 * @param bufferSize_E: The max number of packets that can be stored in the buffer 
 */
bool Rbfr_new_B(uint32_t *rbfrDescriptor_pU32, tRBFR_SIZE_E bufferSize_E)
{
    bool ret_B = true; /* Did we get a buffer? */

    switch (bufferSize_E)
    {
        case RBFR_SIZE_8_E:
            if (rbfr_size8_nextDescriptor_U08 < RBFR_NR_SIZE8_BUFFERS_U08)
            {
                if (rbfrDescriptor_pU32 != NULL)
                {
                    *rbfrDescriptor_pU32 = rbfr_size8_nextDescriptor_U08;

                    rbfr_size8_nextDescriptor_U08 += 1;
                }
                else 
                {
                    /* TODO: error logging */                    
                    ret_B = false;
                }
            }
            else 
            {
                /* No buffers are available */
                /* TODO: error logging      */
                ret_B = false;
            }
            break;
        default:
            /* Invalid buffer size */
            ret_B = false;
    }

    return ret_B;
}

static tRBFR_BUFFER_STR *Rbfr_getRingBuffer_pstr(uint32_t rbfrDescriptor_U32)
{
    tRBFR_BUFFER_STR *ringBuffer_pstr = NULL;

    if (rbfrDescriptor_U32 < RBFR_NR_SIZE8_BUFFERS_U08)
    {
        ringBuffer_pstr = &rbfr_size8_packetBuffer_aSTR[rbfrDescriptor_U32];
    }
    else 
    {
        /* TODO: error logging */
    }

    return ringBuffer_pstr;
}

static bool Rbfr_bufferIsEmpty_B(tRBFR_BUFFER_STR *ringBuffer_pstr)
{
    bool ret_B;

    if (ringBuffer_pstr != NULL)
    {
        ret_B = ringBuffer_pstr->readIndex_U16 == ringBuffer_pstr->writeIndex_U16;
    }
    else
    {
        /* TODO: error logging */
        ret_B = false;
    }

    return ret_B;
}

/*
 * Writes a data packet to the ring buffer. Returns false if there's no 
 * more space in the buffer. 
 * 
 * @param rbfrDescriptor_U32: Ring buffer descriptor
 * @param packetData_U08: The data to be stored
 */
bool Rbfr_write_B(uint32_t rbfrDescriptor_U32, uint8_t packetData_U08)
{
    tRBFR_BUFFER_STR *ringBuffer_pstr = Rbfr_getRingBuffer_pstr(rbfrDescriptor_U32);
    uint16_t          nextWriteIndex_U16;
    bool              ret_B = true;

    if (ringBuffer_pstr != NULL)
    {
        nextWriteIndex_U16 = (ringBuffer_pstr->writeIndex_U16 + 1) & 0x07;

        if (nextWriteIndex_U16 != (ringBuffer_pstr->readIndex_U16))
        {
            /* Theres space in the buffer */
            ringBuffer_pstr->data_pU08[ringBuffer_pstr->writeIndex_U16] = packetData_U08;

            ringBuffer_pstr->writeIndex_U16 = nextWriteIndex_U16;
        }
        else 
        {
            /* No more space in the buffer */
            /* TODO: error logging         */
            ret_B = false;
        }
    }
    else 
    {
        /* TODO: error logging */
        ret_B = false;
    }

    return ret_B;
}

/*
 * Reads a data packet from the ring buffer. Returns false if 
 * the buffer is empty and there's no data to be read.
 * 
 * @param rbfrDescriptor_U32: Ring buffer descriptor
 * @param packetData_pU08: A pointer to where the packet should be stored
 */
bool Rbfr_read_B(uint32_t rbfrDescriptor_U32, uint8_t *packetData_pU08)
{
    tRBFR_BUFFER_STR *ringBuffer_pstr = Rbfr_getRingBuffer_pstr(rbfrDescriptor_U32);
    bool              ret_B = true;

    if (ringBuffer_pstr != NULL)
    {
        if (Rbfr_bufferIsEmpty_B(ringBuffer_pstr) == false)
        {
            *packetData_pU08 = ringBuffer_pstr->data_pU08[ringBuffer_pstr->readIndex_U16];

            ringBuffer_pstr->readIndex_U16 = (ringBuffer_pstr->readIndex_U16 + 1) & 0x07;
        }
        else 
        {
            /* No data to be read  */
            /* TODO: error logging */
            ret_B = false;
        }
    }
    else 
    {
        /* TODO: error logging */
        ret_B = false;
    }

    return ret_B;
}