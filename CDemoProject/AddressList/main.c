//������
#include "addressbook.h"
#include "function.c"

void main(void){
	PADDRESSBOOK pHead=NULL;
	PADDRESSBOOK pTail=NULL; 
	PADDRESSBOOK pCurr=NULL;//�����ͷ��β����ǰָ�� 
	
	int iMenuId;
	int iExitFlag=0;
	int iNewFileFlag=0;//�ļ����ڱ�־ 
	int iNumOfItem=0;//��¼�ڵ�����������ļ���һ�� 
	int i;
	
	char szTempBuf[20]={"\0"};
	FILE *fp;
	 
	fp=fopen("addressbook.txt","rb");
	if(fp==NULL){
		iNewFileFlag=1; 
	}else{
		pHead=(PADDRESSBOOK)malloc(sizeof(ADDRESSBOOK));
		pHead->next=NULL;
		iNumOfItem=ReadData(pHead,fp);
		fclose(fp);
	}
	
	do{
		system("cls");
		printf("***************************************\n");
		printf("***     ��ӭʹ��ͨѶ¼����ϵͳ      ***\n");
		printf("***     ϵͳѡ�		    ***\n");
		printf("***************************************\n");
		for(i=0;i<7;i++){
			printf("\t%s\n",szpMenu[i]);
		} 
		printf("      ��ѡ�� ");
		iMenuId=SelMenuItem();
		switch(iMenuId){
			case CREATEADDRESSBOOK:
				if(iNewFileFlag==0){
					system("cls");
					printf("****ͨѶ¼�����ڣ�����������أ�ѡ��ѡ��****\n");
					getchar(); 
				}else{
					system("cls");
					printf("**************����ͨѶ¼*****************\n");
					pHead=(PADDRESSBOOK)malloc(sizeof(ADDRESSBOOK));
					pHead->next=NULL;
					iNumOfItem=CreateAddressBook(pHead);
					iNewFileFlag=0; 
				}
				break;
				
			case SHOWADDRESSBOOK:
				if(iNewFileFlag==1){
					system("cls");
					printf("****ͨѶ¼�����ڣ�����������أ�*****\n");
					getchar();
				}else{
					pCurr=pHead->next;
					system("cls");
					printf("��    ��     �ƶ��绰����    �̶��绰����\n");
					for(i=0;i<iNumOfItem;i++){
						ShowItemOfBook(pCurr);
						pCurr=pCurr->next; 
					}
					printf("����������أ�");
					getchar();
				}
				break;
			
			case QUERYADDRESSBOOK:
				if(iNewFileFlag==1){
					system("cls");
					printf("*****ͨѶ¼�����ڣ�����������أ�*****\n");
					getchar();
					break;
				}else{
					pCurr=pHead->next;
					system("cls");
					printf("*********��ѯ������*************\n");
					printf("����������");
					gets(szTempBuf);
					pCurr=QueryByName(pCurr,szTempBuf);
					if(pCurr==NULL){
						printf("���޴��ˣ������ⷵ��");
					}else{
						printf("������%-s  �ƶ��绰���룺%-s  �̶��绰���룺%-s\n",pCurr->szName,pCurr->szMobil,pCurr->szTel);
						printf("����������أ�");	
					} 
				}
				getchar();
				break;
				
			case MODIFYADDRESSBOOK:
				if(iNewFileFlag==1){
					system("cls");
					printf("*****ͨѶ¼�����ڣ������������*****\n");
					getchar();
					break;
				}else{
					pCurr=pHead->next;
					system("cls");
					printf("************�޸ĺ���****************\n");
					printf("����Ҫ�޸ĵ�������");
					gets(szTempBuf);
					pCurr=ModifyItem(pCurr,szTempBuf);
					if(pCurr==NULL){
						printf("ͨѶ¼�޴��ˣ�");
					}//end of if	 
				}//end else
				printf("��������˳���");
				getchar();
				break;
			
			case APPENDADDRESSBOOK:
				if(iNewFileFlag==1){
					system("cls");
					printf("*****ͨѶ¼�����ڣ������������*****\n");
					getchar();
					break;
				}else{
					pCurr=pHead->next;
					system("cls");
					printf("************�����ϵ��****************\n");
					pTail=AppendItem(pCurr); 
					if(pTail==NULL){
						iNumOfItem++;
					}//end of if	 
				}//end else
				printf("��������˳���");
				getchar();
				break;
	
			case DELETEADDRESSBOOK:
				if(iNewFileFlag==1){
					system("cls");
					printf("*****ͨѶ¼�����ڣ������������*****\n");
					getchar();
					break;
				}else{
					pCurr=pHead;
					system("cls");
					printf("************ɾ����ϵ��****************\n");
					printf("����Ҫɾ���˵�������");
					gets(szTempBuf);
					pCurr=DeleteItem(pCurr,szTempBuf);
					if(pCurr==NULL){
						printf("ͨѶ¼�޴��ˣ�");
					}else{
						iNumOfItem--;
						printf("�ɹ�ɾ��������������أ�");
					}//end of else	 
				}//end else
				getchar();
				break;
 
 			case EXITADDRESSBOOK:
			 	iExitFlag=1;
				 if(iNewFileFlag==1){
					break;
				}
				fp=fopen("addressbook.txt","wb");
				if(fp==NULL){
					printf("Error! Enter and back!");
					getchar();
					break;
				}else{
					pCurr=pHead->next;
					//д��ڵ���
					 fwrite(&iNumOfItem,sizeof(int),1,fp);
					 while(pCurr!=NULL){
					 	fwrite(pCurr,sizeof(ADDRESSBOOK),1,fp);
					 	pTail=pCurr->next;
					 	free(pCurr);
					 	pCurr=pTail;
					 }//end while
					 fclose(fp);
				}//end of else
				break;
				
			default:
				system("cls");
				printf("*************�޴�ѡ��***************\n");
				printf("             �������������ѡ��       ");
				getchar();
				break;
		} //end switch
	}while(iExitFlag!=1);
	
	system("cls");
	printf("*************��������˳���ллʹ��***************\n");
	getchar();
} 


