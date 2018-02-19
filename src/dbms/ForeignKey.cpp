#include "stdafx.h"
#include "ForeignKey.h"
#include <fstream>
namespace dbms {

	ForeignKey::ForeignKey(ForeignKey && obj)
	{
		id_ = std::move(obj.id_);
		entidadPadreId_ = std::move(obj.entidadPadreId_);
		entidadHijoId_ = std::move(obj.entidadHijoId_);
		detalles_ = std::move(obj.detalles_);
	}
	ForeignKey::ForeignKey(const ForeignKey & obj)
	{
		id_ = obj.id_;
		entidadPadreId_ = obj.entidadPadreId_;
		entidadHijoId_ = obj.entidadHijoId_;
		detalles_ = std::unique_ptr<ForeignKeyDetails>(&(*obj.detalles_));
	}
	ForeignKey & ForeignKey::operator=(const ForeignKey & obj)
	{
		id_ = obj.id_;
		entidadPadreId_ = obj.entidadPadreId_;
		entidadHijoId_ = obj.entidadHijoId_;
		detalles_ = std::unique_ptr<ForeignKeyDetails>(&(*obj.detalles_));
		return *this;
	}

	ForeignKey::ForeignKey(int id, int entidadPadreId, int entidadHijoId, int columnaPadreId, int columnaHijoId)
		:IOInterface("ForeignKey.txt")
	{
		id_ = id;
		entidadPadreId_ = entidadPadreId;
		entidadHijoId_ = entidadHijoId;
		detalles_ = std::unique_ptr<ForeignKeyDetails>(new ForeignKeyDetails(id_, columnaPadreId, columnaHijoId));
	}


	ForeignKey::~ForeignKey()
	{
	}

	void ForeignKey::read()
	{

	}

	void ForeignKey::write()
	{
	}

	ForeignKey::ForeignKeyDetails::ForeignKeyDetails(int id, int columnaPadreId, int columnaHijoId) 
		: IOInterface("ForeignKeyDetails.txt")
	{
		id_ = id;
		columnaPadreId_ = columnaPadreId;
		columnaHijoId_ = columnaHijoId;
	}

	void ForeignKey::ForeignKeyDetails::read()
	{
	}

	void ForeignKey::ForeignKeyDetails::write()
	{
	}

	std::string ForeignKey::ForeignKeyDetails::toString()
	{
		std::string mensaje = std::to_string(id_) + "\t|\t"
			+ std::to_string(columnaPadreId_) + "\t|\t"
			+ std::to_string(columnaHijoId_) + "\n";
		return std::string();
	}

	int ForeignKey::getId()
	{
		return id_;
	}

	int ForeignKey::getEntidadPadreId()
	{
		return entidadPadreId_;
	}

	int ForeignKey::getEntidadHijoId()
	{
		return entidadHijoId_;
	}

	std::string ForeignKey::toString()
	{
		std::string mensaje = std::to_string(id_) + "\t|\t"
			+ std::to_string(entidadPadreId_) + "\t|\t"
			+ std::to_string(entidadHijoId_) + "\n";
		return mensaje;
	}

	int ForeignKey::ForeignKeyDetails::getColumnaPadreId()
	{
		return columnaPadreId_;
	}

	int ForeignKey::ForeignKeyDetails::getColumnaHijoId()
	{
		return columnaHijoId_;
	}


}