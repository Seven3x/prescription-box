#include "sdcard.h"
#define FF_MAX_SS 4096
char SDPath[4];	
FATFS 	SD_FatFs; 		// �ļ�ϵͳ����
FRESULT 	MyFile_Res;    // ������� 
uint8_t write_status = FILE_NORMAL;
/**************************************************************************************************/

//	������FatFs_Check
//	���ܣ�����FatFs�ļ�ϵͳ�Ĺ���
//
void FatFs_Check(void)	//�ж�FatFs�Ƿ���سɹ�����û�д���FatFs���ʽ��SD��
{
	BYTE work[FF_MAX_SS]; 
	
	FATFS_LinkDriver(&SD_Driver, SDPath);		// ��ʼ������
	MyFile_Res = f_mount(&SD_FatFs,"0:",1);	//	����SD��
	
	if (MyFile_Res == FR_OK)	//�ж��Ƿ���سɹ�
	{
		printf("\r\nSD�ļ�ϵͳ���سɹ�\r\n");
	}
	else		
	{
		printf("SD����δ�����ļ�ϵͳ��������ʽ��\r\n");
		
		MyFile_Res = f_mkfs("0:",FM_FAT32,0,work,sizeof work);		//��ʽ��SD����FAT32����Ĭ�ϴ�С16K
		
		if (MyFile_Res == FR_OK)		//�ж��Ƿ��ʽ���ɹ�
			printf("SD����ʽ���ɹ���\r\n");
		else
			printf("��ʽ��ʧ�ܣ���������SD����\r\n");
	}
}
//	������FatFs_GetVolume
//	���ܣ������豸��������������������ʣ������
//
void FatFs_GetVolume(void)	// �����豸����
{
	FATFS *fs;		//����ṹ��ָ��
	uint32_t SD_CardCapacity = 0;		//SD����������
	uint32_t SD_FreeCapacity = 0;		//SD����������
	DWORD fre_clust, fre_sect, tot_sect; 	//���дأ���������������������

	f_getfree("0:",&fre_clust,&fs);			//��ȡSD��ʣ��Ĵ�

	tot_sect = (fs->n_fatent-2) * fs->csize;	//���������� = �ܵĴ� * ÿ���ذ�����������
	fre_sect = fre_clust * fs->csize;			//����ʣ��Ŀ���������	   

	SD_CardCapacity = tot_sect / 2048 ;	// SD�������� = �������� * 512( ÿ�������ֽ��� ) / 1048576(�����MB)
	SD_FreeCapacity = fre_sect / 2048 ;	//����ʣ�����������λΪM
	printf("-------------------��ȡ�豸������Ϣ-----------------\r\n");		
	printf("SD������%dMB\r\n",SD_CardCapacity);	
	printf("SDʣ�ࣺ%dMB\r\n",SD_FreeCapacity);
}

//	������FatFs_FileTest
//	���ܣ������ļ�д��Ͷ�ȡ����
//
uint8_t  FatFs_FileTest(void)	//�ļ�������д�����
{
	uint8_t i = 0;
	uint16_t BufferSize = 0;	
	FIL	MyFile;			// �ļ�����
	UINT 	MyFile_Num;		//	���ݳ���
	BYTE 	MyFile_WriteBuffer[] = "STM32H750 SD�� �ļ�ϵͳ����";	//Ҫд�������
	BYTE 	MyFile_ReadBuffer[1024];	//Ҫ����������
	
	printf("-------------FatFs �ļ�������д�����---------------\r\n");
	
	MyFile_Res = f_open(&MyFile,"0:FatFs Test.txt",FA_CREATE_ALWAYS | FA_WRITE);	//���ļ������������򴴽����ļ�
	if(MyFile_Res == FR_OK)
	{
		printf("�ļ���/�����ɹ���׼��д������...\r\n");
		
		MyFile_Res = f_write(&MyFile,MyFile_WriteBuffer,sizeof(MyFile_WriteBuffer),&MyFile_Num);	//���ļ�д������
		if (MyFile_Res == FR_OK)	
		{
			printf("д��ɹ���д������Ϊ��\r\n");
			printf("%s\r\n",MyFile_WriteBuffer);
		}
		else
		{
			printf("�ļ�д��ʧ�ܣ�����SD�������¸�ʽ��!\r\n");
			f_close(&MyFile);	  //�ر�w`�ļ�	
			return ERROR;			
		}
		f_close(&MyFile);	  //�ر��ļ�			
	}
	else
	{
		printf("�޷���/�����ļ�������SD�������¸�ʽ��!\r\n");
		f_close(&MyFile);	  //�ر��ļ�	
		return ERROR;		
	}
	
	printf("-------------FatFs �ļ���ȡ����---------------\r\n");	
	
	BufferSize = sizeof(MyFile_WriteBuffer)/sizeof(BYTE);									// ����д������ݳ���
	MyFile_Res = f_open(&MyFile,"0:FatFs Test.txt",FA_OPEN_EXISTING | FA_READ);	//���ļ������������򴴽����ļ�
	MyFile_Res = f_read(&MyFile,MyFile_ReadBuffer,BufferSize,&MyFile_Num);			// ��ȡ�ļ�
	if(MyFile_Res == FR_OK)
	{
		printf("�ļ���ȡ�ɹ�������У������...\r\n");
		
		for(i=0;i<BufferSize;i++)
		{
			if(MyFile_WriteBuffer[i] != MyFile_ReadBuffer[i])		// У������
			{
				printf("У��ʧ�ܣ�����SD�������¸�ʽ��!\r\n");
				f_close(&MyFile);	  //�ر��ļ�	
				return ERROR;
			}
		}
		printf("У��ɹ�������������Ϊ��\r\n");
		printf("%s\r\n",MyFile_ReadBuffer);
	}	
	else
	{
		printf("�޷���ȡ�ļ�������SD�������¸�ʽ��!\r\n");
		f_close(&MyFile);	  //�ر��ļ�	
		return ERROR;		
	}	
	
	f_close(&MyFile);	  //�ر��ļ�	
	return SUCCESS;
}


