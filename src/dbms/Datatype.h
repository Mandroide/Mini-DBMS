#pragma once
#include <string>
#include <memory>
#include <map>
namespace dbms {
	enum class Type {
		SMALLINT = 1, INT, BIGINT, NUMERIC, CHAR, VARCHAR
	};

	class Datatype
	{
	private:
		std::string nombre_;
		short length_;
		short precision_;
		Type type_;

		Datatype(const Type& type, const std::string& nombre);

	public:
		Datatype();
		static const Datatype SMALLINT;
		static const Datatype BIGINT;
		static const Datatype INT;
		static const Datatype NUMERIC;
		static const Datatype VARCHAR;
		static const Datatype CHAR;

		static int getSize() { return 6; }

		std::string toString() const;
		Type getType() const;
		short getLength() const;
		short getPrecision() const;
		void setLength(short length);
		void setPrecision(short precision);

		friend class Columna;
		bool operator==(const Datatype& obj);
	};

	// Para transformar enum en su correspondiente tipo de dato.
	const auto tipos = std::unique_ptr<std::map<Type, Datatype>>(
		new std::map<Type, Datatype>{
			{ Type::SMALLINT, Datatype::SMALLINT }, { Type::INT, Datatype::INT }, { Type::BIGINT, Datatype::BIGINT },
			{ Type::NUMERIC, Datatype::NUMERIC }, { Type::CHAR, Datatype::CHAR }, { Type::VARCHAR, Datatype::VARCHAR }
		}

	);

}