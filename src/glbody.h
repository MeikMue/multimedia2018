/***************************************************************************
 *   Copyright (C) 2008, 2012 by Walter Roth                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef GLBODY_H
#define GLBODY_H

#include <QVector>

#include "glesrenderer.h"
#include "glpoint.h"
#include "gldefines.h"

/**
  * \brief A 3D body that uses a GLESRenderer for drawing and GLPoint objects for defining its surface.
  *
  * Overwrite makeSurface() in subclasses to create the GLPoints that form the surface.
  * Set drawingMode to GL_LINE_STRIP or GL_LINES for debugging the surface. Default is GL_TRIANGLE_STRIP.
  * Vertices and indices may be stored in external or internal containers. If GlBody::makeSurface is called
  * with pointers to existing containers, these will be used. Otherwise GlBody::makeSurface will create new
  * containers. Only in this case, the destructor will delete the containers.
  * Overwrite draw() if you do need special drawing procedures.
  */
class GLBody{
    static uint BINARY_FORMAT_VERSION;
public:
     /**Constructor does NOT create the surface.
     */
     GLBody(const QString & name, float radius = 1.0, const GLColorRgba & m_color = GLColorRgba::clBlue, const QString m_textureFile = "");
     /**
      * @brief GLBody Constructor does NOT create the surface.
      * @param offset The offset from coordinate origin to modeldata zero.
      */
     GLBody(QString  name, const QVector3D offset);

    /** Destructor will delete created containers.
     */
    virtual ~GLBody();

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

     /**
     * @brief readBinaryFile File format: 4 bytes uint number of GlPoints, 4 bytes uint number of uint indices
     * number of points GlPoint objects followed by number of indices indices
     * @param dataFileName
     * @param pointContainer To be used for GLPoints. If NULL, a new private container is created
     * @param indexContainer To be used for indices. If NULL, a new private container is created
     * @return
     */
    virtual bool readBinaryModelFile(const QString & dataFileName, QVector<GLPoint> *pointContainer = NULL, QVector<GLushort> *indexContainer = NULL);       // Binaere Datei

     /**
      * @brief rotateModelPoints Rotates model points around axis
      * @param axisCenter The center of the rotation axis
      * @param axisDirection Direction of rotation axis
      * @param angle Clockwise rotation angle.
      */
     virtual void rotateModelPoints(const QVector3D &axisCenter, const QVector3D &axisDirection, double angle);

     /**
     * @brief calculateDrawMatrix Virtual function to calculate the final matrix to be used for drawing.
     * May be overwritten in subclasses. GLBody::calculateDrawMatrix simply copies m_transformationMatrix.
     */
    virtual void calculateDrawMatrix();
   /** Draws the surface and calls makeSurface if required.
    * Needs an active (made current) GL-Context.
    */
    virtual void draw(GLESRenderer * renderer);

    /**
      * Returns true, when line through p1 and p2 intersects body sphere
      * True if line through p1 and p2 intersects cube defined by minCoordinates and maxCoordinates.
      * To be overwritten by subclasses.
      */
    virtual bool isHit(QVector3D p1, QVector3D p2);
     /**
     * @brief isCubeHit
     * @param mouseNear Point 1 on line in model space
     * @param mouseFar Point 2 on line in model space
     * @return True if line defined by mouseNear and mouseFar intersects cube defined by m_minCoordinate and m_maxCoordinate
     */
    virtual bool isCubeHit(QVector3D mouseNear, QVector3D mouseFar);

     /**
     * @brief isTriangleHit
     * @param p1 Triangle point 1
     * @param p2 Triangle point 2
     * @param p3 Triangle point 3
     * @param pLine Point on line
     * @param lineDirection Direction of line
     * @param intersection If not NULL, coordinates of intersection are written to *intersection.
     * @return True, if plane defined by p1, p2, p3 is intersected by line inside the triangle formed by p1, p2, p3.
     */
    static bool isTriangleHit(const QVector3D & p1, const QVector3D & p2, const QVector3D & p3,
                       const QVector3D & pLine, const QVector3D & lineDirection, QVector3D *intersection = NULL);
    /**
    * @brief isParallelogramHit
    * @param p1 Triangle point 1
    * @param p2 Triangle point 2
    * @param p3 Triangle point 3
    * @param pLine Point on line
    * @param lineDirection Direction of line
    * @param intersection If not NULL, coordinates of intersection are written to *intersection.
    * @return True, if plane defined by p1, p2, p3 is intersected by line inside the parallelogram (rectangle) formed by p1, p2, p3.
    */
   static bool isParallelogramHit(const QVector3D & p1, const QVector3D & p2, const QVector3D & p3,
                      const QVector3D & pLine, const QVector3D & lineDirection, QVector3D *intersection = NULL);
     /**
      * @brief isHit
      * @return True if line defined by mousePos intersects cube defined by minCoordinates and maxCoordinates.
      */
     virtual bool isHit(QPoint mousePos, GLESRenderer * renderer);

    /**
      * Returns true, if enclosing spheres touch or intersect
      */
    virtual bool spheresAreColliding(const GLBody * other);

   /** Set textures from files. Returns true on success. Needs a current OpenGL context.
    */
    bool createTextureObjects(                     GLenum minfilter = GL_LINEAR_MIPMAP_NEAREST,
                                                   GLenum magfilter = GL_LINEAR ,
                                                   GLenum wrapmode = GL_CLAMP_TO_EDGE);
    /**
     * @brief deleteTextureObjects delete all texture objects from m_textureIds
     */
    void deleteTextureObjects();

    /** Set texture file. Needs a current OpenGL context.
     */
     bool setTextureFile(const QString & textureFile);
    /**
     * @brief setTextures Alle Texturen aus textureFiles laden.
     * @param minfilter
     * @param magfilter
     * @param wrapmode
     * @return true wenn ok.
     */
    bool setTextureFiles(const QStringList &textureFiles);

    /**
      * Moves the body by adding vMove to all vertices.
      */
    void move(QVector3D vMove);

    /**
     * @brief startAnimation Start an animation process.
     *   Sets animationActive to true.
     *   Overwrite in subclasses to set Begin and End values for animated properties.
     * @param startValue Present state of the animation process
     */
    virtual void startAnimation(double startValue = 0.0);
    /**
     * @brief finishAnimation Finish an animation process.
     *        Sets animationActive to false.
     * Overwrite in subclasses to copy End values for animated properties to Begin values.
     */
    virtual void finishAnimation();
    /**
     * @brief isAnaimationActive
     * @return True, if an animation is in progress.
     */
    bool isAnimationActive(){return m_animationActive;}

    /**
     * @brief localAnimationState
     * @return State in the range from m_animationStart to 1.0
     */
    double localAnimationState(double globalAnimationState);

    /**
     * @brief animateForwards Start upwards animation
     */
    virtual void animateForwards();
    /**
     * @brief animateBackwards Start downwards animation
     */
    virtual void animateBackwards();
    /**
     * @brief updateAnimatedProperties
     * Overwrite to set current values of animated properties.
     */
    virtual void updateAnimatedProperties(double animationState);

    /**
      * Simple gettters
      */
    bool isSelected(){return m_selected;}
    const QVector3D & getCenter()const{return m_center;}

   /**Simple setters
    */
    void setColor(const GLColorRgba & newVal){m_color = newVal;}
    void setSpecularColor(const GLColorRgba & newVal){m_specularColor = newVal;}
    void setShininess(int newVal){m_shininess = newVal;}
    void setSelected(bool newVal){m_selected = newVal;}
    void setDrawingMode(GLint newVal){m_drawingMode = newVal;}
    void setTransformation(const QMatrix4x4 & transformation){m_transformationMatrix = transformation;}
    void setModelOffset(const QVector3D & offset){m_modelOffset = offset;}
    const GLColorRgba & getColor()const{return m_color;}
    const QMatrix4x4 & getTransformation()const{return m_transformationMatrix;}
    const QString & name()const{ return m_name;}
    double getRadius()const{return m_radius;}
    /**
     * @brief setTextureIndex
     * @param i set m_activeTexture to m_textureIds[i]
     */
    void setActiveTextureIndex(int i)
      {m_activeTextureIndex = i;}

    /**
      * Set new center and invalidate surface.
      */
    void setCenter(const QVector3D & newVal);

    void setScale(double scale){m_scale = scale;}

    //for Debugging
    void showFrame(bool show){m_showFrame = show;}
    void showNormals(bool show){m_showNormals = show;}

protected:
    /**
     * @brief calculateIntersection Calculate intersection of line with plane defined by p1,p2,p3
     * @param p1
     * @param p2
     * @param p3
     * @param pLine Point on Line
     * @param lineDirection
     * @param a Multiple of p12
     * @param b Multiple of p13
     * @param intersection Coordinates of intersection
     * @return True if an intersection exists.
     */
    static bool calculateIntersection(const QVector3D & p1, const QVector3D & p2, const QVector3D & p3,
                                      const QVector3D & pLine, const QVector3D & lineDirection,
                                      double * a, double * b, QVector3D *intersection = NULL);

    void createNormals();
    void createFrame();

    /**
     * @brief init Initialize GLBody with defaults.
     */
    void init();
    /**
      * The name  of this object for debugging messages.
      */
    QString m_name;
    /**
      * The center of the enclosing sphere
      */
     QVector3D m_center;

     /**
      * @brief m_minCoordinate The left bottom back corner of the enclosing cube
      */
     QVector3D m_minCoordinate;
     /**
      * @brief m_maxCoordinate The right top front corner of the enclosing cube
      */
     QVector3D m_maxCoordinate;

     /**
       * The radius of the enclosing sphere
       */
     GLfloat m_radius;

     /**
       * The mode to be passed to glDrawArrays or glDrawElements e.g. GL_TRIANGLES, GL_TRIANGLE_STRIP
       */
     GLint m_drawingMode;

     /**
      * @brief m_animationActive Flag for a running animation
      */
     bool m_animationActive;
     /**
      * @brief m_animationStart The value of the animation state when this function is called.
      * e.g. 0.5 if the global animation process is already half finished.
      */
     double m_animationStart;
     /**
      * @brief m_animateForwards Animate to final state or back to start state
      */
     bool m_animateForwards;

    /** The array of points defining the surface.
     *  This *may be* a container not owned by this body.
     */
    QVector <GLPoint> * m_points;

    /**
     * @brief ownPointsContainer Set this Flag, if points container was created by this body.
     */
    bool m_ownPointsContainer;

    /**
     * @brief firstPoint The firstPoint for this body
     */
    int m_firstPoint;

    /**
     * @brief lastPoint The next point for this body. ( last point +1)
     */
    int m_nextPoint;

   /** The array with the indices. May be left empty. 
    */
    QVector <GLushort> * m_indices;

    /**
     * @brief ownPointsContainer Set this Flag, if points container was created by this body.
     */
    bool m_ownIndexContainer;

    /**
    * @brief startIndex The first index for this body
    */
   int m_firstIndex;

   /**
    * @brief indexCount The next index for this body. (last index + 1)
    */
   int m_nextIndex;

   /** The flag for a valid surface.
    */
    bool m_surfaceIsValid;

   /** The textures to be used.
    */
    QVector<GLuint> m_textureIds;
    /**
      * The index of the texture to be used in function draw()
      */
    GLuint m_activeTextureIndex;
    /** The tetxure files.
     */
    QStringList m_textureFilenames;


  /** The diffuse and ambient color for the body.
   */
   GLColorRgba m_color;

  /**
   * The specular color
   */
   GLColorRgba m_specularColor;

  /**
   * Shininess for specular color
   */
   int m_shininess;

   /**
     *  Flag for selected mode.
     */
   bool m_selected;

   QVector3D m_modelOffset;//Offset of model vertices from origin.

   /**
     * This matrix holds the basic transformation for the body and
     * should not be modified after first setting.
     */
   QMatrix4x4 m_transformationMatrix;

   /**
    * @brief m_drawMatrix
     * This matrix is multiplied with the modelview matrix prior to
     * rendering the body.
    */
   QMatrix4x4 m_drawMatrix;
   /**
    * @brief m_scale
    */
   double m_scale; //meters per logical unit
   /**
    * @brief findMinMaxCoordinates Calculate m_minCoordinate an m_maxCoordinate from vertex data.
    * Create frame if m_showFrame is set. Create normals if m_showNormals is set.
    */
   void findMinMaxCoordinates();

   //For debugging
   int m_firstNormalPoint;
   int m_nextNormalPoint;
   int m_firstFramePoint;
   int m_nextFramePoint;
   int m_firstNormalIndex;
   int m_nextNormalIndex;
   int m_firstFrameIndex;
   int m_nextFrameIndex;
   int m_firstHitPoint;
   int m_nextHitPoint;
   bool m_showNormals;
   bool m_showFrame;

};

#endif
