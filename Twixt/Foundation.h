#pragma once

#include <utility>
#include "Pylon.h"
#include "CrossPylon.h"
#include "SinglePylon.h"
#include "SquarePylon.h"
#include "Utilities.h"

namespace twixt
{

	class Pylon;

	class Foundation
	{
	private:
		Position m_position;
		bool m_mined;
		bool m_hasBob;
		bool m_exploded;
		Pylon* m_pylon;

	public:
		Foundation();
		Foundation(Position, bool = false, Pylon* = nullptr);
		Foundation(const Foundation&); //TO DO: take care of memory leak, change allocation to unique_ptr
		Foundation& operator=(Foundation&); //TO DO: take care of memory leak, change allocation to unique_ptr
		~Foundation() = default; // pilonii se distrug din board!!

		Position getPosition() const;
		bool getMined() const;
		bool getExploded() const;
		bool getBob() const;
		Pylon* getPylon() const;


		void setPosition(const Position&);
		void setMined(bool);
		void setExploded(bool);
		void setPylon(Pylon*);
		void setBob(bool);
	};
}