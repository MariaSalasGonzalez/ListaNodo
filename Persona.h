#pragma once
#include<iostream>
#include<sstream>
#include<string>
using namespace std;

class Persona {
private:
	string cedula;
	string nombre;
	int edad;
public:
	Persona(string = "", string = "", int = 0);
	virtual ~Persona();
	string getCedula();
	string getNombre();
	int getEdad();
	void setCedula(string);
	void setNombre(string);
	void setEdad(int);
	friend ostream& operator <<(ostream&, const Persona&);
	Persona& operator = (const Persona&);
	bool operator == (const Persona&);
	bool operator < (const Persona&);
};
