#include"Persona.h"

Persona::Persona(string ced, string nom, int ed)
	: cedula(ced), nombre(nom), edad(ed) {
}
Persona::~Persona() {
}

string Persona::getCedula() { return cedula; }
string Persona::getNombre() { return nombre; }
int Persona::getEdad() { return edad; }
void Persona::setCedula(string ced) { cedula = ced; }
void Persona::setNombre(string nom) { nombre = nom; }
void Persona::setEdad(int ed) { edad = ed; }

ostream& operator <<(ostream& out, const Persona& p) {
	return out << "Cedula..." << p.cedula << endl
		<< "Nombre..." << p.nombre << endl
		<< "Edad....." << p.edad << endl << endl;
}
Persona& Persona::operator = (const Persona& p) {
	this->cedula = p.cedula;     // a = b = c;
	this->nombre = p.nombre;
	this->edad = p.edad;
	return *this;
}

bool Persona::operator == (const Persona&) {
	// Trabajo en Casa
	return true;
}
bool Persona::operator < (const Persona&) {
	// trabajo en Casa..
	return true;
}