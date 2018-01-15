#include "glcube.h"

GLCube::GLCube(const QString & name,const QVector3D& lbb, const QVector3D & rtf,
               const GLColorRgba & color, const QString textureFile)
    :GLBody(name, 1.0, color,textureFile)
{
   m_lbb = lbb;
   m_rtf = rtf;
   m_radius = (lbb - rtf).length() / 2.0;
}

//Würfel. Texturkoordinaten sind gesetzt. Funktioniert mit cube.jpg
void GLCube::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLushort> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);
    //m_drawingMode = GL_POINTS; //Für Punkte
    //m_drawingMode = GL_TRIANGLES; //Für Dreiecke
    m_drawingMode = GL_QUADS;
    m_firstPoint = m_points->size();
    float faktorGroesse = m_rtf.x() - m_lbb.x();

    QVector3D vX = QVector3D(1.0,0.0,0.0);
    QVector3D vY = QVector3D(0.0,1.0,0.0);
    QVector3D vZ = QVector3D(0.0,0.0,1.0);

    QVector3D lbb = m_lbb;
    QVector3D rtf = m_rtf;
    QVector3D ltb = lbb + faktorGroesse * vY;
    QVector3D rtb = rtf - faktorGroesse * vZ;
    QVector3D rbb = lbb + faktorGroesse * vX;
    QVector3D rbf = rtf - faktorGroesse * vY;
    QVector3D lbf = lbb + faktorGroesse * vZ;
    QVector3D ltf = rtf - faktorGroesse * vX;

    //Vorne //Eins
    m_points->append(GLPoint(ltf, vZ, QVector3D(0.0, 1.0, 0.0), GLColorRgba::clRed));
    m_points->append(GLPoint(lbf, vZ, QVector3D(0.0, 0.0, 0.0), GLColorRgba::clRed));
    m_points->append(GLPoint(rbf, vZ, QVector3D(0.125, 0.0, 0.0), GLColorRgba::clRed));
    m_points->append(GLPoint(rtf, vZ, QVector3D(0.125, 1.0, 0.0), GLColorRgba::clRed));

    //Hinten //Sechs
    m_points->append(GLPoint(rtb, -vZ, QVector3D(0.5, 1.0, 0.0), GLColorRgba::clCyan));
    m_points->append(GLPoint(rbb, -vZ, QVector3D(0.5, 0.0, 0.0), GLColorRgba::clCyan));
    m_points->append(GLPoint(lbb, -vZ, QVector3D(0.625, 0.0, 0.0), GLColorRgba::clCyan));
    m_points->append(GLPoint(ltb, -vZ, QVector3D(0.625, 1.0, 0.0), GLColorRgba::clCyan));

    //Rechts //Drei
    m_points->append(GLPoint(rtf, vX, QVector3D(0.125, 1.0, 0.0), GLColorRgba::clBlue));
    m_points->append(GLPoint(rbf, vX, QVector3D(0.125, 0.0, 0.0), GLColorRgba::clBlue));
    m_points->append(GLPoint(rbb, vX, QVector3D(0.25, 0.0, 0.0), GLColorRgba::clBlue));
    m_points->append(GLPoint(rtb, vX, QVector3D(0.25, 1.0, 0.0), GLColorRgba::clBlue));

    //Links //Vier
    m_points->append(GLPoint(ltb, -vX, QVector3D(0.375, 1.0, 0.0), GLColorRgba::clYellow));
    m_points->append(GLPoint(lbb, -vX, QVector3D(0.375, 0.0, 0.0), GLColorRgba::clYellow));
    m_points->append(GLPoint(lbf, -vX, QVector3D(0.5, 0.0, 0.0), GLColorRgba::clYellow));
    m_points->append(GLPoint(ltf, -vX, QVector3D(0.5, 1.0, 0.0), GLColorRgba::clYellow));

    //Oben //Fünf
    m_points->append(GLPoint(ltb, vY, QVector3D(0.25, 1.0, 0.0), GLColorRgba::clGreen));
    m_points->append(GLPoint(ltf, vY, QVector3D(0.25, 0.0, 0.0), GLColorRgba::clGreen));
    m_points->append(GLPoint(rtf, vY, QVector3D(0.375, 0.0, 0.0), GLColorRgba::clGreen));
    m_points->append(GLPoint(rtb, vY, QVector3D(0.375, 1.0, 0.0), GLColorRgba::clGreen));

    //Unten //Zwei
    m_points->append(GLPoint(lbf, -vY, QVector3D(0.625, 1.0, 0.0), GLColorRgba::clWhite));
    m_points->append(GLPoint(lbb, -vY, QVector3D(0.625, 0.0, 0.0), GLColorRgba::clWhite));
    m_points->append(GLPoint(rbb, -vY, QVector3D(0.75, 0.0, 0.0), GLColorRgba::clWhite));
    m_points->append(GLPoint(rbf, -vY, QVector3D(0.75, 1.0, 0.0), GLColorRgba::clWhite));

    m_nextPoint = m_points->size();
}



//void GLCube::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLushort> *indexContainer)
//{
//    GLBody::makeSurface(pointContainer, indexContainer);
//    m_drawingMode = GL_POINTS; //Für Punkte
//    //m_drawingMode = GL_TRIANGLES; //Für Dreiecke
//    m_firstPoint = m_points->size();
//    float faktorGroesse = m_rtf.x() - m_lbb.x();

//    QVector3D vX = QVector3D(1.0,0.0,0.0);
//    QVector3D vY = QVector3D(0.0,1.0,0.0);
//    QVector3D vZ = QVector3D(0.0,0.0,1.0);

//    QVector3D lbb = m_lbb;
//    QVector3D rtf = m_rtf;
//    QVector3D ltb = lbb + faktorGroesse * vY;
//    QVector3D rtb = rtf - faktorGroesse * vZ;
//    QVector3D rbb = lbb + faktorGroesse * vX;
//    QVector3D rbf = rtf - faktorGroesse * vY;
//    QVector3D lbf = lbb + faktorGroesse * vZ;
//    QVector3D ltf = rtf - faktorGroesse * vX;

//    //Vorne
//    m_points->append(GLPoint(ltf, vZ, QVector3D(0, 0, 0), GLColorRgba::clRed));
//    m_points->append(GLPoint(rtf, vZ, QVector3D(0, 0, 0), GLColorRgba::clRed));
//    m_points->append(GLPoint(lbf, vZ, QVector3D(0, 0, 0), GLColorRgba::clRed));

//    m_points->append(GLPoint(rbf, vZ, QVector3D(0, 0, 0), GLColorRgba::clRed));
//    m_points->append(GLPoint(lbf, vZ, QVector3D(0, 0, 0), GLColorRgba::clRed));
//    m_points->append(GLPoint(rtf, vZ, QVector3D(0, 0, 0), GLColorRgba::clRed));

//    //Hinten
//    m_points->append(GLPoint(rtb, -vZ, QVector3D(0, 0, 0), GLColorRgba::clCyan));
//    m_points->append(GLPoint(ltb, -vZ, QVector3D(0, 0, 0), GLColorRgba::clCyan));
//    m_points->append(GLPoint(rbb, -vZ, QVector3D(0, 0, 0), GLColorRgba::clCyan));

//    m_points->append(GLPoint(lbb, -vZ, QVector3D(0, 0, 0), GLColorRgba::clCyan));
//    m_points->append(GLPoint(rbb, -vZ, QVector3D(0, 0, 0), GLColorRgba::clCyan));
//    m_points->append(GLPoint(ltb, -vZ, QVector3D(0, 0, 0), GLColorRgba::clCyan));

//    //Rechts
//    m_points->append(GLPoint(rtf, vX, QVector3D(0, 0, 0), GLColorRgba::clBlue));
//    m_points->append(GLPoint(rtb, vX, QVector3D(0, 0, 0), GLColorRgba::clBlue));
//    m_points->append(GLPoint(rbf, vX, QVector3D(0, 0, 0), GLColorRgba::clBlue));

//    m_points->append(GLPoint(rbb, vX, QVector3D(0, 0, 0), GLColorRgba::clBlue));
//    m_points->append(GLPoint(rbf, vX, QVector3D(0, 0, 0), GLColorRgba::clBlue));
//    m_points->append(GLPoint(rtb, vX, QVector3D(0, 0, 0), GLColorRgba::clBlue));

//    //Links
//    m_points->append(GLPoint(ltb, -vX, QVector3D(0, 0, 0), GLColorRgba::clYellow));
//    m_points->append(GLPoint(ltf, -vX, QVector3D(0, 0, 0), GLColorRgba::clYellow));
//    m_points->append(GLPoint(lbb, -vX, QVector3D(0, 0, 0), GLColorRgba::clYellow));

//    m_points->append(GLPoint(lbf, -vX, QVector3D(0, 0, 0), GLColorRgba::clYellow));
//    m_points->append(GLPoint(lbb, -vX, QVector3D(0, 0, 0), GLColorRgba::clYellow));
//    m_points->append(GLPoint(ltf, -vX, QVector3D(0, 0, 0), GLColorRgba::clYellow));

//    //Oben
//    m_points->append(GLPoint(ltb, vY, QVector3D(0, 0, 0), GLColorRgba::clGreen));
//    m_points->append(GLPoint(rtb, vY, QVector3D(0, 0, 0), GLColorRgba::clGreen));
//    m_points->append(GLPoint(ltf, vY, QVector3D(0, 0, 0), GLColorRgba::clGreen));

//    m_points->append(GLPoint(rtf, vY, QVector3D(0, 0, 0), GLColorRgba::clGreen));
//    m_points->append(GLPoint(ltf, vY, QVector3D(0, 0, 0), GLColorRgba::clGreen));
//    m_points->append(GLPoint(rtb, vY, QVector3D(0, 0, 0), GLColorRgba::clGreen));

//    //Unten
//    m_points->append(GLPoint(lbf, -vY, QVector3D(0, 0, 0), GLColorRgba::clWhite));
//    m_points->append(GLPoint(rbf, -vY, QVector3D(0, 0, 0), GLColorRgba::clWhite));
//    m_points->append(GLPoint(lbb, -vY, QVector3D(0, 0, 0), GLColorRgba::clWhite));

//    m_points->append(GLPoint(rbb, -vY, QVector3D(0, 0, 0), GLColorRgba::clWhite));
//    m_points->append(GLPoint(lbb, -vY, QVector3D(0, 0, 0), GLColorRgba::clWhite));
//    m_points->append(GLPoint(rbf, -vY, QVector3D(0, 0, 0), GLColorRgba::clWhite));

//    m_nextPoint = m_points->size();
//}
