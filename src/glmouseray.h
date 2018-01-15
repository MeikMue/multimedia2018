#ifndef GLMOUSERAY_H
#define GLMOUSERAY_H

#include <QVector>
#include <QVector3D>
#include "glbody.h"
#include "glitem.h"

class GLMouseRay :public GLBody
{
public:

    GLMouseRay(const QString &name, const GLColorRgba & color = GLColorRgba::clBlue);


    virtual void makeSurface(QVector<GLPoint> *pointContainer, QVector<GLushort> *indexContainer);

    void setMousePosition(const QPoint &pos);

    void invalidateSurface(){m_surfaceIsValid = false;}

    void draw(GLESRenderer *renderer);

protected:

    GLESRenderer * m_renderer;
    QPoint m_mousePosition;

};

#endif // GLMOUSERAY_H
