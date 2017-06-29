���̿ռ���Ϣ��Ҫ�� Record ģ���ȡ
get_hddinfo_by_sn()

MAX_HDD_NUM
Mod_syscomplex.h
ModSysComplexDMGetInfo

	u8 nMaxDiskNum = 9;
	SBizDevInfo sDevList[nMaxDiskNum];
	memset(sDevList, 0, sizeof(SBizDevInfo)*nMaxDiskNum);
	
	SBizStoreDevManage sStoreDevMgr;
	sStoreDevMgr.nDiskNum = 0;
	sStoreDevMgr.psDevList = sDevList;
	
BizSysComplexDMGetInfo(&sStoreDevMgr, nMaxDiskNum);


typedef struct
{
	u8 is_disk_exist;
	u8 is_partition_exist[MAX_PARTITION_NUM];
	partition_index ptn_index[MAX_PARTITION_NUM];
	u32 disk_total;
	u32 disk_free;
	u8 storage_type;//'s'->sata, 'u'->'usb'
	u8 disk_physical_idx;//?�¡�?��?��2?����???��������o?
	u8 disk_logic_idx;//?�¡�?��?��2?����????-����o?
	u8 disk_system_idx;//?�̨�3?��2a��?��?��2?������o?sda->0, sdb->1...
	char disk_name[32];//��2?��������???/dev/sda, /dev/sdb...
	char disk_sn[64];//��2?��D����Do??��?����?
}HddInfo;

typedef struct
{
	HddInfo hinfo[MAX_HDD_NUM];
}disk_manager;

typedef struct
{
    disk_manager hddmanager;
} SPublicManager;


// 2.15 ������?D??��
#ifndef HDD_UNFORMAT
#define HDD_UNFORMAT 0 //?��??��??��
#endif
#ifndef HDD_FORMATTING
#define HDD_FORMATTING 1 //??��??��?D
#endif
#ifndef HDD_INUSE
#define HDD_INUSE 2 //��1��??D
#endif
#ifndef HDD_IDLE
#define HDD_IDLE 3 //???D
#endif
#ifndef HDD_SLEEP
#define HDD_SLEEP 4 //DY??
#endif
#ifndef HDD_ERROR
#define HDD_ERROR 5 //3?�䨪
#endif

typedef struct
{
	u8 nType;//0 hdd; 1 usb
	char strDevPath[32];
	u8 nPartitionNo;
	u32 nStatus;//u8 nStatus;//0 ok; 1 unformated; 2 err
	u32 nTotal;
	u32 nFree;
	//u8 storage_type;//'s'->sata, 'u'->'usb'
	u8 disk_physical_idx;//?�¡�?��?��2?����???��������o?
	u8 disk_logic_idx;//?�¡�?��?��2?����????-����o?
	u8 disk_system_idx;//?�̨�3?��2a��?��?��2?������o?sda->0, sdb->1...
	//char disk_name[32];//��2?��������???/dev/sda, /dev/sdb...
	char disk_sn[64];//��2?��D����Do??��?����?
} SDevInfo;
//disk info struct
typedef struct 
{
	int			nDevIdx;	// <STR_DEV_MAX valid dev, -1 empty
	u8			nState;		// 0 checking, 1 valid, 2 empty
	SDevInfo	sDskInfo;
} SDiskInfo;

// 2.14 ??��?��?��騦����?1������D??��
typedef struct
{
	u8 		  nDiskNum;
	SDevInfo  *psDevList;
} SStoreDevManage;

