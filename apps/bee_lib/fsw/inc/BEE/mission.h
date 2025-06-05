#ifndef _BEE_MISSION_H_
#define _BEE_MISSION_H_

#define BEE_PIPE_DEPTH   32
#define MAX_TM_DATASIZE     170
#define MAX_RAW_DATASIZE    200
#define MAX_TC_DATASIZE     170

#define STORE_OPSDATA_FILEPATH      "cf/opsdata.bin"

typedef enum {
    BEE_MODE_EARLY_ORBIT,
    BEE_MODE_NORMAL,
    BEE_MODE_COMMUNICAION,
    HYVIRD_MODE_COMMISSIONING,
    BEE_MODE_EMERGENCY,
    BEE_MODE_MISSION,
    
    //Don't use this.
    BEE_MODE_DEATH,
}BEE_ModType_n;


typedef enum {
    SUBMODE_EO_OK,
    SUBMODE_EO_STANDBY,
    SUBMODE_EO_INITIALIZE,
    SUBMODE_EO_INITIAL_AD,
    SUBMODE_EO_START_TELEMETRY_COLLECT,
    SUBMODE_EO_START_BEACON,
    SUBMODE_EO_DEPLOY_SP,
    SUBMODE_EO_DEPLOY_MMT,
    SUBMODE_EO_DEPLOY_UANT,
    SUBMODE_EO_UPDATE_INITIAL_PRO,
    SUBMODE_EO_START_DETUMBLING,
}HYVIRD_SubmodeType_EO_n;

typedef enum {
    SUBMODE_EM_UNKNOWN,
    SUBMODE_EM_READ_ERROR,
    SUBMODE_EM_EPS,
    SUBMODE_EM_DETUMBLE,
}BEE_SUbmodeType_EM_n;

typedef enum {
    BEE_RUNSTATUS_LIB,
    BEE_RUNSTATUS_CI,
    BEE_RUNSTATUS_EPS,
    BEE_RUNSTATUS_PAYR,
    BEE_RUNSTATUS_UANT,
    BEE_RUNSTATUS_TO,
    BEE_RUNSTATUS_FM,
    BEE_RUNSTATUS_ADCS,
    BEE_RUNSTATUS_GRX,
    BEE_RUNSTATUS_IFCAPP,
    BEE_RUNSTATUS_PAYC,
    BEE_RUNSTATUS_PAYS,
    BEE_RUNSTATUS_SN,
    BEE_RUNSTATUS_STX,
    BEE_RUNSTATUS_UTRX,
    BEE_RUNSTATUS_LOG,
    BEE_RUNSTATUS_DS,
    BEE_RUNSTATUS_HK,
    BEE_RUNSTATUS_SCH,
}BEE_Runstatus_n;

// typedef struct {
//     unsigned int eo_flag_no_effect : 1;
//     unsigned int eo_flag_
// }

typedef struct {
    uint8 CurrentMode;
    uint8 PreviousMode;
}BEE_OpsMode_t;

typedef struct {
    uint8 PreviousSubmode;
    uint8 CurrentSubmode;
}BEE_OpsSubMode_t;

typedef struct {
    uint8 CurrentModeFlag;
    uint8 PreviousModeFlag;
}BEE_OpsFlag_t;

typedef struct{
    BEE_OpsMode_t mode;
    BEE_OpsSubMode_t submode[BEE_MODE_DEATH];
    BEE_OpsFlag_t flag[BEE_MODE_DEATH];
    uint16 RebootCnt;
    uint8 RebootCause;
}BEE_OpsData_t;


typedef struct{
    uint8 MaxBuffer[MAX_TM_DATASIZE];
}BEE_MaxTelemetryBuffer_t;

void BEE_SetRunStatusOn(uint8_t entry);
void BEE_SetRunStatusOff(uint8_t entry);
void BEE_GetRunStatus(uint32_t* status);
void BEE_GetOpsData(BEE_OpsData_t* ops);
void BEE_GetMode(uint8* mode);
void BEE_GetSubMode(uint8* submode);
void BEE_GetSubModeEntry(BEE_OpsSubMode_t* submode, uint8 modeentry);
void BEE_GetModeFlag(uint8* flag);
void BEE_SetMode(uint8 mode, uint8 submode);
void BEE_ConvertMode(uint8 mode);
void BEE_SetSubMode(uint8 submode);
void BEE_SetFlag(uint8 flag);
int BEE_SaveOpts(BEE_OpsData_t *data);
int BEE_LoadOpts(void);

#endif