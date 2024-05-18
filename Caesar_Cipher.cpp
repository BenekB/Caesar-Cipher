//  author: Benedykt Bernard Bela
//  Code::Blocks 17.12

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

//int for;



void wpisz_wirnik (char wirnik_1[2][26], char wirnik_2[2][26], char wirnik_3[2][26]);
void obroc_wirniki (char wirnik_1[2][26], char wirnik_2[2][26], int zmiana);
void pisz_menu();
void czy_poprawne (char &znak);
void szyfrowanie (char wirnik_1[2][26], char wirnik_2[2][26], char wirnik_3[2][26]);
void klucz_kodu (char obrot[3], char wirnik_1[2][26], char wirnik_2[2][26], char wirnik_3[2][26]);
char szyfrowanie_podfunkcja (const char sprawdz, char wirnik_1[2][26], char wirnik_2[2][26], char wirnik_3[2][26]);
void deszyfracja (char wirnik_1[2][26], char wirnik_2[2][26], char wirnik_3[2][26]);
char deszyfracja_podfunkcja ( char sprawdz, char wirnik_1[2][26], char wirnik_2[2][26], char wirnik_3[2][26]);



int main()
{
    char wirnik_1[2][26], wirnik_2[2][26], wirnik_3[2][26];

    wpisz_wirnik (wirnik_1, wirnik_2, wirnik_3);

    char opcje;
    bool czy = true;

    while (czy)         //  glowny mechanizm menu programu
    {
        pisz_menu();

        cin>>opcje;

        switch (opcje)
        {
            case '1':   szyfrowanie (wirnik_1, wirnik_2, wirnik_3); break;
            case '2':   deszyfracja (wirnik_1, wirnik_2, wirnik_3); break;
            case '3':   czy = false; break;
            default:    cout<<"\nNIEPOPRAWNE DANE!!!\n\n\n";
        }
    }

    return 0;
}



void deszyfracja (char wirnik_1[2][26], char wirnik_2[2][26], char wirnik_3[2][26])
{
    char plik_wejscie[60], plik_wyjscie[60];

    cout<<"Prosze podac nazwe pliku wejsciowego z rozszerzeniem > "; cin>>plik_wejscie;
    cout<<"Prosze podac nazwe pliku wyjsciowego z rozszerzeniem > "; cin>>plik_wyjscie;

    ifstream plikin;
    ofstream plikout;
    plikin.open(plik_wejscie);
    plikout.open(plik_wyjscie);


    if (!plikin)            //  sprawdzam, czy dany plik w ogole istnieje
        cout<<"BRAK PLIKU"<<endl;
    else            //  jezeli plik istnieje, to pytam uzytkownika o poczatkowy obrot tablicy
    {
        bool czy = true;
        char obrot[3];              //  tablica zawierajaca poczatkowy stan wirnikow
        char sprawdz;               //  do tej zmiennen bede pobieral znak z pliku


        while (czy)             //  trzy kolejne petle sprawiaja, ze male litery sa zamieniane na wielkie i chronia przed podaniem zlych danych
        {
            cout<<"Podaj stan tablicy I > "; cin>>obrot[0];

            if (obrot[0] >= 65 && obrot[0] <= 90)               //  dana jest poprawna - koncze petle while
                czy = false;
            else if (obrot[0] >= 97 && obrot[0] <= 122)             //  dana jest mala litera - zamieniam ja na wielka
            {
                obrot[0] = obrot[0] - 32;
                czy = false;
            }
            else                                //  dana jest zla
                cout<<"NIEPOPRAWNE DANE\n";
        }

        czy = true;

        while (czy)
        {
            cout<<"Podaj stan tablicy II > "; cin>>obrot[1];

            if (obrot[1] >= 65 && obrot[1] <= 90)
                czy = false;
            else if (obrot[1] >= 97 && obrot[1] <= 122)
            {
                obrot[1] = obrot[1] - 32;
                czy = false;
            }
            else
                cout<<"NIEPOPRAWNE DANE\n";
        }

        czy = true;

        while (czy)
        {
            cout<<"Podaj stan tablicy III > "; cin>>obrot[2];

            if (obrot[2] >= 65 && obrot[2] <= 90)
                czy = false;
            else if (obrot[2] >= 97 && obrot[2] <= 122)
            {
                obrot[2] = obrot[2] - 32;
                czy = false;
            }
            else
                cout<<"NIEPOPRAWNE DANE\n";
        }


        klucz_kodu (obrot, wirnik_1, wirnik_2, wirnik_3);               //  ustawia wirniki wedlug podanego przez uzytkownika klucza

        int zmiana = 1;             //  liczy ile znakow zostalo juz zaszyfrowanych - potrzebne do obrotu tablic po kazdym znaku

        while (plikin.get(sprawdz))             //  uzywam instrukcji .get() aby pobierac ze strumienia tez biale znaki
        {
            czy_poprawne(sprawdz);              //  zamienia polskie znaki na angielskie i male litery na wielkie

            if (sprawdz >= 65 && sprawdz <= 90)             //  dla wielkich liter alfabetu
            {
                plikout<<deszyfracja_podfunkcja (sprawdz, wirnik_1, wirnik_2, wirnik_3);
                obroc_wirniki(wirnik_1, wirnik_2, zmiana);
            }
            else                    //  dla innych znakow niz wielkie litery alfabetu
                plikout<<sprawdz;
        }
    }


    plikin.close();
    plikout.close();

    wpisz_wirnik(wirnik_1, wirnik_2, wirnik_3);             //  ustawiam tablice do stanu poczatkowego, aby moc kolejny raz skorzystac z programu

    cout<<"\n\n";
}


//  szukanie odpowiednich znakow po wirnikach - rozbicie funkcji deszyfracja na dwie dla zwiekszenia czytelnosci
char deszyfracja_podfunkcja ( char sprawdz, char wirnik_1[2][26], char wirnik_2[2][26], char wirnik_3[2][26])           
{
    int i = 0;

    while (sprawdz != wirnik_1[0][i]) i++;
    sprawdz = wirnik_1[1][i];
    i = 0;

    while (sprawdz != wirnik_2[0][i]) i++;
    sprawdz = wirnik_2[1][i];
    i = 0;

    while (sprawdz != wirnik_3[1][i]) i++;
    sprawdz = wirnik_3[0][i];
    i = 0;

    while (sprawdz != wirnik_2[1][i]) i++;
    sprawdz = wirnik_2[0][i];
    i = 0;

    while (sprawdz != wirnik_1[1][i]) i++;
    sprawdz = wirnik_1[0][i];
    i = 0;

    return sprawdz;
}



void szyfrowanie (char wirnik_1[2][26], char wirnik_2[2][26], char wirnik_3[2][26])         //  dzialanie analogicznie jak w funkcjii deszyfracja
{
    char plik_wejscie[60], plik_wyjscie[60];
    cout<<"Prosze podac nazwe pliku wejsciowego z rozszerzeniem > "; cin>>plik_wejscie;
    cout<<"Prosze podac nazwe pliku wyjsciowego z rozszerzeniem > "; cin>>plik_wyjscie;

    ifstream plikin;
    ofstream plikout;
    plikin.open(plik_wejscie);
    plikout.open(plik_wyjscie);


    if (!plikin)
        cout<<"BRAK PLIKU"<<endl;
    else
    {
        bool czy = true;
        char obrot[3], sprawdz;

        while (czy)
        {
            cout<<"Podaj stan tablicy I > "; cin>>obrot[0];

            if (obrot[0] >= 65 && obrot[0] <= 90)
                czy = false;
            else if (obrot[0] >= 97 && obrot[0] <= 122)
            {
                obrot[0] = obrot[0] - 32;
                czy = false;
            }
            else
                cout<<"NIEPOPRAWNE DANE\n";
        }

        czy = true;

        while (czy)
        {
            cout<<"Podaj stan tablicy II > "; cin>>obrot[1];

            if (obrot[1] >= 65 && obrot[1] <= 90)
                czy = false;
            else if (obrot[1] >= 97 && obrot[1] <= 122)
            {
                obrot[1] = obrot[1] - 32;
                czy = false;
            }
            else
                cout<<"NIEPOPRAWNE DANE\n";
        }

        czy = true;

        while (czy)
        {
            cout<<"Podaj stan tablicy III > "; cin>>obrot[2];

            if (obrot[2] >= 65 && obrot[2] <= 90)
                czy = false;
            else if (obrot[2] >= 97 && obrot[2] <= 122)
            {
                obrot[2] = obrot[2] - 32;
                czy = false;
            }
            else
                cout<<"NIEPOPRAWNE DANE\n";
        }


        klucz_kodu (obrot, wirnik_1, wirnik_2, wirnik_3);

        int zmiana = 1;

        while (plikin.get(sprawdz))
        {
            czy_poprawne(sprawdz);

            if (sprawdz >= 65 && sprawdz <= 90)
            {
                plikout<<szyfrowanie_podfunkcja (sprawdz, wirnik_1, wirnik_2, wirnik_3);
                obroc_wirniki(wirnik_1, wirnik_2, zmiana);
            }
            else
                plikout<<sprawdz;
        }
    }


    plikin.close();
    plikout.close();

    wpisz_wirnik(wirnik_1, wirnik_2, wirnik_3);

    cout<<"\n\n";
}


//  dzialanie analogiczne jak w funkcjii deszyfracja_podfunkcja - niewielkie zmiany w zwiazku z roznica w szyfrowaniu i deszyfracji
char szyfrowanie_podfunkcja ( char sprawdz, char wirnik_1[2][26], char wirnik_2[2][26], char wirnik_3[2][26])         
{
    int i = 0;

    while (sprawdz != wirnik_1[0][i]) i++;
    sprawdz = wirnik_1[1][i];
    i = 0;

    while (sprawdz != wirnik_2[0][i]) i++;
    sprawdz = wirnik_2[1][i];
    i = 0;

    while (sprawdz != wirnik_3[0][i]) i++;
    sprawdz = wirnik_3[1][i];
    i = 0;

    while (sprawdz != wirnik_2[1][i]) i++;
    sprawdz = wirnik_2[0][i];
    i = 0;

    while (sprawdz != wirnik_1[1][i]) i++;
    sprawdz = wirnik_1[0][i];
    i = 0;

    return sprawdz;
}



void klucz_kodu (char obrot[3], char wirnik_1[2][26], char wirnik_2[2][26], char wirnik_3[2][26])           //  ustawia tablice wedlug klucza podanego przez uzytkownika
{
    int i = 0;


    while (obrot[0] != wirnik_1[0][i] && i < 26)            //  sprawdza na ktorym miejscu jest znak podany przez uzytkownika jako poczatkowe ustawienie wirnika 1
        i++;

    char *tab = new char[26];

    for (int k = 0; k < i; k++)                 //  trzy ponizsze petle obracaja tablice z wykorzystaniem pomocniczej tablicy "tab"
        tab[k] = wirnik_1[0][k];

    for (int k = 0; k < 26-i; k++)
        wirnik_1[0][k] = wirnik_1[0][i+k];

    for (int k = 0; k < i; k++)
        wirnik_1[0][26-i+k] = tab[k];


    i = 0;

    while (obrot[1] != wirnik_2[0][i] && i < 26)                //  analogicznie - dla wirnika 2
        i++;

    for (int k = 0; k < i; k++)
        tab[k] = wirnik_2[0][k];

    for (int k = 0; k < 26-i; k++)
        wirnik_2[0][k] = wirnik_2[0][i+k];

    for (int k = 0; k < i; k++)
        wirnik_2[0][26-i+k] = tab[k];


    i = 0;

    while (obrot[2] != wirnik_3[0][i] && i < 26)                //  analogicznie -  dla wirnika 3
        i++;

    for (int k = 0; k < i; k++)
        tab[k] = wirnik_3[0][k];

    for (int k = 0; k < 26-i; k++)
        wirnik_3[0][k] = wirnik_3[0][i+k];

    for (int k = 0; k < i; k++)
        wirnik_3[0][26-i+k] = tab[k];


    delete[] tab;
}



void czy_poprawne (char &znak)              //  sprawdza, czy znak z pliku jest wielka litera alfabetu angielskiego
{
    if (znak >= 97 && znak <= 122)              //  zamienia male litery na wielkie
        znak = znak - 32;


    switch (znak)               //  zamienia polskie znaki na angielskie
    {
        case -71:   znak = 'A'; break;
        case -91:   znak = 'A'; break;
        case -26:   znak = 'C'; break;
        case -58:   znak = 'C'; break;
        case -22:   znak = 'E'; break;
        case -54:   znak = 'E'; break;
        case -77:   znak = 'L'; break;
        case -93:   znak = 'L'; break;
        case -15:   znak = 'N'; break;
        case -47:   znak = 'N'; break;
        case -13:   znak = 'O'; break;
        case -45:   znak = 'O'; break;
        case -100:   znak = 'S'; break;
        case -116:   znak = 'S'; break;
        case -65:   znak = 'Z'; break;
        case -81:   znak = 'Z'; break;
        case -97:   znak = 'Z'; break;
        case -113:   znak = 'Z'; break;
    }

}



void pisz_menu ()
{
    cout<<"SZYFROWANIE > 1"<<endl
        <<"DESZYFRACJA > 2"<<endl
        <<"KONIEC PROGRAMU > 3"<<endl
        <<" > ";
}



void wpisz_wirnik (char wirnik_1[2][26], char wirnik_2[2][26], char wirnik_3[2][26])            //  wpisuje zawartosc tablic wedlug zalozen projektowych
{
    int pomoc = 65;             //  65 - 'A' w kodzie ASCII

    for (int i = 0; i < 26; i++)
    {
        wirnik_1[0][i] = pomoc;
        wirnik_2[0][i] = pomoc;
        wirnik_3[0][i] = pomoc;
        pomoc++;
    }

    wirnik_1[1][0] = 'E'; wirnik_1[1][1] = 'K'; wirnik_1[1][2] = 'M'; wirnik_1[1][3] = 'F'; wirnik_1[1][4] = 'L'; wirnik_1[1][5] = 'G'; wirnik_1[1][6] = 'D'; wirnik_1[1][7] = 'Q'; wirnik_1[1][8] = 'V'; wirnik_1[1][9] = 'Z'; wirnik_1[1][10] = 'N'; wirnik_1[1][11] = 'T'; wirnik_1[1][12] = 'O'; wirnik_1[1][13] = 'W'; wirnik_1[1][14] = 'Y'; wirnik_1[1][15] = 'H'; wirnik_1[1][16] = 'X'; wirnik_1[1][17] = 'U'; wirnik_1[1][18] = 'S'; wirnik_1[1][19] = 'P'; wirnik_1[1][20] = 'A'; wirnik_1[1][21] = 'I'; wirnik_1[1][22] = 'B'; wirnik_1[1][23] = 'R'; wirnik_1[1][24] = 'C'; wirnik_1[1][25] = 'J';
    wirnik_2[1][0] = 'A'; wirnik_2[1][1] = 'J'; wirnik_2[1][2] = 'D'; wirnik_2[1][3] = 'K'; wirnik_2[1][4] = 'S'; wirnik_2[1][5] = 'I'; wirnik_2[1][6] = 'R'; wirnik_2[1][7] = 'U'; wirnik_2[1][8] = 'X'; wirnik_2[1][9] = 'B'; wirnik_2[1][10] = 'L'; wirnik_2[1][11] = 'H'; wirnik_2[1][12] = 'W'; wirnik_2[1][13] = 'T'; wirnik_2[1][14] = 'M'; wirnik_2[1][15] = 'C'; wirnik_2[1][16] = 'Q'; wirnik_2[1][17] = 'G'; wirnik_2[1][18] = 'Z'; wirnik_2[1][19] = 'N'; wirnik_2[1][20] = 'P'; wirnik_2[1][21] = 'Y'; wirnik_2[1][22] = 'F'; wirnik_2[1][23] = 'V'; wirnik_2[1][24] = 'O'; wirnik_2[1][25] = 'E';
    wirnik_3[1][0] = 'Y'; wirnik_3[1][1] = 'R'; wirnik_3[1][2] = 'U'; wirnik_3[1][3] = 'H'; wirnik_3[1][4] = 'Q'; wirnik_3[1][5] = 'S'; wirnik_3[1][6] = 'L'; wirnik_3[1][7] = 'D'; wirnik_3[1][8] = 'P'; wirnik_3[1][9] = 'X'; wirnik_3[1][10] = 'N'; wirnik_3[1][11] = 'G'; wirnik_3[1][12] = 'O'; wirnik_3[1][13] = 'K'; wirnik_3[1][14] = 'M'; wirnik_3[1][15] = 'I'; wirnik_3[1][16] = 'E'; wirnik_3[1][17] = 'B'; wirnik_3[1][18] = 'F'; wirnik_3[1][19] = 'Z'; wirnik_3[1][20] = 'C'; wirnik_3[1][21] = 'W'; wirnik_3[1][22] = 'V'; wirnik_3[1][23] = 'J'; wirnik_3[1][24] = 'A'; wirnik_3[1][25] = 'T';
}



void obroc_wirniki (char wirnik_1[2][26], char wirnik_2[2][26], int zmiana)         //  po kazdym znaku obraca wirniki wedlug zalozen projektowych
{
    char *n = new char;             //  wczytanie pierwszzego znaku gornego wiersza z wirnika 1 do zmiennej *n
    *n = wirnik_1[0][0];

    for (int i = 0; i < 25; i++)                //  przesuniecie gornego wiersza wirnika 1 o jedno miejsce w lewo
        wirnik_1[0][i] = wirnik_1[0][i+1];

    wirnik_1[0][25] = *n;               //  ostatnie miejsce gornego wiersza wirnika 1 otrzymuje wartosc zmiennej *n

    delete n;


    if (zmiana%26 == 0)             //  po pelnym obrocie wirnika 1 nastepuje obrot o jendo miejsce wirnika 2 w analogiczny sposob jak powyzej
    {
        char *n = new char;
        *n = wirnik_2[0][0];

        for (int i = 0; i < 25; i++)
            wirnik_2[0][i] = wirnik_1[0][i+1];

        wirnik_2[0][25] = *n;

        delete n;
    }


    zmiana++;
}





