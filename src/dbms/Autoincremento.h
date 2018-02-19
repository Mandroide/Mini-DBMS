#pragma once
namespace dbms {

	class Autoincremento
	{
		int incremento_;
		int entidadId_;
	public:
		Autoincremento(int entidadId);
		virtual ~Autoincremento();
		int getIncremento();
		void setIncremento(int incremento);
	};

}