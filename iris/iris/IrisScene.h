#ifndef __IIRIS_SCENE_H__
#define __IIRIS_SCENE_H__

#include "iris/IrisDefinitions.h"
#include "disposable/IDisposable.h"
#include "gameobject/GameObject.h"

#include "iris/Iris.h"

#include <map>
#include <vector>
#include <stdio.h>

namespace IrisFramework
{
	#define IRIS_MAIN_CAMERA IRIS_SCENE.getCamera()

	class GameObject;
	class Camera;
	class Light;

	typedef std::vector<GameObject*> gameObjectVec_t;
	typedef std::map<unsigned int, GameObject*> gameObjectMap_t;
	typedef std::pair<unsigned int, GameObject*> gameObjectPair_t;

	class IrisScene : public IDisposable
	{
	public:
		IrisScene();
		IrisScene(const char* p_name);
		~IrisScene();

		virtual void awake();
		virtual void start();

		virtual void fixedUpdate();
		virtual void update();
		virtual void lateUpdate();

		virtual void onPreRender();
		virtual void onRender();
		virtual void onPostRender();

		virtual void dispose() override;

		gameObjectPair_t addObject(GameObject *p_gameObject);
		gameObjectPair_t removeObject(GameObject *p_gameObject);

		inline Camera& getCamera();
		inline GameObject& getCameraObject();

		inline Light& getLight1();
		inline Light& getLight2();

		template<class T>
		GameObject* findObjectOfType() const;

		template<class T>
		gameObjectVec_t findObjectsOfType() const;

		gameObjectVec_t getSceneObjects() const;
	private:
		void createCameraObject();
		void createLightObject();
		void createSkyboxObject();

	protected:
		const char* m_name;

		Camera *m_camera;
		Light *m_light1;
		Light *m_light2;

		GameObject *m_skyboxObject;
		GameObject *m_cameraObject;
		GameObject *m_light1Object;
		GameObject *m_light2Object;

		gameObjectMap_t m_sceneObjects;
	};	

	inline Camera &IrisScene::getCamera()
	{
		return *m_camera;
	}

	inline Light &IrisScene::getLight1()
	{
		return *m_light1;
	}

	inline Light &IrisScene::getLight2()
	{
		return *m_light2;
	}

	inline GameObject &IrisScene::getCameraObject()
	{
		return *m_cameraObject;
	}

	template<class T>
	GameObject *IrisScene::findObjectOfType() const
	{
		GameObject *retVal = NULL;

		typedef gameObjectMap_t::const_iterator iterator_t;
		for(iterator_t iterator = m_sceneObjects.begin(); iterator != m_sceneObjects.end(); ++iterator)
		{
			if(T* tClass = (*iterator).second->getComponent<T>())
			{
				retVal = (*iterator).second;
			}
		}

		return retVal;
	}

	template<class T>
	gameObjectVec_t IrisScene::findObjectsOfType() const
	{
		gameObjectVec_t retVal;

		typedef gameObjectMap_t::const_iterator iterator_t;
		for(iterator_t iterator = m_sceneObjects.begin(); iterator != m_sceneObjects.end(); ++iterator)
		{
			if(T* tClass = (*iterator).second->getComponent<T>())
			{
				retVal.push_back((*iterator).second);
			}
		}

		return retVal;
	}
}

#endif
