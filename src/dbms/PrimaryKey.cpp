#include "stdafx.h"
#include "PrimaryKey.h"
#include <chrono>
#include <ctime>
namespace dbms {
	using std::chrono::system_clock;

	int PrimaryKey::contador_ = 0;

	PrimaryKey::PrimaryKey(int entidadId) : IOInterface("PrimaryKey.txt")
	{
		id_ = ++contador_;
		entidadId_ = entidadId;
		//--------------------------------------------------
		time_t fechaActual = system_clock::to_time_t(system_clock::now());
		char temp[28];
		ctime_s(temp, 28, &fechaActual);
		fecha_ = temp;
		//------------------------------------------------------

	}

	PrimaryKey::~PrimaryKey()
	{
	}

	int PrimaryKey::getId()
	{
		return id_;
	}

	int PrimaryKey::getEntidadId()
	{
		return entidadId_;
	}

	void PrimaryKey::read()
	{
	}

	void PrimaryKey::write()
	{
	}

	std::string PrimaryKey::toString()
	{
		std::string mensaje = std::to_string(id_) + "\t|\t" 
			+ std::to_string(entidadId_) + "\t|\t" 
			+ fecha_ + "\n";
		return mensaje;
	}

	std::string PrimaryKey::mostrarCampos()
	{
		std::string mensaje = "id \t|\t entidad_id \t|\t fecha\n";
		return mensaje;
	}


}