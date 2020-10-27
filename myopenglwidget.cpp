//R. Raffin, M1 Informatique, "Surfaces 3D"
//tiré de CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#include "myopenglwidget.h"
#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>

#include <iostream>

#include "segment.h"

static const QString vertexShaderFile   = ":/basic.vsh";
static const QString fragmentShaderFile = ":/basic.fsh";

void myOpenGLWidget::setPoints(Point* points) {
    this->points = points;
}

myOpenGLWidget::myOpenGLWidget(QWidget *parent) :
	QOpenGLWidget(parent)
{
	qDebug() << "init myOpenGLWidget" ;

	QSurfaceFormat sf;
	sf.setDepthBufferSize(24);
	sf.setSamples(16);  // nb de sample par pixels : suréchantillonnage por l'antialiasing, en décalant à chaque fois le sommet
						// cf https://www.khronos.org/opengl/wiki/Multisampling et https://stackoverflow.com/a/14474260
	setFormat(sf);

	setEnabled(true);  // événements clavier et souris
	setFocusPolicy(Qt::StrongFocus); // accepte focus
	setFocus();                      // donne le focus

	m_timer = new QTimer(this);
	m_timer->setInterval(50);  // msec
	connect (m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

myOpenGLWidget::~myOpenGLWidget()
{
	qDebug() << "destroy GLArea";

	delete m_timer;

	// Contrairement aux méthodes virtuelles initializeGL, resizeGL et repaintGL,
	// dans le destructeur le contexte GL n'est pas automatiquement rendu courant.
	makeCurrent();
	tearGLObjects();
	doneCurrent();
}


void myOpenGLWidget::initializeGL()
{
	qDebug() << __FUNCTION__ ;
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);

	makeGLObjects();

	//shaders
	m_program = new QOpenGLShaderProgram(this);
	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFile);  // compile
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFile);

	if (! m_program->link()) {  // édition de lien des shaders dans le shader program
		qWarning("Failed to compile and link shader program:");
		qWarning() << m_program->log();
	}
}

void myOpenGLWidget::doProjection()
{
	//m_mod.setToIdentity();
	//modelMatrix.ortho( -aratio, aratio, -1.0f, 1.0f, -1.0f, 1.0f );
}

/**
 * @brief convertForTriangleRendering : méthode utilisée pour formater les points
 * et les envoyer au VBO pour qu'il puisse afficher le carreau avec des triangles.
 * @param points : les points de base à convertir
 * @param U : le nombre de points sur l'un des 2 axes
 * @param V : le nombre de points sur l'un des 2 axes
 * @return les points agencés correctement pour effectuer le rendu par triangles du carreau
 */
std::vector<Point> convertForTriangleRendering(std::vector<Point>& points, int U, int V) {
    std::vector<Point> new_points;
    for (int u = 0 ; u < U-1 ; ++u) {
        for (int v = 0 ; v < V-1 ; ++v) {
            new_points.push_back(points[V*u+v]);
            new_points.push_back(points[V*(u+1)+v]);
            new_points.push_back(points[V*u+v+1]);

            new_points.push_back(points[V*u+v+1]);
            new_points.push_back(points[V*(u+1)+v]);
            new_points.push_back(points[V*(u+1)+v+1]);
        }
    }
    return new_points;
}

/**
 * @brief convertForLineRendering : méthode pour formaterles points
 * et les envoyer au VBO pour qu'il puisse afficher les points de contrôle du
 * carreau avec des lignes.
 * @param points : les points de base à convertir
 * @return les points agencés correctement pour effectuer le rendu par lignes des points de contrôle
 */
std::vector<Point> convertForLineRendering(std::vector<std::vector<Point>>& points) {
    std::vector<Point> new_points_controle;
    for (int i = 0 ; i < points.size() ; ++i) {
        for (int j = 0 ; j < points[0].size() ; ++j) {
            if (i > 0) {
                new_points_controle.push_back(points[i][j]);
                new_points_controle.push_back(points[i-1][j]);
            }
            if (i < points.size() - 1) {
                new_points_controle.push_back(points[i][j]);
                new_points_controle.push_back(points[i+1][j]);
            }
            if (j > 0) {
                new_points_controle.push_back(points[i][j]);
                new_points_controle.push_back(points[i][j-1]);
            }
            if (j < points[0].size() - 1) {
                new_points_controle.push_back(points[i][j]);
                new_points_controle.push_back(points[i][j+1]);
            }
        }
    }
    return new_points_controle;
}

/**
 * @brief myOpenGLWidget::makeGLObjects méthode principale pour effectuer le rendu du carreau,
 * de ses points de contrôle et éventuellement du point spécifié.
 */
void myOpenGLWidget::makeGLObjects()
{
    std::vector<Point> new_points = convertForTriangleRendering(pointsCarreau, U, V);
    m_sizePoint = new_points.size();
    setPoints(new_points.data());

    //3 Remplissage des tableaux de float pour OpenGL
	QVector<GLfloat> vertData;
    for (int i = 0; i < m_sizePoint; ++i) {
        vertData.append(points[i].getX());
        vertData.append(points[i].getY());
        vertData.append(points[i].getZ());
        vertData.append(1);
        vertData.append(0);
        vertData.append(0);
    }

    std::vector<Point> new_points_controle = convertForLineRendering(pointsControle);
    m_sizePointsControle = new_points_controle.size();
    setPoints(new_points_controle.data());

    for (int i = 0; i < m_sizePointsControle; ++i) {
        vertData.append(points[i].getX());
        vertData.append(points[i].getY());
        vertData.append(points[i].getZ());
        vertData.append(0);
        vertData.append(1);
        vertData.append(0);
    }

    if (set_point_uv) {
        vertData.append(point_uv.getX());
        vertData.append(point_uv.getY());
        vertData.append(point_uv.getZ());
        vertData.append(0);
        vertData.append(0);
        vertData.append(1);
    }

	m_vbo.create();
	m_vbo.bind();

	m_vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}


void myOpenGLWidget::tearGLObjects()
{
	m_vbo.destroy();
}


void myOpenGLWidget::resizeGL(int w, int h)
{
	qDebug() << __FUNCTION__ << w << h;

	//C'est fait par défaut
	glViewport(0, 0, w, h);

	m_ratio = (double) w / h;
	//doProjection();
}

void myOpenGLWidget::paintGL()
{
    if (stocker_sommets) {
        makeGLObjects();
        stocker_sommets = false;
    }

	qDebug() << __FUNCTION__ ;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_program->bind(); // active le shader program

    GLfloat hr = m_radius, wr = hr * m_ratio;

    QMatrix4x4 m;

    m.frustum(-wr, wr, -hr, hr, m_near, m_far);

    m.translate(-m_dist_camera_x, -m_dist_camera_y, -m_dist_camera_z);

    // Rotation de la scène pour l'animation
    m.rotate (m_angle_y, 0, 1, 0);
    m.rotate(m_angle_x, 1, 0, 0);

	m_program->setUniformValue("matrix", m);

    m_program->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    m_program->setAttributeBuffer("colAttr", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
	m_program->enableAttributeArray("posAttr");
	m_program->enableAttributeArray("colAttr");

    glPointSize (30.0f);
    glDrawArrays(GL_TRIANGLES, 0, m_sizePoint);

    if (render_points_controle) {
        glDrawArrays(GL_LINES, m_sizePoint, m_sizePointsControle);
    }

    if (set_point_uv) {
        glDrawArrays(GL_POINTS, m_sizePoint + m_sizePointsControle, 1);
    }

	m_program->disableAttributeArray("posAttr");
	m_program->disableAttributeArray("colAttr");

	m_program->release();
}

void myOpenGLWidget::keyPressEvent(QKeyEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->text();

	switch(ev->key()) {
        case Qt::Key_G :
        case Qt::Key_Space :
            m_angle_y += 5;
            if (m_angle_y >= 360) m_angle_y -= 360;
            update();
            break;
        case Qt::Key_J :
            m_angle_y -= 5;
            if (m_angle_y < 0) m_angle_y += 360;
            update();
            break;
        case Qt::Key_Y :
            m_angle_x += 5;
            if (m_angle_x >= 360) m_angle_x -= 360;
            update();
            break;
        case Qt::Key_H :
            m_angle_x -= 5;
            if (m_angle_x < 0) m_angle_x += 360;
            update();
            break;
		case Qt::Key_Z :
			m_angle += 1;
			if (m_angle >= 360) m_angle -= 360;
			update();
			break;
        case Qt::Key_Down :
            m_dist_camera_y -= 0.05;
            update();
            break;
        case Qt::Key_Up :
            m_dist_camera_y += 0.05;
            update();
            break;
        case Qt::Key_Left :
            m_dist_camera_x -= 0.05;
            update();
            break;
        case Qt::Key_Right :
            m_dist_camera_x += 0.05;
            update();
        break;
		case Qt::Key_A :
			if (m_timer->isActive())
				m_timer->stop();
			else m_timer->start();
			break;
        case Qt::Key_R :
            if (ev->text() == "r") {
                m_radius -= 0.2;
            } else {
                m_radius += 0.2;
            }
            update();
        break;
        case Qt::Key_T :
            if (ev->text() == "t") {
                m_dist_camera_z -= 0.05;
            } else {
                m_dist_camera_z += 0.05;
            }
            update();
        break;
	}
}

void myOpenGLWidget::keyReleaseEvent(QKeyEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->text();
}

void myOpenGLWidget::mousePressEvent(QMouseEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}

void myOpenGLWidget::mouseReleaseEvent(QMouseEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}

void myOpenGLWidget::mouseMoveEvent(QMouseEvent *ev)
{
    //qDebug() << __FUNCTION__ << ev->x() << ev->y();
}

void myOpenGLWidget::onTimeout()
{
	qDebug() << __FUNCTION__ ;

	update();
}





