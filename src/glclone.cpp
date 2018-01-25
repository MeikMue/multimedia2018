#include "glclone.h"
#include <math.h>
#include "glbody.h"

GLClone::GLClone(const QString &name, float radiusBot, float radiusTop, const QString textureFile, const GLColorRgba &color, int stacks, int slices)
  :GLBody(name, radiusBot,color, textureFile)
{

    m_drawingMode = GL_TRIANGLE_STRIP;
    //m_drawingMode = GL_LINE_STRIP;
    m_height = 4;
    //m_FieldCoord = fieldCoord;
    m_stacks = stacks;
    m_slices = slices;
    m_radiusBot = radiusBot;
    m_radiusTop = radiusTop;
    m_color = color;

}

//* normal v_Z
void GLClone::makeSurface(QVector<GLPoint> * pointContainer, QVector<GLushort> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);
    QVector3D southPole = v_Zero; //unit vector, must be scaled by radiusBot later
    QVector3D northPole = southPole + v_Z * m_height;
    QVector3D vertex = -v_Y * m_radiusBot;
    QVector3D top = -v_Y * m_radiusTop;
    QVector3D normal;
    QVector3D texCoord;
    QVector3D texCoordTop;
    QMatrix4x4 longitudeMatrix;
    int iSouthPole = 0; //indices for the poles
    int iNorthPole = 0;

    //start with south pole
    m_firstPoint = m_points->size();
    m_firstIndex = m_indices->size();
    iSouthPole = m_firstPoint;
    m_points->append(GLPoint(southPole,      //vertex
                            -v_Z,            //normal
                           QVector3D(0.5, 0.5, 0.0)//texCoord QVector3D(0.5, 0.5, 0.0)
                           ));

    int slice;
    QVector3D texCenter(0.5,0.5,0.0);

    for(slice = 0; slice <= m_slices; slice ++)
    {
        vertex = -v_Y * m_radiusBot;
        top = -v_Y * m_radiusTop;
        longitudeMatrix.setToIdentity();//always start from scratch
        if(slice != m_slices) //do not rotate by 360 deg for last points, use 0 deg to match first points
            longitudeMatrix.rotate(slice * 360.0 / m_slices, -v_Z);
        //bottom disc 1
        vertex = vertex * longitudeMatrix;
        top = top *longitudeMatrix;
        normal = -v_Z;
        texCoord = texCenter + QVector3D(0.5 * vertex.x() / m_radiusBot, -0.5 * vertex.y() / m_radiusBot, 0.0);
        texCoordTop = texCenter + QVector3D(0.5 * top.x() / m_radiusTop, -0.5 * top.y() / m_radiusTop, 0.0);
        m_points->append(GLPoint(vertex , normal, texCoord));

        //lower cylinder 2
        normal = vertex;

        //leave tex coord as it is
        m_points->append(GLPoint(vertex , normal, texCoord));

        //upper cylinder 3
        vertex += northPole;

        top += northPole;
        m_points->append(GLPoint(top, normal, texCoordTop));

        //top disc 4
        normal = v_Z;
        m_points->append(GLPoint(top, normal, texCoord));
    }

    //end with north pole
    iNorthPole = m_points->size();
    m_points->append(GLPoint(northPole,      //vertex
                            v_Z,               //normal
                           QVector3D(0.5, 0.5, 0.0),//texCoord
                           m_color));
    //m_nextPoint = m_points.size();

    for(slice = 0; slice < m_slices; slice += 2)
    {
        int leftSlice = iSouthPole + 4 * slice;
        int rightSlice = iSouthPole + 4 * (slice + 1);
        //we go upwards from south pole to north pole first
        m_indices->append(iSouthPole);
        m_indices->append(leftSlice + 1); //left bottom disc
        m_indices->append(rightSlice + 1); //right bottom disc
        m_indices->append(rightSlice + 2); //right bottom cylinder
        m_indices->append(leftSlice + 2); //left bottom cylinder
        m_indices->append(rightSlice + 3); //right top cylinder
        m_indices->append(leftSlice + 3 ); //left top cylinder
        m_indices->append(leftSlice + 4); //left top disc
        m_indices->append(rightSlice + 4); //right top disc
        m_indices->append(iNorthPole);
        //we go downwards, back to southpole
        leftSlice += 4;
        rightSlice += 4;
        m_indices->append(rightSlice + 4); //right top disc
        m_indices->append(leftSlice + 4); //left top disc
        m_indices->append(rightSlice + 3); //right top cylinder
        m_indices->append(leftSlice + 3); //left top cylinder
        m_indices->append(rightSlice + 2); //right bottom cylinder
        m_indices->append(leftSlice + 2); //left bottom cylinder
        m_indices->append(leftSlice + 1); //left bottom disc
        m_indices->append(rightSlice + 1); //right bottom disc
        //southpole will be added in next slice
    }

    m_indices->append(iSouthPole); //finally add south pole

    m_nextPoint = m_points->size();
    m_nextIndex = m_indices->size();
//    qDebug() << "Groesse: ";
//    qDebug() << m_points->size();
}

void GLClone::setSelected(bool selected)
{
    m_selected = selected;
}

