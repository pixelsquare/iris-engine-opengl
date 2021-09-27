#include "Transform.h"

#include "iris/Iris.h"
#include "iris/IrisGL.h"
#include "iris/IrisScene.h"
#include "iris/IrisLogger.h"

#include "camera/Camera.h"
#include "gameobject/GameObject.h"

namespace IrisFramework
{
	Transform::Transform() 
	: Component("transform_component"),
	m_parent(0),
	m_position(Vector3f::ZERO),
	m_rotation(Vector3f::ZERO),
	m_scale(Vector3f::ONE)
	{
		m_transform = this;
		m_modelMatrix.identity();
	}

	Transform::Transform(GameObject *p_gameObject)
	: Component("transform_component"), 
	m_parent(0),
	m_position(Vector3f::ZERO),
	m_rotation(Vector3f::ZERO),
	m_scale(Vector3f::ONE)
	{ 		
		m_transform = this;
		m_gameObject = p_gameObject;
		m_modelMatrix.identity();
	}

	Transform::~Transform() {}

	void Transform::awake()
	{
		Component::awake();

		typedef std::vector<Transform*>::iterator it_type;
		for(it_type iterator = m_children.begin(); iterator != m_children.end(); ++iterator)
		{
			Transform *transform = *iterator;
			transform->getGameObject().awake();
		}
	}

	void Transform::start()
	{
		Component::start();

		typedef std::vector<Transform*>::iterator it_type;
		for(it_type iterator = m_children.begin(); iterator != m_children.end(); ++iterator)
		{
			Transform *transform = *iterator;
			IRIS_LOG.internalLog(" + %s\n", (*iterator)->getGameObject().getName());
			transform->getGameObject().start();
		}
	}

	void Transform::fixedUpdate()
	{
		Component::fixedUpdate();
	}

	void Transform::update()
	{
		Component::update();

		typedef std::vector<Transform*>::iterator it_type;
		for(it_type iterator = m_children.begin(); iterator != m_children.end(); ++iterator)
		{
			Transform *transform = *iterator;
			transform->getGameObject().update();
		}
	}

	void Transform::lateUpdate()
	{
		Component::lateUpdate();
	}

	void Transform::onPreRender()
	{
		Component::onPreRender();
	}

	void Transform::onRender()
	{
		Component::onRender();

		m_matrixRoll.identity();
		m_matrixYaw.identity();
		m_matrixPitch.identity();

		m_matrixPitch.rotateX(m_rotation.x);
		m_matrixYaw.rotateY(m_rotation.y);
		m_matrixRoll.rotateZ(m_rotation.z);

		m_modelMatrix.identity();		
		m_matrixRotation = m_matrixPitch * m_matrixYaw * m_matrixRoll;
		m_modelMatrix = m_modelMatrix * m_matrixRotation;
		m_modelMatrix.translate(m_position.x, m_position.y, m_position.z);
		m_modelMatrix.scale(m_scale.x, m_scale.y, m_scale.z);


		//if(m_gameObject->hasCameraAttached())
		//{
		//	// Invert all transformations of the camera
		//	// relative to world objects. (Right-hand side)

		//	m_matrixRoll.identity();
		//	m_matrixYaw.identity();
		//	m_matrixPitch.identity();

		//	m_matrixPitch.rotateX(-m_rotation.x);
		//	m_matrixYaw.rotateY(-m_rotation.y);
		//	m_matrixRoll.rotateZ(-m_rotation.z);

		//	m_modelMatrix.identity();
		//	m_matrixRotation = m_matrixPitch * m_matrixYaw * m_matrixRoll;			

		//	m_modelMatrix.scale(m_scale.x, m_scale.y, m_scale.z);
		//	m_modelMatrix.translate(-m_position.x, -m_position.y, -m_position.z);

		//	m_modelMatrix = m_modelMatrix * m_matrixRotation;

		//	m_localMatrix = m_modelMatrix;
		//	m_modelMatrixView = m_modelMatrix;
		//	IRIS_GL.loadMatrix(m_modelMatrixView.get());
		//}
		//else
		{		
			GameObject *cameraObject = &IRIS_SCENE.getCameraObject();			

			if(NULL != cameraObject)
			{		
				if(NULL == m_parent)
				{
					m_localMatrix = m_modelMatrix;
					Matrix4x4 cameraModelMatrix = cameraObject->getTransform().getModelMatrix();
					cameraModelMatrix = cameraModelMatrix.invert();
					m_modelMatrixView = m_modelMatrix * cameraModelMatrix;
				}
				else
				{
					m_localMatrix = m_modelMatrix * m_parent->getModelMatrix();
					m_modelMatrixView = m_modelMatrix * m_parent->getModelMatrixView();
				}
			}
			else
			{
				// Use engine's default matrix view when we 
				// failed to grab scene's camera object
				if(NULL == m_parent)
				{
					m_localMatrix = m_modelMatrix;
					m_modelMatrixView = m_modelMatrix * IRIS_GL.getCameraMatrixView();
				}
				else
				{
					m_localMatrix = m_modelMatrix * m_parent->getModelMatrix();
					m_modelMatrixView = m_modelMatrix * m_parent->getModelMatrixView();
				}
			}			

			IRIS_GL.loadMatrix(m_modelMatrixView.get());
		}

		typedef std::vector<Transform*>::iterator it_type;
		for(it_type iterator = m_children.begin(); iterator != m_children.end(); ++iterator)
		{
			Transform *transform = *iterator;
			transform->getGameObject().onRender();
		}
	}

	void Transform::onPostRender()
	{
		Component::onPostRender();
	}

	void Transform::dispose()
	{
		Component::dispose();

		typedef std::vector<Transform*>::iterator it_type;
		for(it_type iterator = m_children.begin(); iterator != m_children.end(); ++iterator)
		{
			Transform *transform = *iterator;
			transform->getGameObject().dispose();
			delete transform;
		}

		m_parent = 0;
		delete m_parent;
	}

	void Transform::setPosition(const float& p_posX, const float& p_posY, const float& p_posZ)
	{
		setPosition(Vector3f(p_posX, p_posY, p_posZ));
	}

	void Transform::setPosition(const Vector3f& p_position)
	{
		m_position = p_position;
	}

	Vector3f &Transform::getPosition()
	{
		return m_position;
	}

	void Transform::setRotation(const float& p_rotX, const float& p_rotY, const float& p_rotZ)
	{
		setRotation(Vector3f(p_rotX, p_rotY, p_rotZ));
	}

	void Transform::setRotation(const Vector3f& p_rotation)
	{
		m_rotation = p_rotation;
	}

	Vector3f &Transform::getRotation()
	{
		return m_rotation;
	}

	void Transform::setScale(const float& p_scaleX, const float& p_scaleY, const float& p_scaleZ)
	{
		setScale(Vector3f(p_scaleX, p_scaleY, p_scaleZ));
	}

	void Transform::setScale(const Vector3f& p_scale)
	{
		m_scale = p_scale;
	}

	void Transform::setScale(float p_scale)
	{
		setScale(Vector3f::ONE * p_scale);
	}

	Vector3f &Transform::getScale()
	{
		return m_scale;
	}

	Vector3f Transform::getLocalPosition() const
	{
		return m_localMatrix.getPosition();
	}

	Vector3f Transform::getLocalRotation() const
	{
		return m_localMatrix.getRotation();
	}

	Vector3f Transform::getLocalScale() const
	{
		return m_localMatrix.getScale();
	}

	Vector3f Transform::getForward() const
	{
		return m_modelMatrixView.getForward();
	}

	Vector3f Transform::getRight() const
	{
		return m_modelMatrixView.getRight();
	}

	Vector3f Transform::getUp() const
	{
		return m_modelMatrixView.getUp();
	}

	void Transform::reset()
	{
		m_position = Vector3f::ZERO;
		m_rotation = Vector3f::ZERO;
		m_scale = Vector3f::ONE;

		m_localPosition = Vector3f::ZERO;
		m_localRotation = Vector3f::ZERO;
		m_localScale = Vector3f::ONE;

		m_forward = Vector3f::ZERO;
		m_right = Vector3f::ZERO;
		m_up = Vector3f::ZERO;

		m_localMatrix.identity();
		
		m_matrixYaw.identity();
		m_matrixPitch.identity();
		m_matrixRoll.identity();

		m_matrixRotation.identity();
	}

	Matrix4x4 &Transform::getModelMatrix()
	{
		return m_modelMatrix;
	}

	Matrix4x4 &Transform::getModelMatrixView()
	{
		return m_modelMatrixView;
	}

	void Transform::setParent(Transform *p_parent)
	{
		m_parent = p_parent;
	}

	Transform &Transform::getParent()
	{
		return *m_parent;
	}

	bool Transform::hasParentAttached() const
	{
		return NULL != m_parent;
	}

	void Transform::addChild(Transform *p_child)
	{
		m_children.push_back(p_child);
		p_child->setParent(this);
	}

	void Transform::removeChild(Transform *p_child)
	{
		typedef std::vector<Transform*>::iterator it_type;
		for(it_type iterator = m_children.begin(); iterator != m_children.end(); ++iterator)
		{
			Transform *transform = *iterator;

			if(transform->getGameObject().getName() == p_child->getGameObject().getName())
			{
				transform->setParent(NULL);
				m_children.erase(iterator);
				delete transform;
			}
		}
	}
}