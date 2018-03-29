
/*
function:���˵�������
��������SelMenuItem
������void 
����ֵ��int
*/
int SelMenuItem(void){
	char szBuff[10];
	gets(szBuff);
	return atoi(szBuff)-1;
}

/*
��������ShowItemOfBook
���ܣ���ʾһ��ͨѶ����
��������ʾ�ڵ�ָ�롣PADDRESSBOOK ����
����ֵ����һ���ڵ��ָ�룬 PADDRESSBOOK ����
*/
PADDRESSBOOK ShowItemOfBook(PADDRESSBOOK p){
	printf("%10s%15s%15s\n",p->szName,p->szMobil,p->szTel);
	return p->next;
}

/*
	���ܣ��������ֲ���
	��������QueryByName
	����������ͷָ��	PADDRESSBOOK ����
			��������	�ַ�ָ��
	����ֵ�� ���ҵ�ַ	PADDRESSBOOK ���� 
*/
PADDRESSBOOK QueryByName(PADDRESSBOOK p,char *szpName){
	PADDRESSBOOK pQuer=NULL;
	PADDRESSBOOK pTemp=p;
	while(pTemp!=NULL){
		if(strcmp(szpName,p->szName)==0){
			pQuer=p;
			break;
		}//end if
		p=p->next;
		pTemp=p;
	}//end while
	return pQuer;
}

/*
	���ܣ��޸�ָ������������
	��������ModifyItem
	�����������׵�ַ	PADDRESSBOOK ����
	����ֵ���޸����ַ	PADDRESSBOOK ���� 
*/
PADDRESSBOOK ModifyItem(PADDRESSBOOK p,char*szpName){
	PADDRESSBOOK pModi;
	PADDRESSBOOK pTemp;
	char szBuff[20];
	pModi=NULL;
	pTemp=p;
	while(pTemp!=NULL){
		if(strcmp(szpName,p->szName)==0){
			pModi=p;
			printf("�޸�%s��ͨѶ¼\n",p->szName);
			printf("��������������");
			gets(szBuff);
			if(szBuff[0]!='\0'){
				strcpy(p->szName,szBuff);
			}
			printf("���������ƶ��绰���룺");
			gets(szBuff);
			if(szBuff[0]!='\0'){
				strcpy(p->szMobil,szBuff);
			}
			printf("��������̶��绰���룺");
			gets(szBuff);
			if(szBuff[0]!='\0'){
				strcpy(p->szTel,szBuff);
			} 
			break;
		}
		p=p->next;
		pTemp=p;
	}//end while
	return pModi;
}

/*
	���ܣ���β���������
	��������AppendItem
	������ͷָ��   PADDRESSBOOK ����
	����ֵ��βָ��	PADDRESSBOOK ���� 
*/
PADDRESSBOOK AppendItem(PADDRESSBOOK p){
	PADDRESSBOOK pTail=NULL;
	//����β�ڵ�
	while(p->next!=NULL){
		p=p->next;
	} //end  while
	pTail=(PADDRESSBOOK)malloc(sizeof(ADDRESSBOOK));
	p->next=pTail;
	printf("����������");
	gets(pTail->szName);
	printf("�����ƶ��绰���룺");
	gets(pTail->szMobil);
	printf("����̶��绰���룺");
	gets(pTail->szTel);
	pTail->next=NULL;
	return pTail;	
} 

/*
	���ܣ�ɾ��ָ������������
	��������DeleteItem
	���������ݽڵ��ͷָ�� 	PADDRESSBOOK ����
	����ֵ��ɾ��ǰ���ڵ�ָ��	PADDRESSBOOK ����  
*/
PADDRESSBOOK DeleteItem(PADDRESSBOOK p,char *szpName){
	PADDRESSBOOK pCurr=NULL;
	PADDRESSBOOK pTemp=NULL;
	PADDRESSBOOK pNext=p;
	while(pNext!=NULL){
		if(strcmp(p->next->szName,szpName)==0){
			pCurr=p;
			pTemp=p->next;
			p->next=p->next->next;
			free(pTemp);
			break;
		}
		p=p->next;
		pNext=p;
	}//end while
	return pCurr;
} 

/*
	���ܣ����ļ������ݵ�����
	��������ReadData
	����������ͷָ�� PADDRESSBOOK����
			�ļ�ָ��	FILE* ����
	����ֵ�� �ڵ����	int ���� 
*/
int ReadData(PADDRESSBOOK p,FILE *fp){
	PADDRESSBOOK pTail,pCurr;
	int iNum,i;
	//���ļ����ڵ���
	fread(&iNum,sizeof(int),1,fp);
	for(i=0;i<iNum;i++){
		pTail=(PADDRESSBOOK)malloc(sizeof(ADDRESSBOOK));
		fread(pTail,sizeof(ADDRESSBOOK),1,fp);
		pCurr=pTail;
		p->next=pTail;
		p=pTail; 
	} 
	pTail->next=NULL;
	return iNum;
} 

/*
	���ܣ�����ͨѶ¼����
	��������CreateAddressBook
	����������ͷ�ڵ��ַ	PADDRESSBOOK����
	����ֵ���ڵ���	int ���� 
*/
int CreateAddressBook(PADDRESSBOOK p){
	PADDRESSBOOK pTail=p;
	PADDRESSBOOK pCurr=p;
	int iNumOfItem=0;
	char szTempBuf[20];
	while(1){
		printf("����������");
		gets(szTempBuf);
		if(szTempBuf[0]=='\0'){
			break;
		}
		pTail=(PADDRESSBOOK)malloc(sizeof(ADDRESSBOOK));
		strcpy(pTail->szName,szTempBuf);
		printf("�����ƶ��绰���룺");
		gets(pTail->szMobil); 
		printf("����̶��绰���룺");
		gets(pTail->szTel); 
		pCurr->next=pTail;
		iNumOfItem++;
		pTail->next=NULL;
		pCurr=pTail;
	}//end while
	return iNumOfItem;
}
