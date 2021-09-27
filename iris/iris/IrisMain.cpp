#include "IrisMain.h"
#include "Iris.h"

namespace IrisFramework
{
	IrisMain::IrisMain() { }

	IrisMain::~IrisMain() { }

	IrisMain &IrisMain::Instance()
	{
		static IrisMain instance;
		return instance;
	}

	void IrisMain::onApplicationStart()
	{
		IRIS_ENGINE.initialize();
	}

	void IrisMain::onApplicationQuit()
	{

	}
}