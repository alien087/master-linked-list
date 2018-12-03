#include<bits/stdc++.h>
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
	address last;
};

void CreateEmpty(List *L){
	(*L).first=NULL;
	(*L).last=NULL;
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

		if(IsEmpty(*L)){
			(*L).first = NewElmt;
			(*L).last = NewElmt;
		}
		else {
			NewElmt->next = (*L).first;
			(*L).first = NewElmt;
		}
		(*L).last->next = (*L).first;
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
		address newElmt = Allocation(x);
		(*L).last->next=newElmt;
		(*L).last = newElmt;
		(*L).last->next = (*L).first;
	}
}

void DeleteFirst(List *L, infotype *hapus){
	address temp;
	temp = (*L).first;
	*hapus = temp->info;
	
	if((*L).last==temp) {
		(*L).first=NULL;
		(*L).last=NULL;
	}
	
	else{
		(*L).first = (*L).first->next;
		(*L).last->next=(*L).first;	
	}
	
	temp->next = NULL;
	Deallocation(temp);
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
		
		if((*L).last == (*L).first) DeleteFirst(&(*L), &(*hapus));
		else{
			(*L).last=predTemp;
			predTemp->next=(*L).first;
			free(temp);
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
	
	while(temp->next != (data).first){
		//cout<<temp->info<<"\n";
		temp = temp->next;
	}
	cout<<temp->next->info<<"\n\n";

	return 0;
}
