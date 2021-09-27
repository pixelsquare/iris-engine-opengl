#ifndef __IDEBUGGABLE_H__
#define __IDEBUGGABLE_H__

#include "iris/IrisDefinitions.h"

namespace IrisFramework
{
	class IDebuggable
	{
	public:
		virtual const char *toString() const = 0;

	private:
	protected:
		IDebuggable();
		~IDebuggable();
	};
}

#endif
