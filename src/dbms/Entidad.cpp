#include "stdafx.h"
#include "Entidad.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <filesystem> // C++ 17+
namespace dbms {

	using std::string;
	using std::vector;
	using std::chrono::system_clock;

	// Copy constructor
	Entidad::Entidad(const Entidad & obj) : IOInterface("Systable.txt")
	{
		contadorColumna_ = obj.contadorColumna_;
		id_ = obj.id_;
		contadorRegistro_ = obj.contadorRegistro_;
		nombre_ = obj.nombre_;
		fecha_ = obj.fecha_;
		primaryKey_ = obj.primaryKey_;
		columnas_ = obj.columnas_;
		foreignKeys_ = obj.foreignKeys_;
		registros_ = obj.registros_; // Registros
		mensaje_ = obj.mensaje_;
		esPrimeraColumna = obj.esPrimeraColumna;

	}

	Entidad::Entidad(const int id, const std::string& nombre) : IOInterface("Systable.txt")
	{
		contadorRegistro_ = 0;
		contadorColumna_ = 0;
		id_ = id;
		primaryKey_ = PrimaryKey(id);
		nombre_ = nombre;
		esPrimeraColumna = true;
		columnas_ = vector<Columna>();
		foreignKeys_ = vector<ForeignKey>();
		registros_ = std::map<int, std::vector<std::string>>();
		mensaje_ = "";
		//--------------------------------------------------
		time_t fechaActual = system_clock::to_time_t(system_clock::now());
		char temp[27];
		ctime_s(temp, sizeof(temp), &fechaActual);
		fecha_ = temp;
		//------------------------------------------------------
	}

	// Copy operator.
	Entidad & Entidad::operator=(const Entidad & obj)
	{
		contadorColumna_ = obj.contadorColumna_;
		id_ = obj.id_;
		contadorRegistro_ = obj.contadorRegistro_;
		nombre_ = obj.nombre_;
		fecha_ = obj.fecha_;
		primaryKey_ = obj.primaryKey_;
		columnas_ = obj.columnas_;
		foreignKeys_ = obj.foreignKeys_;
		registros_ = obj.registros_; // Registros
		mensaje_ = obj.mensaje_;
		esPrimeraColumna = obj.esPrimeraColumna;

		return *this;
	}

	Entidad::~Entidad()
	{
	}

	void Entidad::agregarColumna(std::string nombre, Datatype tipo)
	{
		Columna columna = Columna(nombre_, (contadorColumna_ + 1), nombre, tipo);
		if (esPrimeraColumna)
		{
			// Write metadata a systable.txt write();
			write(); // Registra la entidad en el catalogo del sistema.
			writeColumnsFields(columna);
			esPrimeraColumna = false;
		}
		columna.write();
		columnas_.push_back(columna);
		++contadorColumna_;
	}

	std::vector<Columna> Entidad::getColumnas()
	{
		Columna col = Columna(nombre_, 0, nombre_, Datatype::CHAR);

		auto columnasEncontradas = col.readAll();
		std::vector<Columna> columnas{ std::make_move_iterator(std::begin(columnasEncontradas)),
			std::make_move_iterator(std::end(columnasEncontradas)) };
		columnas_ = columnas;
		return columnas_;
	}

	bool Entidad::buscar(int pk)
	{
		return false;
	}

	bool Entidad::buscar(std::string texto)
	{
		return false;
	}

	bool Entidad::isDataValid(std::vector<std::string> data)
	{
		bool isValid = columnas_.size() == data.size();
		//		isValid &= !buscar(data[primaryKey_.getId()]); // En proceso
		for (auto columna : columnas_)
		{
			string valor = data[columna.getId() - 1];
			switch (columna.getTipoDato().getType()) {
			case Type::SMALLINT:
			{
				short entero = std::stoi(valor);
			}
			break;
			case Type::INT:
			{
				int entero = std::stoi(valor);
			}
			break;
			case Type::BIGINT:
			{
				long entero = std::stol(valor);
			}
			break;
			case Type::NUMERIC:
			{
				double numeric = std::stod(valor);
				break;
			}
			}

		}

		return isValid;
	}

	// Beta.
	void Entidad::writeColumnsFields(Columna& columna)
	{
		std::ofstream archivo;
		archivo.open(nombre_ + "/Columna.txt", std::ios::out);

		if (!archivo.fail()) {
			archivo << columna.mostrarCampos();
		}
		else {
			throw std::ios_base::failure("Los campos no pudieron ser escritas correctamente.\n");
		}

		archivo.close();
	}

	void Entidad::alta(std::vector<std::string> data)
	{
		if (isDataValid(data)) {
			registros_[++contadorRegistro_] = data; // Guarda en el map
			std::ofstream archivo;
			archivo.open(nombre_ + "/Data.txt", std::ios::out | std::ios::app);

			if (!archivo.fail()) {
				for (int i = 0; i < data.size() - 1; ++i) {
					archivo << data[i] << "\t|\t";
				}
				archivo << data[data.size() - 1] << "\n";
			}
			archivo.close();
		}

	}

	void Entidad::baja(int id)
	{
		//registros_.erase(registros_.begin() + id);
		--contadorRegistro_;
	}

	void Entidad::sort(std::vector<std::string> data)
	{

	}

	std::string Entidad::toString()
	{
		return "En proceso";
	}

	void Entidad::read()
	{
	}

	// Cada vez  que agregue una entidad, crear carpeta
	void Entidad::write()
	{
		std::ofstream archivo;
		archivo.open(getFilename(), std::ios::out | std::ios::app);

		if (!std::experimental::filesystem::exists(nombre_)) {
			std::experimental::filesystem::create_directory(nombre_); // Crea una carpeta con el nombre de la entidad
		}
		if (!archivo.fail()) {
			archivo << id_ << "\t|\t" << nombre_ << "\t|\t" << fecha_;
		}
		else {
			throw std::ios_base::failure("El archivo " + getFilename() + " no pudo ser escrito correctamente.\n");
		}

		archivo.close();
	}

	// Dame todas las tablas disponibles
	std::vector<Entidad> Entidad::readAll()
	{
		std::ifstream archivo;
		archivo.open(getFilename());

		// Debo ignorar los campos;
		std::vector<Entidad> vectorEntidades;// = std::vector<Entidad>();
		if (!archivo.fail()) {

			std::list<Entidad> entidades;

			bool sonCampos = true;
			while (!archivo.eof()) {
				char pipe;
				if (sonCampos) {
					std::string campos = "";
					std::getline(archivo, campos, '\n');
					sonCampos = false;
				}
				else {
					// Entidad Metadata;
					int id = 0;
					std::string nombre = "";
					std::string fecha = "";

					if (archivo >> id) {
						archivo >> pipe;
						archivo >> nombre;
						archivo >> pipe;
						archivo.ignore();
						std::getline(archivo, fecha);

						Entidad entidad = Entidad(id, nombre);
						entidad.fecha_ = fecha;
						entidades.push_back(entidad);
					}
				}

			}

			std::vector<Entidad> tempVectorEntidades{
				std::make_move_iterator(std::begin(entidades)),
				std::make_move_iterator(std::end(entidades))
			};

			tempVectorEntidades.shrink_to_fit();
			vectorEntidades = tempVectorEntidades;

		}
		else {
			string mensaje = "El archivo " + getFilename() + "no pudo ser leido correctamente.\n";
			throw std::ios_base::failure(mensaje);
		}

		archivo.close();

		return vectorEntidades;
	}

	int Entidad::getId()
	{
		return id_;
	}

	std::string Entidad::getNombre()
	{
		return nombre_;
	}

	std::string Entidad::getFecha()
	{
		return fecha_;
	}

	// En proceso.
	std::map<int, std::vector<string> > Entidad::getData()
	{
		std::ifstream archivo;
		archivo.open(nombre_ + "/Data.txt");
		if (!archivo.fail()) {

		}
		return registros_;
	}

}