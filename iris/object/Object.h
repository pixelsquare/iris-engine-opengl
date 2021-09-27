#ifndef __IRIS_OBJECT_H__
#define __IRIS_OBJECT_H__

#include "iris/IrisDefinitions.h"
#include "disposable/IDisposable.h"

namespace IrisFramework
{
	class Object : public IDisposable
	{
	public:
		Object();
		Object(const char *p_name);
		~Object();

		virtual void dispose() override;

		const char* getName() const;
		unsigned int getInstanceID() const;

	private:
		static unsigned int s_nextGUID;

	protected:
		const char *m_name;
		unsigned int m_guid;
	};
}

#endif
