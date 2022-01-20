/*
Ene Marius-Andrei - 142
EDUARD GABRIEL SZMETEANCA
CodeBlocks GNU GCC Compiler (c++11)
 */

#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <unordered_map>
#include <list>
#include <set>

using namespace std;

class IO{ // clasa de afisare in consola/citire de la tastatura
public:
    friend istream &operator>>(istream &, IO &);
    friend ostream &operator<<(ostream &, const IO &);

    virtual void Afisare(ostream &) const = 0;
    virtual void Citire(istream &) = 0;

    virtual ~IO(); // destructor virtual pentru a putea mostenii din ea;
};
istream &operator >>(istream &in, IO &obj){
    obj.Citire(in);
    return in;
}

ostream &operator<<(ostream &out,const IO &obj){
    obj.Afisare(out);
    return out;
}

IO::~IO()
{
}

class Exception{
public:
    Exception(const Exception &) = default;
    Exception&operator=(const Exception &) = default;
    friend ostream &operator<<(ostream & out, std::exception & ex);
    ~Exception();
};

ostream & operator<<(ostream &out, std::exception &ex){
    string eroare = ex.what();
    //rtti, downcasting
    if(const auto except = dynamic_cast<const bad_exception*>(&ex))
        out << "Bad exception :" + eroare;
    else if(const auto except = dynamic_cast<const bad_alloc*>(&ex))
        out << "Bad alloc: " + eroare;
    else if(const auto except = dynamic_cast<const runtime_error*>(&ex))
        out << "Runtime error: " + eroare;
    else if(const auto except = dynamic_cast<const logic_error*>(&ex))
        out << "Logic error: " + eroare;
    else
        out << "Other error: " + eroare;
    return out;
}

Exception::~Exception()
{
}

template<typename T1, typename T2, typename T3>
class PreData{
protected:
    T1 day;
    T2 month;
    T3 year;
public:
    PreData(T1 _day = 0, T2 _month = 0, T3 _year = 0);
    PreData(const PreData &);
    PreData&operator=(const PreData &);

    virtual ~PreData();
};

template<typename T1, typename T2, typename T3>
PreData<T1, T2, T3>::PreData(T1 _day, T2 _month, T3 _year):
    day(_day),
    month(_month),
    year(_year)
{
}

template<typename T1, typename T2, typename T3>
PreData<T1, T2, T3>::PreData(const PreData & obj){
    day = obj.day;
    month = obj.month;
    year = obj.year;
}
template<typename T1, typename T2, typename T3>
PreData<T1, T2, T3>&PreData<T1, T2, T3>::operator=(const PreData &obj){
    if(this!=&obj){
        day = obj.day;
        month = obj.month;
        year = obj.year;
    }
    return *this;
}

template<typename T1, typename T2, typename T3>
PreData<T1, T2, T3>::~PreData()
{
}

class Data: public PreData<int, int, int>{
public:
    int getDay();
    int getMonth();
    int getYear();
    void setDay(int zi);
    void setMonth(int luna);
    void setYear(int an);
    Data(int _day = 0, int _month = 0, int _year = 0);
    Data(const Data&);
    Data&operator=(const Data&);

    string GetDataString() const;

    virtual ~Data();
};

Data::Data(int _day, int _month, int _year):PreData(_day, _month, _year)
{
}

Data::Data(const Data&obj):PreData(obj)
{
}

Data&Data::operator=(const Data &obj){
    if(this!=&obj){
        PreData::operator=(obj);
    }
    return *this;
}

int Data::getDay(){
    return day;
}

int Data::getMonth(){
    return month;
}

int Data::getYear(){
    return year;
}

void Data::setDay(int zi){
    day = zi;
}

void Data::setMonth(int luna){
    month = luna;
}

void Data::setYear(int an){
    year = an;
}

string Data::GetDataString() const{
    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}

Data::~Data()
{
}

class Malware : public IO{
protected:
    float rating_impact;
    Data data;
    string nume;
    string metoda_infectare;
    vector<string> registri;
public:
    Malware(int zi=0, int luna =0, int an =0, string _nume="Unknown", string _metoda_infectare = "Unknown", vector<string> _registri = {"NULL"});
    Malware(const Malware &) = default;
    Malware&operator=(const Malware &) = default;

    virtual void Calculeaza_Rating() = 0;

    float GetRating();

    void Afisare(ostream & out) const;
    void Citire(istream &in);

    virtual ~Malware(); // destructor virtual pentru a putea mostenii din ea;
};

float Malware::GetRating(){
    return rating_impact;
}

void Malware::Afisare(ostream & out) const{
    out << "\nNume: " << nume;
    out << "\nMetoda infectare: " << metoda_infectare;
    out << "\nRegistri: ";
    for(int i=0; i<(int)registri.size(); i++)
        out << registri[i];
}

void Malware::Citire(istream &in){
    int val;
    cout << "Zi: "; in >> val;
    data.setDay(val);
    cout << "Luna: "; in >> val;
    data.setMonth(val);
    cout << "An: "; in >> val;
    data.setYear(val);
    cout << "Nume: "; in >> nume;
    cout << "Metoda infectare: "; in >> metoda_infectare;
    cout << "Nr de registrii: "; in >> val;
    for (int i=0; i < val; i++){
        string aux;
        in >> aux;
        registri.push_back(aux);
    }
}

Malware::Malware(int zi, int luna, int an, string _nume, string _metoda_infectare, vector<string> _registri):
    nume(_nume),
    metoda_infectare(_metoda_infectare),
    registri(_registri)
{
    rating_impact = 0;
    data = Data(zi, luna, an);
}

Malware::~Malware()
{
}

class Rootkit : public Malware{
protected:
    vector<string> dll;
    vector<string> rau_intentionat;
public:
    Rootkit(int zi=0, int luna =0, int an =0, string _nume="Unknown", string _metoda_infectare = "Unknown", vector<string> _registri = {"NULL"}, vector<string> _dll = {"NULL"}, vector<string> _rau = {"NULL"});
    Rootkit(const Rootkit&) = default;
    Rootkit&operator=(const Rootkit&) = default;

    void Calculeaza_Rating();

    void Afisare(ostream & out) const;
    void Citire(istream &in);

    ~Rootkit(); // destructor virtual pentru a putea mostenii
};

void Rootkit::Afisare(ostream &out) const {
    Malware::Afisare(out);
    for (int i=0; i<(int)dll.size(); i++)
        out << dll[i] << " ";
    for(int i=0; i<(int)rau_intentionat.size(); i++)
        out << rau_intentionat[i];
}

void Rootkit::Citire(istream &in){
    Malware::Citire(in);
    int val;
    cout << "Numar de dll-uri:"; in >> val;
    for(int i=0; i<val; i++){
        string aux;
        in >> aux;
        dll.push_back(aux);
    }
    cout << "Numar de fisiere rau intentionare:"; in>>val;
    for(int i=0; i<val; i++){
        string aux;
        in >> aux;
        rau_intentionat.push_back(aux);
    }
    Calculeaza_Rating();
}

void Rootkit::Calculeaza_Rating(){
    for (int i=0; i<(int)rau_intentionat.size(); i++){
        if (rau_intentionat[i] == "System Service Descriptor Table" || rau_intentionat[i] == "SSDT" || rau_intentionat[i] == "NtCreateFile")
            rating_impact+=100;
    }
    for (int i=0; i<(int)dll.size(); i++)
        if(dll[i] == "ntoskrnl.exe")
            rating_impact *=2;
}

Rootkit::Rootkit(int zi, int luna, int an, string _nume, string _metoda_infectare, vector<string> _registri, vector<string> _dll, vector<string> _rau):
    Malware(zi, luna, an, _nume, _metoda_infectare, _registri),
    dll(_dll),
    rau_intentionat(_rau)
{
}

Rootkit::~Rootkit(){
}

class Keylogger: public Malware{
protected:
    vector<string> functii;
    vector<string> taste_speciale;
public:
    Keylogger(int zi=0, int luna =0, int an =0, string _nume="Unknown", string _metoda_infectare = "Unknown", vector<string> _registri = {"NULL"},
              vector<string> _functii = {"null"}, vector<string> _taste = {"null"});
    Keylogger(const Keylogger&) = default;
    Keylogger&operator=(const Keylogger&) = default;

    void Calculeaza_Rating();

    void Afisare(ostream & out) const;
    void Citire(istream &in);

    virtual ~Keylogger();

};

void Keylogger::Afisare(ostream &out) const {
    Malware::Afisare(out);
    for (int i=0; i<(int)functii.size(); i++)
        out << functii[i] << " ";
    for(int i=0; i<(int)taste_speciale.size(); i++)
        out << taste_speciale[i];
}

void Keylogger::Citire(istream &in){
    Malware::Citire(in);
    int val;
    cout << "Numar de functii:"; in >> val;
    for(int i=0; i<val; i++){
        cout << "\nFunctia: ";
        string aux;
        in >> aux;
        functii.push_back(aux);
    }
    cout << "Numar taste speciale:"; in>>val;
    for(int i=0; i<val; i++){
        cout << "Tasta: ";
        string aux;
        in >> aux;
        taste_speciale.push_back(aux);
    }
}

void Keylogger::Calculeaza_Rating(){
    unordered_map<string, int> help;
    for(int i=0; i<(int)taste_speciale.size(); i++){

    }
}

Keylogger::Keylogger(int zi, int luna, int an, string _nume, string _metoda_infectare, vector<string> _registri, vector<string> _functii, vector<string> _taste):
    Malware(zi, luna, an, _nume, _metoda_infectare, _registri),
    functii(_functii),
    taste_speciale(_taste)
{
}

Keylogger::~Keylogger(){}

class Kernel_keylogger : public Keylogger, public Rootkit{
private:
    bool ascuns;
public:
    Kernel_keylogger(bool _ascuns = false);
    Kernel_keylogger(const Kernel_keylogger &) = default;
    Kernel_keylogger&operator=(const Kernel_keylogger &) = default;

    void Calculeaza_Rating();

    void Afisare(ostream & out) const;
    void Citire(istream &in);

    ~Kernel_keylogger();
};

void Kernel_keylogger::Afisare(ostream &out) const {
    Keylogger::Afisare(out);
    Rootkit::Afisare(out);
    out << "Fisierul " <<ascuns << " este ascuns";
}

void Kernel_keylogger::Citire(istream &in){
    cout << "Ascuns ?:"; in >> ascuns;
    Keylogger::Citire(in);
    Rootkit::Citire(in);
}

void Kernel_keylogger::Calculeaza_Rating(){}

Kernel_keylogger::Kernel_keylogger(bool _ascuns):Keylogger(), Rootkit()
{
}

Kernel_keylogger::~Kernel_keylogger(){}

class Ransomware: public Malware {
private:
    int rating_criptare;
    float rating_obfuscare;
public:
    Ransomware(int zi=0, int luna =0, int an =0, string _nume="Unknown", string _metoda_infectare = "Unknown",
               vector<string> _registri = {"NULL"}, int rating_criptare = 0, float rating_obfuscare = 0);
    Ransomware(const Ransomware&) = default;
    Ransomware&operator=(const Ransomware &) = default;

    void Calculeaza_Rating();

    void Afisare(ostream & out) const;
    void Citire(istream &in);

    ~Ransomware();
};

Ransomware::Ransomware(int zi, int luna, int an, string _nume, string _metoda_infectare, vector<string> _registri, int rating_1, float rating_2):
    Malware(zi, luna, an, _nume, _metoda_infectare, _registri),
    rating_criptare(rating_1),
    rating_obfuscare(rating_2)
{
}

void Ransomware::Afisare(ostream &out) const {
    Malware::Afisare(out);
    out << "\nRating criptare: " << rating_criptare;
    out << "\nRating obsfucare: " << rating_obfuscare;
}

void Ransomware::Citire(istream &in){
    Malware::Citire(in);
}

void Ransomware::Calculeaza_Rating(){}

Ransomware::~Ransomware(){}

class Computer{
private:
    vector<Malware*> virusi;
    static int contorCOD;
    const int ID;
    float rating_final;
public:
    Computer();

    void operator+=(Malware * obj);

    friend ostream & operator<<(ostream &out, const Computer & obj);
    friend istream & operator>>(istream &out, Computer &obj);

    void functie_calc_rating_final();

    ~Computer();
};

void Computer::functie_calc_rating_final(){
    for(int i=0; i<(int)virusi.size(); i++){
        rating_final += virusi[i]->GetRating();
    }
}

void Computer::operator+=(Malware *obj){
    virusi.push_back(obj);
    rating_final+=obj->GetRating();
}

ostream & operator<<(ostream &out, const Computer & obj){
    for (int i=0; i<(int)obj.virusi.size(); i++)
        out << *obj.virusi[i] << " ";
    out << "Rating final: " << obj.rating_final;
    return out;
}

istream & operator>>(istream &in, Computer &obj){
    cout << "Numarul de calculatoare: ";
    int nr_calc;
    in >> nr_calc;
    for(int i=0; i<nr_calc; i++){
        cout << "1-Rootkit, 2-Keylogger, 3-Kernel, 4-Ransomware: ";
        int val;
        cin >> val;
        switch(val){
            case 1:{
                Malware * aux = new Rootkit();
                cin >> *aux;
                obj.virusi.push_back(aux);
            break;
            }
            case 2:{
                Malware * aux = new Keylogger();
                cin >> *aux;
                obj.virusi.push_back(aux);
                break;
            }
            case 3:{
                Keylogger * aux = new Kernel_keylogger;
                cin >> *aux;
                obj.virusi.push_back(aux);
            break;
            }
            case 4:{
                Malware * aux = new Ransomware();
                cin >> *aux;
                obj.virusi.push_back(aux);
            break;
            }
        }
    }
    return in;
}

Computer::Computer():ID(contorCOD++)
{
    rating_final = 0;
}

int Computer::contorCOD = 0;

Computer::~Computer(){
    if(virusi.empty())
        virusi.clear();
}

class Meniu{ //design pattern: singleton
private:
    Meniu();
    Meniu(const Meniu &) = delete;
    Meniu&operator=(const Meniu &) = delete;

    vector<Computer*> calc;

    static Meniu *g_instance;
public:
    static Meniu *get_instance();
    static void delete_Instance();
    ~Meniu();
};

Meniu *Meniu::g_instance = nullptr;

Meniu::Meniu(){
    try{
    // aici scrii efectiv codul pe care-l scriai in main
        cout << "numar de calculatoare: ";
        int nr;
        cin >> nr;
        for(int i=0; i< nr; i++){
            Computer *obj = new Computer();
            cin >> *obj;
            calc.push_back(obj);
        }

    }
    catch(exception &e){
        cout << "Opps " << e << " :( \n";
    }
}

Meniu *Meniu::get_instance(){
    if(!g_instance)
        g_instance = new Meniu();
    return g_instance;
}

Meniu::~Meniu(){
    if(calc.empty())
        calc.clear();
}

void Meniu::delete_Instance(){
    delete g_instance;
    g_instance = nullptr;
}


int main()
{
    Meniu * arhiva = arhiva->get_instance();
    arhiva->delete_Instance();
    return 0;
}
