#pragma once

#include <utility>
#include "Pylon.h"
#include "observer_ptr.h"

namespace twixt
{
	class Pylon;

	class Bridge
	{
	private:
		using Position = std::pair<uint8_t, uint8_t>;
		nonstd::observer_ptr<Pylon> m_pylonStart;
		nonstd::observer_ptr<Pylon> m_pylonEnd;
		Position m_posStart;
		Position m_posEnd;

	public:
		__declspec(dllexport) Bridge();
		__declspec(dllexport) Bridge(nonstd::observer_ptr<Pylon>, nonstd::observer_ptr<Pylon>, const Position&, const Position&);
		__declspec(dllexport) Bridge(const Bridge&);
		__declspec(dllexport) Bridge& operator=(const Bridge&);
		__declspec(dllexport) ~Bridge() = default;

		__declspec(dllexport) nonstd::observer_ptr<Pylon> getPylonStart() const;
		__declspec(dllexport) nonstd::observer_ptr<Pylon> getPylonEnd() const;
		__declspec(dllexport) Position getPosStart() const;
		__declspec(dllexport) Position getPosEnd() const;

		__declspec(dllexport) void setPylonStart(nonstd::observer_ptr<Pylon>);
		__declspec(dllexport) void setPylonEnd(nonstd::observer_ptr<Pylon>);
		__declspec(dllexport) void setPosStart(const Position&);
		__declspec(dllexport) void setPosEnd(const Position&);
	};
}

