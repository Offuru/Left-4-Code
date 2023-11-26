#pragma once

#include <utility>
#include "Pylon.h"
#include "Utilities.h"

namespace twixt
{

	class Pylon;

	class Bridge
	{
	private:
		Pylon* m_pylonStart;
		Pylon* m_pylonEnd;
		Position m_posStart;
		Position m_posEnd;

	public:
		Bridge();
		Bridge(Pylon*, Pylon*, const Position&, const Position&);
		Bridge(const Bridge&);
		Bridge& operator=(const Bridge&);
		~Bridge() = default;

		Pylon* getPylonStart() const;
		Pylon* getPylonEnd() const;
		Position getPosStart() const;
		Position getPosEnd() const;

		void setPylonStart(Pylon*);
		void setPylonEnd(Pylon*);
		void setPosStart(const Position&);
		void setPosEnd(const Position&);
	};
}
