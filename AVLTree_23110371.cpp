#include <bits/stdc++.h>
#define LH -1
#define EH 0
#define RH 1
#define ElementType int
using namespace std;

struct AVLNode {
    char balFactor;
    ElementType key;
    int count;
    AVLNode *pLeft;
    AVLNode *pRight;
};

AVLNode* CreateNode(ElementType key) {
    AVLNode *p = new AVLNode();
    p->balFactor = EH;
    p->key = key;
    p->count=1;
    p->pLeft = NULL;
    p->pRight = NULL;
    return p;
}

int IsEmptyTree(AVLNode* root) {
    return root == NULL;
}

void LL(AVLNode* &T) {
    AVLNode *T1 = T->pLeft;
    T->pLeft = T1->pRight;
    T1->pRight = T;

    switch (T1->balFactor) {
        case LH:
            T->balFactor = EH;
            T1->balFactor = EH;
            break;
        case EH:
            T->balFactor = LH;
            T1->balFactor = RH;
            break;
    }

    T = T1;
}

void LR(AVLNode* &T) {
    AVLNode *T1 = T->pLeft;
    AVLNode *T2 = T1->pRight;

    T->pLeft = T2->pRight;
    T2->pRight = T;
    T1->pRight = T2->pLeft;
    T2->pLeft = T1;

    switch (T2->balFactor) {
        case LH:
            T->balFactor = RH;
            T1->balFactor = EH;
            break;
        case EH:
            T->balFactor = EH;
            T1->balFactor = EH;
            break;
        case RH:
            T->balFactor = EH;
            T1->balFactor = LH;
            break;
    }

    T2->balFactor = EH;
    T = T2;
}

void RR(AVLNode* &T) {
    AVLNode *T1 = T->pRight;
    T->pRight = T1->pLeft;
    T1->pLeft = T;

    switch (T1->balFactor) {
        case RH:
            T->balFactor = EH;
            T1->balFactor = EH;
            break;
        case EH:
            T->balFactor = RH;
            T1->balFactor = LH;
            break;
    }

    T = T1;
}

void RL(AVLNode* &T) {
    AVLNode *T1 = T->pRight;
    AVLNode *T2 = T1->pLeft;

    T->pRight = T2->pLeft;
    T2->pLeft = T;
    T1->pLeft = T2->pRight;
    T2->pRight = T1;

    switch (T2->balFactor) {
        case RH:
            T->balFactor = LH;
            T1->balFactor = EH;
            break;
        case EH:
            T->balFactor = EH;
            T1->balFactor = EH;
            break;
        case LH:
            T->balFactor = EH;
            T1->balFactor = RH;
            break;
    }

    T2->balFactor = EH;
    T = T2;
}

bool InsertNode(AVLNode* &root, AVLNode* &a) {
    if (root == NULL) {
        root = a;
        return true;
    }

    bool heightIncreased = false;

    if (a->key < root->key) {
        if (InsertNode(root->pLeft, a)) {
            switch (root->balFactor) {
                case RH:
                    root->balFactor = EH;
                    heightIncreased = false;
                    break;
                case EH:
                    root->balFactor = LH;
                    heightIncreased = true;
                    break;
                case LH:
                    if (root->pLeft->balFactor == LH) {
                        LL(root);
                    } else {
                        LR(root);
                    }
                    heightIncreased = false;
                    break;
            }
        }
    } 
	else if (a->key > root->key) {
        if (InsertNode(root->pRight, a)) {
            switch (root->balFactor) {
                case LH:
                    root->balFactor = EH;
                    heightIncreased = false;
                    break;
                case EH:
                    root->balFactor = RH;
                    heightIncreased = true;
                    break;
                case RH:
                    if (root->pRight->balFactor == RH) {
                        RR(root);
                    } else {
                        RL(root);
                    }
                    heightIncreased = false;
                    break;
            }
        }
    } 
	else {
		a->count++;
        return false;
    }
    return heightIncreased;
}
bool DeleteNode(AVLNode* &root, ElementType key) {
    if (root == NULL) return false;

    bool heightDecreased = false;

    if (key < root->key) {
        if (DeleteNode(root->pLeft, key)) {
            switch (root->balFactor) {
                case LH:
                    root->balFactor = EH;
                    heightDecreased = true;
                    break;
                case EH:
                    root->balFactor = RH;
                    heightDecreased = false;
                    break;
                case RH:
                    if (root->pRight->balFactor == RH) {
                        RR(root);
                        heightDecreased = true;
                    } else {
                        RL(root);
                        heightDecreased = false;
                    }
                    break;
            }
        }
    } 
    else if (key > root->key) {
        if (DeleteNode(root->pRight, key)) {
            switch (root->balFactor) {
                case RH:
                    root->balFactor = EH;
                    heightDecreased = true;
                    break;
                case EH:
                    root->balFactor = LH;
                    heightDecreased = false;
                    break;
                case LH:
                    if (root->pLeft->balFactor == LH) {
                        LL(root);
                        heightDecreased = true;
                    } else {
                        LR(root);
                        heightDecreased = false;
                    }
                    break;
            }
        }
    } 
    else {
        AVLNode* temp = root;
        if (root->pLeft == NULL) {
            root = root->pRight;
            heightDecreased = true;
        } 
        else if (root->pRight == NULL) {
            root = root->pLeft;
            heightDecreased = true;
        } 
        else {
            AVLNode* replace = root->pRight;
            while (replace->pLeft != NULL) {
                replace = replace->pLeft;
            }
            root->key = replace->key;
            DeleteNode(root->pRight, replace->key);
        }
        delete temp;
    }

    return heightDecreased;
}
AVLNode* SearchNode(AVLNode* T, ElementType a){
	if(!T)
		return NULL;
	if(T->key==a)	return T;
	AVLNode *p=SearchNode(T->pLeft,a);
	if(p)	return p;
	return SearchNode(T->pRight,a);
}
void PrintTree_PreOrder(AVLNode* T){
	if(T!=NULL){
		cout<<T->key<<" ";
		PrintTree_PreOrder(T->pLeft);
		PrintTree_PreOrder(T->pRight);
	}
}
void PrintTree_InOrder(AVLNode* T){
	if(T!=NULL){
		PrintTree_PreOrder(T->pLeft);
		cout<<T->key<<" ";
		PrintTree_PreOrder(T->pRight);
	}
}
void PrintTree_PostOrder(AVLNode* T){
	if(T!=NULL){
		PrintTree_PreOrder(T->pLeft);
		PrintTree_PreOrder(T->pRight);
		cout<<T->key<<" ";
	}
}
int HighT(AVLNode* T){
	if(!T)	return 0;
	int hl=HighT(T->pLeft);
	int hr=HighT(T->pRight);
	if(hl>hr)
		return 1+hl;
	else
		return 1+hr;
}
int CountNodeMedium (AVLNode* root)
{
	if (!root) return 0;
	int nlm = CountNodeMedium (root->pLeft);
	int nrm = CountNodeMedium (root->pRight);
	if (root->pLeft || root->pRight)
		return (1 + nlm + nrm);
	return (nlm + nrm);
}
int CountNode (AVLNode* root)
{
	if (!root) return 0;
	int nl = CountNode (root->pLeft);
	int nr = CountNode (root->pRight);
	return (1 + nl + nr);
}
int CountLeafNodes(AVLNode* root) {
    if (!root) 
        return 0;
    if (!root->pLeft && !root->pRight) 
        return 1;
    return CountLeafNodes(root->pLeft) + CountLeafNodes(root->pRight);
}
	
int CountEven(AVLNode* root){
	if (!root) return 0;
		int nlm = CountEven(root->pLeft);
		int nrm = CountEven(root->pRight);
	if(root->key%2==0)
		return 1+nlm+nrm;
	return (nlm + nrm);
}
long SumNode(AVLNode* T){
	if(!T)	return 0;
	int suml=SumNode(T->pLeft);
	int sumr=SumNode(T->pRight);
	return T->key+suml+sumr;
}
ElementType Max(ElementType a, ElementType b){
	return a>b ? a:b;
}
ElementType NodeMax(AVLNode* root){
	if(!root->pLeft && !root->pRight)
		return root->key;
	ElementType maxl=NodeMax(root->pLeft);
	ElementType maxr=NodeMax(root->pRight);
	return Max(root->key,(maxl,maxr));
}
ElementType Min(ElementType a, ElementType b){
	return a<b ? a:b;
}
ElementType NodeMin(AVLNode* root){
	if(!root->pLeft && !root->pRight)
		return root->key;
	ElementType minl=NodeMin(root->pLeft);
	ElementType minr=NodeMin(root->pRight);
	return Min(root->key,(minl,minr));
}
ElementType NegNodeMax(AVLNode* root){
	if(root->key<0)
		return root->key;
	else
		return INT_MIN;
	ElementType maxl=NegNodeMax(root->pLeft);
	ElementType maxr=NegNodeMax(root->pRight);
	if(root->key<0)
		return Max(root->key,(maxl,maxr));
	return Max(maxl,maxr);
}
int countDistinctValues(ElementType arr[], int n) {
    AVLNode* root = new AVLNode;
    for (int i = 0; i < n; ++i) {
    	AVLNode* p=CreateNode(arr[i]);
        InsertNode(root,p);
    }
    return CountNode(root);
}
void printCounts(AVLNode* root) {
    if (root!=NULL) {
        printCounts(root->pLeft);
        cout << "'" << root->key << "' xuat hien " << root->count << " lan" << endl;
        printCounts(root->pRight);
    }
}
void menu(){
	cout<<"=====================Menu=====================";
	cout<<"\n0.Thoat chuong trinh";
	cout<<"\n1.Chieu cao cay";
	cout<<"\n2.So node cua nhanh cay";
	cout<<"\n3.So phan tu chan tren cay";
	cout<<"\n4.Tong gia tri cac nut tren cay";
	cout<<"\n5.Gia tri lon nhat va gia tri nho nhat tren cay";
	cout<<"\n6.Phan tu max am tren cay";
	cout<<"\n7.So gia tri phan biet trong day so cho truoc";
	cout<<"\n8.So luong phan tu cua cua cac gia tri phan biet";
	cout<<"\n9.Nhap phan tu";
	cout<<"\n10.Xoa phan tu";
	cout<<"\n11.Xuat kieu tien tu";
	cout<<"\n12.Xuat kieu trung tu";
	cout<<"\n13.Xuat kieu hau tu";
	cout<<"\nHay nhap lua chon cua ban: ";
}
void Execute(){
	AVLNode *T, *a;
	T=NULL;
	int n,choice,value;
	int b[101];
	do{
		menu();
		cin>>choice;
		switch(choice){
			case 0:
				cout<<"Thoat chuong trinh thanh cong!";
				exit(0);
			case 1:
				cout<<HighT(T);
				break;
			case 2:
				cout<<CountNodeMedium(T);
				break;
			case 3:
				cout<<CountLeafNodes(T);
				break;
			case 4:
				cout<<SumNode(T);
				break;
			case 5:
				cout<<"Gia tri lon nhat: "<<NodeMax(T)<<", gia tri nho nhat: "<<NodeMin(T);
				break;
			case 6:
				cout<<NegNodeMax(T);
				break;
			case 7:
				cout<<"Nhap vao so luong phan tu: ";
				cin>>n;
				cout<<"Nhap vao mot day so n phan tu: ";
				for(int i=0;i<n;i++){
					cin>>b[i];
				}
				cout<<countDistinctValues(b,n);
				break;
			case 8:
				printCounts(T);
				break;
			case 9:
				cout<<"Nhap gia tri: ";
				cin>>value;
				a=CreateNode(value);
				InsertNode(T,a);
				break;
			case 10:
				cout<<"Nhap gia tri can xoa: ";
				cin>>value;
				DeleteNode(T,value);
				break;
			case 11:
				PrintTree_PreOrder(T);
				break;
			case 12:
				PrintTree_InOrder(T);
				break;
			case 13:
				PrintTree_PostOrder(T);
				break;
			default:
				cout<<"Nhap loi, nhap lai";
			
		}
		cout<<"\n";
		system("pause");
		system("cls");
	}while(choice!=0);
}
int main(){
	Execute();
	return 0;
	
}

