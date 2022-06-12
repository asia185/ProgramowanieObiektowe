                                                                    /* JOANNA TARASIUK, NR INDEKSU 39461, GRUPA 210A */

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;
public:
    Date(){}
    Date(int day, int month, int year)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }
    
    //operator =
    Date operator=(const Date& d)
    {
        day = d.day;
        month = d.month;
        year = d.year;
        return *this;
    }
    
    void show()
    {
        cout << day << "." << month << "." << year;
    }
};

                                    //////////////////////////////////////////////    KLASA BAZOWA    ////////////////////////////////////////////////////////

class Osoba
{
public:
    string imie;
    string nazwisko;
    
    virtual void create() = 0;
    virtual void show() = 0;
    virtual void remove() = 0;
};

/* void show(Osoba* o) {
    for (Osoba* i=o; i; i++) {
        i->show();
    }
} */

                                    //////////////////////////////////////////////    WLASCICIEL   ////////////////////////////////////////////////////////

class Wlasciciel : virtual public Osoba
{
private:
    string nazwaHotelu;
    long long nr_tel;
public:
    void create();
    void show();
    void remove();
    
    //operator =
    Wlasciciel operator=(const Wlasciciel& w)
    {
        imie = w.imie;
        nazwisko = w.nazwisko;
        nazwaHotelu = w.nazwaHotelu;
        nr_tel = w.nr_tel;
        return *this;
    }
    
    // operator >>
    friend istream& operator>>(istream & cin, Wlasciciel & wlasciciel)
    {
        cin >> wlasciciel.imie;
        cin >> wlasciciel.nazwisko;
        cin >> wlasciciel.nazwaHotelu;
        cin >> wlasciciel.nr_tel;
        return cin;
    }
    
    // operator <<
    friend ostream& operator<<(ostream& cout, const Wlasciciel& wlasciciel)
    {
        cout << "Imie " << wlasciciel.imie;
        cout << "Nazwisko " << wlasciciel.nazwisko;
        cout << "Nazwa hotelu " << wlasciciel.nazwaHotelu;
        cout << "Nr telefonu" << wlasciciel.nr_tel;
        return cout;
    }
};


void Wlasciciel::create()
{
    cout << "Podaj imie:" << endl;
    cin >> imie;
    cout << "Podaj nazwisko:" << endl;
    cin >> nazwisko;
    cout << "Podaj nazwe hotelu" << endl;
    cin >> nazwaHotelu;
    cout << "Podaj nr telefonu:" << endl;
    cin >> nr_tel;
}

void  Wlasciciel::show()
{
    cout << imie << " " << nazwisko << " " << nazwaHotelu << " " << nr_tel << endl;
}

void Wlasciciel::remove(){}



                                    //////////////////////////////////////////////    GOSCIE   ////////////////////////////////////////////////////////

class Person : virtual public Osoba
{
public:
    //operator =
    Person operator=(const Person& p)
    {
        numerPokoju = p.numerPokoju;
        arrivalDate = p.arrivalDate;
        leavingDate = p.leavingDate;
        return *this;
    }
    
    int numerPokoju;
    Date arrivalDate;
    Date leavingDate;
    void create();
    void show();
    void remove();
};


void Person::create()
{
    int day, month, year;
    
    cout << "Imie: ";
    cin >> imie;
    cout << "Nazwisko: ";
    cin >> nazwisko;
    
    cout << "Rozpoczecie"<<endl;
    
    cout << "Dzien: ";
    cin >> day;
    cout << "Miesiac: ";
    cin >> month;
    cout << "Rok: ";
    cin >> year;
    arrivalDate = Date(day, month, year);
    
    cout << "Zakonczenie"<<endl;
    
    cout << "Dzien: ";
    cin >> day;
    cout << "Miesiac: ";
    cin >> month;
    cout << "Rok: ";
    cin >> year;
    leavingDate = Date(day, month, year);
}

void Person::show()
{
    cout << imie << " " << nazwisko << endl;
}

void Person::remove(){}


                                    //////////////////////////////////////////////    HOTEL    ////////////////////////////////////////////////////////

class Hotel
{
public:
    class Room
    {
    public:
        int number;
        Person *person;
        bool reserved;
        
        void create(int roomNumber);
        void show();
        void setReservation(Person *person);
        void removeReservation();
        void remove();
        
        //operator =
        Room operator=(const Room& r)
        {
            number = r.number;
            person = r.person;
            reserved = r.reserved;
            return *this;
        }
    };
    
    string nazwaHotelu;
    int wysokosc;
    int szerokosc;
    
    vector<Person> goscie;
    vector<Room> rooms;
    
public:
    
    //operator []
    Room &operator[](int numerPokoju)
    {
        if(numerPokoju >= rooms.size() || numerPokoju < 0)
        {
            cout << "Error: Zly indeks tablicy" <<endl;
            return rooms[0];
        }
        return rooms[numerPokoju];
    }
    
    
    //operator ()
    void operator()(Person *person, int roomNumber)
    {
        if(rooms[roomNumber].reserved == true)
        {
            cout << "Pokoj zajety. Rezerwacja niemozliwa." << endl;
            return;
        }
        goscie.push_back(*person);
        rooms[roomNumber].setReservation(person);
        cout << "Zarezerowano pokoj nr" << roomNumber << endl;
    }
    
    
    void create()
    {
        cout << "Podaj nazwe hotelu: " << endl;
        cin >> this->nazwaHotelu;
        cout << "Podaj ilosc pieter w hotelu: " << endl;
        cin >> this->wysokosc;
        cout << "Podaj ilosc pokoi na kazdym pietrze:" << endl;
        cin >> this->szerokosc;
        
        Room *room = new Room();
        for(int i = 0; i < wysokosc*szerokosc; i++)
        {
            room->create(i);
            rooms.push_back(*room);
        }
    }
    
    void show()
    {
        cout << "Nazwa: " << this->nazwaHotelu << " Ilosc pokoi: " << this->wysokosc * this->szerokosc << endl;
    }
};

void Hotel::Room::create(int roomNumber)
{
    this->number = roomNumber;
    this->reserved = false;
}

void Hotel::Room::show()
{
    cout << "Pokoj nr. " << number << endl;
    if(reserved)
    {
        cout << "Pokoj zarezerwowany przez: ";
        person->show();
        cout << endl;
        cout << "Od: ";
        person->arrivalDate.show();
        cout << endl;
        cout << "Do: ";
        person->leavingDate.show();
        cout << endl;
    }
    else
    {
        cout << "Pokoj wolny" << endl;
    }
}

void Hotel::Room::setReservation(Person *person)
{
    this->reserved = true;
    this->person = person;
}


void Hotel::Room::removeReservation()
{
    this->reserved = false;
    delete this->person;
}


                                    //////////////////////////////////////////////    MENU   ////////////////////////////////////////////////////////

int main()
{
    vector<Wlasciciel> wlasciciele;
    vector<Osoba*> osoby;
    vector<Hotel> hotele;
    
    char wybor;
    
    for (;;)
    {
    powrot:
        cout << "                               SIEC HOTELI \"MyHotel\"" << endl;
        cout << "Menu:" << endl;
        cout << "   1: Zarzadzanie wlascicielami" << endl;
        cout << "   2: Zarzadzanie hotelami" << endl;
        cout << "   3: Zarzadzanie goscmi" << endl;
        cout << "   4: Zarzadzanie pracownikami"<<endl;
        cout << "   5: Koniec programu" << endl;

        cin >> wybor;
        
        switch (wybor)
        {
            case '1':
                for (;;)
                {
                    Wlasciciel *wlasciciel = new Wlasciciel();
                    
                    cout << "                   Wlasciciele" << endl;
                    cout << "-------------------------------" << endl;
                    cout << "Menu:" << endl;
                    cout << "    a: Nowy wlasciciel" << endl;
                    cout << "    b: Wyswietlanie wlascicieli" << endl;
                    cout << "    c: Usuwanie wlascicieli" << endl;
                    cout << "    d: Powrot" << endl;
                    cin >> wybor;
                    switch (wybor)
                    {
                        case 'a':
                            wlasciciel->create();
                            wlasciciele.push_back(*wlasciciel);
                            break;
                        case 'b':
                            if(wlasciciele.size() == 0)
                            {
                                cout << "Lista wlascicieli jest pusta" << endl;
                                break;
                            }
                            for(int i = 0; i  < wlasciciele.size(); i++)
                            {
                                cout << i << ". ";
                                wlasciciele[i].show();
                            }
                            break;
                        case 'c':
                            if(wlasciciele.size() == 0)
                            {
                                cout << "Lista wlascicieli jest pusta" << endl;
                                break;
                            }
                            for(int i = 0; i  < wlasciciele.size(); i++)
                            {
                                cout << i << ". ";
                                wlasciciele[i].show();
                            }
                            
                            cout << "Podaj numer wlasciciela ktorego chcesz usunac" << endl;
                            int numer;
                            cin >> numer;
                            while(numer < 0 || numer >= wlasciciele.size())
                            {
                                cout << "Bledny numer, podaj jeszcze raz" << endl;
                                cin >> numer;
                            }
                            wlasciciele.erase(wlasciciele.begin() + numer);
                            break;
                        case 'd':
                            goto powrot;
                            break;
                        default: cout << "Blad" << endl;
                    }
                }
                break;
                
                
            case '2':
                for (;;)
                {
                    cout << "               Hotele " << endl;
                    cout << "-----------------------------" << endl;
                    cout << "Menu:" << endl;
                    cout << "    a: Wprowadzanie hotelu" << endl;
                    cout << "    b: Wyswietlanie hoteli" << endl;
                    cout << "    c: Usuwanie hoteli" << endl;
                    cout << "    d: Powrot" << endl;
                    cin >> wybor;
                    switch (wybor)
                    {
                        case 'a':
                        {
                            int size_hotels;
                            cout << "Ile hoteli chcesz stworzyc?" << endl;
                            cin >> size_hotels;
                            
                            Hotel *hotel = new Hotel();
                            
                            for(int i = 0; i < size_hotels; i++)
                            {
                                cout << "Hotel " << i << "." << endl;
                                hotel->create();
                                hotele.push_back(*hotel);
                            }
                        }
                            break;
                        case 'b':
                            if(hotele.size() == 0)
                            {
                                cout << "Lista hoteli jest pusta" << endl;
                                break;
                            }
                            for(int i = 0; i < hotele.size(); i++)
                            {
                                hotele[i].show();
                            }
                            break;
                        case 'c':
                            if(hotele.size() == 0)
                            {
                                cout << "Lista hoteli jest pusta" << endl;
                                break;
                            }
                            for(int i = 0; i < hotele.size(); i++)
                            {
                                cout << i << ".";
                                hotele[i].show();
                            }
                            
                            cout << "Podaj numer hotelu ktorego chcesz usunac" << endl;
                            int numer;
                            cin >> numer;
                            
                            while(numer < 0 || numer >= hotele.size())
                            {
                                cout << "Bledny numer, podaj jeszcze raz" << endl;
                                cin >> numer;
                            }
                            hotele.erase(hotele.begin() + numer);
                            break;
                        case 'd':
                            goto powrot;
                            break;
                        default: cout << "Blad" << endl;
                    }
                }
                break;
                
                
            case '3':
                for (;;)
                {
                    Person *person = new Person();
                    
                    cout << "                       Goscie" << endl;
                    cout << "-----------------------------" << endl;
                    cout << "Menu:" << endl;
                    cout << "    a: Dodaj goscia do hotelu" << endl;
                    cout << "    b: Wyswietl informacje o gosciach w hotelach" << endl;
                    cout << "    c: Usun goscia z hotelu" << endl;
                    cout << "    d: Powrot" << endl;
                    cin >> wybor;
                    
                    switch (wybor)
                    {
                        case 'a':
                        {
                            if(hotele.size() == 0)
                            {
                                cout << "Lista hoteli jest pusta" << endl;
                                break;
                            }
                            
                            for(int i = 0; i < hotele.size(); i++)
                            {
                                cout << i << ".";
                                hotele[i].show();
                            }
                            
                            int numerHotelu;
                            
                            cout << "Wybierz hotel do ktorego chcesz dodac goscia" << endl;
                            cin >> numerHotelu;
                            
                            while(numerHotelu < 0 || numerHotelu >= hotele.size())
                            {
                                cout << "Bledny numer, podaj jeszcze raz" << endl;
                                cin >> numerHotelu;
                            }
                            
                            bool zajete = true;
                            
                            for(int i = 0; i < hotele[numerHotelu].rooms.size(); i++)
                            {
                                if(hotele[numerHotelu].rooms[i].reserved == false)
                                    zajete = false;
                            }
                            
                            
                            if(zajete == true)
                            {
                                cout << "Wszystkie pokoje zajete w tym hotelu" << endl;
                                break;
                            }
                            
                            int numerPokoju;
                            cout << "Wybierz numer pokoju do ktorego chcesz dodac goscia" << endl;
                            cin >> numerPokoju;
                            while(numerPokoju < 0
                                  || hotele[numerHotelu].rooms.size() <= numerPokoju
                                  || hotele[numerHotelu].rooms[numerPokoju].reserved == true)
                            {
                                cout << "Bledny numer, podaj jeszcze raz" << endl;
                                cin >> numerPokoju;
                            }
                            person->create();
                            person->numerPokoju = numerPokoju;
                            
                            hotele[numerHotelu](person, numerPokoju);
                            
                            
                            //hotele[numerHotelu].goscie.push_back(*person);
                            //hotele[numerHotelu][numerPokoju].setReservation(person);
                            break;
                        }
                        case 'b':
                        {
                            if(hotele.size() == 0)
                            {
                                cout << "Lista gosci jest pusta" << endl;
                                break;
                            }
                            
                            int iloscGosci = 0;
                            for(int i = 0; i < hotele.size(); i++)
                                iloscGosci += hotele[i].goscie.size();
                            
                            if(iloscGosci == 0)
                            {
                                cout << "Lista gosci jest pusta" << endl;
                                break;
                            }
                            else
                            {
                                for(int i = 0; i < hotele.size(); i++)
                                {
                                    cout << "Hotel: " << hotele[i].nazwaHotelu << endl;
                                    if(hotele[i].goscie.size() == 0)
                                        cout << "Brak gosci w tym hotelu." << endl;
                                    else{
                                        for(int j = 0; j <hotele[i].goscie.size(); j++)
                                        {
                                            cout << j << ". ";
                                            hotele[i].goscie[j].show();
                                        }
                                        cout << endl;
                                    }
                                }
                            }
                        }
                            break;
                            
                        case 'c':
                        {
                            if(hotele.size() == 0)
                            {
                                cout << "Lista gosci jest pusta" << endl;
                                break;
                            }
                            int iloscGosci = 0;
                            for(int i = 0; i < hotele.size(); i++)
                                iloscGosci += hotele[i].goscie.size();
                            
                            if(iloscGosci == 0)
                            {
                                cout << "Lista gosci jest pusta" << endl;
                                break;
                            }
                            else
                            {
                                for(int i = 0; i < hotele.size(); i++)
                                {
                                    cout << i << ". ";
                                    hotele[i].show();
                                    cout << "Ilosc gosci w tym hotelu: " << hotele[i].goscie.size();
                                    cout << endl;
                                }
                                
                                cout << "Podaj numer hotelu z ktorego chcesz usunac goscia" << endl;
                                int numerHotelu;
                                cin >> numerHotelu;
                       
                                while(numerHotelu < 0 || numerHotelu >= hotele.size() || hotele[numerHotelu].goscie.size() == 0)
                                {
                                    cout << "Bledny numer, podaj jeszcze raz" << endl;
                                    cin >> numerHotelu;
                                }
                                
                                for(int i = 0; i < hotele[numerHotelu].goscie.size(); i++)
                                {
                                    cout << i << ". ";
                                    hotele[numerHotelu].goscie[i].show();
                                }
                                
                                int numerGoscia;
                                cout << "Podaj numer goscia ktorego chcesz usunac" << endl;
                                cin >> numerGoscia;
                                
                                while(numerGoscia < 0 || numerGoscia >= hotele[numerHotelu].goscie.size())
                                {
                                    cout << "Bledny numer, podaj jeszcze raz" << endl;
                                    cin >> numerGoscia;
                                }
                                
                                //operator []
                                hotele[numerHotelu][ hotele[numerHotelu].goscie[numerGoscia].numerPokoju ].removeReservation();
                                
                                hotele[numerHotelu].goscie.erase(hotele[numerHotelu].goscie.begin() + numerGoscia);
                            }
                        }
                            break;
                        case 'd':
                            goto powrot;
                            break;
                        default: cout << "Blad" << endl;
                    }
                }
                break;
             
            case'4':
                cout<< "Polimorfizm"<<endl;
                osoby.push_back(new Wlasciciel());
                osoby.push_back(new Person());
                
                cout << "Wprowadz managera"<<endl;
                osoby.at(0)->create();
                osoby.at(0)->show();
                cout<<"Wprowadz pracownika hotelu i okres jego pracy"<<endl;
                osoby.at(1)->create();
                osoby.at(1)->show();
                
                break;
                
            case '5':
                
                cout<< "Koniec programu"<<endl;
                return 0;
            default: cout << "Blad" << endl;
        }
    }
}

