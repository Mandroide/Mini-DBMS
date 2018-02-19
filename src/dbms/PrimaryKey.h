#pragma once
#include "IOInterface.h"
#include "Columna.h"
#include <string>
#include <set>
namespace dbms {
class PrimaryKey : IOInterface
{
private:
	int id_;
	static int contador_;
	int entidadId_;
	std::string fecha_;
public:
	PrimaryKey(){}
	PrimaryKey(int entidadId);
	virtual ~PrimaryKey();
	int getId();
	int getEntidadId();
	virtual void read() override;
	virtual void write() override;
	virtual std::string toString() override;
	static std::string mostrarCampos();
};

}