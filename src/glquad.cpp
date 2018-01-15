#include "glquad.h"

GLQuad::GLQuad(const QString & name, float radius, const GLColorRgba & color, const QString textureFile) : GLBody(name, 1.0, color,textureFile)
{
    m_drawingMode = GL_QUADS;
    m_radius = radius;
}

void GLQuad::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLushort> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);
    m_firstPoint = m_points->size();
    m_firstIndex = m_indices->size();

    for(int zeile = 4; zeile > -4; zeile-=2)
    {
        for(int spalte = -4; spalte < 4; spalte+=2)
        {
            m_points->append(GLPoint(QVector3D(spalte * 2*m_radius, zeile * 2*m_radius, 0.0), v_Z, v_Zero)); //1 Vierreck Punkt
            m_points->append(GLPoint(QVector3D(spalte * 2*m_radius, zeile * 2*m_radius -2, 0.0), v_Z, v_Zero)); //2 Vierreck Punkt
            m_points->append(GLPoint(QVector3D(spalte * 2*m_radius +2, zeile * 2*m_radius -2, 0.0), v_Z, v_Zero)); //3 Vierreck Punkt
            m_points->append(GLPoint(QVector3D(spalte * 2*m_radius +2, zeile * 2*m_radius, 0.0), v_Z, v_Zero)); //4 Vierreck Punkt
        }
    }
    for(int zeile = 3; zeile > -4; zeile-=2)
    {
        for(int spalte = -3; spalte < 4; spalte+=2)
        {
            m_points->append(GLPoint(QVector3D(spalte * 2*m_radius, zeile * 2*m_radius, 0.0), v_Z, v_Zero)); //1 Vierreck Punkt
            m_points->append(GLPoint(QVector3D(spalte * 2*m_radius, zeile * 2*m_radius -2, 0.0), v_Z, v_Zero)); //2 Vierreck Punkt
            m_points->append(GLPoint(QVector3D(spalte * 2*m_radius +2, zeile * 2*m_radius -2, 0.0), v_Z, v_Zero)); //3 Vierreck Punkt
            m_points->append(GLPoint(QVector3D(spalte * 2*m_radius +2, zeile * 2*m_radius, 0.0), v_Z, v_Zero)); //4 Vierreck Punkt
        }
    }

    m_nextPoint = m_points->size();
    m_nextIndex = m_indices->size();
}

QVector3D GLQuad::fieldToPosition(const QPoint &field)
{
    int x;
    int y;

    if (field.x() >= 0)
    {
        if (field.x() % 2 == 0)
        {
            x = field.x() + m_radius;
        }
        else
        {
            x = field.x();
        }
    }
    else
    {
        if (field.x() % 2 == 0)
        {
            x = field.x() - m_radius;
        }
        else
        {
            x = field.x();
        }
    }
    if (field.y() >= 0)
    {
        if (field.y() % 2 == 0)
        {
            y = field.y() + m_radius;
        }
        else
        {
            y = field.y();
        }
    }
    else
    {
        if (field.y() % 2 == 0)
        {
            y = field.y() - m_radius;
        }
        else
        {
            y = field.y();
        }
    }

    return QVector3D(x, y, 0.0);
}

