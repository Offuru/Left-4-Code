#include "Utilities.h"

bool twixt::counterclockwiseOrder(const Position& A, const Position& B, const Position& C)
{
	//verify if the third points are in counterclock wise order
	return (C.second - A.second) * (B.first - A.first) >
		(B.second - A.second) * (C.first - A.first);
}
