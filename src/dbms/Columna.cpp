#include "stdafx.h"
#include "Columna.h"
#include <fstream>
#include <algorithm>
namespace dbms {

	using namespace std;

	// Copy constructor
	Columna::Columna(const Columna & columna)
	{
		id_ = columna.id_;
		entidadId_ = columna.entidadId_;
		nombre_ = columna.nombre_;
		tipoDato_ = columna.tipoDato_;
	}

	Columna::Columna(const int entidadId, const int id, const std::string & nombre, const Datatype & tipoDato)
	{
		id_ = id;
		entidadId_ = entidadId;
		nombre_ = nombre;
		tipoDato_ = tipoDato;
	}

	Columna::Columna(const std::string& entidadNombre, const int id, const std::string& nombre, const Datatype& tipoDato)
		: IOInterface(entidadNombre + "/Columna.txt")
	{
		id_ = id;
		nombre_ = nombre;
		tipoDato_ = tipoDato;
		entidadId_ = 0;
	}


	Columna::Columna(const std::string& entidadNombre, const int entidadId, const int id, 
		const std::string& nombre, const Datatype& tipoDato) :  IOInterface(entidadNombre + "/Columna.txt")
	{
		id_ = id;
		entidadId_ = entidadId;
		nombre_ = nombre;
		tipoDato_ = tipoDato;
	}


	Columna::~Columna()
	{
	}

	int Columna::getId()
	{
		return id_;
	}

	int Columna::getEntidadId()
	{
		return entidadId_;
	}

	std::string Columna::getNombre()
	{
		return nombre_;
	}

	Datatype Columna::getTipoDato()
	{
		return tipoDato_;
	}

	std::string Columna::toString()
	{
		std::string tipoDato = tipoDato_.toString();

		// IF ES NUMERIC O CHAR
		switch (tipoDato_.getType()) {
		case Type::CHAR:
		case Type::VARCHAR:
		case Type::NUMERIC:
			tipoDato.append("(" + std::to_string(tipoDato_.getLength()) );

			// Si es NUMERIC ponle precision.
			tipoDato.append( (tipoDato_.getType() == Type::NUMERIC)? ", "
				+ std::to_string(tipoDato_.getPrecision()) : "");

			tipoDato.append(")");
			break;
		}

		std::string registro = std::to_string(entidadId_) + "\t|\t"
			+ std::to_string(id_) + "\t|\t"
			+ nombre_ + "\t|\t"
			+ tipoDato + '\n';

		return registro;
	}

	void Columna::read()
	{
		// En proceso
	}

	void Columna::write()
	{
		std::ofstream archivo;
		archivo.open(getFilename(), std::ios::out | std::ios::app);

		if (!archivo.fail()) {
			archivo << toString();
		}
		else {
			throw std::ios_base::failure("El archivo " + getFilename() + " no pudo ser escrito correctamente.\n");
		}

		archivo.close();
	}

	std::list<Columna> Columna::readAll()
	{
		std::ifstream archivo;
		archivo.open(getFilename());
		list<Columna> columnas;

		// Debo ignorar los campos;
		if (!archivo.fail()) {
			char pipe;
			bool sonCampos = true;

			// Columna Metadata;
			int entidadId;
			int id;
			std::string nombre;
			std::string tipoDato;
			Datatype datatype;

			while (!archivo.eof()) {

				if (sonCampos) {
					for (int i = 0; i < 3; ++i) 
					{
						archivo >> tipoDato;
						archivo >> pipe;
					}
					archivo >> tipoDato;
					sonCampos = false;
					continue;
				}
				archivo >> entidadId;
				archivo >> pipe;
				archivo >> id;
				archivo >> pipe;
				archivo >> nombre;
				archivo >> pipe;

				archivo >> tipoDato;


				std::transform(tipoDato.begin(), tipoDato.end(), tipoDato.begin(), ::toupper);

				// INTENTAR AVERIGUAR SI TIENE PARENTESIS;
				size_t open = tipoDato.find_first_of('(');
				bool isFound = open >= 0;
				if (!isFound)
				{
					datatype.nombre_ = tipoDato;
				}
				else
				{
					datatype.nombre_ = tipoDato.substr(0, open - 1);

					bool esNumeric = (datatype.toString() == Datatype::NUMERIC.toString());

					if (esNumeric)
					{
						// Busca longitud del NUMERIC.
						datatype.type_ = Type::NUMERIC;
						size_t coma = datatype.nombre_.find_first_of(',', open);
						datatype.length_ = stoi(datatype.nombre_.substr(open + 1, (coma - open) - 1));

						// Busca precision del NUMERIC.
						size_t close = datatype.toString().find_first_of(')', coma);
						datatype.precision_ = stoi(datatype.nombre_.substr(coma + 1, (close - coma) - 1));
					}

					else {
						bool esVarchar = datatype.toString() == Datatype::VARCHAR.toString();

						datatype.type_ = (esVarchar) ? Type::VARCHAR : Type::CHAR;
						size_t close = datatype.toString().find_first_of(')', open);
						datatype.length_ = stoi(datatype.nombre_.substr(open + 1, (close - open) - 1));
					}

				}
				Columna columna = Columna(id, entidadId, nombre, datatype);
				columnas.push_back(columna);
			}
		}
		else {
			string mensaje = "El archivo " + getFilename() + "no pudo ser leido correctamente.\n";
			throw std::ios_base::failure(mensaje);
		}

		return columnas;
	}

	std::string Columna::mostrarCampos()
	{
		std::string mensaje = "entidad_id \t|\t colId \t|\t colNombre \t|\t colTipo\r\n";
		return mensaje;
	}

}