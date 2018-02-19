#include "Datatype.h"
namespace dbms {


	// Definicion de constantes

	const Datatype Datatype::SMALLINT = Datatype(Type::SMALLINT, "SMALLINT" );
	const Datatype Datatype::INT = Datatype(Type::INT, "INT");
	const Datatype Datatype::BIGINT = Datatype(Type::BIGINT, "BIGINT");
	const Datatype Datatype::NUMERIC = Datatype(Type::NUMERIC, "NUMERIC");
	const Datatype Datatype::CHAR = Datatype(Type::CHAR, "CHAR");
	const Datatype Datatype::VARCHAR = Datatype(Type::VARCHAR, "VARCHAR");



	Datatype::Datatype(const Type& type, const std::string& nombre) : Datatype()
	{
		type_ = type;
		nombre_ = nombre;

	}

	Datatype::Datatype() {
		length_ = 1;
		precision_ = 0;
	}

	std::string Datatype::toString() const
	{
		return nombre_;
	}
	Type Datatype::getType() const
	{
		return type_;
	}
	short Datatype::getLength() const
	{
		return length_;
	}
	short Datatype::getPrecision() const
	{
		return precision_;
	}
	void Datatype::setLength(short length)
	{
		length_ = length;
	}
	void Datatype::setPrecision(short precision)
	{
		precision_ = precision;
	}

	bool Datatype::operator==(const Datatype& obj)
	{
		return obj.type_ == obj.type_;
	}


}