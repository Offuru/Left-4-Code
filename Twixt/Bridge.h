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
		std::shared_ptr<Pylon> m_pylonStart;
		std::shared_ptr<Pylon> m_pylonEnd;
		Position m_posStart;
		Position m_posEnd;

	public:
		Bridge();
		Bridge(std::shared_ptr<Pylon>, std::shared_ptr<Pylon>, const Position&, const Position&);
		Bridge(const Bridge&);
		Bridge& operator=(const Bridge&);
		~Bridge() = default;

		std::shared_ptr<Pylon> getPylonStart() const;
		std::shared_ptr<Pylon> getPylonEnd() const;
		Position getPosStart() const;
		Position getPosEnd() const;

		void setPylonStart(std::shared_ptr<Pylon>);
		void setPylonEnd(std::shared_ptr<Pylon>);
		void setPosStart(const Position&);
		void setPosEnd(const Position&);
	};
}
