#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

struct data{
	int No,durasi;
	tm* CT; //CT=CurrentTime
	int id, plat;
};

typedef struct TElmtList *address;
typedef struct TElmtList{
	data info;
 	address next;
 	address prev;
} ElmtList;

typedef struct {
	address first;
 	address last;
}List ;

//SELEKTOR
#define info(P) (P)->info
#define Next(P) (P)->next
#define Prev(P) (P)->prev
#define First(L) ((L).first)
#define Last(L) ((L).last)

bool IsEmpty(List L){
	return (First(L)==NULL && Last(L)==NULL);
}

void CreateList(List *L){
	First(*L)=NULL;
	Last(*L)=NULL;
}

address Allocation(data info){
	address NewElmt;
	NewElmt = (ElmtList*) malloc (sizeof(ElmtList));
	info(NewElmt) = info;
	Next(NewElmt)=NULL;
	Prev(NewElmt)=NULL;
	return NewElmt;
}

void Deallocation (address hapus){
	free(hapus);
}

void DeleteAfter (List *L, address *Pdel, address Prec);
void DeleteFirst(List *L, address *P);

void Search (List L, int x){
	address P = First(L);
	while(P !=NULL){
		if(info(P).No==x){
			cout<<info(P).No;
			cout<<info(First(L)).No;
			if(P==First(L)) DeleteFirst(&L, &First(L));
			else DeleteAfter(&L, &P, Prev(P));
			break;
		}
		P=Next(P);
		cout<<"Berhasil menghapus no "<< x;
		
	}
	
}

bool SearchDouble (List L, int x){
	address P = First(L);
	while(P !=NULL){
		if(info(P).No==x){
			return true;
			break;
		}
		P=Next(P);
	}
	return false;
	
}

 void waktu (tm* now);
 
void SearchLiat (List L, int x){
	address temp = First(L);
	while(temp !=NULL){
		if(info(temp).No==x){
			cout<<"Nomor Urut : "<<temp->info.No<<"\n";
		    cout<<"Nomor ID   : "<<temp->info.id<<"\n";
		    cout<<"Nomor Plat : "<<temp->info.plat<<"\n";
		    cout<<"Durasi : "<<temp->info.durasi<<" Hari \n";
		    cout<<"Waktu : ";
			waktu(temp->info.CT);
			cout<<"\n";
			break;
		}
		temp=Next(temp);
		cout<<"Data Tidak Ditemukan \n \n ";
		
	}
	
}


void InsertFirst(List *L, address P){
	if(IsEmpty(*L)){
		First(*L)=P;
		Last(*L)=P;
	}else{
		Next(P)=First(*L);
		Prev(First(*L))=P;
		First(*L)=P;
	}
}



void InsertLast(List *L, address P){
	if(IsEmpty(*L)){
		InsertFirst(L,P);
	}else{
		Next(Last(*L))=P;
		Prev(P)=Last(*L);
		Last(*L)=P;
	}
}
void InsertAfter(List *L, address P, address Prec){
	if(Next(Prec)==NULL){
		InsertLast(L,P);
	}else{
		Next(P)=Next(Prec);
		Prev(P)=Prec;
		Prev(Next(Prec))=P;
		Next(Prec)=P;
	}
}
void InsertBefore (List *L, address P, address Succ){
	if(Succ == First(*L)){
		InsertFirst(L,P);
	}else{
		Next(Prev(Succ))=P;
		Prev(P)=Prev(Succ);
		Next(P)=Succ;
		Prev(Succ)=P;
	}
}
void DeleteFirst(List *L, address *P){
	*P=First(*L);
	First(*L)=Next(*P);
	Next(*P)=NULL;
	Prev(First(*L))=NULL;
	Deallocation(*P);
}
void DeleteLast(List *L, address *p){
	*p=Last(*L);
	Last(*L)=Prev(*p);
	Next(Last(*L))=NULL;
	Prev(*p)=NULL;
	Deallocation(*p);
}
void DeleteAfter (List *L, address *Pdel, address Prec){

	Next(Prec) = Next(*Pdel);
	Prev(Next(*Pdel))=Prec;
	Prev(*Pdel)=NULL;
	Next(*Pdel)=NULL;
	Deallocation(*Pdel);	
	
}
void DeleteBefore (List *L, address *Pdel, address Succ){
	*Pdel = Prev(Succ);
	Next(Prev(*Pdel))=Succ;
	Prev(Succ)=Prev(*Pdel);
	Prev(*Pdel)=NULL;
	Next(*Pdel)=NULL;
	Deallocation(*Pdel);
}
 void waktu (tm* now){
    cout << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday << " Jam "
         <<  now->tm_hour << ":"
         <<  now->tm_min
         << "\n";
 }
 

 
void func(List *L, data *q)
{
    address p = (ElmtList*) malloc(sizeof(ElmtList));
    p->info.No = q->No;
    p->info.id = q->id;
    p->info.plat = q->plat;
    p->info.durasi = q->durasi;
    p->info.CT = q->CT;
    InsertFirst(L, p);
    
}
 
 
 void TambahPenyewaan(List *L){
 	data *q = (data*)malloc(sizeof(data));
    cout<<"Nomor Urut : ";
 	cin>> q->No;
 	bool kondisi = SearchDouble(*L, q->No);
 	if(kondisi) cout<<"Data Sudah ada \n";
 	else{
 		cout<<"id Peminjam : ";
	 	cin>>q->id;
	 	cout<<" Plat : ";
	 	cin>>q->plat;
		cout<<"Durasi : ";
	 	cin>>q->durasi;
	 	time_t t =time(0);   // get time now
	    q->CT = localtime(&t);
	    func(L, q);
		cout<<"Penyimpanan Berhasil \n";
	 }
 
 }
 void UpdatePenyewaan(){
 	
 }
 
 
 void HapusPenyewaan(List *L){
 	int info;
 	cout<<"No Urut anda yang mau di hapus : ";
 	cin>>info;
 	Search(*L,info);
 	cout<<"Berhasil di hapus";
 }
 
 
 void CariPenyewaan(List L){
 	int info;
 	cout<<"No Urut anda yang mau dicari : ";
 	cin>>info;
 	SearchLiat(L,info);
 }
 
   void DaftarPenyewaan(List L){
  
	if(!IsEmpty(L)){
		address temp =First(L);
		while(Next(temp)!=NULL){
			cout<<"Nomor Urut : "<<temp->info.No<<"\n";
		    cout<<"Nomor ID   : "<<temp->info.id<<"\n";
		    cout<<"Nomor Plat : "<<temp->info.plat<<"\n";
		    cout<<"Durasi : "<<temp->info.durasi<<" Hari \n";
		    cout<<"Waktu : ";
			waktu(temp->info.CT);
			cout<<"\n";
			temp = Next(temp);
		}
			cout<<"Nomor Urut : "<<temp->info.No<<"\n";
		    cout<<"Nomor ID   : "<<temp->info.id<<"\n";
		    cout<<"Nomor Plat : "<<temp->info.plat<<"\n";
		    cout<<"Durasi : "<<temp->info.durasi<<"Jam \n";
		    cout<<"Waktu : ";
			waktu(temp->info.CT);
			cout<<"\n";
	}
	
 }
 
 
 void menu(List *L){
 	int i;
 	while(i!=6){
	 
 	cout<<"Pilian Menu\n"
 		<<"1. Tampilkan Daftar Penyewaan\n"
 		<<"2. Tambahkan Penyewaan\n"
 		<<"3. Update Penyewaan\n"
 		<<"4. Hapus Penyewaan\n"
 		<<"5. Cari Penyewaan\n"
 		<<"6. Keluar\n";
 		cout<<"Pilihan : ";
 		cin>>i;
 		switch (i){
 			case 1:
 				DaftarPenyewaan(*L);
 				break;
 			case 2:
 				TambahPenyewaan(L);
 				break;
 			case 3:
 				UpdatePenyewaan();
 				break;
 			case 4:
 				HapusPenyewaan(L);
 				break;
 			case 5:
 				CariPenyewaan(*L);
 				break;
 			case 6:
 				break ;
		}
	}	 
 }

 
 
int main(){
	List sewa;
	CreateList(&sewa);
	menu(&sewa);		
}
