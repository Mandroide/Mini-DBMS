#include "stdafx.h"
#include "Autoincremento.h"

namespace dbms {


Autoincremento::Autoincremento(int entidadId)
{
	entidadId_ = entidadId;
}

Autoincremento::~Autoincremento()
{
}

int Autoincremento::getIncremento()
{
	return incremento_;
}

void Autoincremento::setIncremento(int incremento)
{
	incremento_ = incremento;
}
}