#pragma once
#include "IOInterface.h"
#include <string>
#include <memory>
namespace dbms {

class ForeignKey : IOInterface
{
private:
	int id_;
	int entidadPadreId_;
	int entidadHijoId_;
	// Detalles
	class ForeignKeyDetails : IOInterface
	{
	private:
		int id_;
		int columnaPadreId_;
		int columnaHijoId_;
	public:
		ForeignKeyDetails(int id, int columnaPadreId, int columnaHijoId);
		virtual void read() override;
		virtual void write() override;
		virtual std::string toString() override;
		int getColumnaPadreId();
		int getColumnaHijoId();

	};
	std::unique_ptr<ForeignKeyDetails> detalles_;


public:
	ForeignKey(ForeignKey&& obj);
	ForeignKey(const ForeignKey& obj); // Copy constructor
	ForeignKey& operator=(const ForeignKey& obj);
	ForeignKey(int id, int entidadPadreId, int entidadHijoId, int columnaPadreId, int columnaHijoId);
	virtual ~ForeignKey();
	virtual void read() override;
	virtual void write() override;
	virtual std::string toString() override;
	int getId();
	int getEntidadPadreId();
	int getEntidadHijoId();

};

}