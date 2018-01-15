#include "glmouseray.h"


GLMouseRay::GLMouseRay(const QString &name, const GLColorRgba &color) : GLBody(name, 1.0, color)

{

}

void GLMouseRay::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLushort> *indexContainer)
{
    Q_UNUSED (pointContainer);
    Q_UNUSED (indexContainer);

    if(!m_renderer)
        return;
    //DO NOT call GLBody::makeSurface here, we need our own containers!
    if(m_firstPoint == m_nextPoint) //we have no points yet
    {
        m_points = new QVector<GLPoint>();
        m_indices = new QVector<GLushort>();
    }
    m_points->clear();
    m_indices->clear();
    m_firstPoint = m_points->size();
    m_firstIndex = m_indices->size();

    QVector3D nearPoint, farPoint;
    m_renderer->calculateMousePoints(&nearPoint, &farPoint, m_mousePosition);

    nearPoint.setZ (nearPoint.z ()- 3.0f);
    farPoint.setZ (farPoint.z ()- 3.0f);

    if (! (m_mousePosition.x() == 0 && m_mousePosition.y() == 0))
    {
        QVector3D normal = v_X;
        QVector3D texCoord = v_Zero;
        m_indices->append(m_points->size());
        m_points->append(GLPoint(nearPoint, normal,texCoord, m_color));
        m_indices->append(m_points->size());
        m_points->append(GLPoint(farPoint, normal,texCoord, m_color));
    }

    m_nextPoint = m_points->size();
    m_nextIndex = m_indices->size();
    findMinMaxCoordinates();
    m_surfaceIsValid = true;
}

void GLMouseRay::setMousePosition(const QPoint &pos)
{
    m_mousePosition = pos;
    invalidateSurface();
}

void GLMouseRay::draw(GLESRenderer *renderer)
{
    m_color = GLColorRgba::clWhite;
    m_renderer = renderer; //set it for this drawing
    GLint oldLineWidth[4];
    glGetIntegerv(GL_LINE_WIDTH, oldLineWidth);
    glLineWidth(3);
    GLshort oldPointSize = renderer->pointSize();
    renderer->setPointSize(10);
    bool oldLighting = renderer->isLightingEnabled();
    renderer->setLightingEnabled(false);
    m_drawingMode = GL_POINTS;
    GLBody::draw(renderer);
    m_drawingMode = GL_LINES;
    GLBody::draw(renderer);
    glLineWidth(oldLineWidth[0]);
    renderer->setLightingEnabled(oldLighting);
    renderer->setPointSize(oldPointSize);
    m_renderer = NULL;
}
