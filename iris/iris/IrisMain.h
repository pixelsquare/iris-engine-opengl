#ifndef __IRIS_MAIN_H__
#define __IRIS_MAIN_H__

namespace IrisFramework
{
	#define IRIS_MAIN IrisMain::Instance()

	class IrisMain
	{
	public:
		static IrisMain& Instance();

		virtual void onApplicationStart();
		virtual void onApplicationQuit();

	private:
		IrisMain();
		~IrisMain();

	protected:
	};
}

#endif