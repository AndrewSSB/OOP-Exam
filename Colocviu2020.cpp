#include <iostream>
#include <vector>
using namespace std;
class Masca{
protected:
    string tip;
public:
    Masca(){
        tip="-";
    }
    Masca(string tip){
        this->tip=tip;
    }
    Masca(const Masca&m){
        this->tip=m.tip;
    }
    Masca& operator=(const Masca&m){
        if (this!=&m){
           this->tip=m.tip;
        }
        return *this;
    }
    virtual ~Masca(){}
    virtual int pret()=0;
    virtual istream& citire_virtuala(istream&in){
        cout<<"\nTip masca: ";
        in>>tip;
        return in;
    }
    virtual ostream& afisare_virtuala(ostream&out) const{
        out<<"\nTip masca: "<<tip;
        return out;
    }
    friend istream& operator>>(istream&in, Masca&m);
    friend ostream& operator<<(ostream&out,const Masca&m);
};

istream& operator>>(istream&in,Masca&m){
    return m.citire_virtuala(in);
}

ostream& operator<<(ostream&out,const Masca&m){
    return m.afisare_virtuala(out);
}

class MascaChirurgicala:public Masca{
private:
    string culoare;
    int nr_pliuri;
public:
    MascaChirurgicala():Masca(){
        this->culoare="-";
        this->nr_pliuri=0;
    }
    MascaChirurgicala(string tip,string culoare, int nr_pliuri):Masca(tip){
        this->culoare=culoare;
        this->nr_pliuri=nr_pliuri;
    }
    MascaChirurgicala(const MascaChirurgicala&m):Masca(m){
        this->culoare=m.culoare;
        this->nr_pliuri=m.nr_pliuri;
    }
    MascaChirurgicala& operator=(const MascaChirurgicala&m){
        if (this!=&m){
            Masca::operator=(m);
            this->culoare=m.culoare;
            this->nr_pliuri=m.nr_pliuri;
        }
        return *this;
    }
    ~MascaChirurgicala(){}
    int pret(){
        if (tip=="ffp1")
            return 5;
        else if (tip=="ffp2")
            return 10;
        else if (tip=="ffp3")
            return 15;
    }
    istream& citire_virtuala(istream&in){
        Masca::citire_virtuala(in);
        cout<<"\nCuloare: ";
        in.get();
        char aux[100];
        in.getline(aux,100);
        string s(aux);
        culoare=s;
        cout<<"\nNr pliuri: ";
        in>>nr_pliuri;
        return in;
    }
    ostream& afisare_virtuala(ostream&out) const{
        Masca::afisare_virtuala(out);
        out<<"\nCuloare: "<<culoare;
        out<<"\nNr pliuri: "<<nr_pliuri;
        return out;
    }
};
class MascaPolicarbonat:public Masca{
private:
    string tip_prindere;
public:
    MascaPolicarbonat(){
        this->tip="ffp0";
        this->tip_prindere="-";
    }
    MascaPolicarbonat(string tip_prindere,string tip="ffp0"){
        this->tip=tip;
        this->tip_prindere=tip_prindere;
    }
    MascaPolicarbonat(const MascaPolicarbonat&m):Masca(m){
        this->tip_prindere=tip_prindere;
    }
    MascaPolicarbonat& operator=(const MascaPolicarbonat&m){
        if (this!=&m){
            Masca::operator=(m);
            this->tip_prindere=m.tip_prindere;
        }
        return *this;
    }
    ~MascaPolicarbonat(){}
    int pret(){
        return 20;
    }
    istream& citire_virtuala(istream&in){
        cout<<"\nTip prindere: ";
        in>>tip_prindere;
        return in;
    }
    ostream& afisare_virtuala(ostream& out) const{
        Masca::afisare_virtuala(out);
        out<<"\nTip prindere: "<<tip_prindere;
        return out;
    }
    friend istream& operator>>(istream& in, MascaPolicarbonat* m);
    friend ostream& operator<<(ostream&out,MascaPolicarbonat*m);
};
istream& operator>>(istream&in,MascaPolicarbonat*m){
    return m->citire_virtuala(in);
}
ostream& operator<<(ostream&out,MascaPolicarbonat*m){
    return m->afisare_virtuala(out);
}

class Dezinfectant{
protected:
    int nr_specii;
    vector<string>ingrediente;
    vector<string>suprafete;
public:
    Dezinfectant(){
        nr_specii=0;
    }
    Dezinfectant(int nr_specii,vector<string>ingrediente,vector<string> suprafete){
        this->nr_specii=nr_specii;
        for (int i=0;i<ingrediente.size();++i)
            this->ingrediente.push_back(ingrediente[i]);
        for (int i=0;i<suprafete.size();++i)
            this->suprafete.push_back(suprafete[i]);
    }
    Dezinfectant(const Dezinfectant&d){
        this->nr_specii=d.nr_specii;
        for (int i=0;i<d.ingrediente.size();++i)
            this->ingrediente.push_back(d.ingrediente[i]);
        for (int i=0;i<d.suprafete.size();++i)
            this->suprafete.push_back(d.suprafete[i]);
    }
    Dezinfectant& operator=(const Dezinfectant&d){
        if (this!=&d){
            this->nr_specii=d.nr_specii;
            for (int i=0;i<d.ingrediente.size();++i)
                this->ingrediente.push_back(d.ingrediente[i]);
            for (int i=0;i<d.suprafete.size();++i)
                this->suprafete.push_back(d.suprafete[i]);
        }
        return *this;
    }
    virtual ~Dezinfectant(){
        if (this->ingrediente.empty())
            this->ingrediente.clear();
        if (this->suprafete.empty())
            this->suprafete.clear();
    }
    virtual float eficienta()=0;
    int pret(){
        float ef=this->eficienta();
        if (ef<0.9)
            return 10;
        else if (ef>=0.9 && ef<0.95)
            return 20;
        else if (ef>=0.95 && ef<0.975)
            return 30;
        else if (ef>=0.975&&ef<0.99)
            return 40;
        else if (ef>=0.99&&ef<0.9999)
            return 50;

    }
};

class DezinfectantBacterii:public Dezinfectant{
public:
    DezinfectantBacterii():Dezinfectant(){}
    DezinfectantBacterii(int nr_specii,vector<string>ingrediente,vector<string> suprafete):Dezinfectant(nr_specii,ingrediente,suprafete){}
    DezinfectantBacterii(const DezinfectantBacterii&d):Dezinfectant(d){}
    ~DezinfectantBacterii(){}
    DezinfectantBacterii& operator=(const DezinfectantBacterii&d){
        if (this!=&d)
            Dezinfectant::operator=(d);
        return *this;
    }
    float eficienta(){
        long long x=1;
        for (int i=1;i<=9;++i)
            x=x*10;
        return (float)nr_specii/x;
    }
};

class DezinfectantFungi:public Dezinfectant{
public:
    DezinfectantFungi():Dezinfectant(){}
    DezinfectantFungi(int nr_specii,vector<string>ingrediente,vector<string> suprafete):Dezinfectant(nr_specii,ingrediente,suprafete){}
    DezinfectantFungi(const DezinfectantFungi&d):Dezinfectant(d){}
    ~DezinfectantFungi(){}
    DezinfectantFungi& operator=(const DezinfectantFungi&d){
        if (this!=&d)
            Dezinfectant::operator=(d);
        return *this;
    }
    float eficienta(){
        float x=1;
        for (int i=1;i<=6;++i)
            x=x*10;
        x=x*1.5;
        return (float)nr_specii/x;
    }
};

class DezinfectantVirusuri:public Dezinfectant{
public:
    DezinfectantVirusuri():Dezinfectant(){}
    DezinfectantVirusuri(int nr_specii,vector<string>ingrediente,vector<string> suprafete):Dezinfectant(nr_specii,ingrediente,suprafete){}
    DezinfectantVirusuri(const DezinfectantVirusuri&d):Dezinfectant(d){}
    ~DezinfectantVirusuri(){}
    DezinfectantVirusuri& operator=(const DezinfectantVirusuri&d){
        if (this!=&d)
            Dezinfectant::operator=(d);
        return *this;
    }
    float eficienta(){
        long long x=1;
        for (int i=1;i<=8;++i)
            x=x*10;
        return (float)nr_specii/x;
    }
};

class Achizitie{
private:
    int zi;
    int luna;
    int an;
    string client;
    vector<Dezinfectant*>dez;
    vector<Masca*>masti;
public:
    Achizitie(){
        zi=0;
        luna=0;
        an=0;
    }
    Achizitie(int zi,int luna,int an,string client){
        this->zi=zi;
        this->luna=luna;
        this->an=an;
        this->client=client;
    }
    Achizitie(const Achizitie&a){
        this->zi=a.zi;
        this->luna=a.luna;
        this->an=a.an;
        this->client=a.client;
        for (int i=0;i<a.dez.size();++i)
            this->dez.push_back(a.dez[i]);
        for (int i=0;i<a.masti.size();++i)
            this->masti.push_back(a.masti[i]);
    }
    Achizitie& operator=(const Achizitie&a){
        if (this!=&a){
            this->zi=a.zi;
            this->luna=a.luna;
            this->an=a.an;
            this->client=a.client;
            for (int i=0;i<a.dez.size();++i)
                this->dez.push_back(a.dez[i]);
            for (int i=0;i<a.masti.size();++i)
                this->masti.push_back(a.masti[i]);
        }
        return *this;
    }
    ~Achizitie(){
        if (this->dez.empty())
            this->dez.clear();
        if (this->masti.empty())
            this->masti.clear();
    }
    Achizitie& operator+=(MascaChirurgicala*m){
        this->masti.push_back(m);
        return *this;
    }
    Achizitie& operator+=(MascaPolicarbonat*m){
        this->masti.push_back(m);
        return *this;
    }
    Achizitie& operator+=(Dezinfectant*d){
        this->dez.push_back(d);
        return *this;
    }
    bool operator<(Achizitie&a){
        int pret1=0;
        for (int i=0;i<this->dez.size();++i)
            pret1=pret1+this->dez[i]->pret();
        for (int i=0;i<this->masti.size();++i)
            pret1=pret1+this->masti[i]->pret();
        int pret2=0;
        for (int i=0;i<a.dez.size();++i)
            pret2=pret2+a.dez[i]->pret();
        for (int i=0;i<a.masti.size();++i)
            pret2=pret2+a.masti[i]->pret();
        if (pret1<pret2)
            return true;
        return false;
    }
    bool operator==(Achizitie&a){
        int pret1=0;
        for (int i=0;i<this->dez.size();++i)
            pret1=pret1+this->dez[i]->pret();
        for (int i=0;i<this->masti.size();++i)
            pret1=pret1+this->masti[i]->pret();
        int pret2=0;
        for (int i=0;i<a.dez.size();++i)
            pret2=pret2+a.dez[i]->pret();
        for (int i=0;i<a.masti.size();++i)
            pret2=pret2+a.masti[i]->pret();
        if (pret1==pret2)
            return true;
        return false;
    }
    string nume(){
        return this->client;
    }
};

int main()
{
    MascaChirurgicala mc1,mc2("ffp2","verde brotcael",55),mc3(mc1),mc4,mc5;
    mc4=mc2;
    //cin>>mc5;
    //cout<<mc1<<mc2;
    MascaPolicarbonat* mp1=new MascaPolicarbonat(),*mp2=new MascaPolicarbonat();
    MascaPolicarbonat *mp3=new MascaPolicarbonat("elastic");
    //cin>>mp1>>mp2;
    //cout<<mp3;
    Dezinfectant* d1 = new DezinfectantBacterii(100000000, vector<string>({"sulfati non-ionici","suflati cationci", "parfumuri", "Linalool", "Metilpropanol butilpentil"}),vector<string>({"lemn","sticla", "metal", "ceramica", "marmura"}));
    Dezinfectant* d2 = new DezinfectantVirusuri(50000000, vector<string>({"Alkil Dimetilm Benzil Crlorura de amoniu","parfumuri", "Butilpentil metilpropinal"}), vector<string>({"lemn, sticla, ceramica, marmura"}));
    Dezinfectant* d3 = new DezinfectantFungi(1400000, vector<string>({"Alkil Etil Benzil Crlorura de amoniu","parfumuri", "Butilpentil metilpropinal"}), vector<string>({"sticla, plastic"}));
    //cout << d1->eficienta() << " " << d2->eficienta() << " " << d3->eficienta() << '\n';
    Achizitie *a1=new Achizitie(26,5,2020,"PlushBio SRL");
    *a1+=mp1;
    *a1+=(&mc1);
    *a1+=d3;
    Achizitie *a2=new Achizitie(25,5,2020,"Gucci");
    *a2+=d1;
    *a2+=d2;
    *a2+=d2;
    Achizitie a3,a4(*a1);
    a3=*a2;
    if (*a1<*a2)
        cout<<a1->nume()<<" are valoarea facturii mai mica.\n";
    else if (*a1==*a2)
        cout<<a1->nume()<<" si "<<a2->nume()<<" au aceeasi valoare a facturii.\n";
    else
        cout<<a2->nume()<<" are valoarea facturii mai mica.\n";
}