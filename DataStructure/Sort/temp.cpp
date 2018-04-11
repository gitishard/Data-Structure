#include <iostream>
using namespace std;
//void InsertSort(int L[]){
//	for(int i = 2;i <= 10; ++i){
//		int j;
//		if(L[i] <= L[i-1]) {	//the former is bigger than the current one
//			L[0] = L[i];		//复制为哨兵
//			L[i] = L[i-1];		
//			for(j = i-2;L[0] <= L[j]; --j){
//				L[j+1] = L[j];	//记录后移
//			}//endfor
//			L[j+1] = L[0];	//插入到正确的位置
//		}//endif
//	}//endfor
//}

//void ShellInsert(int L[],int dk){
//	//dk is the increment(两个元素的位置差)
//	for(int i = dk+1;i <= 10; ++i){
//		if(L[i] <= L[i-dk]) {
//			L[0] = L[i];
//			int j;
//			for(j = i-dk;j > 0 && L[0] <= L[j];j-=dk){
//				L[j+dk] = L[j];
//			}//endfor
//			L[j+dk] = L[0];
//		}//endif
//	}//endfor
//}
//void ShellSort(int L[],int dlta[],int t){
//	//按照增量序列dl[0]~dl[t-1]对顺序表L作希尔排序
//	//dkta[]是增量表，t是要使用的增量个数
//	for(int k = 0;k < t; ++k){
//		ShellInsert(L,dlta[k]);
//	}//endfor
//}

//void BInsertSort(int L[]){
//	int high,low,m;
//	for(int i = 2;i <= 10 ; ++i){
//		L[0] = L[i];	//将L[i]暂存到L[0]
//		low = 1;
//		high = i-1;
//		while(low <= high){
//			m = (low + high)/2;
//			if (L[0] <= L[m]) {
//				high = m - 1;	//插入低半区
//			} else {
//				low = m + 1;	//插入高半区
//			}
//		}//endwhile
//		//while退出时high<low,j-1位置是待插元素
//		for(int j = i-1;j >= high+1; --j){
//			L[j+1] = L[j];//记录后移
//		}//endfor
//		L[high+1] = L[0];//插入
//	}//endfor
//}

//数据表类定义
//const int SIZE = 100;		//静态链表最大容量
//const int MAXINT = 10000;	//最大整数
//
//template <class T>
//struct StaListNode{
//	T data;		//记录项
//	int next;	//指针项
//};
//template <class T>
//class StaticList {
//	public:
//		StaListNode<T> node[SIZE];
//		int curlen;	//链表实际长度
//		StaticList();
//		//~StaticList();
//};
//template <class T>
//StaticList<T>::StaticList(){
//	cout << "创建静态链表"<<endl;
//	cout << "请输入静态链表的实际长度："<<endl;
//	cin  >>curlen;
//	cout << "请输入各结点数量："<<endl;
//	node[0].data = MAXINT;
//	node[0].next = 0;
//	for(int i = 1;i <= curlen; ++i){
//		node[i].next = 0;
//		cin >> node[i].data;
//	}//endfor
//}
//template <class T>
//void StaListInsertSort(){
//	StaticList<T> sl;
//	int min,max;
//	sl.node[0].next = 1;	//把第一个元素视为最小的
//	sl.node[1].next = 0;	//初始化形成只有头结点的循环链表
//	max = min = 1;
//
//	for(int i = 2;i <= sl.curlen; ++i){
//		//找到最小值并插入正确位置
//		if(sl.node[i].data <= sl.node[min].data) {
//			sl.node[0].next = i;	//首元素的next是最小值的位置
//			//当前元素插入到最小的的前面
//			sl.node[i].next  = min;
//			min = i;				//min <-curPosition
//		}//endif
//
//		//找到最大值并插入正确位置
//		if(sl.node[i].data >= sl.node[max].data) {
//			sl.node[i].next = 0;	//最大元素的next是0
//			sl.node[max].next = i;	//把当前元素插入到最大元素后
//			max = i;				//max <-curPosition
//		}//endif
//
//		if(sl.node[i].data < sl.node[max].data && sl.node[i].data > sl.node[min].data) {
//			int index1 = min,index2;
//			while(sl.node[i].data >= sl.node[index1].data){
//				//从最小值开始向后遍历(升序)找到插入位置
//				index2 = index1;
//				index1 = sl.node[index1].next;
//			}//endwhile
//			//index1是插入位置的下一个位置，插在第index2元素后
//			sl.node[i].next = index1;
//			sl.node[index2].next = i;
//		}//endif
//	}//endfor
//	
//	cout <<"表插入排序结果如下："<<endl;
//	T index = sl.node[0].next;
//	while(index != 0){//最大值的next是0
//		cout << sl.node[index].data <<"\t";
//		index = sl.node[index].next;
//	}//endwhile
//	cout<<endl;
//}
int Partition(int L[],int low,int high){
	/*
	 交换顺序表L中的子[low][high]中的记录，枢轴记录到位，并返回其所在位置，
	 此时在它之前（后）的记录均不大（小）于它
	 */
	int  pivo;//枢轴
	L[0] = L[low];	//用子表的第一个记录作枢轴记录
	pivo = L[low];

	while(low < high){		//从表的两端交替向中间扫描

		while(low < high && L[high] >= pivo){
			--high;
		}//endwhile
		L[low] = L[high];//将比枢轴小的移动至低端此元素参与小于枢轴的比较

		while(low < high && L[low] <= pivo){
			++low;
		}//endwhile
		L[high] = L[low];//将比枢轴大的记录移至高端

	}//endwhile
	L[low] = L[0];	//枢轴记录到位
	return low;				//返回枢轴位置
}
void QSort(int L[],int low,int high){
	int mid;//接受枢轴位置
	if(low < high) {//if low equals high which means all elements had been traversed
		mid = Partition(L,low,high);
		QSort(L,low,mid-1);		//对低子表排序
		QSort(L,mid+1,high);	//对高子表排序
	}//endif
}
int main(int argc, char* argv[]){
	int a[10] = {0,4,7,3,9,12,10,6,2,5};
	//InsertSort(a);
	//BInsertSort(a);
	//StaListInsertSort<int>();
	QSort(a,1,9);

	//int a2[11] = {0,4,7,3,9,12,10,6,2,5,1};
	//int d[5]={5,4,3,2,1};
	//ShellSort(a2,d,5);
	
	for(int i = 1;i <= 9; ++i){
		cout <<a[i]<<" ";
	}//endfor
	return 0;
}
