#include "glsphere.h"

GLSphere::GLSphere(const QString &name, float radius, const GLColorRgba &color,
                   const QString textureFile, int stacks, int slices)
 :GLBody(name, radius,color, textureFile )
{
  m_stacks = stacks;
  m_slices = slices;
  m_drawingMode = GL_TRIANGLE_STRIP;
}

void GLSphere::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLushort> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);
    //m_drawingMode = GL_POINTS;
    //m_drawingMode = GL_LINE_STRIP;
    m_firstPoint = m_points->size();
    m_firstIndex = m_indices->size();
    int iSouthPole = 0;
    int iNorthPole = 0;

    QVector3D vertex;
    QVector3D normal;
    GLColorRgba color = m_color; Q_UNUSED(color);
    QVector3D texCoord;
    QMatrix4x4 stackRotor;
    QMatrix4x4 sliceRotor;

    float hilfSlice = 0.0f;
    for(int slice = 0; slice < m_slices; slice++)
    {

        //Setzt Punkt von Kreisbahn um Z
        double longitude = 360.0 / m_slices * slice;
        sliceRotor.setToIdentity();
        sliceRotor.rotate(longitude, v_Z);
        float hilfStack = 0.0f;
        for(int stack = -m_stacks /2 + 1; stack < m_stacks /2; stack ++)//int stack = -m_stacks /2 + 1; stack < m_stacks /2; stack ++
        {//x/2 -1 -(-x/2 +1) +1 wegen null=> x/2-1+x/2-1+1 => x-1-1+1 => x-1
            //Zeichnet alle auf dem Breitengrad des Punktes, nur Halbkreis, beginnt "hinten"(-Z)
           vertex = v_X;
           stackRotor.setToIdentity();
           double latitude = 180.0 / m_stacks * stack;
           stackRotor.rotate(latitude, -v_Y);
           vertex = sliceRotor * stackRotor * vertex;
           normal = vertex;
           vertex = vertex * m_radius;

           texCoord = QVector3D(0.0 + (hilfSlice/m_slices), 1.0 - (hilfStack/m_stacks), 0.0);
           m_points->append(GLPoint(vertex, normal, texCoord));
           hilfStack++;
        }
        hilfSlice++;
    }

    QVector3D southPole = -v_Z * m_radius;
    normal = -v_Z;
    iSouthPole = m_points->size();
    texCoord = QVector3D(0.5, 1.0, 0.0);
    m_points->append(GLPoint(southPole, normal, texCoord));

    QVector3D northPole = -southPole;
    normal = -normal;
    iNorthPole = m_points->size();
    texCoord = QVector3D(0.5, 0.0, 0.0);
    m_points->append(GLPoint(northPole, normal, texCoord));

    ///Wichtig für Erdkugel
    int slice = 0;
    double longitude = 360.0 / m_slices * slice;
    sliceRotor.setToIdentity();
    sliceRotor.rotate(longitude, v_Z);
    float hilfStack = 0.0f;
    for(int stack = -m_stacks /2 + 1; stack < m_stacks /2; stack ++)
    {
        vertex = v_X;
        stackRotor.setToIdentity();
        double latitude = 180.0 / m_stacks * stack;
        stackRotor.rotate(latitude, -v_Y);
        vertex = sliceRotor * stackRotor * vertex;
        normal = vertex;
        vertex = vertex * m_radius;

        texCoord = QVector3D(1.0, 1.0 - (hilfStack/m_stacks), 0.0);
        m_points->append(GLPoint(vertex, normal, texCoord));
        hilfStack++;
    }
    int letzteSpalte = m_points->size()-1; ///Wichtig für Erdkugel //Minus 1, da letzter Punkt einen vor Feldende liegt

    for(int slice = 0; slice < m_slices; slice +=2) //+=2 weil jeder Druchlauf einmal Hoch plus Runter bedeutet
    {
        m_indices->append(iSouthPole);
        for(int stack = 0; stack < m_stacks -1; stack ++){
            m_indices->append(stack + slice * (m_stacks -1));
            m_indices->append(stack + slice * (m_stacks -1) + m_stacks -1);
        }
        m_indices->append(iNorthPole);

        if(slice == m_slices - 2){ //Nur noch 2 LG bzw Flächen offen. Hinweg ist durch oben schon erledigt. Rückweg == 0er LG
            for(int stack = (m_stacks -1) -1; stack >= 0; stack --)
            {
                ///Wichtig für Erdkugel: Für Erdkugel entfernt: //m_indices->append(stack); //reuse points of first column
                m_indices->append(letzteSpalte); //Wichtig für Erdkugel
                m_indices->append(stack +(slice + 2) * (m_stacks -1) - m_stacks + 1);
                //                      6 + 28 * 7 - 9 = 193
                letzteSpalte--; ///Wichtig für Erdkugel
            }
        }else{
            for(int stack = (m_stacks -1) -1; stack >= 0; stack --)
            {
                //m_indices->append(Breitengrad (fängt am Nordpol+1 (vorne) an + neuer Breitengrad, deshalb "+2" * ein Halbkreis));
                m_indices->append(stack + (slice + 2) * (m_stacks -1));
                //m_indices->append(stack + slice * (m_stacks -1) + m_stacks -1); rückwärts, deshalb die "alten" Werte
                m_indices->append(stack + (slice + 2) * (m_stacks -1) - m_stacks + 1);
            }
        }
        m_indices->append(iSouthPole);
    }

    m_nextPoint = m_points->size();
    m_nextIndex = m_indices->size();
    findMinMaxCoordinates();
}

//void GLSphere::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLushort> *indexContainer)
//{
//    GLBody::makeSurface(pointContainer, indexContainer);
//    m_drawingMode = GL_POINTS;
//    //m_drawingMode = GL_LINE_STRIP;
//    m_firstPoint = m_points->size();
//    m_firstIndex = m_indices->size();
//    int iSouthPole = 0;
//    int iNorthPole = 0;

//    QVector3D vertex;
//    QVector3D normal;
//    GLColorRgba color = m_color;
//    QVector3D texCoord;
//    QMatrix4x4 stackRotor;
//    QMatrix4x4 sliceRotor;

//    for(int slice = 0; slice < m_slices; slice++)
//    {
//        //Setzt Punkt von Kreisbahn um Z
//        double longitude = 360.0 / m_slices * slice;
//        sliceRotor.setToIdentity();
//        sliceRotor.rotate(longitude, v_Z);
//        for(int stack = -m_stacks /2 + 1; stack < m_stacks /2; stack ++)//int stack = -m_stacks /2 + 1; stack < m_stacks /2; stack ++
//        {
//            //Zeichnet alle auf dem Breitengrad des Punktes, nur Halbkreis, beginnt "hinten"(-Z)
//           vertex = v_X;
//           stackRotor.setToIdentity();
//           double latitude = 180.0 / m_stacks * stack;
//           stackRotor.rotate(latitude, -v_Y);
//           vertex = sliceRotor * stackRotor * vertex;
//           normal = vertex;
//           vertex = vertex * m_radius;
//           m_points->append(GLPoint(vertex, normal, texCoord, color));
//        }
//    }

//    QVector3D southPole = -v_Z * m_radius;
//    normal = -v_Z;
//    iSouthPole = m_points->size();
//    m_points->append(GLPoint(southPole, normal, texCoord));

//    QVector3D northPole = -southPole;
//    normal = -normal;
//    iNorthPole = m_points->size();
//    m_points->append(GLPoint(northPole, normal, texCoord));

//    for(int slice = 0; slice < m_slices; slice +=2) //+=2 weil jeder Druchlauf einmal Hoch plus Runter bedeutet
//    {
//        m_indices->append(iSouthPole);
//        for(int stack = 0; stack < m_stacks -1; stack ++){
//            m_indices->append(stack + slice * (m_stacks -1));
//            m_indices->append(stack + slice * (m_stacks -1) + m_stacks -1);
//        }
//        m_indices->append(iNorthPole);

//        if(slice == m_slices - 2){ //Nur noch 2 LG bzw Flächen offen. Hinweg ist durch oben schon erledigt. Rückweg == 0er LG
//            for(int stack = (m_stacks -1) -1; stack >= 0; stack --)
//            {
//                m_indices->append(stack); //reuse points of first column
//                m_indices->append(stack +(slice + 2) * (m_stacks -1) - m_stacks + 1);
//            }
//        }else{
//            for(int stack = (m_stacks -1) -1; stack >= 0; stack --)
//            {
//                //m_indices->append(Breitengrad (fängt am Nordpol+1 (vorne) an + neuer Breitengrad, deshalb "+2" * ein Halbkreis));
//                m_indices->append(stack + (slice + 2) * (m_stacks -1));
//                //m_indices->append(stack + slice * (m_stacks -1) + m_stacks -1); rückwärts, deshalb die "alten" Werte
//                m_indices->append(stack + (slice + 2) * (m_stacks -1) - m_stacks + 1);
//            }
//        }
//        m_indices->append(iSouthPole);
//    }

//    m_nextPoint = m_points->size();
//    m_nextIndex = m_indices->size();
//    findMinMaxCoordinates();
//}
