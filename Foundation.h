#pragma once

#include <utility>

class Foundation
{
private:
	std::pair<uint8_t, uint8_t> m_position;
	bool m_mined;
	Pylon* m_pylon;

public:
	Foundation();
	Foundation(std::pair<uint8_t, uint8_t>, bool, Pylon*);
	Foundation(const Foundation&);
	Foundation& operator=(const Foundation&);
	~Foundation();

	std::pair<uint8_t, uint8_t> getPosition() const;
	bool getMined() const;
	Pylon* getPylon() const;

	void setPosition(const std::pair<uint8_t, uint8_t>&);
	void setMined(bool);
	void setPylon(Pylon*);
};

