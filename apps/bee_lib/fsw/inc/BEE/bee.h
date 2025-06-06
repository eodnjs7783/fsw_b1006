#ifndef _BEE_H_
#define _BEE_H_

#include <cfe.h>
#include "mission.h"
#include "msgids.h"
#include "perfids.h"
#include "msg.h"



typedef enum {
    CMD_RETCODE_TYPE_OK,
    CMD_RETCODE_TYPE_UNKNOWN,
    CMD_RETCODE_TYPE_CFE,
    CMD_RETCODE_TYPE_FSW_IMPL,
    CMD_RETCODE_TYPE_FSW_TBL,
    CMD_RETCODE_TYPE_OSAL,
    CMD_RETCODE_TYPE_PSP,
    CMD_RETCODE_TYPE_APP,
    CMD_RETCODE_TYPE_LIB,
    CMD_RETCODE_TYPE_DRIVER,
    CMD_RETCODE_TYPE_USER,
    CMD_RETCODE_TYPE_BADCMD,
    CMD_RETCODE_TYPE_PARLEN,
    CMD_RETCODE_TYPE_APPDATA,
    CMD_RETCODE_TYPE_APPUTILS,
}BEE_AppCmdRetcode_Type_n;

typedef enum {
    DEVICE_SUCCESS      = 0,
    DEVICE_ERROR        = -1,
    DEVICE_ERR_NULL     = -2,
    DEVICE_ERR_RANGE    = -3,
    DEVICE_ERR_READ     = -4,
    DEVICE_ERR_WRITE    = -5,
}BEE_DeviceRetcode_Type_n;

int32 HVD_LibInit(void);

#define COMMAND_CASE_HANDLING_NOARG(status_type, mtype, func) \
    if (VerifyCmdLength(MsgPtr, sizeof(mtype))) { \
        status = func(); \
        statusType = status_type; \
    }

#define COMMAND_CASE_HANDLING_ARG(status_type, mtype, func, arg) \
    if (VerifyCmdLength(MsgPtr, sizeof(mtype))) { \
        status = func(((mtype*)MsgPtr)->arg); \
        statusType = status_type; \
    }

#define COMMAND_CASE_HANDLING_UDATA(status_type, mtype, func, payload) \
    if (VerifyCmdLength(MsgPtr, sizeof(mtype))) { \
        status = func(&((mtype*)MsgPtr)->payload); \
        statusType = status_type; \
    }

#define TELEMETRY_CASE_HANDLING_NOARG(status_type, mtype, func, reptype) \
    if (VerifyCmdLength(MsgPtr, sizeof(mtype))) { \
        status = func((reptype*)&ReportMsg->Data.MaxBuffer); \
        ReportMsg->Report.DataSize = sizeof(reptype); \
        statusType = status_type; \
    }

#define TELEMETRY_CASE_HANDLING_ARG(status_type, mtype, func, arg, reptype) \
    if (VerifyCmdLength(MsgPtr, sizeof(mtype))) { \
        status = func(((mtype*)MsgPtr)->arg, (reptype*)&ReportMsg->Data.MaxBuffer); \
        ReportMsg->Report.DataSize = sizeof(reptype); \
        statusType = status_type; \
    }

#define TELEMETRY_CASE_HANDLING_UDATA(status_type, mtype, func, payload, reptype) \
    if (VerifyCmdLength(MsgPtr, sizeof(mtype))) { \
        status = func(&((mtype*)MsgPtr)->payload, (reptype*)&ReportMsg->Data.MaxBuffer); \
        ReportMsg->Report.DataSize = sizeof(reptype); \
        statusType = status_type; \
    }

bool VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength);

void ResetAppCmdCounters(BEE_AppCount_t * AppCnt);
void ResetDeviceCmdCounters(BEE_AppCount_t * AppCnt);
void ResetCounters(BEE_AppCount_t * AppCnt);
void CmdCounter(BEE_AppCount_t * AppCnt);
void CmdErrCounter(BEE_AppCount_t * AppCnt, BEE_CmdExecutionReportMsg_t * ExecMsg);

void ReportExecStatus(CFE_SB_Msg_t* _msg);
// int32 BEE_EnrollExecStatus(BEE_AppData_t* AppData, BEE_CmdExecutionReportMsg_t* ExecMsg);

// void BEE_ReportAppData(BEE_AppData_t * AppData);


#endif