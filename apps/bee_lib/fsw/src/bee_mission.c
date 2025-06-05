#include <cfe.h>
#include <BEE/bee.h>
#include <fcntl.h>      // open
#include <unistd.h>     // read, write, close
#include <string.h>



BEE_OpsData_t OpsData;
uint32 Runstatus;

void BEE_SetRunStatusOn(uint8_t entry)
{
    Runstatus |= 0x00000001 << entry;
    return;
}

void BEE_SetRunStatusOff(uint8_t entry)
{
    Runstatus |= ~0x00000001 << entry;
    return;
}

void BEE_GetRunStatus(uint32_t* status)
{
    *status = Runstatus;
    return;
}

void BEE_GetOpsData(BEE_OpsData_t* ops)
{
    if(!ops)
        return NULL;
    memcpy(ops, &OpsData, sizeof(OpsData));
    return;
}

void BEE_GetMode(uint8* mode)
{
    if(!mode)
        return;
    mode = &OpsData.mode.CurrentMode;
    return;
}

void BEE_GetSubMode(uint8* submode)
{
    if(!submode)
        return;
    submode = &OpsData.submode[OpsData.mode.CurrentMode].CurrentSubmode;
    return;
}

void BEE_GetSubModeEntry(BEE_OpsSubMode_t* submode, uint8 modeentry)
{
    if(!submode)
        return;
    memcpy(submode, &OpsData.submode[modeentry], sizeof(BEE_OpsSubMode_t));
    return;
}

void BEE_GetModeFlag(uint8* flag)
{
    if(!flag)
        return;
    flag = &OpsData.flag[OpsData.mode.CurrentMode].CurrentModeFlag;
    return;
}

void BEE_SetMode(uint8 mode, uint8 submode)
{
    OpsData.mode.PreviousMode = OpsData.mode.CurrentMode;
    OpsData.mode.CurrentMode = mode;
    OpsData.submode[mode].PreviousSubmode = OpsData.submode[mode].CurrentSubmode;
    OpsData.submode[mode].CurrentSubmode = submode;
    BEE_SaveOpts(&OpsData);
    return;
}

void BEE_ConvertMode(uint8 mode)
{
    OpsData.mode.PreviousMode = OpsData.mode.CurrentMode;
    OpsData.mode.CurrentMode = mode;
    BEE_SaveOpts(&OpsData);
}

void BEE_SetSubMode(uint8 submode)
{
    OpsData.submode[OpsData.mode.CurrentMode].PreviousSubmode = OpsData.submode[OpsData.mode.CurrentMode].CurrentSubmode;
    OpsData.submode[OpsData.mode.CurrentMode].CurrentSubmode = submode;
    BEE_SaveOpts(&OpsData);
    return;
}

void BEE_SetFlag(uint8 flag)
{
    OpsData.flag[OpsData.mode.CurrentMode].PreviousModeFlag = OpsData.flag[OpsData.mode.CurrentMode].CurrentModeFlag;
    OpsData.flag[OpsData.mode.CurrentMode].CurrentModeFlag = flag;
    BEE_SaveOpts(&OpsData);
    return;
}

// void BEE_SetRebootCount()

int BEE_SaveOpts(BEE_OpsData_t *data) {
    int fd = open(STORE_OPSDATA_FILEPATH, O_WRONLY | O_CREAT | O_TRUNC, 0644); // 파일 열기 (쓰기 모드, 파일 없으면 생성)
    if (fd < 0) {
        return -1;
    }

    ssize_t written = write(fd, data, sizeof(BEE_OpsData_t)); // 데이터 쓰기
    if (written != sizeof(BEE_OpsData_t)) {
        close(fd);
        return -1;
    }

    close(fd); // 파일 닫기
    
    memcpy(&OpsData, data, sizeof(BEE_OpsData_t));
    return 0;
}

// 데이터 읽기 함수
int BEE_LoadOpts(void) {
    int fd = open(STORE_OPSDATA_FILEPATH, O_RDONLY); // 파일 열기 (읽기 모드)
    if (fd < 0) {
        return -1;
    }

    int read_bytes = read(fd, &OpsData, sizeof(BEE_OpsData_t)); // 데이터 읽기
    if (read_bytes < sizeof(BEE_OpsData_t)) {
        close(fd);
        return -1;
    }

    // printf("Mode: %d", OpsData.mode.CurrentMode);

    close(fd); // 파일 닫기
    return 0;
}