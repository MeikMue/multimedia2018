#ifndef GLCUBE_H
#define GLCUBE_H

#include "glbody.h"

class GLCube : public GLBody
{
public:
    GLCube(const QString & name,const QVector3D& lbb = v_Zero, const QVector3D & rtf = v_XYZ,
            const GLColorRgba & color = GLColorRgba::clBlue, const QString textureFile = "");

    /** Creates the surface. Should be called, when a GL engine is already running.
      * To be overwritten by subclasses. GLESBody::createSurface should be called at the beginning
      * of overriding functions. It will create the pointContainer, if none is supplied
      * Is called automatically by draw, if required.
      * MUST NOT be called without a working GL engine.
      *
      * @param pointContainer The container for the geometry data. If NULL, a new one is created.
      * @param indexContainer The container for the index data. If NULL, a new one is created.
      * Created containers will be deleted by destructor.
      */
    virtual void makeSurface(QVector<GLPoint> * pointContainer, QVector<GLushort> *indexContainer);

private:
    QVector3D m_lbb;
    QVector3D m_rtf;
};

#endif // GLCUBE_H
