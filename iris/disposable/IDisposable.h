#ifndef __IDISPOSABLE_H__
#define __IDISPOSABLE_H__

#include "iris/IrisDefinitions.h"

namespace IrisFramework
{
	class IDisposable
	{
	public:
		virtual void dispose() = 0;

	private:
	protected:
		IDisposable();
		~IDisposable();
	};
}

#endif
