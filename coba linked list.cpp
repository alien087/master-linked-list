#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<math.h>
using namespace std;

typedef int infotype;
typedef struct TElmt *address;
typedef struct TElmt{
	infotype info;
	address next;
} Elmt;

struct List{
	address first;
};

void CreateEmpty(List *L){
	(*L).first=NULL;
}

bool IsEmpty(List L){
	return ((L).first==NULL);
}

address Allocation(infotype x){
	address NewElmt;
	
	NewElmt = (Elmt*) malloc(sizeof(Elmt));
	NewElmt->info = x;
	NewElmt->next = NULL;
	
	return NewElmt;
}

void Deallocation(address hapus){
	free(hapus);
}

void InsertFirst(List *L, infotype x){
	address NewElmt;
	NewElmt = Allocation(x);
	
	if(NewElmt != NULL){
		if(IsEmpty(*L)){
			(*L).first = NewElmt;
		}
		else{
			NewElmt->next = (*L).first;
			(*L).first = NewElmt;
		}
	}
}

void InsertAfter(address *PredElmt, infotype x){
	address NewElmt;
	NewElmt = Allocation(x);
	
	if(NewElmt != NULL){
		NewElmt->next = (*PredElmt)->next;
		(*PredElmt)->next=NewElmt;
	}
}

void InsertLast(List *L, infotype x){
	if (IsEmpty(*L)) InsertFirst(&(*L), x);
	else {
		address temp;
		temp = (*L).first;
		
		while(temp->next!=NULL) temp = temp->next;
		
		InsertAfter(&temp, x);
	}
}

void DeleteFirst(List *L, infotype *hapus){
	if(!IsEmpty(*L)){
		address temp;
		temp = (*L).first;
		*hapus = temp->info;
		(*L).first = (*L).first->next;
		temp->next = NULL;
		Deallocation(temp);
	}
}

void DeleteAfter(address pred, infotype *hapus){
	if(pred->next != NULL){
		address temp;
		temp = pred->next;
		*hapus = temp->info;
		pred->next = temp->next;
		temp->next = NULL;
		Deallocation(temp);
	}
}

void DeleteLast(List (*L), infotype *hapus){
	if(!IsEmpty(*L)){
		address temp, predTemp;
		predTemp = NULL;
		temp = (*L).first;
		while(temp->next != (*L).first){
			predTemp = temp;
			temp = temp->next;
		}
		
		if(temp == (*L).first) DeleteFirst(&(*L), &(*hapus));
		else DeleteAfter(predTemp, &(*hapus));
	}
}

void Sort(List (*L), int n){
	address p, q, temp;
	int j;
	p=(*L).first;
	q=p->next;
	for(int i=0; i<n; i++){
		for(int j=0; j<n-i-i; j++){
			if(p->info>q->info){
				temp = p;
				p = q;
				q = temp;
			}
			p=p->next;
			q=q->next;
		}
	}
}

int main(){
	address temp;
	List data;
	infotype x, tempHapus,n;
	
	CreateEmpty(&data);
	
	cin>>n;
	
	for(int i=0; i<n; i++) {
		cin>>x;
		InsertLast(&data, x);
	}
	
	temp = data.first;
	
	while(temp->next != data.first){
		cout<<temp->info<<"\n";
		temp = temp->next;
	}
}
