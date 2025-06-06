#ifndef _BEE_MSGIDS_H_
#define _BEE_MSGIDS_H_

typedef enum {
    BEE_OFFSET_CMD_MID     = 0x1870,

    EM_EPS_CHECK_SOC_MID,
    
    FTP_REPLY_MID,

    IFC_CMD_MID,
    IFC_SNC_MID,
    IFC_OIF_MID,
    IFC_SIF_MID,

    FM_CMD_MID,
    FM_SNC_MID,
    FM_OIF_MID,
    FM_SIF_MID,
    FM_SEND_HK_MID,
    FM_SEND_BCN_MID,
    FM_SEND_AOD_MID,

    EPS_CMD_MID,
    EPS_SNC_MID,
    EPS_OIF_MID,
    EPS_SIF_MID,
    EPS_SEND_HK_MID,
    EPS_SEND_BCN_MID,

    ADCS_CMD_MID,
    ADCS_SNC_MID,
    ADCS_OIF_MID,
    ADCS_SIF_MID,
    ADCS_SEND_HK_MID,
    ADCS_SEND_BCN_MID,
    ADCS_SEND_AOD_MID,

    GRX_CMD_MID,
    GRX_SNC_MID,
    GRX_OIF_MID,
    GRX_SIF_MID,
    GRX_SEND_GPS_RAW_MID,
    
    STX_CMD_MID,
    STX_SNC_MID,
    STX_OIF_MID,
    STX_SIF_MID,
    STX_SEND_HK_MID,
    STX_SEND_BCN_MID,

    UANT_CMD_MID,
    UANT_SNC_MID,
    UANT_OIF_MID,
    UANT_SIF_MID,
    UANT_SEND_HK_MID,
    UANT_SEND_BCN_MID,

    UTRX_CMD_MID,
    UTRX_SNC_MID,
    UTRX_OIF_MID,
    UTRX_SIF_MID,
    UTRX_SEND_HK_MID,
    UTRX_SEND_BCN_MID,

    PAYC_CMD_MID,
    PAYC_SNC_MID,
    PAYC_OIF_MID,
    PAYC_SIF_MID,
    PAYC_SEND_HK_MID,
    PAYC_SEND_BCN_MID,

    PAYR_CMD_MID,
    PAYR_SNC_MID,
    PAYR_OIF_MID,
    PAYR_SIF_MID,
    PAYR_SEND_HK_MID,
    PAYR_SEND_BCN_MID,

    PAYS_CMD_MID,
    PAYS_SNC_MID,
    PAYS_OIF_MID,
    PAYS_SIF_MID,
    PAYS_SEND_HK_MID,
    PAYS_SEND_BCN_MID,

    CI_INPUT_MID,
    CI_CMD_MID,
    CI_OIF_MID,

    TO_CMD_MID,
    TO_OIF_MID,
    TO_WAKEUP_MID,
    TO_CMD_EXEC_REPORT_MID,

    SN_CMD_MID,
    SN_OIF_MID,

    HK_CMD_MID,
    HK_SEND_HK_MID,
    HK_SEND_COMBINED_PKT_MID,
    
    SCH_CMD_MID,
    SCH_SEND_HK_MID,
    
    DS_CMD_MID,
    DS_SEND_HK_MID,

    LOG_CMD_MID,
    LOG_SEND_HK_MID,

}BEE_msgids_n;

typedef enum {
    BEE_OFFSET_TLM_MID     = 0x0860,

    IFC_TLM_HK_MID,
    IFC_TLM_BCN_MID,

    FM_TLM_HK_MID,
    FM_TLM_BCN_MID,
    FM_TLM_AOD_MID,

    EPS_TLM_HK_MID,
    EPS_TLM_BCN_MID,

    ADCS_TLM_HK_MID,
    ADCS_TLM_BCN_MID,
    ADCS_TLM_AOD_MID,

    GRX_TLM_GPS_RAW_MID,

    STX_TLM_HK_MID,
    STX_TLM_BCN_MID,

    UANT_TLM_HK_MID,
    UANT_TLM_BCN_MID,

    UTRX_TLM_HK_MID,
    UTRX_TLM_BCN_MID,

    PAYC_TLM_HK_MID,
    PAYC_TLM_BCN_MID,

    PAYS_TLM_HK_MID,
    PAYS_TLM_BCN_MID,

    PAYR_TLM_HK_MID,
    PAYR_TLM_BCN_MID,

    CI_TLM_HK_MID,
    CI_TLM_INFO_MID,
    
    TO_TLM_OUT_MID,
    TO_TLM_INFO_MID,
    TO_TLM_RETCODE_MID,

    TO_DATA_OUT_MID,
    TO_DATA_TYPE_MID,

    SN_TLM_HK_MID,
    
    SN_TLM_INFO_MID,
    SN_TLM_RETCODE_MID,

    HK_TLM_HK_MID,
    HK_COMBINED_PKT_HK_MID,
    HK_COMBINED_PKT_AOD_MID,
    HK_COMBINED_PKT_GPS_MID,
    HK_COMBINED_PKT_BCN_MID,

    SCH_UNUSED_MID,
    SCH_TLM_HK_MID,
    SCH_TLM_DIAG_MID,

    DS_TLM_HK_MID,
    DS_TLM_DIAG_MID,

    LOG_REPORT_LONG_MID,
    LOG_REPORT_SHORT_MID,
}BEE_tlmids_n;

#endif