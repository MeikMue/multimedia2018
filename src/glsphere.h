#ifndef GLSPHERE_H
#define GLSPHERE_H

#include "glbody.h"

/**
 * @brief The GLSphere class A sphere with minimum number of vertices. **NOT SUITABLE for textures**
 */
class GLSphere : public GLBody
{
public:
    GLSphere(const QString & name, float radius = 1.0, const GLColorRgba & color = GLColorRgba::clBlue,
             const QString textureFile = "",
             int stacks = 256, int slices = 256);
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
    int m_stacks;
    int m_slices;
};

#endif // GLSPHERE_H
