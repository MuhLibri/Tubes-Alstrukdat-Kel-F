#include "CommandGame.h"

void splashInitGame()
{
    printf("=== SELAMAT DATANG DI OVERCOOKING SIMULATOR ===\n");
}

void splashExitGame()
{
    printf("=== TERIMA KASIH TELAH BERMAIN OVERCOOKING SIMULATOR ===\n");
    printf("===     games by Fakhri Akmal Nigel Libri Zaydan     ===\n");
}

void helpStartGame()
{
    printf("Daftar command yang tersedia:\n");
    printf("HELP\t- Menampilkan daftar command yang tersedia\n");
    printf("START\t- Memulai game\n");
    printf("EXIT\t- Keluar dari game\n");
}

void helpInGame()
{
    printf("Daftar command yang tersedia:\n");
    printf("HELP\t- Menampilkan daftar command yang tersedia\n");
    printf("\nCommand memasak:\n");
    printf("BUY\t- Membeli makanan dari toko\n");
    printf("MIX\t- Mencampurkan dua/lebih bahan makanan\n");
    printf("CHOP\t- Memotong bahan makanan menjadi potongan-potongan kecil\n");
    printf("FRY\t- Menggoreng bahan makanan\n");
    printf("BOIL\t- Merebus bahan makanan\n");
    printf("* Dekatkan Simulator ke lokasi memasak tersebut untuk melakukan aksi!\n");
    printf("\nCommand pergerakan:\n");
    printf("MOVE X\t- bergerak kearah yang dituju \n");
    printf("\t  X : NORTH, EAST, WEST, SOUTH\n");
    printf("WAIT X Y - Menunggu X jam Y menit\n");
    printf("\nCommand lain:\n");
    printf("DELIVERY- Menampilkan daftar barang yang dipesan\n");
    printf("INVENTORY - Menampilkan daftar bahan makanan yang dimiliki\n");
    printf("CATALOG\t- Menampilkan daftar makanan yang tersedia pada aplikasi\n");
    printf("COOKBOOK - Menampilkan daftar resep yang tersedia pada aplikasi\n");
    printf("RECOMMENDATION - Menampilkan resep yang dapat dibuat\n");
    printf("UNDO\t- Kembali ke kondisi sebelumnya\n");
    printf("REDO\t- Kembali ke kondisi setelah UNDO\n");
    printf("EXIT\t- Keluar dari game\n");        
}

void exitGame(PrioQueue *inventory, PrioQueue *delivery, Stack *undo, Stack *redo)
{
    delAllPriqueue(delivery);
    delAllPriqueue(inventory);
    delAllStack(undo);
    delAllStack(redo);
}

void commandStartError()
{
    if (isLineSame(currentLine, "START") || isLineSame(currentLine, "EXIT"))
    {/* Do Nothing */}
    else
    {
        if(!endWord)
        {
            printf("Jangan gunakan spasi di awal atau diakhir command!\n");
        }
        printf("Command tidak dikenali. Silahkan masukkan command yang benar\n");
        printf("Ketik 'HELP' untuk melihat daftar command yang tersedia\n");
        printf("\nMasukkan command: ");
        STARTCOMMAND();
        STARTWORD();
    
        while (isWordSame(currentWord, "HELP"))
        {    
            helpStartGame();
            printf("\nMasukkan command: ");
            STARTCOMMAND();
            STARTWORD();
        }   
        commandStartError();
    }
}

void commandInGameError()
{
    if(isLineSame(currentLine, "HELP") || isLineSame(currentLine, "BUY") || isLineSame(currentLine, "MIX") || isLineSame(currentLine, "CHOP") || isLineSame(currentLine, "FRY") || isLineSame(currentLine, "BOIL") || isLineSame(currentLine, "DELIVERY") || isLineSame(currentLine, "INVENTORY") || isLineSame(currentLine, "CATALOG") || isLineSame(currentLine, "COOKBOOK") || isLineSame(currentLine, "RECOMMENDATION") || isLineSame(currentLine, "UNDO") || isLineSame(currentLine, "REDO") || isLineSame(currentLine, "EXIT"))
    {/* Do Nothing */}
    else if (isWordSame(currentWord, "WAIT"))
    {
        if(endWord)
        {
            printf("Anda tidak memasukkan parameter X jam Y menit dengan benar!\n");
            printf("WAIT X Y\n");
            printf("\nMasukkan command: ");
            STARTCOMMAND();
            STARTWORD();
            commandInGameError();
        }
        else
        {
            ADVWORD();
            if(isWordInt(currentWord))
            {
                if(!endWord)
                {
                    ADVWORD();
                    if(isWordInt(currentWord))
                    {
                        if(endWord)
                        {
                            STARTWORD();
                        }
                        else
                        {
                            printf("Jangan tambahkan karakter lain!\n");
                            printf("Gunakan Format: WAIT X Y\nX untuk jam dan Y untuk menit\n");
                            printf("\nMasukkan command: ");
                            STARTCOMMAND();
                            STARTWORD();
                            commandInGameError(); 
                        }
                    }
                    else
                    {
                        printf("Y harus berupa angka!\n");
                        printf("Gunakan Format: WAIT X Y\nX untuk jam dan Y untuk menit\n");
                        printf("\nMasukkan command: ");
                        STARTCOMMAND();
                        STARTWORD();
                        commandInGameError(); 
                    }
                }
                else
                {
                    printf("Masukkan parameter Y dengan benar!\n");
                    printf("Gunakan Format: WAIT X Y\nX untuk jam dan Y untuk menit\n");
                    printf("\nMasukkan command: ");
                    STARTCOMMAND();
                    STARTWORD();
                    commandInGameError();
                }
            }
            else
            {
                printf("X harus berupa angka!\n");
                printf("Gunakan Format: WAIT X Y\nX untuk jam dan Y untuk menit\n");
                printf("\nMasukkan command: ");
                STARTCOMMAND();
                STARTWORD();
                commandInGameError();
            }
        
        }
    }
    else if(isWordSame(currentWord, "MOVE"))
    {
        if(endWord)
        {
            printf("Anda tidak memasukkan X dengan benar!\n");
            printf("Gunakan Format: MOVE X\n");
            printf("X = {NORTH, SOUTH, EAST, WEST}\n");
            printf("\nMasukkan command: ");
            STARTCOMMAND();
            STARTWORD();

            commandInGameError();
        }
        else
        {
            ADVWORD();
            if(isWordSame(currentWord, "NORTH") || isWordSame(currentWord, "SOUTH") || isWordSame(currentWord, "EAST") || isWordSame(currentWord, "WEST"))
            {
                if(endWord)
                {
                    STARTWORD();
                }
                else
                {
                    printf("Jangan tambahkan karakter lain!\n");
                    printf("Gunakan Format: MOVE X\n");
                    printf("X = {NORTH, SOUTH, EAST, WEST}\n");
                    printf("\nMasukkan command: ");
                    STARTCOMMAND();
                    STARTWORD();
                    commandInGameError();
                }
            }
            else
            {
                printf("X harus berupa NORTH, SOUTH, EAST, atau WEST!\n");
                printf("Gunakan Format: MOVE X\n");
                printf("X = {NORTH, SOUTH, EAST, WEST}\n");
                printf("\nMasukkan command: ");
                STARTCOMMAND();
                STARTWORD();

                commandInGameError();
            }
        }
    }
    else
    {
        if (isWordSame(currentWord, "START"))
        {
            printf("Game sudah dimulai!\n");
            printf("Silakan masukkan commmand 'EXIT' untuk keluar game dan memulai ulang game\n");
            printf("Ketik 'HELP' untuk melihat daftar command yang tersedia\n");
            printf("\nMasukkan command: ");
            STARTCOMMAND();
            STARTWORD();
        }
        else
        {
            if(!endWord)
            {
                printf("Jangan gunakan spasi di awal atau diakhir command!\n");
            }
            printf("Command tidak dikenali. Silahkan masukkan command yang benar\n");
            printf("Ketik 'HELP' untuk melihat daftar command yang tersedia\n");
            printf("\nMasukkan command: ");
            STARTCOMMAND();
            STARTWORD();
        }
        commandInGameError();
    }
}

void RECOMMENDATION(SIMULATOR s, ListResep lr, ListMakanan lm) {
    // KAMUS
    MultiSet multiSetInventory, makeableFood;
    int i, currentId;
    // ALGORITMA
    for (i = 0; i < NBElmt(INVENTORY(s)); i++) {
        addMS(&multiSetInventory, Info(Elmt(INVENTORY(s), i)), 1); 
    }

    makeableFood = getMakableResep(multiSetInventory, lr);

    if (!isEmptyMS(makeableFood)) {
        printf("Tidak ada makanan yang dapat direkomendasikan\n\n");

    } else {
        printf("Berikut daftar makanan yang direkomendasikan\n");
        while (!isEmptyMS(makeableFood)) {
            currentId = ELMTMS(makeableFood, 0);
            printf(" - %s\n", NamaMknId(lm, currentId).Tabword);
            removeMS(&makeableFood, currentId, 1);
        }
    }
}

void DELIVERY(SIMULATOR S)
{
    PrintDelivery(DELIV(S));
}

void INVENTORYMakanan(SIMULATOR S){
    PrintPrioQueue(INVENTORY(S));
}

void Catalogue(ListMakanan lm)
{
    DisplayCatalog(lm);
}

void BuyFood(SIMULATOR *s, ListMakanan lm, boolean *flag)
{
    /* KAMUS LOKAL */
    ListMakanan buyAbleFood;
    boolean isSuccess;
    int inputUser;
    IDEM id;

    /* ALGORITMA */
    *flag = false;

    if (isAdjacent(*s, 'T'))
    {
        buyAbleFood = DisplayBuyAbleLM(lm);
        printf("\nKirim 0 untuk exit.\n\n");
        printf("Masukkan command = ");
        STARTCOMMAND();
        STARTWORD();

        while (!isWordInt(currentWord))
        {
            printf("'%s' Bukan angka!\n", currentWord.String);
            printf("Masukan command yang susuai\n");
            printf("Masukkan command = ");
            STARTCOMMAND();
            STARTWORD();
        }
        inputUser = wordToInt(currentWord);
        while (inputUser != 0)
        {
            if (inputUser < 0 || inputUser > LengthLM(buyAbleFood))
            {
                printf("'%d' tidak valid!\n", inputUser);
                printf("Pilih angka 0 - %d\n", LengthLM(buyAbleFood));
                printf("Masukkan command = ");
                STARTCOMMAND();
                STARTWORD();
            }
            else
            {
                isSuccess = true;
                *flag = true;
                while(isSuccess && !endWord)
                {
                    Enqueue(&DELIV(*s), ElmtLM(buyAbleFood, inputUser - 1));
                    printf("%s Berhasil dipesan! Mohon tunggu selama ", GetNamaMkn(buyAbleFood, inputUser - 1));
                    DisplayTIMEk(GetActionTimeMkn(buyAbleFood, inputUser - 1));
                    printf("\n");

                    ADVWORD();
                    if (isWordInt(currentWord))
                    {
                        inputUser = wordToInt(currentWord);
                        isSuccess = (inputUser >= 0 && inputUser <= LengthLM(buyAbleFood));
                        
                        if (!isSuccess)
                        {
                            printf("'%d' tidak valid!\n", inputUser);
                            printf("Pilih angka 0 - %d\n", LengthLM(buyAbleFood));
                        }
                    }
                    else
                    {
                        isSuccess = false;
                        printf("'%s' Bukan angka!\n", currentWord.String);
                    }
                }

                // last angka jika sudah endWord, tetapi masih success
                if(isSuccess)
                {
                    Enqueue(&DELIV(*s), ElmtLM(buyAbleFood, inputUser -1));
                    printf("%s Berhasil dipesan! Mohon tunggu selama ", GetNamaMkn(buyAbleFood, inputUser - 1));
                    DisplayTIMEk(GetActionTimeMkn(buyAbleFood, inputUser - 1));
                    printf("\n");
                }

                printf("Ingin memesan lagi?\n");
                printf("Masukkan command = ");
                STARTCOMMAND();
                STARTWORD();
            }
        }
    }
    else
    {
        printf("BNMO tidak berada di area Telepon!!\n");
    }
}

void COOKFOOD(SIMULATOR *s, ListMakanan lm, ListResep lr, Notifikasi *notif, char *action) {
    // KAMUS
    TIME actionTime;
    MultiSet listBahan;
    PrioQueue tempInventory;
    ListMakanan actionableFood, expFood, delivFood, newFood, tempUsedFood, usedFood;
    boolean isSuccess, flagDeliv, flagExp;
    int n, id, currIdBahan, failureId, actionMinute;

    // ALGORITMA
    // Inisialisasi awal
    CreateListMakanan(&expFood);
    CreateListMakanan(&delivFood);
    CreateListMakanan(&newFood);
    CreateListMakanan(&usedFood);

    actionableFood = DisplayActionAbleLM(lm, action);
    printf("Kirim 0 untuk exit.\n\n");
    printf("Command = ");
    STARTCOMMAND();
    STARTWORD();
    

    // Nanti tambahin pengecekan currentWORD integer bukan
    n = wordToInt(currentWord);
    while (n != 0) {

        // Jika n diluar opsi pilihan
        if ((n < 0) || (n > LengthLM(actionableFood)) || (!isWordInt(currentWord))) {
            printf("Masukan command yang sesuai\n\n");

        // Jija n sesuai 0 <= n <= Length(actionableFood)
        } else {

            // Inisialisasi 
            // Nomor id pilihan pengguna
            id = GetIdMkn(actionableFood, n-1);
            listBahan = getListBahan(lr, id);
            isSuccess = true;
            tempInventory = INVENTORY(*s);
            CreateListMakanan(&tempUsedFood);

            // Loop untuk tes apakah terdapat bahan yang cukup dari inventory
            while ((!isEmptyMS(listBahan)) && (isSuccess)) {
                currIdBahan = ELMTMS(listBahan, 0);
                if (searchMkn(tempInventory, MknId(lm, currIdBahan))) {
                    removeFromInventory(&tempInventory, currIdBahan);
                    insertLM(&tempUsedFood, MknId(lm, currIdBahan));
                    removeMS(&listBahan, currIdBahan, 1);
                } else {
                    isSuccess = false;
                    failureId = currIdBahan;
                }
            }

            if (isSuccess) {
                printf("%s telah berhasil dibuat dan masuk ke dalam inventory\n\n", NamaMknId(lm, id).Tabword);
                
                Enqueue(&tempInventory, MknId(lm, id));
                INVENTORY(*s) = tempInventory;

                insertLM(&newFood, MknId(lm, id));
                accumLM(&usedFood, tempUsedFood);

                actionTime = ActionTimeMknId(lm, id);
                actionMinute = TIMEToMin(actionTime);
                NextNMin(&WAKTU(*s), actionMinute);
                waitCommand(&DELIV(*s), &INVENTORY(*s), &flagDeliv, &flagExp, &expFood, &delivFood, Hour(actionTime), Minute(actionTime));
                setAllNotif(notif, expFood, delivFood, usedFood, newFood);


            } else {
                printf("Gagal membuat %s karena kamu tidak memiliki bahan berikut: \n", NamaMknId(lm, id).Tabword);
                printf("- %s\n\n", NamaMknId(lm, failureId).Tabword);
            }

        }
        printf("Kirim 0 untuk exit.\n\n");
        printf("Command = ");
        STARTCOMMAND();
        STARTWORD();
        n = wordToInt(currentWord);

    }
}

void undoGame(SIMULATOR *S, SIMULATOR InitSim, Notifikasi *Notif, Stack *Undo, Stack *Redo)
{
    if (IsEmptyStack(*Undo))
    {
        printf("Undo tidak bisa dilakukan\n");
        printf("Anda sudah berada di keadaan paling awal!\n");
    }
    else
    {
        ElStackURType valOut;
        Pop(Undo, &valOut);
        Push(Redo, valOut);

        *Notif = Nof(valOut);

        if (IsEmptyStack(*Undo))
        {
            *S = InitSim;
        }
        else
        {
            *S = InfoTopSim(*Undo);
        }
    }
}

void redoGame(SIMULATOR *S, Notifikasi *Notif, Stack *Undo, Stack *Redo)
{
    if (IsEmptyStack(*Redo))
    {
        printf("Redo tidak bisa dilakukan\n");
        printf("Anda sudah berada di keadaan terbaru!\n");
    }
    else
    {
        ElStackURType valOut;
        Pop(Redo, &valOut);
        Push(Undo, valOut);
        *S = Sim(valOut);
        *Notif = Nof(valOut);
    }
}

void saveUndoRedoGame(SIMULATOR S, SIMULATOR InitSim, Notifikasi Notif, Stack *Undo, Stack *Redo)
{
    ElStackURType valIn;
    if (!(isTimeSame(WAKTU(S), WAKTU(InitSim))))
    {
        // Handle kejadian pertama kali keadaan sim berubah
        if (IsEmptyStack(*Undo))
        {
            valIn = MakeElStack(S, Notif);
            Push(Undo, valIn);
        }
        else
        {
            if (isTimeSame(WAKTU(S), WAKTU(InfoTopSim(*Undo))))
            {
                // Do Nothing 
            }
            else
            {
                valIn = MakeElStack(S, Notif);
                Push(Undo, valIn);
                resetStack(Redo);
            }
        }
    }
}

void WAIT(SIMULATOR *S, boolean *FlagDeliv, boolean *FlagExp, ListMakanan *LMakananEXP, ListMakanan *ListDelivDone)
{
    int hour, minute;
    ADVWORD();
    hour = wordToInt(currentWord);
    ADVWORD();
    minute = wordToInt(currentWord);
    waitCommand(&DELIV(*S), &INVENTORY(*S), FlagDeliv, FlagExp, LMakananEXP, ListDelivDone, hour, minute);
    // printf("menunggu %d  %d\n", hour, minute);
    NextNMin(&WAKTU(*S), (60*hour)+minute);
}