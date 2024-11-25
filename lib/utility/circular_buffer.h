/**
 * 
*/
#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include <stdint.h>
#include <string.h>

typedef struct __MCU_CIRCULAR_CONTEXT__
{
    uint32_t    R;
    uint32_t    W;
    uint32_t    BufDepth;
    int8_t*     CircularBuf;
} MCU_CIRCULAR_CONTEXT;

void MCUCircular_Config(MCU_CIRCULAR_CONTEXT* CircularBuf, void* Buf, uint32_t Len);

int32_t MCUCircular_GetSpaceLen(MCU_CIRCULAR_CONTEXT* CircularBuf);

void MCUCircular_PutData(MCU_CIRCULAR_CONTEXT* CircularBuf, void* InBuf, uint16_t Len);

int32_t MCUCircular_GetData(MCU_CIRCULAR_CONTEXT* CircularBuf, void* OutBuf, uint16_t MaxLen);

uint16_t MCUCircular_GetDataLen(MCU_CIRCULAR_CONTEXT* CircularBuf);

int32_t MCUCircular_AbortData(MCU_CIRCULAR_CONTEXT* CircularBuf, uint16_t MaxLen);

int32_t MCUCircular_ReadData(MCU_CIRCULAR_CONTEXT* CircularBuf, void* OutBuf, uint16_t MaxLen);


typedef struct __MCU_DOUBLE_CIRCULAR_CONTEXT__
{
    uint32_t    R1;
    uint32_t    R2;
    uint32_t    W;
    uint32_t    BufDepth;
    int8_t*     CircularBuf;
} MCU_DOUBLE_CIRCULAR_CONTEXT;


void MCUDCircular_Config(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf, void* Buf, uint32_t Len);

int32_t MCUDCircular_GetSpaceLen(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf);

void MCUDCircular_PutData(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf, void* InBuf, uint16_t Len);

int32_t MCUDCircular_GetData1(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf, void* OutBuf, uint16_t MaxLen);

uint16_t MCUDCircular_GetData1Len(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf);

int32_t MCUDCircular_ReadData1(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf, void* OutBuf, uint16_t MaxLen);

int32_t MCUDCircular_GetData2(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf, void* OutBuf, uint16_t MaxLen);

uint16_t MCUDCircular_GetData2Len(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf);



#ifdef __cplusplus
}
#endif//__cplusplus

#endif /*CIRCULAR_BUFFER_H*/