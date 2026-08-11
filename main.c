#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char gameBoard[3][3] = {{'1','2','3'}, {'4','5','6'}, {'7','8','9'}};

char playerMove, currentPlayer = 'X';

void drawBoard();

void computerMove();

int playGame(char player, char symbol);

char checkWinner();

int main(int argc, char const *argv[])
{
     char status = ' ';
    srand(time(NULL)); 

    while(1){
        drawBoard();
        
        // 1. OYUNCU (X) HAMLESİ
        printf("\n[+] Player X, Enter to number ---> ");
        scanf(" %c", &playerMove);
        
        if (playGame(playerMove, 'X') == 1) {
            
            // X'in hamlesinden sonra oyun bitti mi?
            status = checkWinner();
            if (status != ' ') break; 
            
            // 2. BİLGİSAYAR (O) HAMLESİ
            computerMove(); 
            
            // O'nun hamlesinden sonra oyun bitti mi?
            status = checkWinner();
            if (status != ' ') break;
        }
    }

    // Oyun bittiğinde tahtanın son halini gösteriyoruz
    drawBoard();

    // Sonuç Ekranı
    if (status == 'X') {
        printf("\n[***] TEBRIKLER! Siz kazandiniz (X)! [***]\n");
    } else if (status == 'O') {
        printf("\n[!] BILGISAYAR KAZANDI (O)! Daha iyi sanslar...\n");
    } else if (status == 'B') {
        printf("\n[=] OYUN BERABERE BITTI! Taktiksel bir mucadele.\n");
    }

    
    return 0;
}

void drawBoard(){

    system("clear");

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("| %c |", gameBoard[i][j]);
        }
        printf("\n");
    }

    printf(">>>> Coded By Gurkan Guler \n ");
}

int playGame(char move, char playerSymbol){
   for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (gameBoard[i][j] == move) {
                gameBoard[i][j] = playerSymbol;
                return 1; // Başarılı
            }
        }
    }
    return 0; // Geçersiz hamle
}

void computerMove() {
    int row, col;
    int availableSpaces = 0;

    // Önce tahtada boş yer kalmış mı diye kontrol ediyoruz
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (gameBoard[i][j] != 'X' && gameBoard[i][j] != 'O') {
                availableSpaces++;
            }
        }
    }

    // Eğer boş yer yoksa bilgisayar hamle yapmaya çalışmaz
    if (availableSpaces == 0) return;

    // Bilgisayar boş bir hücre bulana kadar rastgele koordinat üretir
    do {
        row = rand() % 3; // 0, 1 veya 2
        col = rand() % 3; // 0, 1 veya 2
    } while (gameBoard[row][col] == 'X' || gameBoard[row][col] == 'O');

    // Bulduğu boş yere 'O' harfini atar
    gameBoard[row][col] = 'O';
}

char checkWinner() {
    // 1. Satırları kontrol et
    for (int i = 0; i < 3; i++) {
        if (gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2]) {
            return gameBoard[i][0];
        }
    }

    // 2. Sütunları kontrol et
    for (int i = 0; i < 3; i++) {
        if (gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i]) {
            return gameBoard[0][i];
        }
    }

    // 3. Sol Üst -> Sağ Alt Çaprazı kontrol et
    if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2]) {
        return gameBoard[0][0];
    }

    // 4. Sağ Üst -> Sol Alt Çaprazı kontrol et
    if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0]) {
        return gameBoard[0][2];
    }

    // 5. Beraberlik kontrolü (Eğer hala rakam kaldıysa oyun devam ediyordur)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameBoard[i][j] != 'X' && gameBoard[i][j] != 'O') {
                return ' '; // Oyun devam ediyor
            }
        }
    }

    return 'B'; // Boş hücre kalmadı ve kimse kazanamadıysa Beraberlik (B) döner
}
