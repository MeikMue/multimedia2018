#ifndef GLClone_H
#define GLClone_H

#include <QVector>
#include <QVector3D>
#include "glbody.h"

class GLClone : public GLBody
{
public:


    GLClone(const QString & name, float radiusBot = 1.0f, float radiusTop = 1.0f, const QString textureFile = "", const GLColorRgba & color = GLColorRgba::clBlue,
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
    float m_radiusBot;
    float m_radiusTop;
    QPoint m_FieldCoord;
};

#endif // GLClone_H
