#include <iostream>
#include<cstdlib>
using namespace std;

typedef int infotype;
typedef struct TElmtList *address;
typedef struct TElmtList{
 infotype info;
 address next;
 address prev;
} ElmtList;

typedef struct {
 address first;
 address last;
}List ;

 //SELEKTOR 
#define Info(P) (P)->info
#define Next(P) (P)->next
#define Prev(P) (P)->prev
#define First(L) ((L).first)
#define Last(L) ((L).last)

//KONSTANTA
#define Nil NULL
#define Infinity 99999


/****************** TEST LIST KOSONG ******************/
bool IsEmpty(List L) {
/* Mengirim true jika list kosong. Lihat definisi di atas. */
 return (First(L) == NULL && Last(L) == NULL);
}


/****************** PEMBUATAN LIST KOSONG ******************/
void createList(List *L) {
 First(*L) = NULL;
 Last(*L) = NULL;
}

/****************** Manajemen Memori ******************/
address Allocation(infotype x) {
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Next(P)=Nil, Prev(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
 address NewElmt;
 NewElmt = (ElmtList*) malloc (sizeof(ElmtList));
 Info(NewElmt) = x;
 Next(NewElmt) = Nil;
 Prev(NewElmt) = Nil;
 return NewElmt;
}

void Deallocation(address hapus) {
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
 free(hapus);
}


/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X){
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
	address P = First(L);
	while (P != Nil){
		if (Info(P) == X){
			return P;
		}
		P = Next(P);
	}
	return Nil;
}


/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsertFirst(List *L, infotype x) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
 address NewElmt;
 NewElmt = Allocation(x);
 if (NewElmt != NULL) {
 if(IsEmpty(*L)){
 First(*L) = NewElmt;
 Last(*L) = NewElmt;
 } else{
 Next(NewElmt) = First(*L);
 Prev(First(*L)) = NewElmt;
 First(*L) = NewElmt;
 }
 }
}

void InsertLast(List *L, infotype x) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
 address NewElmt;
 NewElmt = Allocation(x);
 if (NewElmt != NULL) {
 if(IsEmpty(*L)){
 InsertFirst(L,x);
 } else{
 Next(Last(*L)) = NewElmt;
 Prev(NewElmt) = Last(*L);
 Last(*L) = NewElmt;
 }
 }
}


/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
	if(IsEmpty(*L)){
 First(*L) = P;
 Last(*L) = P;
 } else{
 Next(P) = First(*L);
 Prev(First(*L)) = P;
 First(*L) = P;
 }
}

void InsertLast (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
	if(IsEmpty(*L)){
 InsertFirst(L,P);
 } else{
 Next(Last(*L)) = P;
 Prev(P) = Last(*L);
 Last(*L) = P;
 }
}

void InsertAfter (List *L, address P, address Prec){
/* I.S. Prec pastilah elemen list; P sudah dialokasi */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
	if(Next(Prec) == Nil){
	InsertLast(L,P);
	}else{
	Next(P) = Next(Prec);
	Prev(P) = Prec;
	Prev(Next(Prec))= P;
	Next(Prec) = P;
	}
}

void InsertBefore (List *L, address P, address Succ){
/* I.S. Succ pastilah elemen list; P sudah dialokasi */
/* F.S. Insert P sebagai elemen sebelum elemen beralamat Succ */
	if(Succ == First(*L)){
	InsertFirst(L,P);
	}else{
	Next(Prev(Succ)) = P;
	Prev(P) = Prev(Succ);
	Next(P) = Succ;
	Prev(Succ) = P;
	}
}


/*** PENGHAPUSAN SEBUAH ELEMEN ***/

void DelFirst (List *L, address *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/* Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
	*P = First(*L);
	First(*L) = Next(*P);
	Prev(First(*L)) = Nil;
	Deallocation(*P);
}

void DelLast (List *L, address *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan */
/* Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, jika ada */
	*P = Last(*L);
	Last(*L) = Prev(*P);
	Next(Last(*L)) = Nil;
	Prev(*P) = Nil;
	Deallocation(*P);
}



void DelAfter (List *L, address *Pdel, address Prec){
/* I.S. List tidak kosong. Prec adalah anggota list. */
/* F.S. Menghapus Next(Prec): */
/* Pdel adalah alamat elemen list yang dihapus */
	*Pdel = Next(Prec);
	Next(Prec) = Next(*Pdel);
	Prev(Next(*Pdel)) = Prec;
	Prev(*Pdel) = Nil;
	Next(*Pdel)= Nil;
	Deallocation(*Pdel);
}

void DelBefore (List *L, address *Pdel, address Succ){
/* I.S. List tidak kosong. Succ adalah anggota list. */
/* F.S. Menghapus Prev(Succ): */
/* Pdel adalah alamat elemen list yang dihapus */
	*Pdel = Prev(Succ);
	Next(Prev(*Pdel)) = Succ;
	Prev(Succ) = Prev(*Pdel);
	Prev(*Pdel) = Nil;
	Next(*Pdel) = Nil;
	Deallocation(*Pdel);
}

void DelP (List *L, infotype X){
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X */
/* maka P dihapus dari list dan didealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
	address P = Search(*L,X);
	address prec = Prev(P);
	if (P != Nil){
		if(P == First(*L)){
			DelFirst(L,&P);
		}else if(P == Last(*L)){
			DelLast(L,&P);
		}else{
			DelAfter(L,&P,prec);
		}
	}
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintForward (List L){
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen pertama */
/* ke elemen terakhir secara horizontal ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
	cout<<"[";
	if(!IsEmpty(L)){
	address temp =First(L);
	while(Next(temp)!=NULL){
	cout<<Info(temp) <<", ";
	temp = Next(temp);
	}
	cout<<Info(temp);
	}
	cout<<"]"<<endl;
}

void PrintBackward (List L){
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen terakhir */
/* ke elemen pertama secara horizontal ke kanan: [en,en-1,...,e2,e1] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [30,20,1] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
	cout<<"[";
	if(!IsEmpty(L)){
	address temp =Last(L);
	while(Prev(temp)!=NULL){
	cout<<Info(temp) <<", ";
	temp = Prev(temp);
	}
	cout<<Info(temp);
	}
	cout<<"]"<<endl;
}


int main(){
	List L;
	createList(&L);
	int x, y, hapus;
	cout<<"Masukkan Jumlah Angka : "; cin>>x;
	
	for(int i=0; i<x; i++){
		cin>>y;
		InsertLast(&L, y);
	}
	
	PrintForward(L);
	
	cout<<"Masukkan Angka Yang ingin Dihapus : "; cin>>hapus;
	 DelP(&L, hapus);
	 
	cout<<"Setelah Penghapusan : "; PrintForward(L);
}
