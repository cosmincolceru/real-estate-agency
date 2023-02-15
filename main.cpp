#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <typeinfo>
#include <exception>
#include <set>
#include <map>

using namespace std;

template<class T>
T modificaPret(T ob, double pret) {
	*ob += pret;
	return ob;
}

template<class T>
void comparaImobile(T im1, T im2) {
	if (*im1 < *im2)
		cout << "Primul imobil este mai mic decat al doilea" << endl;
	else
		cout << "Al doilea imobil este mai mic decat primul" << endl;		 
}

template<class T> 
class Cartier {
private:
	set<T> imobile;
public:
	Cartier(set<T> imobile = {}) {
		this->imobile = imobile;
	}
	void adaugaImobil(T im) {
		this->imobile.insert(im);
	}
	void afiseazaImobilele() {
		for (const auto& im : imobile) {
			cout << im << endl;
		}
	}
};

class NumarInvalid: public exception {
public:
	virtual const char* what() throw() {
		return "Valoarea trebuie sa fie un numar intreg main mare decat 0\n";
	}
} numarInvalid;

class IOInterface {
public:
    virtual istream& read(istream& in) = 0;
    virtual ostream& write(ostream& out) const = 0 ;
};


class Imobil: public IOInterface {
protected:
	double pret;
	string strada;
	int numar;
	bool vandut;
public:
	Imobil();
	Imobil(double pret, string strada, int numar, bool vandut); 
	Imobil(const Imobil& im);
	Imobil& operator=(const Imobil& im);
	friend istream& operator>>(istream& in, Imobil& im);
	friend ostream& operator<<(ostream& out, const Imobil& im);
	istream& read(istream& in);
	ostream& write(ostream& out) const;

	double getPret();
	string getStrada();
	int getNumar();
	bool getVandut();

	void setPret(double pret);
	void setStrada(string strada);
	void setNumar(int numar);
	void setVandut(bool vandut);

	Imobil& operator+=(double x);	// adauga x la pretul imobilului
	Imobil& operator-=(double x);	// scade x din pretul imobilului
	bool operator==(const Imobil& c);  //verifica daca imobilele au aceeasi adresa
	explicit operator int();
	virtual bool operator<(const Imobil& c) const; // compara preturile

	virtual void afisPretPeMetru2() = 0; // afiseaza pretul pe metru patrat al imobilului

	~Imobil();
};

Imobil::Imobil() {
	this->pret = -1;
	this->strada = "Necunoscut";
	this->numar = -1;
	this->vandut = false;
}

Imobil::Imobil(double pret, string strada, int numar, bool vandut) {
	this->pret = pret;
	this->strada = strada;
	this->numar = numar;
	this->vandut = vandut;
}

Imobil::Imobil(const Imobil& im) {
	this->pret = im.pret;
	this->strada = im.strada;
	this->numar = im.numar;
	this->vandut = im.vandut;
}

Imobil& Imobil::operator=(const Imobil& im) {
	if (this != &im) {
		this->pret = im.pret;
		this->strada = im.strada;
		this->numar = im.numar;
		this->vandut = im.vandut;
	}
	return *this;
}

istream& operator>>(istream& in, Imobil& im) {
	return im.read(in);
}

ostream& operator<<(ostream& out, const Imobil& im) {
	return im.write(out);
}

istream& Imobil::read(istream& in) {
	while (true) {
		cout << "Scrie pretul: ";
		try {
			in >> this->pret;
			if (this->pret < 0)
				throw 1;
			break;
		} catch(int x) {
			cout << "Pretul trebuie sa fie mai mare decat 0\n";

		}
	}
	
	cout << "Scrie strada: ";
	in >> this->strada;

	while (true) {
		cout << "Scrie numarul: ";
		try {
			in >> this->numar;
			if (this->numar < 1) 
				throw string("Numar invalid\n");
			break;
		} catch (string s) {
			cout << s;
		}
	}
	
	while (true) {
		cout << "Scrie 1 daca imobilul este vandut sau 0 daca nu este vandut: ";
		try {
			int x;
			in >> x;
			if (x != 0 && x != 1)
				throw x;
			this->vandut = x;
			break;
		} catch (int x) {
			cout << "Ati introdus o valoare gresita" << endl;
		} 
	}
	return in;
}

ostream& Imobil::write(ostream& out) const {
	out << "Pretul este " << this->pret << endl;
	out << "Adresa este strada " << this->strada << ", numarul " << this->numar << endl;
	if (this->vandut == true)
		out << "Imobilul este vandut" << endl;
	else 
		out << "Imobilul este disponibil" << endl;
	return out;
}

double Imobil::getPret() {
	return this->pret;
}

string Imobil::getStrada() {
	return this->strada;
}

int Imobil::getNumar() {
	return this->numar;
}

bool Imobil::getVandut() {
	return this->vandut;
}

void Imobil::setPret(double pret) {
	this->pret = pret;
}

void Imobil::setStrada(string strada) {
	this->strada = strada;
}

void Imobil::setNumar(int numar) {
	this->numar = numar;
}

void Imobil::setVandut(bool vandut) {
	this->vandut = vandut;
}

Imobil& Imobil::operator+=(double x) {
	this->pret += x;
	return *this;
}

Imobil& Imobil::operator-=(double x) {
	this->pret -= x;
	return *this;
}

bool Imobil::operator==(const Imobil& im) {
	if (this->strada == im.strada &&
		this->numar == im.numar)
		return true;
	return false;
}

Imobil::operator int() {
	return (int)this->pret;
}

bool Imobil::operator<(const Imobil& im) const {
	return this->pret < im.pret;
}

Imobil::~Imobil() {
	// cout << "Obiect imobil distrus" << endl;
}


class Casa: public virtual Imobil {
protected:
	int nrCamere;
	int suprafata;
	
	int anConstructie;

	const int idCasa;
	static int contorIdCasa;
public:
	Casa();
	Casa(double pret, string strada, int numar, bool vandut, int nrCamere, int suprafata, int anConstructie);
	Casa(const Casa& c);
	Casa& operator= (const Casa& c);
	
	int getNrCamere();
	int getSuprafata();
	int getAnConstructie();
	int getIdCasa();
	static int getContorIdCasa();

	void setNrCamere(int nrCamere);
	void setSuprafata(int suprafata);
	void setAnConstructie(int anConstructie);
	void setVandut(bool vandut);

	istream& read(istream& in);
	ostream& write(ostream& out) const;

	Casa operator++();   //incrementeaza pretul casei
	Casa operator++(int);
	Casa operator+(double x);	//aduna la pretul casei
	Casa operator-(double x);   //scade din pretul casei
	Casa operator+(Casa c);
	friend Casa operator+(double x, Casa c);
	friend Casa operator-(double x, Casa c);
	
	bool operator<(const Casa& c) const;   //verifica daca prima casa are suprafata mai mica decat a doua

	void afisPretPeMetru2(); 

	~Casa();
};

int Casa::contorIdCasa = 0;

Casa::Casa(): Imobil(), idCasa(++contorIdCasa){
	this->nrCamere = -1;
	this->suprafata = -1;
	this->anConstructie = -1;
}

Casa::Casa(double pret, string strada, int numar, bool vandut, int nrCamere, int suprafata, int anConstructie): Imobil(pret, strada, numar, vandut),
														  													   	idCasa(++contorIdCasa) {
	this->nrCamere = nrCamere;
	this->suprafata = suprafata;
	this->anConstructie = anConstructie;
}

Casa::Casa (const Casa& c): Imobil(c),
							idCasa(c.idCasa) {
	this->nrCamere = c.nrCamere;
	this->suprafata = c.suprafata;
	this->anConstructie = c.anConstructie;
}

Casa& Casa::operator= (const Casa& c) {
	if (this != &c) {
		Imobil::operator=(c);
		this->nrCamere = c.nrCamere;
		this->suprafata = c.suprafata;
		this->anConstructie = c.anConstructie;
	}
	return *this;
}

int Casa::getNrCamere() {
	return this->nrCamere;
}

int Casa::getSuprafata() {
	return this->suprafata;
}

int Casa::getAnConstructie() {
	return this->anConstructie;
}

int Casa::getIdCasa() {
	return this->idCasa;
}

int Casa::getContorIdCasa() {
	return Casa::contorIdCasa;
}

void Casa::setNrCamere(int nrCamere) {
	this->nrCamere = nrCamere;
}

void Casa::setSuprafata(int suprafata) {
	this->suprafata = suprafata;
}

void Casa::setAnConstructie(int anConstructie) {
	this->anConstructie = anConstructie;
}

void Casa::afisPretPeMetru2() {     
	cout << "Pretul pe metru patrat al casei este " << this->pret / this->suprafata << " euro pe metru patrat" << endl;
}

istream& Casa::read(istream& in) {
	Imobil::read(in);
	while (true) {
		cout << "Scrie suprafata: ";
		try {
			in >> this->suprafata;
			if (this->suprafata < 1) 
				throw numarInvalid;
			break;
		} catch (NumarInvalid n) {
			cout << n.what();
		}
	}

	while (true) {
		cout << "Scrie numarul de camere: ";
		try {
			in >> this->nrCamere;
			if (this->nrCamere < 1) 
				throw numarInvalid;
			break;
		} catch (NumarInvalid n) {
			cout << n.what();
		}
	}
	
	while (true) {
		cout << "Scrie anul de constructie: ";
		try {
			in >> this->anConstructie;
			if (this->anConstructie < 1000 || this->anConstructie > 2022)
				throw string("An invalid\n");
			break;
		} catch (string s) {
			cout << s;
		}		
	}
}

ostream& Casa::write(ostream& out) const {
	Imobil::write(out);
	out << "Casa are " << this->nrCamere << " camere" << endl;
	out << "Suprafata casei este de " << this->suprafata << "mp2" << endl;
	out << "Casa a fost construita in anul " << this->anConstructie << endl;
}

Casa Casa::operator++() {
	this->pret++;
	return *this;
}

Casa Casa::operator++(int) {
	Casa aux = *this;
	this->pret++;
	return aux;
}

Casa Casa::operator+(double x) {
	Casa aux = *this;
	aux.pret = aux.pret + x;
	return aux;
}

Casa Casa::operator-(double x) { 
	Casa aux = *this;
	aux.pret = aux.pret - x;
	return aux;
}

Casa Casa::operator+(Casa c) {
	c.pret = c.pret + this->pret;
	c.nrCamere = c.nrCamere + this->nrCamere;
	c.suprafata = c.suprafata + this->suprafata;
	return c;
}

Casa operator+(double x, Casa c) {
	c.pret = c.pret + x;
	return c;
}

Casa operator-(double x, Casa c) {
	c.pret = c.pret - x;
	return c;
}

bool Casa::operator<(const Casa& c) const {
	if (this->suprafata < c.suprafata)
		return true;
	return false;
}

Casa::~Casa() {
	// cout << "Obiect casa distrus" << endl;
}


class Apartament: public Imobil {
private:
	int nrCamere;
	int suprafata;
	char scara;
	int etaj;
	int nrApartament;
	int anConstructie;

	const int idApartament;
	static int contorIdApartament;

public:
	Apartament();
	Apartament(float pret, int nrCamere, int suprafata, string strada, int bloc, char scara, int etaj, int nrApartament, int anConstructie, bool vandut);
	Apartament(const Apartament& ap);
	Apartament& operator= (const Apartament& ap);

	istream& read(istream& in);
	ostream& write(ostream& out) const;

	Apartament operator++();    //incrementeaza pretul
	Apartament operator++(int);
	Apartament operator+(float x);   //aduna la pret
	Apartament operator-(float x);	 //scade din pret
	Apartament operator+(Apartament a);
	friend Apartament operator+(float x, Apartament a);
	friend Apartament operator-(float x, Apartament a);
	
	bool operator==(const Imobil& a);
	bool operator==(const Apartament& a);	//verifica daca apartamentele au aceeasi adresa, inclusiv scara, etajul si nummarul apartamentului
	bool operator<(const Apartament& a) const;   	//verifica daca primul apartament are suprafata mai mica decat al doilea

	int getNrCamere();
	int getSuprafata();
	char getScara();
	int getEtaj();
	int getNrApartament();
	int getAnConstructie();
	int getIdApartament();
	static int getContorIdApartament();

	void setNrCamere(int nrCamere);
	void setSuprafata(int suprafata);
	void setScara(char scara);
	void setEtaj(int etaj);
	void setNrApartament(int nrApartament);
	void setAnConstructie(int anConstructie);
	
	void afisPretPeMetru2();  // de modificat

	~Apartament();
};

int Apartament::contorIdApartament = 0;

Apartament::Apartament(): Imobil(), idApartament(++contorIdApartament) {
	this->nrCamere = -1;
	this->suprafata = -1;
	this->scara = '-';
	this->etaj = -1;
	this->nrApartament = -1;
	this->anConstructie = -1;
}

Apartament::Apartament(float pret, int nrCamere, int suprafata, string strada, int nuamar, char scara, int etaj, int nrApartament, int anConstructie, bool vandut): Imobil(pret, strada, numar, vandut), idApartament(++contorIdApartament) {
	
	this->nrCamere = nrCamere;
	this->suprafata = suprafata;
	this->scara = scara;
	this->etaj = etaj;
	this->nrApartament = nrApartament;
	this->anConstructie = anConstructie;
}

Apartament::Apartament(const Apartament& ap): Imobil(ap), idApartament(ap.contorIdApartament) {
	this->nrCamere = ap.nrCamere;
	this->suprafata = ap.suprafata;
	this->scara = ap.scara;
	this->etaj = ap.etaj;
	this->nrApartament = ap.nrApartament;
	this->anConstructie = ap.anConstructie;
}

Apartament& Apartament::operator= (const Apartament& ap) {
	if (this != &ap) {
		Imobil::operator=(ap);
		this->nrCamere = ap.nrCamere;
		this->suprafata = ap.suprafata;
		this->scara = ap.scara;
		this->etaj = ap.etaj;
		this->nrApartament = ap.nrApartament;
		this->anConstructie = ap.anConstructie;
	}
	return *this;
}

int Apartament::getNrCamere() {
	return this->nrCamere;
}

int Apartament::getSuprafata() {
	return this->suprafata;
}

char Apartament::getScara() {
	return this->scara;
}

int Apartament::getEtaj() {
	return this->etaj;
}

int Apartament::getNrApartament() {
	return this->nrApartament;
}

int Apartament::getAnConstructie() {
	return this->anConstructie;
}

int Apartament::getIdApartament() {
	return this->idApartament;
}

int Apartament::getContorIdApartament() {
	return Apartament::contorIdApartament;
}

void Apartament::setNrCamere(int nrCamere) {
	this->nrCamere = nrCamere;
}

void Apartament::setSuprafata(int suprafata) {
	this->suprafata = suprafata;
}

void Apartament::setScara(char scara) {
	this->scara = scara;
}

void Apartament::setEtaj(int etaj) {
	this->etaj = etaj;
}

void Apartament::setNrApartament(int nrApartament) {
	this->nrApartament = nrApartament;
}

void Apartament::setAnConstructie(int anConstructie) {
	this->anConstructie = anConstructie;
}

void Apartament::afisPretPeMetru2() {     
	cout << "Pretul pe metru patrat al apartamentului este " << this->pret / this->suprafata << " euro pe metru patrat" << endl;
}

istream& Apartament::read(istream& in) {
	Imobil::read(in);
	while (true) {
		cout << "Scrie numarul de camere: ";
		try {
			in >> this->nrCamere;
			if (this->nrCamere < 1) 
				throw numarInvalid;
			break;
		} catch (NumarInvalid n) {
			cout << n.what();
		}
	}
	while (true) {
		cout << "Scrie suprafata: ";
		try {
			in >> this->suprafata;
			if (this->suprafata < 1) 
				throw numarInvalid;
			break;
		} catch (NumarInvalid n) {
			cout << n.what();
		}
	}
	
	cout << "Scrie scara la care este apartamentul: ";
	in >> this->scara;

	while (true) {
		cout << "Scrie etajul la care este apartamentul: ";
		try {
			in >>this->etaj;
			if (this->etaj < 0) 
				throw this->etaj;
		} catch (int x) {
			cout << x << " nu este un etaj valid" << endl;
		}
	}

	while (true) {
		cout << "Scrie numarul apartamentului: ";
		try {
			in >> this->nrApartament;
			if (this->nrApartament < 1) 
				throw numarInvalid;
			break;
		} catch (NumarInvalid n) {
			cout << n.what();
		}
	}
	
	while (true) {
		cout << "Scrie anul de constructie al cladirii: ";
		try {
			in >> this->anConstructie;
			if (this->anConstructie < 1000 || this->anConstructie > 2022)
				throw string("An invalid\n");
			break;
		} catch (string s) {
			cout << s;
		}		
	}
	return in;
}

ostream& Apartament::write(ostream& out) const {
	Imobil::write(out);
	out << "Apartamentul are " << this->nrCamere << " camere" << endl;
	out << "Suprafata apartamentului este de " << this->suprafata << "mp2" << endl;	
	out << "Apartamentul este la  scara " << this->scara << ", etajul " << this->etaj << ", numarul " << this->nrApartament << endl;
	out << "Blocul a fost construit in anul " << this->anConstructie << endl;
	return out;
}

Apartament Apartament::operator++() {
	this->pret++;
	return *this;
}

Apartament Apartament::operator++(int) {
	Apartament aux = *this;
	this->pret++;
	return aux;
}

Apartament Apartament::operator+(float x) {
	Apartament aux = *this;
	aux.pret = aux.pret + x;
	return aux;
}

Apartament Apartament::operator-(float x) {
	Apartament aux = *this;
	aux.pret = aux.pret - x;
	return aux;
}

Apartament Apartament::operator+(Apartament a) {
	a.pret = a.pret + this->pret;
	a.nrCamere = a.nrCamere + this->nrCamere;
	a.suprafata = a.suprafata + this->suprafata;
	return a;
}

Apartament operator+(float x, Apartament a) {
	a.pret = a.pret + x;
	return a;
}

Apartament operator-(float x, Apartament a) {
	a.pret = a.pret - x;
	return a;
}

bool Apartament::operator==(const Imobil& a) {
	// nu am nevoie sa folosesc functia, e aici doar ca sa nu primesc o eroare
}

bool Apartament::operator==(const Apartament& a) {
	if (this->strada == a.strada&&
		this->numar == a.numar &&
		this->etaj == a.etaj &&
		this->scara == a.scara &&
		this->nrApartament == nrApartament)
		return true;
	return false;
}

bool Apartament::operator<(const Apartament& a) const {
	if (this->suprafata < a.suprafata)
		return true;
	return false;
}

Apartament::~Apartament() {
	// cout << "Obiect apartament disturs" << endl;
}


class Cladire: public Imobil {
private:
	float pret;
	int nrEtaje;
	int nrApartamente;
	bool areLift;

	map<int, int> apartamenteDisponibile;   // 0 - apartamentul i nu este disponibil
								   			// 1 - apartamentul i este disponibil
	list<Apartament> listaApartamente;
	
	char *strada;
	int numar;

	int anConstructie;

	const int idCladire;
	static int contorIdCladire;

public:
	Cladire();
	Cladire(float pret, int nrEtaje, int nrApartamente, list <Apartament> listaApartamente, bool areLift, map<int, int>apartamenteDisponibile, string strada, int numar, int anConstructie, bool vandut);
	Cladire(const Cladire& cl);
	Cladire& operator= (const Cladire& cl);

	istream& read(istream& in);
	ostream& write(ostream& out) const;

	Cladire operator++();	//incrementeaza pretul cladirii
	Cladire operator++(int);
	Cladire operator+(float x);		//aduna la pretul cladirii
	Cladire operator-(float x);		//scade din pretul cladirii
	Cladire operator+(Cladire cl);
	friend Cladire operator+(float x, Cladire cl);
	friend Cladire operator-(float x, Cladire cl);
	
	bool operator<(const Cladire& cl) const;		//verifica daca prima cladire are mai putine apartamente decat a doua

	friend Cladire operator+(Cladire cl, Apartament& a);	//adauga un apartament la lista de apartamente a cladirii
	friend Cladire operator+(Apartament& a, Cladire cl);
	Apartament operator[](int index);	//face referinta la apartementul din lista de apartamente

	int getNrEtaje();
	int getNrApartamente();
	list <Apartament> getListaApartamente();
	bool getAreLift();
	map<int, int> getApartamenteDisponibile();
	int getAnConstructie();
	int getIdCladire();
	static int getContorIdCladire();
		
	void setNrEtaje(int nrEtaje);
	void setNrApartamente(int nrApartamente);
	void setListaApartamente(list <Apartament> listaApartamente);
	void setAreLift(bool areLift);
	void setApartamenteDisponibile(map<int, int> apartamenteDisponibile);
	void setAnConstructie(int anConstructie);
	
	void afisPretPeMetru2(); // in cazul acetei clase va afisa pret/nrApartmente
	void afisApartamenteDisponibile();   //afiseaza apartamentele disponibile din cladire

	~Cladire();
};

int Cladire::contorIdCladire = 0;

Cladire::Cladire(): Imobil(), idCladire(++contorIdCladire) {
	this->nrEtaje = -1;
	this->nrApartamente = -1;
	this->areLift = false;
	this->apartamenteDisponibile = {};
	this->listaApartamente = {};
	this->anConstructie = -1;
}

Cladire::Cladire(float pret, int nrEtaje, int nrApartamente, list <Apartament> listaApartamente,  bool areLift, map<int, int> apartamenteDisponibile, string strada, int numar, int anConstructie, bool vandut): Imobil(pret, strada, numar, vandut), idCladire(++contorIdCladire) {
	this->nrEtaje = nrEtaje;
	this->nrApartamente = nrApartamente;
	this->listaApartamente = listaApartamente;
	this->areLift = areLift;
	this->apartamenteDisponibile = apartamenteDisponibile;
	this->anConstructie = anConstructie;
}

Cladire::Cladire(const Cladire& cl): Imobil(cl), idCladire(contorIdCladire) {
	this->nrEtaje = cl.nrEtaje;
	this->nrApartamente = cl.nrApartamente;
	this->areLift = cl.areLift;
	this->listaApartamente = cl.listaApartamente;
	this->apartamenteDisponibile = cl.apartamenteDisponibile;
	this->anConstructie = cl.anConstructie;
}

Cladire& Cladire::operator= (const Cladire& cl) {
	if (this != &cl) {
		Imobil::operator=(cl);
		this->nrEtaje = cl.nrEtaje;
		this->nrApartamente = cl.nrApartamente;
		this->areLift = cl.areLift;
		this->listaApartamente = cl.listaApartamente;
		this->apartamenteDisponibile = cl.apartamenteDisponibile;
		this->anConstructie = cl.anConstructie;
	}
	return *this;
}

int Cladire::getNrEtaje() {
	return this->nrEtaje;
}

int Cladire::getNrApartamente() {
	return this->nrApartamente;
}

list<Apartament> Cladire::getListaApartamente() {
	return this->listaApartamente;
}

bool Cladire::getAreLift() {
	return this->areLift;
}

map<int, int> Cladire::getApartamenteDisponibile() {
	return this->apartamenteDisponibile;
}

int Cladire::getAnConstructie() {
	return this->anConstructie;
}

int Cladire::getIdCladire() {
	return this->idCladire;
}

int Cladire::getContorIdCladire() {
	return Cladire::contorIdCladire;
}

void Cladire::setNrEtaje(int nrEtaje) {
	this->nrEtaje = nrEtaje;
}

void Cladire::setNrApartamente(int nrApartamente) {
	this->nrApartamente = nrApartamente;
}

void Cladire::setListaApartamente(list <Apartament> listaApartamente) {
	this->listaApartamente = listaApartamente;
}

void Cladire::setAreLift(bool areLift) {
	this->areLift = areLift;
}

void Cladire::setApartamenteDisponibile(map<int, int> apartamenteDisponibile) {
	this->apartamenteDisponibile = apartamenteDisponibile;
}

void Cladire::setAnConstructie(int anConstructie) {
	this->anConstructie = anConstructie;
}

void Cladire::afisApartamenteDisponibile() {
	bool exista = false;
	for (int i = 1; i <= nrApartamente; i++)
		if (apartamenteDisponibile[i] == 1) {
			cout << i << " ";
			exista = true;
		}
	if (!exista)
		cout << "Nu exista apartamente disponibile.";
	cout << endl;
}

istream& Cladire::read(istream& in) {
	Imobil::read(in);
	while (true) {
		cout << "Scrie numarul de etaje al cladirii: ";
		try {
			in >> this->nrEtaje;
			if (this->nrEtaje < 1) 
				throw numarInvalid;
			break;
		} catch (NumarInvalid n) {
			cout << n.what();
		}
	}
	while (true) {
		cout << "Scrie numarul de apartamente: ";
		try {
			in >> this->nrApartamente;
			if (this->nrApartamente < 1) 
				throw numarInvalid;
			break;
		} catch (NumarInvalid n) {
			cout << n.what();
		}
	}
	
	while (true) {
		cout << "Scrie 1 daca cladirea are lift sau 0 daca nu are: ";
		try {
			int x;
			in >> x;
			if (x != 0 && x != 1)
				throw x;
			this->areLift = x;
			break;
		} catch (int x) {
			cout << "Ati introdus o valoare gresita" << endl;
		} 
	}
	cout << "Pentru fiecare apartament scrie 0 daca este disponibil si 1 daca nu este: " << endl;
	for (int i = 0; i < this->nrApartamente; i++) {
		while (true) {
			cout << "Apartamentul " << i + 1 << ": ";
			try {
				int x;
				in >> x;
				if (x != 0 && x != 1)
					throw x;
				this->apartamenteDisponibile[i] = x;
				break;
			} catch (int x) {
				cout << "Ati introdus o valoare gresita" << endl;
			} 
		}
	}
	while (true) {
		cout << "Scrie anul de constructie: ";
		try {
			in >> this->anConstructie;
			if (this->anConstructie < 1000 || this->anConstructie > 2022)
				throw string("An invalid\n");
			break;
		} catch (string s) {
			cout << s;
		}		
	}
	return in;
}

ostream& Cladire::write(ostream& out) const {
	Imobil::write(out);
	out << "Cladirea are " << this->nrEtaje << " etaje si " << this->nrApartamente << " apartamente" << endl;
	if (this->areLift == 0)
		out << "Cladirea nu are lift" << endl;
	else 
		out << "Cladire are lift" << endl;
	out << "Apartamentele disponibile sunt: ";
	for (auto& ap : apartamenteDisponibile) {
		if (ap.second == 0)
			cout << ap.first + 1 << " ";
	}
	// for (int i = 0; i < this->nrApartamente; i++)
	// 	if (this->apartamenteDisponibile[i] == 0)
	// 		out << i + 1 << " ";
	cout << endl;
	out << "Anul de constructie este: " << this->anConstructie << endl;
	return out;
}

Cladire Cladire::operator++() {
	this->pret++;
	return *this;
}

Cladire Cladire::operator++(int) {
	Cladire aux = *this;
	this->pret++;
	return aux;
}

Cladire Cladire::operator+(float x) {
	Cladire aux = *this;
	aux.pret = aux.pret + x;
	return aux;
}

Cladire Cladire::operator-(float x) {
	Cladire aux = *this;
	aux.pret = aux.pret - x;
	return aux;
}

Cladire Cladire::operator+(Cladire cl) {
	cl.pret = cl.pret + this->pret;
	cl.nrApartamente = cl.nrApartamente + this->nrApartamente;
	return cl;
}

Cladire operator+(float x, Cladire cl) {
	cl.pret = cl.pret + x;
	return cl;
}

Cladire operator-(float x, Cladire cl) {
	cl.pret = cl.pret - x;
	return cl;
}

bool Cladire::operator<(const Cladire& cl) const {
	if (this->nrApartamente < cl.nrApartamente)
		return true;
	return false;
}

Cladire operator+(Cladire cl, Apartament& a) {
	cl.listaApartamente.push_back(a);
	return cl;
}

Cladire operator+(Apartament& a, Cladire cl) {
	cl.listaApartamente.push_back(a);
	return cl;
}

Apartament Cladire::operator[](int index) {
	list<Apartament>::iterator it = this->listaApartamente.begin();
	advance(it, index);
	return *it;
}

void Cladire::afisPretPeMetru2() {     
	cout << "Pretul pe apartament al cladirii este " << this->pret / this->nrApartamente << " euro pe apartament" << endl;
}

Cladire::~Cladire() {
	// cout << "Obiect cladire distrus" << endl;
}


class Teren: public virtual Imobil {
protected:
	int suprafata;

	const int idTeren;
	static int contorIdTeren;

public:
	Teren();
	Teren(float pret, int suprafata, string strada, int numar, bool vandut);
	Teren(const Teren& t);

	Teren& operator= (const Teren& t);

	void citire();
	void afisare();

	istream& read(istream& in);
	ostream& write(ostream& out) const;

	Teren operator++();		//incrementeaza pretul
	Teren operator++(int);
	Teren operator+(float x);	//aduna la pret
	Teren operator-(float x);	//scade din pret
	Teren operator+(Teren t);
	friend Teren operator+(float x, Teren t);
	friend Teren operator-(float x, Teren t);
	
	bool operator<(const Teren& t) const;		//verifica daca primul teren are suprafata mai mica decat al doilea

	int getSuprafata();
	int getIdTeren();
	static int getContorIdTeren();

	void setSuprafata(int suprafata);

	void afisPretPeMetru2(); /// de modificat

	~Teren();
};

int Teren::contorIdTeren = 0;

Teren::Teren(): Imobil(), idTeren(++contorIdTeren) {
	this->suprafata = -1;
}

Teren::Teren(float pret, int suprafata, string strada, int numar, bool vandut): Imobil(pret, strada, numar, vandut), idTeren(++contorIdTeren) {
	this->suprafata = suprafata;
}

Teren::Teren(const Teren& t): Imobil(t), idTeren(contorIdTeren) {
	this->suprafata = t.suprafata;
}

Teren& Teren::operator= (const Teren& t) {
	if (this != &t) {
		Imobil::operator=(t);
		this->suprafata = t.suprafata;
	}
	return *this;
}

int Teren::getSuprafata() {
	return this->suprafata;
}

int Teren::getIdTeren() {
	return this->idTeren;
}

int Teren::getContorIdTeren() {
	return Teren::contorIdTeren;
}

void Teren::setSuprafata(int suprafata) {
	this->suprafata = suprafata;
}

void Teren::afisPretPeMetru2() {     
	cout << "Pretul pe metru patrat al terenului este " << this->pret / this->suprafata << " euro pe metru patrat" << endl;
}

istream& Teren::read(istream& in) {
	if (typeid(*this) == typeid(Teren)) 
		Imobil::read(in);
		
	while (true) {
		cout << "Scrie suprafata: ";
		try {
			in >> this->suprafata;
			if (this->suprafata < 1) 
				throw numarInvalid;
			break;
		} catch (NumarInvalid n) {
			cout << n.what();
		}
	}
	return in;
}

ostream& Teren::write(ostream& out) const {
	if (typeid(*this) == typeid(Teren))
		Imobil::write(out);
	out << "Suprafata terenului este de " << this->suprafata << "mp2" << endl;
	return out;
}

Teren Teren::operator++() {
	this->pret++;
	return *this;
}

Teren Teren::operator++(int) {
	Teren aux = *this;
	this->pret++;
	return aux;
}

Teren Teren::operator+(float x) {
	Teren aux = *this;
	aux.pret = aux.pret + x;
	return aux;
}

Teren Teren::operator-(float x) {
	Teren aux = *this;
	aux.pret = aux.pret - x;
	return aux;
}

Teren Teren::operator+(Teren t) {
	t.pret = t.pret + this->pret;
	t.suprafata = t.suprafata + this->suprafata;
	return t;
}

Teren operator+(float x, Teren t) {
	t.pret = t.pret + x;
	return t;
}

Teren operator-(float x, Teren t) {
	t.pret = t.pret - x;
	return t;
}

bool Teren::operator<(const Teren& t) const {
	if (this->suprafata < t.suprafata)
		return true;
	return false;
}

Teren::~Teren() {
	// cout << "Obiect teren distrus" << endl;
}


class CasaCuGradina: public virtual Casa,
					 public virtual Teren {
private: 
	bool areGaraj;
	bool arePiscina;

	const int idCasaCuGradina;
	static int contorIdCasaCuGradina;
public:
	CasaCuGradina();
	CasaCuGradina(double pret, string strada, int numar, int suprafataCasa, int nrCamere, int anConstructie, int suprafataGradina, bool vandut, bool areGaraj, bool arePiscina);
	CasaCuGradina(const CasaCuGradina& cg);
	CasaCuGradina& operator=(const CasaCuGradina& cg);

	istream& read(istream& in);
	ostream& write(ostream& out) const;

	CasaCuGradina operator++();  //incrementeaza pretul
	CasaCuGradina operator++(int);
	CasaCuGradina operator+(double x);    //aduna la pret
	CasaCuGradina operator-(double x);    //scade din pret
	bool operator<(const CasaCuGradina& cg) const;	  //verifica daca prima prima casa cu gradina are suprafata casei mai mica decat a doua

	bool getAreGaraj();
	bool getArePiscina();
	int getIdCasaCuGradina();
	static int getContorIdCasaCuGradina();

	void setAreGaraj(bool areGaraj);
	void setArePiscina(bool arePiscina);

	void afisPretPeMetru2();

	~CasaCuGradina();
};

int CasaCuGradina::contorIdCasaCuGradina = 0;

CasaCuGradina::CasaCuGradina(): Imobil(), Casa(), Teren(), idCasaCuGradina(++contorIdCasaCuGradina) {
	this->areGaraj =  false;
	this->arePiscina = false;
}

CasaCuGradina::CasaCuGradina(double pret, string strada, int numar, int suprafataCasa, int nrCamere, int anConstructie, int suprafataGradina, bool vandut, bool areGaraj, bool arePiscina): 
										Imobil(pret, strada, numar, vandut), 
										Casa(pret, strada, numar, vandut, nrCamere, suprafataCasa, anConstructie),
										Teren(pret, suprafataGradina, strada, numar, vandut),
										idCasaCuGradina(++contorIdCasaCuGradina) {
	this->areGaraj = areGaraj;
	this->arePiscina = arePiscina; 
}

CasaCuGradina::CasaCuGradina(const CasaCuGradina& cg): Imobil(cg), Casa(cg), Teren(cg), idCasaCuGradina(contorIdCasaCuGradina) {
	this->areGaraj = cg.areGaraj;
	this->arePiscina = cg.arePiscina;
}

CasaCuGradina& CasaCuGradina::operator=(const CasaCuGradina& cg) {
	if (this != &cg) {
		Casa::operator=(cg);
		Teren::operator=(cg);
		this->areGaraj = cg.areGaraj;
		this->arePiscina = cg.arePiscina;
	}
	return *this;
}

istream& CasaCuGradina::read(istream& in) {
	cout << "Casa: " << endl;
	Casa::read(in);
	cout << "Gradina: " << endl;
	Teren::read(in);

	while (true) {
		cout << "Scrie 1 daca are garaj sau 0 daca nu are: ";
		try {
			int x;
			in >> x;
			if (x != 0 && x != 1)
				throw x;
			this->areGaraj = x;
			break;
		} catch (int x) {
			cout << "Ati introdus o valoare gresita" << endl;
		} 
	}

	while (true) {
		cout << "Scrie 1 daca are piscina sau 0 daca nu are: ";
		try {
			int x;
			in >> x;
			if (x != 0 && x != 1)
				throw x;
			this->arePiscina = x;
			break;
		} catch (int x) {
			cout << "Ati introdus o valoare gresita" << endl;
		} 
	}

	return in;
}

ostream& CasaCuGradina::write(ostream& out) const {
	Casa::write(out);
	Teren::write(out);
	if (this->areGaraj)
		out << "Imobilul are garaj" << endl;
	else 
		out << "Imobilul nu are garaj" << endl;
	if (this->arePiscina)
		out << "Imobilul are piscina" << endl;
	else 
		out << "Imobilul nu are piscina" << endl;
	return out;
}	

CasaCuGradina CasaCuGradina::operator++() {
	this->pret++;
	return *this;
}

CasaCuGradina CasaCuGradina::operator++(int) {
	CasaCuGradina aux = *this;
	this->pret++;
	return aux;
}

CasaCuGradina CasaCuGradina::operator+(double x) {
	CasaCuGradina aux = *this;
	aux.pret = aux.pret + x;
	return aux;
}

CasaCuGradina CasaCuGradina::operator-(double x) {
	CasaCuGradina aux = *this;
	aux.pret = aux.pret - x;
	return aux;
}

bool CasaCuGradina::operator<(const CasaCuGradina& cg) const {
	if (this->Casa::suprafata < cg.Casa::suprafata) 
		return true;
	return false;
}

bool CasaCuGradina::getAreGaraj() {
	return this->areGaraj;
}

bool CasaCuGradina::getArePiscina() {
	return this->arePiscina;
}

int CasaCuGradina::getIdCasaCuGradina() {
	return this->idCasaCuGradina;
}

int CasaCuGradina::getContorIdCasaCuGradina() {
	return CasaCuGradina::contorIdCasaCuGradina;
}

void CasaCuGradina::setAreGaraj(bool areGaraj) {
	this->areGaraj = areGaraj;
}

void CasaCuGradina::setArePiscina(bool arePiscina) {
	this->arePiscina = arePiscina;
}

void CasaCuGradina::afisPretPeMetru2() {     
	cout << "Pretul pe metru patrat al casei cu gradina este " << this->pret / (Teren::suprafata + Casa::suprafata) << " euro pe metru patrat" << endl;
}

CasaCuGradina::~CasaCuGradina() {
	//cout << "Obiect casa cu gradina disturs" << endl;
}

class MeniuInteractiv {
private:
	static MeniuInteractiv *obiect;

	MeniuInteractiv() {}
	MeniuInteractiv(const MeniuInteractiv& m) {}
	MeniuInteractiv& operator=(const MeniuInteractiv& m) {}
public:
	static MeniuInteractiv* getInstance();
	void afiseazaMeniu();
};

MeniuInteractiv* MeniuInteractiv::getInstance() {
	if (!obiect) 
		obiect = new MeniuInteractiv();
	return obiect;
}

void MeniuInteractiv::afiseazaMeniu() {
	vector<Imobil*> listaImobile;

	int k = 1, comanda;
	while (k) {
		system("CLS");
		cout << "\n1 - Adauga imobil" << endl;
		cout << "2 - Vezi imbobil" << endl;
		cout << "3 - Stop\n" << endl;
		cin >> comanda;
		switch(comanda) {
			case 1: {
				system("CLS");
				cout << "\n1 - Adauga o casa" << endl;
				cout << "2 - Adauga un apartament" << endl;
				cout << "3 - Adauga o cladire" << endl;
				cout << "4 - Adauga un teren" << endl;
				cout << "5 - Adauga o casa cu gradina\n" << endl;
				
				int x;
				cin >> x;
				system("CLS");
				switch (x) {
					case 1: {
						Casa c;
						cin >> c;
						bool ok = true;
						for (int i = 0; i < listaImobile.size(); i++)
							if (typeid(*listaImobile[i]) == typeid(Casa) && 
								c == *listaImobile[i]) {
									system("CLS");
									cout << "Exista deja o casa la adresa specificata" << endl;
									ok = false;
									cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
									cin >> x;
								}
						if (ok) {
							listaImobile.push_back(new Casa(c));
							system("CLS");
							cout << "Casa adaugata!" << endl;
							cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
							cin >> x;
						}
						break;
					}
					case 2: {
						Apartament a;
						cin >> a;
						bool ok = true;
						for (int i = 0; i < listaImobile.size(); i++)
							if (typeid(*listaImobile[i]) == typeid(Apartament) && 
								a == *listaImobile[i]) {
									system("CLS");
									cout << "Exista deja un apartament la adresa specificata" << endl;
									ok = false;
									cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
									cin >> x;
								}
						if (ok) {
							listaImobile.push_back(new Apartament(a));
							system("CLS");
							cout << "Apartament adaugat!" << endl;
							cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
							cin >> x;
						}
						break;
					}
					case 3: {
						Cladire cl;
						cin >> cl;
						bool ok = true;
						for (int i = 0; i < listaImobile.size(); i++)
							if (typeid(*listaImobile[i]) == typeid(Cladire) && 
								cl == *listaImobile[i]) {
									system("CLS");
									cout << "Exista deja o cladire la adresa specificata" << endl;
									ok = false;
									cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
									cin >> x;
								}
						if (ok) {
							listaImobile.push_back(new Cladire(cl));
							system("CLS");
							cout << "Cladire adaugata!" << endl;
							cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
							cin >> x;
						}
						break;
					}
					case 4: {
						Teren t;
						cin >> t;
						bool ok = true;
						for (int i = 0; i < listaImobile.size(); i++)
							if (typeid(*listaImobile[i]) == typeid(Teren) && 
								t == *listaImobile[i]) {
									system("CLS");
									cout << "Exista deja un apartament la adresa specificata" << endl;
									ok = false;
									cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
									cin >> x;
								}
						if (ok) {
							listaImobile.push_back(new Teren(t));
							system("CLS");
							cout << "Teren adaugat!" << endl;
							cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
							cin >> x;
						}
						break;
					}
					case 5: {
						CasaCuGradina cg;
						cin >> cg;
						bool ok = true;
						for (int i = 0; i < listaImobile.size(); i++)
							if (typeid(*listaImobile[i]) == typeid(Apartament) && 
								cg == *listaImobile[i]) {
									system("CLS");
									cout << "Exista deja o casa cu gradina la adresa specificata" << endl;
									ok = false;
									cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
									cin >> x;
								}
						if (ok) {
							listaImobile.push_back(new CasaCuGradina(cg));
							system("CLS");
							cout << "Casa cu gradina adaugata!" << endl;
							cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
							cin >> x;
						}
						break;
					}
					default: {
						cout << "Ati introdus o valoare gresita" << endl;
						cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
						cin >> x;
						break;
					}
				}
				break;
			}
			case 2: {
				system("CLS");
				if (listaImobile.size() > 0) {		//daca exista imobile in lista le afisam
					for (int i = 0; i < listaImobile.size(); i++) {
						cout << "Imobilul numarul " << i + 1 << ": " << endl;	
						if (typeid(*listaImobile[i]) == typeid(Casa))		// verificam ce tip de obiect avem si specificam acest lucru la afisare
							cout << "Casa: " << endl;
						else if (typeid(*listaImobile[i]) == typeid(Apartament))
							cout << "Apartament: " << endl;
						else if (typeid(*listaImobile[i]) == typeid(Cladire))
							cout << "Cladire: " << endl;
						else if (typeid(*listaImobile[i]) == typeid(Teren))
							cout << "Teren: " << endl;
						else if (typeid(*listaImobile[i]) == typeid(CasaCuGradina))
							cout << "Casa cu gradina: " << endl;
						cout << *listaImobile[i] << endl;
					}		
					
					cout << "1 - Cumpara un imobil" << endl;
					cout << "2 - Modifica pretul unui imobil" << endl;
					cout << "3 - Vezi pretul pe metru patrat al unui imobil" << endl;
					cout << "4 - Compara doua imobile de acelasi tip" << endl;
					cout << "5 - Vezi suprafata gradinii unei case" << endl;
					cout << "6 - Creeaza un cartier" << endl;
					cout << "7 - Intoarce-te la meniul principal" << endl;
					
					int x;
					cin >> x;

					switch (x) {
						case 1: {
							cout << "Scrieti numarul imobilului pe care doriti sa il cumparati: ";
							int nr;
							try {
								cin >> nr;
								system("CLS");
								if (nr > listaImobile.size())
									throw string("Ati introdus o valoare gresita");

								if (listaImobile[nr - 1]->getVandut() == false) {
									cout << "Pretul imobiluli este " << listaImobile[nr - 1]->getPret() << endl;
									cout << "1 - Cumpara" << endl;
									cout << "2 - Anuleaza" << endl;
									int z;
									cin >> z;
									if (z == 1) {
										
										listaImobile.erase(listaImobile.begin() + nr - 1);
										cout << "Imobil cumparat!" << endl;
										cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
										cin >> nr;
									}
								}
								else {
									cout << "Nu poti cumpara aceast imobil" << endl;
									cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
									cin >> nr;
								}
								
							} catch (string s) {
								cout << s << endl;
								cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
								cin >> nr;
							}
	
							break;
						}
						case 2: {
							cout << "Scrieti numarul imobiluli caruia doriti sa ii modificati pretul: ";
							int nr;

							cin >> nr;
							cout << "1 - Mareste pretul" << endl;
							cout << "2 - Micsoreaza pretul" << endl;
							int var;
							cin >> var;
							switch (var) {
								case 1: {
									cout << "Cu ce suma vreti sa mariti pretul?" << endl;
									double suma;
									cin >> suma;
									listaImobile[nr - 1] = modificaPret(listaImobile[nr - 1], suma);
									system("CLS");											
									cout << "Pret modificat!" << endl;
									cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
									cin >> var;
									break;
								}
								case 2: {
									cout << "Cu ce suma vreti sa micsorati pretul?" << endl;
									double suma;
									cin >> suma;
									listaImobile[nr - 1] = modificaPret(listaImobile[nr - 1], -suma);
									system("CLS");											
									cout << "Pret modificat!" << endl;
									cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
									cin >> var;
									break;
								}
								default: {
									system("CLS");
									cout << "Ati introdus o valoare gresita" << endl;
									cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
									cin >> var;
									break;
								}
							}
							break;
						}
						case 3: {
							cout << "Scrieti numarul imobilului caruia vreti sa ii vedeti pretul pe metru patrat: ";
							int nr;
							cin >> nr;
							listaImobile[nr - 1]->afisPretPeMetru2();
							cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
							cin >> nr;
							break;
						}
						case 4: {
							cout << "Scrieti numerele imobilelor pe care vreti sa le cumparati: ";
							int im1, im2;
							try {
								cin >> im1 >> im2;
								if (im1 - 1 >= listaImobile.size() || im2 - 1  >= listaImobile.size())
									throw string("Imobilele specificate nu exista\n");
								if (typeid(*listaImobile[im1 - 1]) != typeid(*listaImobile[im2 - 1]))
									cout << "Cele doua imobile nu pot fi comparate" << endl;
								else {
									comparaImobile(listaImobile[im1 - 1], listaImobile[im2 - 1]);
									cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
									int z;
									cin >> z;
								}
							} catch (string s) {
								cout << s;
								cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
								int z;
								cin >> z;
							}
			
							break;
						}
						case 5: {
							cout << "Scrie numarul casei: ";
							int c;
							try {
								cin >> c;
								if (c - 1 > listaImobile.size())
									throw string("Casa specificata nu exista\n");
								
								Teren *t = dynamic_cast<Teren*>(listaImobile[c - 1]);
								if (t) {
									cout << "Suprafata gradinii este " << t->getSuprafata() << endl;
									cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
									int z;
									cin >> z;
								}
								else {
									cout << "Casa specifiacata nu are gradina" << endl;
									cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
									int z;
									cin >> z;
								}

							} catch (string s) {
								cout << s;
							}

							break;
						}
						case 6: {
							cout << "Ce tip de imobile sunt in cartier?" << endl;
							cout << "1 - Case" << endl;
							cout << "2 - Cladiri" << endl;
							int t;
							cin >> t;
							if (t == 1) {
								Cartier<Casa> crt;
								cout << "Cate case doriti sa introduceti?" <<endl;
								int n;
								cin >> n;
								for (int i = 0; i < n; i++) {
									cout << "Scrieti numarul casei: ";
									int j;
									cin >> j;
									Casa *c = dynamic_cast<Casa*>(listaImobile[j - 1]);	
									if (c)								
										crt.adaugaImobil(*c);
									else 
										cout << "Imobilul nu poate fi adaugat" << endl;
								}

								system("CLS");
								cout << "Cartier creat: " << endl;
								crt.afiseazaImobilele();

								cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
								int z;
								cin >> z;

							}
							else if (t == 2) {
								Cartier<Cladire> crt;
								cout << "Cate cladiri doriti sa introduceti?" <<endl;
								int n;
								cin >> n;
								for (int i = 0; i < n; i++) {
									cout << "Scrieti numarul cladirii: ";
									int j;
									cin >> j;
									Cladire *cl = dynamic_cast<Cladire*>(listaImobile[j - 1]);									
									if (cl)
										crt.adaugaImobil(*cl);
									else 
										cout << "Imobilul nu poate fi adaugat" << endl;
								}

								system("CLS");
								cout << "Cartier creat: " << endl;
								crt.afiseazaImobilele();

								cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
								int z;
								cin >> z;
							}
							else {
								cout << "Ati introdus o valoare gresita" << endl;
								cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
								int z;
								cin >> z;
							}
							break;
						}
						case 7: {
							// nu facem nimic, iesim din switch
							break;
						}
						default: {
							system("CLS");
							cout << "Ati introdus o valoare gresita" << endl;
							cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
							cin >> x;
							break;
						}
					}
				}
				else {
					cout << "Nu exista imobile in lista" << endl;
					cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
					int x;
					cin >> x;
				}
				break;
			}
			case 3: {
				k = 0;	//oprim programul
				break;
			}
			default: {
				system("CLS");
				cout << "Ati introdus o valoare gresita" << endl;
				cout << "Apasa 1 pentru a te intoarce la meniul principal" << endl;
				int y;
				cin >> y;
				break;
			}
		}
	}
}

MeniuInteractiv* MeniuInteractiv::obiect = 0;

int main() {
	MeniuInteractiv *meniulMeu;
	meniulMeu->getInstance();
	meniulMeu->afiseazaMeniu();

	return 0;
}