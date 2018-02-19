#pragma once
#include "IOInterface.h"
#include "Columna.h"
#include "PrimaryKey.h"
#include "ForeignKey.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
namespace dbms {
class Entidad : IOInterface
{
private:
	int contadorColumna_;
	int id_;
	int contadorRegistro_;
	std::string nombre_;
	std::string fecha_;
	PrimaryKey primaryKey_;
	std::vector<Columna> columnas_;
	std::vector<ForeignKey> foreignKeys_;
	std::map<int, std::vector<std::string>> registros_; // Registros
	std::string mensaje_;
	bool esPrimeraColumna = true;

	// Persistencia automatizada.
	virtual void read() override;

	bool isDataValid(std::vector<std::string> data);

	virtual void write() override; // Agregar entidades

	void writeColumnsFields(Columna& columna);

public:
	Entidad(const Entidad& obj);
	Entidad(const int id, const std::string& nombre);
	Entidad& operator=(const Entidad& obj);
	virtual ~Entidad();

	void agregarColumna(std::string nombre, Datatype tipo);
	std::vector<Columna> getColumnas();
	bool buscar(int pk);
	bool buscar(std::string texto);
	void alta(std::vector<std::string> data); // Enviar a Tabla.txt
	void baja(int id);
	void sort(std::vector<std::string> data);
	virtual std::vector<Entidad> readAll();
	virtual std::string toString() override;

	int getId();
	std::string getNombre();
	std::string getFecha();
	std::map<int, std::vector<std::string>> getData();


};

}