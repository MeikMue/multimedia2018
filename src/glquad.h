#ifndef GLQUAD_H
#define GLQUAD_H

#include "glbody.h"
class GLQuad : public GLBody
{
public:
    GLQuad(const QString & name, float radius = 1.0f, const GLColorRgba & color = GLColorRgba::clBlue, const QString textureFile = "");
    virtual void makeSurface(QVector<GLPoint> *pointContainer, QVector<GLushort> *indexContainer);

    QVector3D fieldToPosition(const QPoint & field);
protected:
    float m_radius;
};

#endif // GLQUAD_H
