#ifndef _BEE_TCTYPE_H_
#define _BEE_TCTYPE_H_

#include <cfe.h>

#include "mission.h"

typedef struct {
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint8 Data[MAX_TC_DATASIZE];
} OS_PACK BEE_VariableLengthCmd_t;

typedef struct {
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];
} OS_PACK BEE_NoArgsCmd_t;

typedef struct {
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint8 arg;
} OS_PACK BEE_U8ArgsCmd_t;

typedef struct {
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint16 arg;
} OS_PACK BEE_U16ArgsCmd_t;

typedef struct {
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint32 arg;
} OS_PACK BEE_U32ArgsCmd_t;

typedef struct {
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint64 arg;
} OS_PACK BEE_U64ArgsCmd_t;

typedef struct {
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];
    int8 arg;
} OS_PACK BEE_S8ArgsCmd_t;

typedef struct {
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];
    int16 arg;
} OS_PACK BEE_S16ARgsCmd_t;

typedef struct {
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];
    int32 arg;
} OS_PACK BEE_S32ArgsCmd_t;

typedef struct {
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];
    int64 arg;
} OS_PACK BEE_S64ArgsCmd_t;

typedef struct {
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];
    float arg;
} OS_PACK BEE_FloatArgsCmd_t;

typedef struct {
    uint16 AppCmdCounter;
    uint16 AppErrCounter;
    uint16 DeviceCmdCounter;
    uint16 DeviceErrCounter;
} OS_PACK BEE_AppCount_t;

typedef struct {
    uint8 RetCodeType;
    int32 RetCode;
    CFE_SB_MsgId_t MsgId;
    uint16 CommandCode;
    uint16 DataSize;
    uint8 UsedState;
} OS_PACK BEE_CmdExecutionReportMsg_t;

typedef struct {
    uint8 TlmHeader[CFE_SB_TLM_HDR_SIZE];
    BEE_CmdExecutionReportMsg_t Report;
} OS_PACK BEE_TelemetryHeader_t;

typedef struct {
    BEE_TelemetryHeader_t Hdr;
    uint8_t Udata[MAX_TM_DATASIZE];
} OS_PACK BEE_Telemetry_t;

#endif