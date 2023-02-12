/*
 * FAT_FILE_SYSTEM.h
 *
 *  Created on: Nov 21, 2022
 *      Author: hp
 */

#ifndef APP_FAT_FILE_SYSTEM_FAT_FILE_SYSTEM_H_
#define APP_FAT_FILE_SYSTEM_FAT_FILE_SYSTEM_H_


#include "HAL/SD_CARD/SD_CARD.h"

// LBA logical byte addressing

// in the master boot recored we are looking to the first partiton (there are 4 partiton no more )

#define MBR_Partition_OFFSET 0x01BE // Master boot recorded
#define MBR_LBA_FIRST_SECTOR_OFFSET 0x08
#define MBR_NUMBER_OF_SECTORS_OFFSET 0x0C
// we are looking in it for the volume id where is information about how we get Root Directory First Cluster


#define Volume_ID_BytesPerSector_OFFSET 0x0B
#define Volume_ID_SectorsPerCluster_OFFSET 0x0D
#define Volume_ID_NumberOfReservedSectors_OFFSET 0x0E
#define Volume_ID_NumberOfFATs_OFFSET 0x10
#define Volume_ID_SectorsPerFAT_OFFSET 0x24
#define Volume_ID_RootDirectoryFirstCluster_OFFSET 0x2C
#define Volume_ID_BytesPerSector_OFFSET 0x0B
#define Volume_ID_Signature_OFFSET 0x1FE


typedef struct
		{

		u32 Partition_LBA ; // logical byte addressing of the first Partition place in the sd card
		u32 Sectors_Number; // the number of sectors in the sd card or the size of the sd card
		u32 RootDirectoryFirstCluster; // the lba of the root Directory

		//--------------------- some information to convert between cluster and lba
		u8 SectorsPerCluster;
		u64 Cluster_Begin_LBA;
		//---------------------

		}
FAT32_FILE_SYSTEM;



FAT32_FILE_SYSTEM FAT32_INIT(SD_CARD_ID* SD_CARD);


#endif /* APP_FAT_FILE_SYSTEM_FAT_FILE_SYSTEM_H_ */
