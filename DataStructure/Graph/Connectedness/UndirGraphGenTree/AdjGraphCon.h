#ifndef __ADJDFSFOREST__
#define __ADJDFSFOREST__

#include "../../../Queue/LinkQueue.h"

#define MAX_VERTEX_NUM 20

template <class T>
struct CSTree{//树的二叉链表存储
	T data;
	CSTree *firstchild;
	CSTree *nextsibling;
};

struct ArcNode{
	int adjvex;					//position of the vertex pointed by the arc
	struct ArcNode *nextarc;	//point to next arc
	int *info;					//pointer about relative information of the arc
};

template <class T>
struct VNode{
	T data;						//infomation of the vertex
	ArcNode *firstarc;			//point to the first pointer depended on this vertex
};

template <class T>
struct _ATGraph{
	VNode<T> vertexs[MAX_VERTEX_NUM];//vertex set
	int vexNum;					//number of vertexs
	int arcNum;					//number of edges
	int kind;					//caterage of graph
};

template <class T>
class ATGraph{
	_ATGraph<T> atgraph;
	bool visited[MAX_VERTEX_NUM];
	public:
		void CreateGraph();
		void DestroyGraph();
		int  LocateVertex(T u);	//return the position in graph of vertex u
		T    GetVertex(int index);//retrun value of vertex whose number is index
		void PutVertex(T v,T value);//assign value to v
		int  FirstAdjVertex(T v);	//return the index of first adjacent node of V, otherwise null
		int  NextAdjVertex(T v,T w);//return the next adjacent node of v related to w,otherwise null
		void InsertVertx(T v);		//add new vertex v
		bool DeleteVertex(T v);		//delete vertex v
		bool InsertArc(T v,T w);	//add <v,w>, also still add <w,v> if graph is undirected
		void DeleteArc(T v,T w);	//delete <v,w>, alse <w,v> if it's undorected
		bool (*VisitFunc)(T v);		//visit vertex v
		void DFS(int index);		//traverse recursively by Depth-first traversal
		bool DFSTraverse(bool (*visit)(T v)); //Depth-first
		bool BFSTraverse(bool (*visit)(T v)); //Breath-first
		void Display();

		//for connectness
		void DFSTree(int index,CSTree<T> *&t);//从第index个结点出发深度优先遍历图，建立根为t的生成树
		void DFSForest(CSTree<T> *&t);//建立无向图的深度优先生成森林的孩子兄弟链表
		void PreOrderTraverse(CSTree<T> *&t,bool (*visit)(T v));//先根遍历链表结构的树t
		void BTreetoForest(CSTree<T> *&t);//二叉树(左分支是孩子，右分支是兄弟),转化为森林
};
#endif

template <class T>
bool visit(T v){
	cout << v << " ";
	return true;
}
template <class T>
int ATGraph<T>::LocateVertex(T u){
	//return the position of u
	for(int i = 0;i < atgraph.vexNum; ++i){
		if(atgraph.vertexs[i].data == u){
			return i;
		}
	}//endfor
	return -1;
}
template <class T>
void ATGraph<T>::CreateGraph(){
	int w,i,j;
	T v1,v2;
	cout << "Please choose caterage:\n"
		 << "0\tDirected Graph\n"
		 << "1\tDirected NetWork\n"
		 << "2\tUDirected Graph\n"
		 << "3\tUDirected NetWork\n";
	cin  >> atgraph.kind;
	cout << "Please enter the number of vertexs and arcs:";
	cin  >> atgraph.vexNum >> atgraph.arcNum;
	cout << "Please enter the value of each vertexs:";
	for(int i = 0;i < atgraph.vexNum; ++i){
		cin >> atgraph.vertexs[i].data;
		atgraph.vertexs[i].firstarc = NULL;
	}//endfor
	/*if (atgraph.kind % 2) {//net
		cout << "Please enter weight, end and start of each arc!"<< endl;
	} else {	//graph
		cout << "Pelase enter end and start of each arc!"<<endl;
	}*/
	for(int k = 0;k < atgraph.arcNum; ++k){
		if (atgraph.kind % 2) {
			cout << "Please enter weight, end and start of a arc:";
			cin  >> w >> v1 >> v2;
		} else {
			cout << "Pelase enter end and start of a arc:";
			cin  >> v1 >> v2;
		}
		i = LocateVertex(v1);
		j = LocateVertex(v2);
		ArcNode *p = new ArcNode;	
		p->adjvex = j;
		p->nextarc = NULL;
		if(atgraph.kind % 2){//net
			p->info = new int;
			*(p->info) = w;
		} else {//graph
			p->info = NULL;
		}
		p->nextarc = atgraph.vertexs[i].firstarc;//insert table head
		atgraph.vertexs[i].firstarc = p;
		if(atgraph.kind > 1){//undirected
			ArcNode *p = new ArcNode;
			p->adjvex = i;
			p->nextarc = NULL;
			if (atgraph.kind == 3) {
				p->info = new int;
				*(p->info) = w;
			} else {
				p->info = NULL;
			}
			p->nextarc = atgraph.vertexs[j].firstarc;//insert table head
			atgraph.vertexs[j].firstarc = p;
		}
	}//endfor
}
template <class T>
void ATGraph<T>::DestroyGraph(){
	ArcNode *p,*q;
	for(int i = 0;i < atgraph.vexNum; ++i){
		//relax node from 0 successively
		p = atgraph.vertexs[i].firstarc;
		while(p){
			q = p->nextarc;
			if(atgraph.kind % 2){
				delete p->info;
			}
			delete p;
			p = q;
		}//endwhile
	}//endfor
	atgraph.arcNum = 0;
	atgraph.vexNum = 0;
}
template <class T>
T ATGraph<T>::GetVertex(int index){
	//return vlaue of the index vertex
	if(index < 0||index >= atgraph.vexNum){
		return 0;
	}
	return atgraph.vertexs[index].data;
}
template <class T>
void ATGraph<T>::PutVertex(T v,T value){
	int i = LocateVertex(v);
	if(i < 0)
		return;
	atgraph.vertexs[i].data = value;
}
template <class T>
int ATGraph<T>::FirstAdjVertex(T v){
	int i = LocateVertex(v);
	ArcNode *p = atgraph.vertexs[i].firstarc;//p point to the first adjacent of i index
	if (p) {
		return p->adjvex;
	} else {
		return -1;
	}
}
template <class T>
int ATGraph<T>::NextAdjVertex(T v,T w){
	int i = LocateVertex(v);
	int j = LocateVertex(w);
	ArcNode *p = atgraph.vertexs[i].firstarc;
	while(p && (p->adjvex != j)){//p point to w
		p = p->nextarc;
	}//endwhile
	if (!p || !p->nextarc) {//v,w is not the last node
		return -1;
	} else {
		return p->nextarc->adjvex;
	}
}
template <class T>
void ATGraph<T>::InsertVertx(T v){
	if(atgraph.vexNum > MAX_VERTEX_NUM)
		return;//can not insert
	if(LocateVertex(v) >= 0)
		return;
	atgraph.vertexs[atgraph.vexNum].data = v;
	atgraph.vertexs[atgraph.vexNum].firstarc = NULL;
	atgraph.vexNum++;
}
template <class T>
bool ATGraph<T>::DeleteVertex(T v){
	if(atgraph.vexNum >= MAX_VERTEX_NUM)
		return false;
	ArcNode  *p,*q;
	int i,j;
	i = LocateVertex(v);
	if(i < 0)
		return false;
	p = atgraph.vertexs[i].firstarc;
	while(p){
		q = p;
		p = p->nextarc;
		if(atgraph.kind % 2)
			delete q->info;
		delete q;
		atgraph.arcNum--;
	}//endwhile
	atgraph.vexNum--;
	for(j = i;j < atgraph.vexNum;++j){//move the node after v forward
		atgraph.vertexs[j] = atgraph.vertexs[j+1];
	}
	for(j = 0;j < atgraph.vexNum;++j){//delete the edge with v as the in arc
		p = atgraph.vertexs[j].firstarc;
		while(p){
			if(p->adjvex == i){//find out the node waiting for being deleted
				if(p == atgraph.vertexs[j].firstarc){//the first adjacent node of node to be deleted
					atgraph.vertexs[j].firstarc = p->nextarc;
					if(atgraph.kind % 2)
						delete p->info;

					delete p;
					p = atgraph.vertexs[j].firstarc;
					
					if(atgraph.kind < 2)
						atgraph.arcNum--;
				} else {
					q->nextarc = p->nextarc;
					if(atgraph.kind % 2)
						delete p->info;
					delete p;
					p = q->nextarc;
					if(atgraph.kind < 2)
						atgraph.arcNum--;
				}
			} else {
				if(p->adjvex > i){
					p->adjvex--;
				}
				q = p;
				p = p->nextarc;
			}
		}//endwhile
	}
	return true;
}
template <class T>
bool ATGraph<T>::InsertArc(T v,T w){
	ArcNode *p;
	int i,j,w1;
	i = LocateVertex(v);
	j = LocateVertex(w);
	if(i < 0||j < 0)
		return false;
	atgraph.arcNum++;
	if(atgraph.kind % 2){
		cout << "Please enter the weight of "<< v <<"->"<<w;
		cin >> w1;
	}
	p = new ArcNode;
	p->adjvex = j;
	p->nextarc = NULL;
	if (atgraph.kind % 2) {
		p->info = new int;
		*(p->info) = w1;
	} else {
		p->info = NULL;
	}
	//insert into tabel head
	p->nextarc = atgraph.vertexs[i].firstarc;
	atgraph.vertexs[i].firstarc = p;
	if(atgraph.kind > 1){
		p = new ArcNode;
		p->adjvex = i;
		p->nextarc = NULL;
		if (atgraph.kind == 3) {
			p->info = new int;
			*(p->info) = w1;
		} else {
			p->info = NULL;
		}
		p->nextarc = atgraph.vertexs[j].firstarc;
		atgraph.vertexs[j].firstarc = p;
	}
	return true;
}
template <class T>
void ATGraph<T>::DeleteArc(T v,T w){
	ArcNode *p,*q;
	int i = LocateVertex(v);
	int j = LocateVertex(w);
	if(i < 0||j < 0||i == j)
		return;
	p = atgraph.vertexs[i].firstarc;
	while(p && p->adjvex != j){//p is not empty and the node is not to be deleted p pointing to
		q = p;
		p = p->nextarc;
	}
	if(p && p->adjvex == j){
		if (p == atgraph.vertexs[i].firstarc) {
			atgraph.vertexs[i].firstarc = p->nextarc;
		} else {
			q->nextarc = p->nextarc;
		}
		if(atgraph.kind % 2)
			delete p->info;
		delete p;
		atgraph.arcNum--;
	}
	if(atgraph.kind > 1){
		p = atgraph.vertexs[j].firstarc;
		while(p && p->adjvex != j){
			q = p;
			p = p->nextarc;
		}
	}
	if(p && p->adjvex == i){
		if (p == atgraph.vertexs[j].firstarc) {
			atgraph.vertexs[j].firstarc = p->nextarc;
		} else {
			q->nextarc = p->nextarc;
		}
		if(atgraph.kind == 3)//undirected net
			delete p->info;
		delete p;
	}
}
template <class T>
void ATGraph<T>::DFS(int index){
	T v1;
	visited[index] = true;
	VisitFunc(atgraph.vertexs[index].data);
	v1 = GetVertex(index);
	for(int i = FirstAdjVertex(v1);i >=0; i = NextAdjVertex(v1,GetVertex(i))){
		if(!visited[i])
			DFS(i);
	}//endfor
}
template <class T>
bool ATGraph<T>::DFSTraverse(bool (*visit)(T v)){
	VisitFunc = visit;
	for(int i = 0;i < MAX_VERTEX_NUM; ++i){
		visited[i] = false;
	}//endfor
	for(int i = 0;i < atgraph.vexNum; ++i){
		if(!visited[i])
			DFS(i);
	}//endfor
	cout << endl;
	return true;
}
template <class T>
bool ATGraph<T>::BFSTraverse(bool (*visit)(T v)){
	LinkQueue<int> q;
	int receive;
	T u1;
	for(int i = 0;i < MAX_VERTEX_NUM; ++i){
		visited[i] = false;
	}//endfor
	for(int i = 0;i < atgraph.vexNum; ++i){
		if(!visited[i]){
			visited[i] = true;
			if(!visit(atgraph.vertexs[i].data))
				return false;
			q.EnQueue(i);
			while(!q.QueueEmpty()){
				receive = q.DeQueue();
				u1 = GetVertex(receive);
				for(int j = FirstAdjVertex(u1);j >= 0; j = NextAdjVertex(u1,GetVertex(j))){
					if(!visited(j)){
						visited[j] = true;
						if(!visit(atgraph.vertexs[j].data))
							return false;
						q.EnQueue(j);
					}
				}//endfor
			}
		}
	}//endfor
	cout << endl;
	return true;
}
template <class T>
void ATGraph<T>::Display(){
	ArcNode *p;
	switch(atgraph.kind){
		case 0:cout <<"Directed Graph"<<endl;break;
		case 1:cout <<"Directed Net"<<endl;break;
		case 2:cout <<"UnDirected Graph"<<endl;break;
		case 3:cout <<"UnDirected Net"<<endl;break;
	}//endswitch
	cout << atgraph.vexNum <<" Vertexs"<<endl;
	for(int i = 0;i < atgraph.vexNum; ++i){
		cout << atgraph.vertexs[i].data <<" ";
	}//endfor
	cout << endl;
	cout <<atgraph.arcNum <<"Arcs"<<endl;
	for(int i = 0;i < atgraph.vexNum; ++i){
		p = atgraph.vertexs[i].firstarc;
		while(p){
			if (atgraph.kind < 2) {
				cout << atgraph.vertexs[i].data << "->"<<atgraph.vertexs[p->adjvex].data<<'\t';
				if(atgraph.kind == 1)
					cout << *(p->info);
				cout << endl;
			} else {
				if(i < p->adjvex){
					cout << atgraph.vertexs[i].data << "-" <<atgraph.vertexs[p->adjvex].data<<'\t';
					if(atgraph.kind == 3)
						cout << *(p->info);
					cout << endl;
				}
			}
			p = p->nextarc;
		}
	}//endfor
}
template <class T>
void ATGraph<T>::DFSTree(int index,CSTree<T> *&t){
//从第index个结点出发，深度优先遍历图，建立根为t的生成树
	CSTree<T> *p,*q;
	T v1;
	int w;
	visited[index] = true;
	bool firsttag = true;
	v1 = GetVertex(index);
	for(w = FirstAdjVertex(v1); w >= 0; w = NextAdjVertex(v1,GetVertex(w))){
		//w依次为v的邻接顶点
		if(visited[w] == false){
			p = new CSTree<T>;
			p->data = GetVertex(w);
			p->firstchild = NULL;
			p->nextsibling = NULL;
			if(firsttag){
				//w是v的第一个未被访问的邻接顶点，作为根的左孩子结点
				t->firstchild = p;
				firsttag = false;
			} else {
				//w是v的其他未被访问的邻接结点，作为上一邻接定点的右兄弟
				q->nextsibling = p;
			}
			q = p;
			//从第w个顶点出发深度优先遍历图G,建立生成子树*q
			DFSTree(w,q);
		}
	}
}
template <class T>
void ATGraph<T>::DFSForest(CSTree<T>* &t){
	//建立无向图的深度优先生成森林的孩子兄弟链表
	CSTree<T> *p,*q;
	t = NULL;
	for(int index = 0;index <= atgraph.vexNum;++index){
		visited[index] = false;
	}
	for(int index = 0;index <= atgraph.vexNum;++index){
		if(visited[index] == false){
			//第index个顶点不曾被访问
			//建立以第index个顶点为根的生成树
			p = new CSTree<T>;
			p->data = GetVertex(index);
			p->firstchild = NULL;
			p->nextsibling = NULL;
			if (!t) {
				t = p;//t是第一棵生成树
			} else {
				//前一棵的根的兄弟是其他生成树的根
				q->nextsibling = p;
			}
			q = p;//q指示当前生成树的根
			DFSTree(index,p);//建立以p为根的生成树
		}
	}
}
template <class T>
void ATGraph<T>::PreOrderTraverse(CSTree<T>* &t,bool (*visit)(T v)){
	//先根遍历二叉链表结构的树t
	if(t){
		visit(t->data);
		PreOrderTraverse(t->firstchild,visit);
		PreOrderTraverse(t->nextsibling,visit);
	}
}
template <class T>
void ATGraph<T>::BTreetoForest(CSTree<T>* &t){
	//二叉树(左分支是孩子，右分支是兄弟)转换为森林
	CSTree<T> *q;
	int j = 0;
	while(t){
		q = t;
		t = t->nextsibling;
		if(t){
			j++;
			q->nextsibling = NULL;
		} else {
			if(j > 0)
				j++;
		}
		if (j == 0) {
			cout << "先序遍历生成树为: "<<endl;
		} else {
			cout << "先序遍历生成森林第"<<j<<"棵树为："<<endl;
		}
		PreOrderTraverse(q,visit);
		cout << endl;
	}//endwhile
}
