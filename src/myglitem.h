#ifndef MYGLITEM_H
#define MYGLITEM_H
#include "glitem.h"
#include "glcube.h"
#include "glsphere.h"
#include "gldisc.h"
#include "glquad.h"
#include "glmouseray.h"
#include <QMouseEvent>


class MyGlItem : public GLItem
{
public:
    MyGlItem();
    virtual void paintUnderQmlScene();
    virtual void paintOnTopOfQmlScene();



    int m_firstTrianglePoint;
    int m_lastTrianglePoint;
    float m_scaling_factor;

    int m_firstNormalIndex;
    int m_numberOfNormalVertices;

    void createF(double height);
    void createCube(const QVector3D &Ulbb, const QVector3D &Urtf);

    void drawF(double height);
    void drawCube();
    void createVisibleNormals();
    void drawNormals();
    void drawWhite();
    void drawBlack();
    void initializeDice();
    virtual void mousePressed(int x, int y) override;
    virtual bool isHit(QVector3D p1, QVector3D p2);
    QPoint punktInEbene(QVector3D p1, QVector3D p2);
    bool discAufFeld(QVector3D feldmitte);
    //void doSynchronizeThreads();
private:
    void createTriangles();
    void setupGeometry();
    void drawTriangles();
    int m_taskNumber;
    float m_radius;
    GLCube * m_cube;
    GLSphere * m_sphere;
    GLDisc * m_disc_white;
    GLDisc * m_disc_black;
    GLQuad * m_quad;
    GLMouseRay * m_mouseRay;
    QMouseEvent * m_lastMouseEvent;
    //White
    QVector3D w_eins;
    QVector3D w_zwei;
    QVector3D w_drei;
    QVector3D w_vier;
    QVector3D w_fuenf;
    QVector3D w_sechs;
    QVector3D w_sieben;
    QVector3D w_acht;
    QVector3D w_neun;
    QVector3D w_zehn;
    QVector3D w_elf;
    QVector3D w_zwoelf;
    //Black
    QVector3D b_eins;
    QVector3D b_zwei;
    QVector3D b_drei;
    QVector3D b_vier;
    QVector3D b_fuenf;
    QVector3D b_sechs;
    QVector3D b_sieben;
    QVector3D b_acht;
    QVector3D b_neun;
    QVector3D b_zehn;
    QVector3D b_elf;
    QVector3D b_zwoelf;

    QVector3D m_getroffenerDisc;

};

#endif // MYGLITEM_H
