#include "port.h"

QPoint Port::getWorldPosition()
{
	return mPosition + QPoint(static_cast<int>(mParent->position().x()), static_cast<int>(mParent->position().y()));
}