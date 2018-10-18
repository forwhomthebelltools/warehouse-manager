#include <iostream>
#define NOME_FILE "prodotto.dat"
#include <fstream>

using namespace std;

//--------------------

void LeggiRecord();
void Inserisci();
void Lista();
void Modifica();
void VerificaArchivio();


struct Prodotto
{
    char codice[11];
    char titolo[21];
    char note[41];
};

//--------------------

int main()
{
    int x;
    cout << "I MIEI PRODOTTI" << endl << endl;
    do
    {
        cout << "1 - VUOTO" << endl;
        cout << "2 - Inserisci" << endl;
        cout << "3 - Modifica" << endl;
        cout << "4 - Lista" << endl;
        cout << "0 - ESCI" << endl;
        cout << "" << endl;
        cout << "Operazione: ";
        cin >> x;
        switch(x)
        {
            case 1:
            //LeggiRecord();
            break;
            case 2:
            Inserisci();
            break;
            case 3:
            Modifica();
            break;
            case 4:
            Lista();
            break;
            break;
        }
    }while (x != 0);
    return 0;

}

//--------------------

void VerificaArchivio()
{
    ofstream f;
    f.open(NOME_FILE, ios::binary | ios::app);
    f.close();
}

void Inserisci()
{
    cout << "INSERIMENTO PRODOTTO" << endl;
    Prodotto p;
    cout << "Codice Prodotto: ";
    cin >> p.codice;
    cin.ignore(260, '\n');
    cout << "Titolo: ";
    cin.getline(p.titolo, 30);
    cout << "Note: ";
    cin.getline(p.note, 40);
    /*
    FILE * f;
    f = fopen(NOME_FILE, "a");
    fseek(f,0,2);
    fwrite(&p, sizeof(Prodotto), 1, f);
    printf("Il cursore e' ora in posizione: %d \n",ftell(f));
    fclose(f);
    return;
    */

    ofstream f;
    f.open(NOME_FILE, ios::binary | ios::app );
    f.write(reinterpret_cast<char*>(&p), sizeof(p));
    //f.write((char *) &p, sizeof(p));
    f.close();
    return;

}

void Modifica()
{
    int posizione;
    cout << "Quale record vuoi modificare? ";
    cin >> posizione;
    fstream f;
    f.open(NOME_FILE, ios::binary | ios::in | ios::out);
    if(!f)
    {
        cout << "Il file specificato non esiste!";
        return;
    }
    Prodotto Elemento;
    int count = 0;
    while(f.read((char *) &Elemento, sizeof(Elemento)))
    {
        count++;
        if (count == posizione-1)
        {
            cout << "MODIFICA PRODOTTO" << endl;
            cout << "Codice Prodotto: ";
            cin >> Elemento.codice;
            cin.ignore(260, '\n');
            cout << "Titolo: ";
            cin.getline(Elemento.titolo, 30);
            cout << "Note: ";
            cin.getline(Elemento.note, 40);
            f.write(reinterpret_cast<char*>(&Elemento), sizeof(Elemento));
            f.close();
            return;

        }
    }


    /*
    FILE * f;
    f = fopen(NOME_FILE, "w+b");
    fseek(f, posizione - 1 * sizeof(Prodotto), 0);
    Prodotto p2;
    fread(&p2, sizeof(Prodotto), 1, f);
    fclose(f);
    cout << "Titolo: " << p2.titolo << endl;
    cout << "Note: " << p2.note << endl;
    return;
    */
}

void Lista()
{
    cout << "LISTA PRODOTTI" << endl;
    ifstream f;
    f.open(NOME_FILE, ios::binary | ios::in);
    if(!f)
    {
        cout << "Il file specificato non esiste!";
        return;
    }
    f.seekg(0, ios::beg);
    Prodotto Elemento;
    int count = 0;
    while(f.read((char *) &Elemento, sizeof(Elemento)))
    {
        count++;
        cout << "ID n: " << count;
        cout << " - Codice:" << Elemento.codice;
        cout << " - Titolo:" << Elemento.titolo;
        cout << " - Note:" << Elemento.note;
        cout << endl;
    }
    cout << "There are " << count << " data inside!" << endl;

    f.close();
    return;

}
