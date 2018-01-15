#include "myglitem.h"
#include <QQuickWindow>

MyGlItem::MyGlItem()
{
    m_backgroundColor = GLColorRgba::clBlack;

    /*
     * 0 entspricht einem Würfel
     * 1 entspricht dem F
     * Stand Blatt 5
     */
    m_taskNumber = 9000;

    m_radius = 1.0f;

    //Für Blatt 6 createCube wird nicht mehr benötigt
    m_cube = new GLCube("MyCube", v_Zero, v_XYZ, GLColorRgba::clBlue, "../MM2017/textures/cube.jpg");
    m_sphere = new GLSphere("MySphere", 5.0, GLColorRgba::clBlue, "../MM2017/textures/earthmap1024x512.jpg");
    m_disc_white = new GLDisc("MyDiscWhite", m_radius, "../MM2017/textures/white_disc.jpg");
    m_disc_black = new GLDisc("MyDiscBlack", m_radius, "../MM2017/textures/black_disc.jpg");
    initializeDice();
    m_quad = new GLQuad("MyQuad");
    m_mouseRay = new GLMouseRay("MouseRay");
    m_lastMouseEvent = NULL;
}

void MyGlItem::paintUnderQmlScene()
{

}

void MyGlItem::paintOnTopOfQmlScene()
{
    m_renderer->setColorArrayEnabled(false);
    m_renderer->setLightingEnabled(true);
    m_renderer->setTextureEnabled(true);
    m_renderer->setAmbientLightBrightness(0.5);

    //Blatt 3 Aufgabe 1
    //drawCube();

    //Blatt 3 Aufgabe 2
//    m_renderer->scale(QVector3D(1.0, 5.0, 1.0));
//    drawCube();
//    m_renderer->scale(QVector3D(1.0, 0.2, 1.0));
//    m_renderer->translate(1.0, 2.0 * m_scaling_factor * 0.2, 0.0);
//    m_renderer->scale(QVector3D(2.0, 1.0, 1.0));
//    drawCube();
//    m_renderer->scale(QVector3D(0.5, 1.0, 1.0));
//    m_renderer->translate(0.0, 2.0  * m_scaling_factor * 0.2, 0.0);
//    m_renderer->scale(QVector3D(3.0, 1.0, 1.0));
//    drawCube();


      switch(m_taskNumber)
    {
        case 0:
            drawCube();
            drawNormals();
            break;
        case 1:
            //Blatt 5
            m_renderer->scale(QVector3D(1.0, 5.0, 1.0));
            drawCube();
            drawNormals();
            m_renderer->scale(QVector3D(1.0, 0.2, 1.0));
            m_renderer->translate(1.0, 2.0 * m_scaling_factor * 0.2, 0.0);
            m_renderer->scale(QVector3D(2.0, 1.0, 1.0));
            drawCube();
            drawNormals();
            m_renderer->scale(QVector3D(0.5, 1.0, 1.0));
            m_renderer->translate(0.0, 2.0  * m_scaling_factor * 0.2, 0.0);
            m_renderer->scale(QVector3D(3.0, 1.0, 1.0));
            drawCube();
            drawNormals();
            break;
        default:
            break;
    }

    //Blatt 6
    //m_cube->draw(renderer());
    //m_sphere->draw(renderer());

    //Blatt 8
//    m_quad->draw(renderer());
//    m_mouseRay->draw(renderer());
//    drawWhite();
//    drawBlack();


    //Blatt 9
    //m_cube->draw(renderer()); //Würfel
    m_sphere->draw(renderer()); //Weltkugel
}

bool MyGlItem::isHit(QVector3D p1, QVector3D p2)
{
    bool ergebnis = false;
    QPoint punktZEbene = punktInEbene(p1, p2);
    if (!(punktZEbene.x() >= 8 || punktZEbene.x() < -8 || punktZEbene.y() >= 8 || punktZEbene.y() < -8))
    {
        QVector3D lineVector = p2 - p1;
        QVector3D center = m_quad->fieldToPosition(punktZEbene);
        double area = QVector3D::crossProduct((center - p1), lineVector).length();
        double distance = area / lineVector.length();
        //qDebug("Radius: %f", radius);
        //prüfen ob Vector auf Feldboden getroffen wurde und Vector auf dem Feld steht
        ergebnis = distance < m_radius && discAufFeld(center);
    }
    else
    {
        QVector3D amArschDerWelt = QVector3D(1000,1000,1000);
        m_getroffenerDisc = amArschDerWelt;
    }
    return ergebnis;
}

bool MyGlItem::discAufFeld(QVector3D feldmitte)
{
    bool vectorGetroffen = false;
    if (feldmitte == w_eins)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == w_zwei)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == w_drei)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == w_vier)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == w_fuenf)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == w_sechs)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == w_sieben)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == w_acht)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == w_neun)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == w_zehn)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == w_elf)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == w_zwoelf)
    {
        vectorGetroffen = true;
    }

    else if (feldmitte == b_eins)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == b_zwei)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == b_drei)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == b_vier)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == b_fuenf)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == b_sechs)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == b_sieben)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == b_acht)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == b_neun)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == b_zehn)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == b_elf)
    {
        vectorGetroffen = true;
    }
    else if (feldmitte == b_zwoelf)
    {
        vectorGetroffen = true;
    }
    else
    {
        qDebug() << "Kein Disc auf dem Feld";
    }

    if (vectorGetroffen)
    {
        m_getroffenerDisc = feldmitte;
    }
    return vectorGetroffen;
}

QPoint MyGlItem::punktInEbene(QVector3D p1, QVector3D p2)
{
    QVector3D p1p2 = p2 - p1;
    QVector3D vectorZNull = p1 + (p1.z()/p1p2.z()*-1)*p1p2;
    //qDebug() << "Z Wert: " <<vectorZNull.z();
    return QPoint(vectorZNull.x(), vectorZNull.y());
}

void MyGlItem::mousePressed(int x, int y)
{
    qDebug() << "MyGlItem::mousePressed at x:" << x << " y: " << y;
    QPoint *point = new QPoint(x, y);
    //m_mouseRay->setMousePosition(*point);

    QVector3D nearPoint, farPoint;
    QPoint mousePosition = *point;
    m_renderer->calculateMousePoints(&nearPoint, &farPoint, mousePosition);

    nearPoint.setZ (nearPoint.z ()-3.0f);
    farPoint.setZ (farPoint.z ()-3.0f);

    //nur mit doSynchronisThread
    //m_lastMouseEvent->setAccepted(false);

    if (isHit(nearPoint, farPoint))
    {
        qDebug() << "Treffer";
        //window
    }
    else
    {
        qDebug() << "Kein Treffer";
    }
    if(window())
        window()->update();
}

void MyGlItem::initializeDice()
{
    //White
    w_eins = QVector3D(-7, -7, 0);
    w_zwei = QVector3D(-3, -7, 0);
    w_drei = QVector3D(1, -7, 0);
    w_vier = QVector3D(5, -7, 0);
    w_fuenf = QVector3D(-5, -5, 0);
    w_sechs = QVector3D(-1, -5, 0);
    w_sieben = QVector3D(3, -5, 0);
    w_acht = QVector3D(7, -5, 0);
    w_neun = QVector3D(-7, -3, 0);
    w_zehn = QVector3D(-3, -3, 0);
    w_elf = QVector3D(1, -3, 0);
    w_zwoelf = QVector3D(5, -3, 0);

    //Black
    b_eins = QVector3D(7, 7, 0);
    b_zwei = QVector3D(3, 7, 0);
    b_drei = QVector3D(-1, 7, 0);
    b_vier = QVector3D(-5, 7, 0);
    b_fuenf = QVector3D(5, 5, 0);
    b_sechs = QVector3D(1, 5, 0);
    b_sieben = QVector3D(-3, 5, 0);
    b_acht = QVector3D(-7, 5, 0);
    b_neun = QVector3D(7, 3, 0);
    b_zehn = QVector3D(3, 3, 0);
    b_elf = QVector3D(-1, 3, 0);
    b_zwoelf = QVector3D(-5, 3, 0);
}

void MyGlItem::drawWhite()
{
    //Stein eins nach unten links legen
    m_renderer->pushMvMatrix();
    m_renderer->translate(w_eins);
    if (m_getroffenerDisc == w_eins)
    {
        m_disc_white->setSelected(true);
    }
    else
    {
        m_disc_white->setSelected(false);
    }
    m_disc_white->draw(renderer());
    //Stein zwei
    m_renderer->pushMvMatrix();
    m_renderer->translate(w_zwei-w_eins);
    if (m_getroffenerDisc == w_zwei)
    {
        m_disc_white->setSelected(true);
    }
    else
    {
        m_disc_white->setSelected(false);
    }
    m_disc_white->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein drei
    m_renderer->pushMvMatrix();
    m_renderer->translate(w_drei-w_eins);
    if (m_getroffenerDisc == w_drei)
    {
        m_disc_white->setSelected(true);
    }
    else
    {
        m_disc_white->setSelected(false);
    }
    m_disc_white->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein vier
    m_renderer->pushMvMatrix();
    m_renderer->translate(w_vier-w_eins);
    if (m_getroffenerDisc == w_vier)
    {
        m_disc_white->setSelected(true);
    }
    else
    {
        m_disc_white->setSelected(false);
    }
    m_disc_white->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein fuenf
    m_renderer->pushMvMatrix();
    m_renderer->translate(w_fuenf-w_eins);
    if (m_getroffenerDisc == w_fuenf)
    {
        m_disc_white->setSelected(true);
    }
    else
    {
        m_disc_white->setSelected(false);
    }
    m_disc_white->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein sechs
    m_renderer->pushMvMatrix();
    m_renderer->translate(w_sechs-w_eins);
    if (m_getroffenerDisc == w_sechs)
    {
        m_disc_white->setSelected(true);
    }
    else
    {
        m_disc_white->setSelected(false);
    }
    m_disc_white->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein sieben
    m_renderer->pushMvMatrix();
    m_renderer->translate(w_sieben-w_eins);
    if (m_getroffenerDisc == w_sieben)
    {
        m_disc_white->setSelected(true);
    }
    else
    {
        m_disc_white->setSelected(false);
    }
    m_disc_white->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein acht
    m_renderer->pushMvMatrix();
    m_renderer->translate(w_acht-w_eins);
    if (m_getroffenerDisc == w_acht)
    {
        m_disc_white->setSelected(true);
    }
    else
    {
        m_disc_white->setSelected(false);
    }
    m_disc_white->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein neun
    m_renderer->pushMvMatrix();
    m_renderer->translate(w_neun-w_eins);
    if (m_getroffenerDisc == w_neun)
    {
        m_disc_white->setSelected(true);
    }
    else
    {
        m_disc_white->setSelected(false);
    }
    m_disc_white->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein zehn
    m_renderer->pushMvMatrix();
    m_renderer->translate(w_zehn-w_eins);
    if (m_getroffenerDisc == w_zehn)
    {
        m_disc_white->setSelected(true);
    }
    else
    {
        m_disc_white->setSelected(false);
    }
    m_disc_white->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein elf
    m_renderer->pushMvMatrix();
    m_renderer->translate(w_elf-w_eins);
    if (m_getroffenerDisc == w_elf)
    {
        m_disc_white->setSelected(true);
    }
    else
    {
        m_disc_white->setSelected(false);
    }
    m_disc_white->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein zwoelf
    m_renderer->pushMvMatrix();
    m_renderer->translate(w_zwoelf-w_eins);
    if (m_getroffenerDisc == w_zwoelf)
    {
        m_disc_white->setSelected(true);
    }
    else
    {
        m_disc_white->setSelected(false);
    }
    m_disc_white->draw(renderer());
    m_renderer->popMvMatrix();

    m_renderer->popMvMatrix();



}

void MyGlItem::drawBlack()
{
    //Stein eins nach unten links legen
    m_renderer->pushMvMatrix();
    m_renderer->translate(b_eins);
    if (m_getroffenerDisc == b_eins)
    {
        m_disc_black->setSelected(true);
    }
    else
    {
        m_disc_black->setSelected(false);
    }
    m_disc_black->draw(renderer());
    //Stein zwei
    m_renderer->pushMvMatrix();
    m_renderer->translate(b_zwei-b_eins);
    if (m_getroffenerDisc == b_zwei)
    {
        m_disc_black->setSelected(true);
    }
    else
    {
        m_disc_black->setSelected(false);
    }
    m_disc_black->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein drei
    m_renderer->pushMvMatrix();
    m_renderer->translate(b_drei-b_eins);
    if (m_getroffenerDisc == b_drei)
    {
        m_disc_black->setSelected(true);
    }
    else
    {
        m_disc_black->setSelected(false);
    }
    m_disc_black->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein vier
    m_renderer->pushMvMatrix();
    m_renderer->translate(b_vier-b_eins);
    if (m_getroffenerDisc == b_vier)
    {
        m_disc_black->setSelected(true);
    }
    else
    {
        m_disc_black->setSelected(false);
    }
    m_disc_black->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein fuenf
    m_renderer->pushMvMatrix();
    m_renderer->translate(b_fuenf-b_eins);
    if (m_getroffenerDisc == b_fuenf)
    {
        m_disc_black->setSelected(true);
    }
    else
    {
        m_disc_black->setSelected(false);
    }
    m_disc_black->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein sechs
    m_renderer->pushMvMatrix();
    m_renderer->translate(b_sechs-b_eins);
    if (m_getroffenerDisc == b_sechs)
    {
        m_disc_black->setSelected(true);
    }
    else
    {
        m_disc_black->setSelected(false);
    }
    m_disc_black->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein sieben
    m_renderer->pushMvMatrix();
    m_renderer->translate(b_sieben-b_eins);
    if (m_getroffenerDisc == b_sieben)
    {
        m_disc_black->setSelected(true);
    }
    else
    {
        m_disc_black->setSelected(false);
    }
    m_disc_black->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein acht
    m_renderer->pushMvMatrix();
    m_renderer->translate(b_acht-b_eins);
    if (m_getroffenerDisc == b_acht)
    {
        m_disc_black->setSelected(true);
    }
    else
    {
        m_disc_black->setSelected(false);
    }
    m_disc_black->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein neun
    m_renderer->pushMvMatrix();
    m_renderer->translate(b_neun-b_eins);
    if (m_getroffenerDisc == b_neun)
    {
        m_disc_black->setSelected(true);
    }
    else
    {
        m_disc_black->setSelected(false);
    }
    m_disc_black->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein zehn
    m_renderer->pushMvMatrix();
    m_renderer->translate(b_zehn-b_eins);
    if (m_getroffenerDisc == b_zehn)
    {
        m_disc_black->setSelected(true);
    }
    else
    {
        m_disc_black->setSelected(false);
    }
    m_disc_black->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein elf
    m_renderer->pushMvMatrix();
    m_renderer->translate(b_elf-b_eins);
    if (m_getroffenerDisc == b_elf)
    {
        m_disc_black->setSelected(true);
    }
    else
    {
        m_disc_black->setSelected(false);
    }
    m_disc_black->draw(renderer());
    m_renderer->popMvMatrix();
    //Stein zwoelf
    m_renderer->pushMvMatrix();
    m_renderer->translate(b_zwoelf-b_eins);
    if (m_getroffenerDisc == b_zwoelf)
    {
        m_disc_black->setSelected(true);
    }
    else
    {
        m_disc_black->setSelected(false);
    }
    m_disc_black->draw(renderer());
    m_renderer->popMvMatrix();

    m_renderer->popMvMatrix();



}

void MyGlItem::drawCube()
{
    drawTriangles();
}

void MyGlItem::drawTriangles()
{
    if(m_lastTrianglePoint > m_lastAxesPoint)
    {
        //m_renderer->setColorArrayEnabled(true);
        //m_renderer->setLightingEnabled(true);
        //m_renderer->setTextureEnabled(false);
        int stride = sizeof(GLPoint);
        m_renderer->activateAttributeArray(GLESRenderer::VERTEX_LOCATION, m_points[0].vertexPointer(), stride);
        m_renderer->activateAttributeArray(GLESRenderer::COLOR_LOCATION, m_points[0].colorPointer(), stride);
        m_renderer->activateAttributeArray(GLESRenderer::NORMAL_LOCATION, m_points[0].normalPointer(), stride);

        glDrawArrays(GL_TRIANGLES, m_firstTrianglePoint, m_lastTrianglePoint - m_firstTrianglePoint + 1);

        m_renderer->disableAttributeArrays();

        m_renderer->setColorArrayEnabled(m_colorArrayEnabled);
        m_renderer->setLightingEnabled(m_lightingEnabled);
    }
}

void MyGlItem::createTriangles()
{
    m_firstTrianglePoint = m_points.size();

    m_points.append(GLPoint(QVector3D(0,0,0), QVector3D(0, 0, 1), QVector3D(0,0,0), GLColorRgba::clRed));
    m_points.append(GLPoint(QVector3D(2,0,0), QVector3D(0, 0, 1), QVector3D(0,0,0), GLColorRgba::clGreen));
    m_points.append(GLPoint(QVector3D(0,2,0), QVector3D(0, 0, 1), QVector3D(0,0,0), GLColorRgba::clBlue));

    m_lastTrianglePoint = m_points.size() -1;
}

//void MyGlItem::doSynchronizeThreads()
//{
//    if(m_lastMouseEvent && !m_lastMouseEvent->isAccepted()) //last mouse event still pending
//    {
//        m_disc_white->invalidateSurface();
//        m_disc_black->invalidateSurface();
//        //m_mouseRay->setMousePosition(m_lastMouseEvent->pos());
//        m_lastMouseEvent->setAccepted(true);
//    }
//}



void MyGlItem::setupGeometry()
{
    m_drawAxes = false;

    GLItem::setupGeometry();

    //Blatt 3
    //createF(3.7);
    //drawF(32.50);


     // Blatt5
    switch(m_taskNumber)
    {
        case 0:
            createCube(QVector3D(0,0,0), QVector3D(1,1,1));
            break;
        case 1:
            drawF(5);
            break;

    }
    //createVisibleNormals();


}

void MyGlItem::drawNormals()
{
    if(m_numberOfNormalVertices - m_firstNormalIndex == 0) //We have no axes
    {
        printf("drawNormals() called");
    }

    GLfloat lineWidth[4]; //4 floats, just for safety
    glGetFloatv(GL_LINE_WIDTH, lineWidth);
    glLineWidth(1.0);
    //m_renderer->setColorArrayEnabled(false);
    m_renderer->setLightingEnabled(false);
    int stride = sizeof(GLPoint);
    m_renderer->activateAttributeArray(GLESRenderer::VERTEX_LOCATION, m_points[0].vertexPointer(), stride);
    m_renderer->activateAttributeArray(GLESRenderer::COLOR_LOCATION, m_points[0].colorPointer(), stride);

    glDrawArrays(GL_LINES, m_firstNormalIndex, m_numberOfNormalVertices);
    m_renderer->setLightingEnabled(m_lightingEnabled);
}

void MyGlItem::createVisibleNormals()
{
    m_firstNormalIndex = m_points.size();
    for (int i = m_firstTrianglePoint; i <= m_lastTrianglePoint; i++)
    {
        m_points.append(GLPoint(m_points.at(i).vertex(), v_Y, v_Zero, GLColorRgba::clWhite));
        m_points.append(GLPoint(m_points.at(i).vertex() + m_points.at(i).normal(), v_Y, v_Zero, GLColorRgba::clWhite));
    }
    m_numberOfNormalVertices = m_points.size() - m_firstNormalIndex;

}

void MyGlItem::drawF(double height)
{
    m_scaling_factor = height;
    m_firstTrianglePoint = m_points.size();
    createCube(QVector3D(0,0,0), QVector3D(height/5, height/5, height/5));
    m_lastTrianglePoint = m_points.size() -1;
}

void MyGlItem::createF(double height)
{
    m_firstTrianglePoint = m_points.size();
    //Turm
    createCube(QVector3D(0,0,0), QVector3D(height/5, height/5, height/5));
    createCube(QVector3D(0, height/5, 0), QVector3D(height/5, 2*height/5, height/5));
    createCube(QVector3D(0, 2*height/5, 0), QVector3D(height/5, 3*height/5, height/5));
    createCube(QVector3D(0, 3*height/5, 0), QVector3D(height/5, 4*height/5, height/5));
    createCube(QVector3D(0, 4*height/5, 0), QVector3D(height/5, 5*height/5, height/5));
    //Erster Strich
    createCube(QVector3D(height/5, 2*height/5,0), QVector3D(2*height/5, 3*height/5, height/5));
    createCube(QVector3D(2*height/5, 2*height/5,0), QVector3D(3*height/5, 3*height/5, height/5));
    //Zweiter Strich
    createCube(QVector3D(height/5, 4*height/5,0), QVector3D(2*height/5, 5*height/5, height/5));
    createCube(QVector3D(2*height/5, 4*height/5,0), QVector3D(3*height/5, 5*height/5, height/5));
    createCube(QVector3D(3*height/5, 4*height/5,0), QVector3D(4*height/5, 5*height/5, height/5));
    m_lastTrianglePoint = m_points.size() -1;
}

/**
Corner vertices of the cube

    ltb_____________rtb
     /            /|
    /            / |
ltf/____________/rtf
   |   |        |  |
   |   |        |  |
   |lbb|________|__|rbb
   |  /         |  /
   | /          | /
lbf|/___________|/rbf

*/
void MyGlItem::createCube(const QVector3D & Ulbb, const QVector3D &Urtf)
{
    float faktorGroesse = Urtf.x() - Ulbb.x();

    QVector3D vX = QVector3D(1.0,0.0,0.0);
    QVector3D vY = QVector3D(0.0,1.0,0.0);
    QVector3D vZ = QVector3D(0.0,0.0,1.0);

    QVector3D lbb = Ulbb;
    QVector3D rtf = Urtf;
    QVector3D ltb = lbb + faktorGroesse * vY;
    QVector3D rtb = rtf - faktorGroesse * vZ;
    QVector3D rbb = lbb + faktorGroesse * vX;
    QVector3D rbf = rtf - faktorGroesse * vY;
    QVector3D lbf = lbb + faktorGroesse * vZ;
    QVector3D ltf = rtf - faktorGroesse * vX;

   switch(m_taskNumber)
   {
       case 0:
            m_firstTrianglePoint = m_points.size();
            break;
   }


    //Vorne
    m_points.append(GLPoint(ltf, vZ, QVector3D(0, 0, 0), GLColorRgba::clRed));
    m_points.append(GLPoint(rtf, vZ, QVector3D(0, 0, 0), GLColorRgba::clRed));
    m_points.append(GLPoint(lbf, vZ, QVector3D(0, 0, 0), GLColorRgba::clRed));

    m_points.append(GLPoint(rbf, vZ, QVector3D(0, 0, 0), GLColorRgba::clRed));
    m_points.append(GLPoint(lbf, vZ, QVector3D(0, 0, 0), GLColorRgba::clRed));
    m_points.append(GLPoint(rtf, vZ, QVector3D(0, 0, 0), GLColorRgba::clRed));

    //Hinten
    m_points.append(GLPoint(rtb, -vZ, QVector3D(0, 0, 0), GLColorRgba::clCyan));
    m_points.append(GLPoint(ltb, -vZ, QVector3D(0, 0, 0), GLColorRgba::clCyan));
    m_points.append(GLPoint(rbb, -vZ, QVector3D(0, 0, 0), GLColorRgba::clCyan));

    m_points.append(GLPoint(lbb, -vZ, QVector3D(0, 0, 0), GLColorRgba::clCyan));
    m_points.append(GLPoint(rbb, -vZ, QVector3D(0, 0, 0), GLColorRgba::clCyan));
    m_points.append(GLPoint(ltb, -vZ, QVector3D(0, 0, 0), GLColorRgba::clCyan));

    //Rechts
    m_points.append(GLPoint(rtf, vX, QVector3D(0, 0, 0), GLColorRgba::clBlue));
    m_points.append(GLPoint(rtb, vX, QVector3D(0, 0, 0), GLColorRgba::clBlue));
    m_points.append(GLPoint(rbf, vX, QVector3D(0, 0, 0), GLColorRgba::clBlue));

    m_points.append(GLPoint(rbb, vX, QVector3D(0, 0, 0), GLColorRgba::clBlue));
    m_points.append(GLPoint(rbf, vX, QVector3D(0, 0, 0), GLColorRgba::clBlue));
    m_points.append(GLPoint(rtb, vX, QVector3D(0, 0, 0), GLColorRgba::clBlue));

    //Links
    m_points.append(GLPoint(ltb, -vX, QVector3D(0, 0, 0), GLColorRgba::clYellow));
    m_points.append(GLPoint(ltf, -vX, QVector3D(0, 0, 0), GLColorRgba::clYellow));
    m_points.append(GLPoint(lbb, -vX, QVector3D(0, 0, 0), GLColorRgba::clYellow));

    m_points.append(GLPoint(lbf, -vX, QVector3D(0, 0, 0), GLColorRgba::clYellow));
    m_points.append(GLPoint(lbb, -vX, QVector3D(0, 0, 0), GLColorRgba::clYellow));
    m_points.append(GLPoint(ltf, -vX, QVector3D(0, 0, 0), GLColorRgba::clYellow));

    //Oben
    m_points.append(GLPoint(ltb, vY, QVector3D(0, 0, 0), GLColorRgba::clGreen));
    m_points.append(GLPoint(rtb, vY, QVector3D(0, 0, 0), GLColorRgba::clGreen));
    m_points.append(GLPoint(ltf, vY, QVector3D(0, 0, 0), GLColorRgba::clGreen));

    m_points.append(GLPoint(rtf, vY, QVector3D(0, 0, 0), GLColorRgba::clGreen));
    m_points.append(GLPoint(ltf, vY, QVector3D(0, 0, 0), GLColorRgba::clGreen));
    m_points.append(GLPoint(rtb, vY, QVector3D(0, 0, 0), GLColorRgba::clGreen));

    //Unten
    m_points.append(GLPoint(lbf, -vY, QVector3D(0, 0, 0), GLColorRgba::clWhite));
    m_points.append(GLPoint(rbf, -vY, QVector3D(0, 0, 0), GLColorRgba::clWhite));
    m_points.append(GLPoint(lbb, -vY, QVector3D(0, 0, 0), GLColorRgba::clWhite));

    m_points.append(GLPoint(rbb, -vY, QVector3D(0, 0, 0), GLColorRgba::clWhite));
    m_points.append(GLPoint(lbb, -vY, QVector3D(0, 0, 0), GLColorRgba::clWhite));
    m_points.append(GLPoint(rbf, -vY, QVector3D(0, 0, 0), GLColorRgba::clWhite));

    switch(m_taskNumber)
    {
        case 0:
            m_lastTrianglePoint = m_points.size() -1;
            break;
    }


    //drawTriangles();
    //paintOnTopOfQmlScene();
}
