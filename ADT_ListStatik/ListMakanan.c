/* File: ListMakanan.c */
/* Implementasi header ListMakanan.h */

#include "ListMakanan.h"


/* ********** KONSTRUKTOR ********** */
void CreateListMakanan(ListMakanan *l)
{
    /* I.S. l sembarang */
    /* F.S. Terbentuk List Makanan kosong dengan kapasitas CONFIG_SIZELM */
    LengthLM(*l) = 0;
}

/* ********** SELEKTOR ********** */
/* l adalah ListMakanan; selektor khusus dalam file; l tak dapat berubah */
// #define LengthLM(l) (l).NElmt           /* get/set ukuran list */
// #define ListMkn(l) (l)._MAKANAN_        /* get/set pointer list */
// #define ElmtLM(l,i) LMakanan[i]         /* get/set elemen list ke-i */

IDEM GetIdMkn(ListMakanan l, int i)
{
    /* l terdefinisi dan i valid untuk l, yaitu [0..NElmt-1] */
    /* Mengembalikan int ID makanan index ke-i */
    return ID(ElmtLM(l, i));
}

NamaMakanan GetNamaMkn(ListMakanan l, int i)
{
    /* l terdefinisi dan i valid untuk l, yaitu [0..NElmt-1] */
    /* Mengembalikan String nama makanan index ke-i*/
    return Judul(ElmtLM(l, i));
}

TIME GetKadaluarsaMkn(ListMakanan l, int i)
{
    /* l terdefinisi dan i valid untuk l, yaitu [0..NElmt-1] */
    /* Mengembalikan _TIPE_TIME_ dari kadaluarsa makanan index ke-i*/
    return Exp(ElmtLM(l, i));
}

TIME GetActionTimeMkn(ListMakanan l, int i)
{
    /* l terdefinisi dan i valid untuk l, yaitu [0..NElmt-1] */
    /* Mengembalikan _TIPE_TIME_ dari Waktu pengiriman makanan index ke-i*/
    return TimeAct(ElmtLM(l, i));
}

Word GetActionLocMkn(ListMakanan l, int i)
{
    /* l terdefinisi dan i valid untuk l, yaitu [0..NElmt-1] */
    /* Mengembalikan String lokasi aksi makanan index ke-i*/
    return Locate(ElmtLM(l, i));
}

// POINT GetUkuranMkn(ListMakanan l, int i);
/* l terdefinisi dan i valid untuk l, yaitu [0..NElmt-1] */
/* Mengembalikan _TIPE_UKURAN_MAKANAN_  makanan index ke-i*/

/* ***** Operasi pencarian elemen ***** */
boolean isIdValid(ListMakanan l, IDEM id)
{
    /* Mengembalikan true jika id ada di dalam list */
    /* KAMUS LOKAL */
    IdxTypeLM i;
    boolean found;

    /* ALGORITMA */
    while (!found && i <= LengthLM(l))
    {
        found = ID(ElmtLM(l, i)) == id;
        i++;
    }

    return found;
}

IdxTypeLM SearchIndexbyId(ListMakanan l, IDEM id)
{
    /* mengembalikan index jika menemukan Id pada list */
    /* KAMUS LOKAL */
    IdxTypeLM i;
    boolean found;

    /* ALGORITMA */
    i = 0;
    found = false;
    while (!found && i < LengthLM(l))
    {
        if (ID(ElmtLM(l, i)) == id)
        {
            found = true;
        }
        else
        {
            i++;
        }
    }

    if (found)
    {
        return i;
    }
    else
    {
        return IDX_UNDEF_LM;
    }
}

/* Precond : untuk setiap parameter Id adalah valid dan pasti ada dalam list makanan */
ElListMakananType MknId(ListMakanan l, IDEM id)
{
    /* mengambalikan tipe Makanan berdasarkan ID makanan */
    /* KAMUS LOKAL */
    IdxTypeLM i;

    /* ALGORITMA */
    i = SearchIndexbyId(l, id);
    return ElmtLM(l, i);
}

NamaMakanan NamaMknId(ListMakanan l, IDEM id)
{
    /* mengambalikan nama makanan berdasarkan ID makanan */
    return Judul(MknId(l, id));
}

TIME KedaluarsaMknId(ListMakanan l, IDEM id)
{
    /* Mengembalikan nama makanan berdasarkan ID makanan */
    return Exp(MknId(l, id));
}

TIME ActionTimeMknId(ListMakanan l, IDEM id)
{
    /* Mengembalikan waktu pengiriman makanan berdasarkan Id makanan*/
    return TimeAct(MknId(l, id));
}

LokasiAksi ActionLocId(ListMakanan l, IDEM id)
{
    /* Mengembalikan lokasi aksi makanan berdasarkan Id makanan */
    return Locate(MknId(l, id));
}

void insertLM(ListMakanan *l, MAKANAN m)
/* I.S. l tidak penuh, l dan m terdefinisi */
/* F.S. elemen m ditambahkan ke akhir list l */
{
    ElmtLM(*l, LengthLM(*l)) = m;
    LengthLM(*l) = LengthLM(*l) + 1;
}

void accumLM(ListMakanan *l1, ListMakanan l2) 
/* I.S. l1 dan l2 terdefinisi, jumlah dari panjang l1 dan l2 tidak melebih CONFIG_SIZELM */
/* F.S. isi dari l2 tersalin dan ditambahkan ke l1*/
{
    // KAMUS LOKAL
    int i;
    // ALGORITMA
    if (LengthLM(l2) > 0) {
        for (i = 0; i < LengthLM(l2); i++) {
            ElmtLM(*l1, LengthLM(*l1)) = ElmtLM(l2, i);
            LengthLM(*l1) = LengthLM(*l1) + 1;
        }
    }
}

/* ********** INPUT / OUTPUT ********** */
void SetUpListMakanan(ListMakanan *l, char *filename)
{
    /* I.S. Sembarang */
    /* I.F. Terbentuk list makanan berdasarkan hasil konfigurasi */
    /* NElmt list pasti sama dengan CONFIG_SIZELM */
    /* KMAMUS LOKAL */
    IdxTypeLM i;
    TIME tempT;
    MAKANAN tempM;
    int D, M, H;

    CreateListMakanan(l);
    STARTLINE(filename);
    STARTWORD();
    LengthLM(*l) = wordToInt(currentWord);
    i = 0;

    while (i < LengthLM(*l))
    {
        // ID
        ADVLINE();
        STARTWORD();
        ID(tempM) = wordToInt(currentWord);
        // Judul Makanan
        ADVLINE();
        Judul(tempM) = currentLine;
        // exp Time
        ADVLINE();
        STARTWORD();
        D = wordToInt(currentWord);
        ADVWORD();
        M = wordToInt(currentWord);
        ADVWORD();
        H = wordToInt(currentWord);
        CreateTime(&tempT, D, M, H);
        Exp(tempM) = tempT;
        // TAction Time
        ADVLINE();
        STARTWORD();
        D = wordToInt(currentWord);
        ADVWORD();
        M = wordToInt(currentWord);
        ADVWORD();
        H = wordToInt(currentWord);
        CreateTime(&tempT, D, M, H);
        TimeAct(tempM) = tempT;
        // lokasi
        ADVLINE();
        STARTWORD();
        Locate(tempM) = currentWord;

        ElmtLM(*l, i) = tempM;
        i++;
    }
}

ListMakanan DisplayBuyAbleLM(ListMakanan l)
{
    /* I.S. l tidak kosong, terdapat command BUY dan Simulator adjecent dengan B */
    /* F.S. menampilkan bahan makanan yang memiliki String _LOKASI_AKSI_MAKANAN_ "BUY" */
    /* contoh tampilan :
        =========================
        =          BUY          =
        =========================
        List Bahan Makanan:
        1. Cabai (2 menit)
        2. Bawang (1 menit)
        3. Ayam Mentah (5 jam)
    */
    /* KAMUS LOKAL */
    int i, n;
    ListMakanan listBuyable;

    /* ALGORITMA */
    printf("=========================================\n");
    printf("=                   BUY                 =\n");
    printf("=========================================\n");
    printf("List Bahan Makanan\n");

    CreateListMakanan(&listBuyable);
    i = 0;
    while (i < LengthLM(l))
    {
        if (isWordSame(GetActionLocMkn(l, i), "Buy"))
        {
            printf("   %d. %s   \t(", LengthLM(listBuyable)+1, GetNamaMkn(l, i).Tabword);
            DisplayTIMEk(GetActionTimeMkn(l, i));
            printf(")");
            printf("\n");
            ElmtLM(listBuyable, LengthLM(listBuyable)) = ElmtLM(l, i);
            LengthLM(listBuyable)++;
        }
        i++;
    }

    return listBuyable;
}

ListMakanan DisplayActionAbleLM(ListMakanan l, char *Lchar)
{
    /* I.S. l tidak kosong str valid yaitu command / simuulator terdapat pada FRY, CHOP, BOIL, MIX */
    /* F.S menampilkan bahan makanan yang memiliki String _LOKASI_AKSI_MAKANAN_ str */
    /* contoh tampilan :
    =========================
    =          FRY          =
    =========================
    List Bahan Makanan yang Bisa Dibuat:
    1. Ayam Goreng
    2. Sambal Goreng
    */
    /* KAMUS LOKAL */
    int i, n;
    ListMakanan listActionable;

    /* ALGORITMA */
    CreateListMakanan(&listActionable);

    i = 0;
    printf("===========");
    while (Lchar[i] != '\0')
    {
        printf("=");
        i++;
    }
    printf("===========\n");
    printf("=          ");
    printf("%s", Lchar);
    printf("          =\n");
    i = 0;
    printf("===========");
    while (Lchar[i] != '\0')
    {
        printf("=");
        i++;
    }
    printf("===========\n");

    i = 0;
    n = 1;
    printf("List Bahan Makanan yang Bisa Dibuat:\n");
    while (i < LengthLM(l))
    {
        if (isWordSame(GetActionLocMkn(l, i), Lchar))
        {
            ElmtLM(listActionable, LengthLM(listActionable)) = ElmtLM(l, i);
            LengthLM(listActionable)++;
            printf("   %d. %s", n, GetNamaMkn(l, i).Tabword);
            printf("\n");
            n++;
        }
        i++;
    }
    return listActionable;
}

void DisplayCatalog(ListMakanan l)
{
    /* I.S. l tidak kosong */
    /* F.S menampilkan Katalog makanan ketika command "CATALOG"*/
    /* Katalog adalah semua makanan dan bahan yang tersedia pada program */
    /* contoh tampilan :
    List Makanan
    |- Nama -|- Durasi Kedaluwarsa -|- Aksi yang  -|- Action Time -|
    |        |                      |- Diperlukan -|               |
    */
    /* KAMUS LOKAL */
    int i, cntStr, tempInt;
    TIME tempTime;

    printf("\xc9");
    for (i = 1; i <= 50; i++)
    {
        printf("\xcd"); // ░
    }
    printf(" LIST MAKANAN ");
    for (i = 1; i <= 51; i++)
    {
        printf("\xcd"); // ░
    }
    printf("\xbb");
    printf("\n");

    printf(" |-%20sNama%20s-|-%4sDurasi Kedaluarsa%3s-|-%sAksi yang %s-|-%7sAction Time%6s-|\n", "", "", "", "", "", "", "", "");
    printf(" | %20s    %20s | %4s                 %3s | %sDiperlukan%s | %7s           %6s |\n", "", "", "", "", "", "", "", "");

    for (i = 0; i < LengthLM(l); i++)
    {
        printf(" | ");

        cntStr = 0; // Nama Makanan
        while (GetNamaMkn(l, i).Tabword[cntStr] != '\0')
        {
            printf("%c", GetNamaMkn(l, i).Tabword[cntStr]);
            cntStr++;
        }
        while (cntStr < 44)
        {
            printf(" ");
            cntStr++;
        }
        printf(" | ");

        cntStr = 0; // Kedaluarsa Time
        DisplayTIMEk(GetKadaluarsaMkn(l, i));
        tempTime = GetKadaluarsaMkn(l, i);
        tempInt = TIMEToMin(GetKadaluarsaMkn(l, i));

        cntStr += 7;
        if (tempTime.M > 9)
        {
            cntStr++;
        }

        if (tempInt >= 60)
        {
            cntStr += 6;

            if (tempTime.H >= 10)
            {
                cntStr++;
            }
        }

        if (tempInt >= 1440)
        {
            cntStr += 7;
            if (tempTime.D >= 10)
            {
                cntStr++;
            }

            if (tempTime.D >= 100)
            {
                cntStr++;
            }
        }

        while (cntStr < 24)
        {
            printf(" ");
            cntStr++;
        }
        printf(" | ");

        cntStr = 0; // Action Loc
        while (GetActionLocMkn(l, i).String[cntStr] != '\0')
        {
            printf("%c", GetActionLocMkn(l, i).String[cntStr]);
            cntStr++;
        }
        while (cntStr < 10)
        {
            printf(" ");
            cntStr++;
        }
        printf(" | ");

        cntStr = 0; // Action Time
        DisplayTIMEk(GetActionTimeMkn(l, i));
        tempTime = GetActionTimeMkn(l, i);
        tempInt = TIMEToMin(GetActionTimeMkn(l, i));

        cntStr += 7;
        if (tempTime.M > 9)
        {
            cntStr++;
        }

        if (tempInt >= 60)
        {
            cntStr += 6;

            if (tempTime.H >= 10)
            {
                cntStr++;
            }
        }

        if (tempInt >= 1440)
        {
            cntStr += 7;
            if (tempTime.D >= 10)
            {
                cntStr++;
            }

            if (tempTime.D >= 100)
            {
                cntStr++;
            }
        }

        while (cntStr < 24)
        {
            printf(" ");
            cntStr++;
        }

        printf(" | \n");
    }

    printf("\xc8");
    for (i = 1; i <= 46; i++)
    {
        printf("\xcd"); // ░
    }
    printf(" OVERCOOKING SIMULATOR ");
    for (i = 1; i <= 46; i++)
    {
        printf("\xcd"); // ░
    }
    printf("\xbc");
    printf("\n");
}