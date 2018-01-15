#ifndef GLDISC_H
#define GLDISC_H

#include <QVector>
#include <QVector3D>
#include "glbody.h"

class GLDisc : public GLBody
{
public:


    GLDisc(const QString & name, float radius = 1.0f, const QString textureFile = "", const GLColorRgba & color = GLColorRgba::clBlue,
           int stacks = 10, int slices = 18);


    virtual void makeSurface(QVector<GLPoint> * pointContainer, QVector<GLushort> *indexContainer);
    void setSelected(bool selected);

    void invalidateSurface(){m_surfaceIsValid = false;}

    //virtual bool isHit(QVector3D p1, QVector3D p2);
protected:
//    QVector3D lbb;
//    QVector3D rtf;
    double m_height;
    int m_stacks;
    int m_slices;
    QPoint m_FieldCoord;
};

#endif // GLDISC_H
