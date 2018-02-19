#pragma once
#include "IOInterface.h"
#include "Datatype.h"
#include <string>
#include <map>
#include <memory>
#include <list>
namespace dbms {

	class Columna : IOInterface
	{
	private:
		int id_;
		int entidadId_; // FK
		std::string nombre_;
		Datatype tipoDato_;

		Columna(const int entidadId, const int id, const std::string& nombre, const Datatype& tipoDato);

	public:
		Columna(){}
		Columna(const Columna& columna);
		Columna(const std::string& entidadNombre, const int id, const std::string& nombre, const Datatype& tipoDato);
		Columna(const std::string& entidadNombre, const int entidadId, const int id, 
			const std::string& nombre, const Datatype& tipoDato);
		virtual ~Columna();
		int getId();
		int getEntidadId(); // FK
		std::string getNombre();
		Datatype getTipoDato();
		virtual void read() override;
		virtual void write() override;
		std::list<Columna> readAll();
		std::string toString() override;
		std::string mostrarCampos();
	};

}