#include "platform\GLView.h"

IRIS_BEGIN

GLContextAttributes GLView::s_glContextAttributes = GLContextAttributes();

GLView::GLView()
: m_windowWidth(WINDOW_WIDTH)
, m_windowHeight(WINDOW_HEIGHT)
{
}

GLView::~GLView()
{
    m_windowWidth = 0.0f;
    m_windowHeight = 0;
}

std::string GLView::toString() const
{
	return "< GLView | ";
}

void GLView::setContextAttributes(GLContextAttributes& p_contextAttributes)
{
	s_glContextAttributes = p_contextAttributes;
}

GLContextAttributes GLView::getContextAttributes()
{
	return s_glContextAttributes;
}

IRIS_END
