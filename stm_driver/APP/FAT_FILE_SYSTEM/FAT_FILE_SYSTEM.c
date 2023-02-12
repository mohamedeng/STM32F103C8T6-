/*
 * FAT_FILE_SYSTEM.c
 *
 *  Created on: Nov 21, 2022
 *      Author: hp
 */

#include "FAT_FILE_SYSTEM.h"

/*
(unsigned long)fat_begin_lba = Partition_LBA_Begin + Number_of_Reserved_Sectors;
(unsigned long)cluster_begin_lba = Partition_LBA_Begin + Number_of_Reserved_Sectors + (Number_of_FATs * Sectors_Per_FAT);
(unsigned char)sectors_per_cluster = BPB_SecPerClus;
(unsigned long)root_dir_first_cluster = BPB_RootClus;
*/

//lba_addr = cluster_begin_lba + (cluster_number - 2) * sectors_per_cluster;

u32 FAT32_GET_LBA_ADDR(FAT32_FILE_SYSTEM* FAT,u64 cluster_number)
{
	return (FAT->Cluster_Begin_LBA +(cluster_number - 2) * FAT->SectorsPerCluster);

}


FAT32_FILE_SYSTEM FAT32_INIT(SD_CARD_ID* SD_CARD)
{
	FAT32_FILE_SYSTEM FAT;
	u8 MBR[512]; // master boot recorded
	SD_CARD_u8_READ_BLOCK(SD_CARD, 0, (u8*) MBR);

	FAT.Partition_LBA = (	 MBR[MBR_Partition_OFFSET+MBR_LBA_FIRST_SECTOR_OFFSET+3] << 24 |
							 MBR[MBR_Partition_OFFSET+MBR_LBA_FIRST_SECTOR_OFFSET+2] << 16 |
							 MBR[MBR_Partition_OFFSET+MBR_LBA_FIRST_SECTOR_OFFSET+1] <<  8 |
							 MBR[MBR_Partition_OFFSET+MBR_LBA_FIRST_SECTOR_OFFSET]) ;

	FAT.Sectors_Number =(	 MBR[MBR_Partition_OFFSET+MBR_NUMBER_OF_SECTORS_OFFSET+3] << 24 |
							 MBR[MBR_Partition_OFFSET+MBR_NUMBER_OF_SECTORS_OFFSET+2] << 16 |
							 MBR[MBR_Partition_OFFSET+MBR_NUMBER_OF_SECTORS_OFFSET+1] <<  8 |
							 MBR[MBR_Partition_OFFSET+MBR_NUMBER_OF_SECTORS_OFFSET]) ;

	// first sector of the partition
	SD_CARD_u8_READ_BLOCK(SD_CARD, FAT.Partition_LBA, (u8*) MBR);


	u16 Signature = MBR[Volume_ID_Signature_OFFSET+1] <<  8 |
 	 	     	    MBR[Volume_ID_Signature_OFFSET];
	if (Signature != 0xAA55)
	{
		// if the fat Sectors Number and Partition LBA = 0 then the fat file system init give me error
 		FAT.Sectors_Number = 0;
		FAT.Partition_LBA = 0;
		return FAT;
	}

	u16 BytesPerSector = MBR[Volume_ID_BytesPerSector_OFFSET+1] <<  8 |
						 MBR[Volume_ID_BytesPerSector_OFFSET];


	u16 NumberofReservedSectors	= MBR[Volume_ID_NumberOfReservedSectors_OFFSET+1] <<  8 |
			 	 	 	 	 	  MBR[Volume_ID_NumberOfReservedSectors_OFFSET];

	u8 NumberofFATs = MBR[Volume_ID_NumberOfFATs_OFFSET];

	u32 SectorsPerFAT =(	 MBR[Volume_ID_SectorsPerFAT_OFFSET+3] << 24 |
			 	 	 	 	 MBR[Volume_ID_SectorsPerFAT_OFFSET+2] << 16 |
							 MBR[Volume_ID_SectorsPerFAT_OFFSET+1] <<  8 |
							 MBR[Volume_ID_SectorsPerFAT_OFFSET]) ;


	FAT.RootDirectoryFirstCluster = (	 MBR[Volume_ID_RootDirectoryFirstCluster_OFFSET+3] << 24 |
										 MBR[Volume_ID_RootDirectoryFirstCluster_OFFSET+2] << 16 |
										 MBR[Volume_ID_RootDirectoryFirstCluster_OFFSET+1] <<  8 |
										 MBR[Volume_ID_RootDirectoryFirstCluster_OFFSET]) ;

	FAT.Cluster_Begin_LBA = FAT.Partition_LBA + NumberofReservedSectors + (NumberofFATs * SectorsPerFAT);

	FAT.SectorsPerCluster = MBR[Volume_ID_SectorsPerCluster_OFFSET];


	SD_CARD_u8_READ_BLOCK(SD_CARD, FAT.Partition_LBA, (u8*) MBR);


	return FAT;
}
