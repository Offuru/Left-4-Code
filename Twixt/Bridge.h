#pragma once

#include <utility>
#include "Pylon.h"
#include "Utilities.h"
#include "observer_test.h"

namespace twixt
{

	class Pylon;

	class Bridge
	{
	private:
		nonstd::observer_ptr<Pylon> m_pylonStart;
		nonstd::observer_ptr<Pylon> m_pylonEnd;
		Position m_posStart;
		Position m_posEnd;

	public:
		Bridge();
		Bridge(nonstd::observer_ptr<Pylon>, nonstd::observer_ptr<Pylon>, const Position&, const Position&);
		Bridge(const Bridge&);
		Bridge& operator=(const Bridge&);
		~Bridge() = default;

		nonstd::observer_ptr<Pylon> getPylonStart() const;
		nonstd::observer_ptr<Pylon> getPylonEnd() const;
		Position getPosStart() const;
		Position getPosEnd() const;

		void setPylonStart(nonstd::observer_ptr<Pylon>);
		void setPylonEnd(nonstd::observer_ptr<Pylon>);
		void setPosStart(const Position&);
		void setPosEnd(const Position&);
	};
}
