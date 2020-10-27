#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QObject>
#include <QWidget>

#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include "point.h"

/**
 * @brief The myOpenGLWidget class : Classe qui s'occupe du rendu OpenGL des éléments géométriques.
 * Ils sont affichés sur une QOpenGLWidget.
 */
class myOpenGLWidget : public QOpenGLWidget,
			   protected QOpenGLFunctions
{
	Q_OBJECT

public:
    explicit myOpenGLWidget(QWidget *parent = nullptr);
	~myOpenGLWidget();

public slots:

signals:  // On ne les implémente pas, elles seront générées par MOC ;
		  // les paramètres seront passés aux slots connectés.

protected slots:
	void onTimeout();

protected:
	void initializeGL() override;
	void doProjection();
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void keyPressEvent(QKeyEvent *ev) override;
	void keyReleaseEvent(QKeyEvent *ev) override;
	void mousePressEvent(QMouseEvent *ev) override;
	void mouseReleaseEvent(QMouseEvent *ev) override;
	void mouseMoveEvent(QMouseEvent *ev) override;

    /**
     * @brief setPoints : Permet de définir la liste de points à envoyer dans le VBO prochainement
     * @param points : les points à rendre convertis en Point* pour l'envoyer facilement au VBO.
     */
    void setPoints(Point* points);

private:

    /**
     * @brief m_near : la valeur du near clipping plane
     */
    float m_near = 1.0;

    /**
     * @brief m_far : la valeur du far clipping plane
     */
    float m_far = 20.0;

    /**
     * @brief m_radius : la valeur du FOV
     */
    float m_radius = 0.5;

    /**
     * @brief m_angle_x : la valeur de la rotation actuelle de la scène selon l'axe x
     */
    float m_angle_x = 0;

    /**
     * @brief m_angle_y : la valeur de la rotation actuelle de la scène selon l'axe y
     */
    float m_angle_y = 0;

    /**
     * @brief m_dist_camera_z : l'emplacement de la caméra sur l'axe z
     */
    double m_dist_camera_z = 3.0;

    /**
     * @brief m_dist_camera_x : l'emplacement de la caméra sur l'axe x
     */
    double m_dist_camera_x = 0.0;

    /**
     * @brief m_dist_camera_y : l'emplacement de la caméra sur l'axe y
     */
    double m_dist_camera_y = -1;
	double m_angle = 0;
	QTimer *m_timer = nullptr;
	double m_ratio = 1;

    /**
     * @brief points : les points pour lesquels effectuer le rendu, à renseigner avec la méthode setPoints
     */
    Point* points;

    /**
     * @brief m_sizePoint, m_sizePointsControle : le nombre de points à rendre
     */
    int m_sizePoint = 0;
    int m_sizePointsControle = 0;

	//RR matrices utiles
	QMatrix4x4 m_modelView;
	QMatrix4x4 m_projection;
	QMatrix4x4 m_model;

    //stocke les sources des shaders
	QOpenGLShaderProgram *m_program;

    //le vbo pour le rendu
	QOpenGLBuffer m_vbo;

    /**
     * @brief makeGLObjects : fonction dans laquelle on renseigne le VBO avec les coordonnées
     * et les couleurs des points à rendre.
     */
	void makeGLObjects();

    /**
     * @brief tearGLObjects : destruction du VBO
     */
	void tearGLObjects();

    /**
     * @brief pointsCarreau : les coordonnées des points appartenant au carreau de Bézier, à convertir
     * dans makeGLObjects si on veut que le rendu soit fait avec une autre primitive que des points.
     * (Ici le rendu de ces points est fait avec des triangles).
     */
    std::vector<Point> pointsCarreau;

    /**
     * @brief pointsControle : les coordonnées des points de contrôle du carreau de Bézier, à convertir
     * dans makeGLObjects si on veut que le rendu soit fait avec une autre primitive que des points.
     * (Ici le rendu de ces points est fait avec des lignes).
     */
    std::vector<std::vector<Point>> pointsControle;
    Point point_uv;

    /**
     * @brief U : le nombre de points du carreau de Bézier sur l'un des 2 axes
     */
    int U;

    /**
     * @brief V : le nombre de points du carreau de Bézier sur l'un des 2 axes
     */
    int V;

    /**
     * @brief stocker_sommets : booléen déterminant si il faut ou pas appeler makeGLObjects dans GLPaint,
     * c'est-à-dire s'il y a un carreau de Bézier à rendre. Faux au lancement du programme, vrai dès que
     * l'utilisateur génère un carreau.
     */
    bool stocker_sommets = false;

    /**
     * @brief render_points_controle : si il faut ou pas afficher le polygone de contrôle.
     */
    bool render_points_controle = true;

    /**
     * @brief set_point_uv : si il faut ou pas afficher un point spécifique appartenant au carreau.
     */
    bool set_point_uv = false;
public:

    /**
     * @brief setData : méthode devant être appelée de l'extérieur afin de renseigner les informations
     * sur le carreau de Bézier à afficher, càd les points du carreau et ses points de contrôle.
     * @param U : le nombre de points du carreau de Bézier sur l'un des 2 axes
     * @param V : le nombre de points du carreau de Bézier sur l'un des 2 axes
     * @param pointsCarreau : les points du carreau de Bézier.
     * @param pointsControle : les points de contrôle du carreau.
     */
    void setData(int U, int V, std::vector<Point> pointsCarreau, std::vector<std::vector<Point>> pointsControle) {
        this->U = U;
        this->V = V;
        this->pointsCarreau = pointsCarreau;
        this->pointsControle = pointsControle;
        stocker_sommets = true;
    }

    /**
     * @brief inverserRenduPointsControle : appelée quand l'utilisateur clique sur le bouton
     * "Afficher / Masquer le polygone de contrôle".
     */
    void inverserRenduPointsControle() {
        render_points_controle = !render_points_controle;
    }

    /**
     * @brief setPointUV : appelée quand l'utilisateur déplace l'un des 2 sliders u et v
     * pour afficher un point spécifique du carreau. Met le booléen set_point_uv à true
     * car il faut désormais afficher un nouveau point.
     * @param point : le point évalué à afficher.
     */
    void setPointUV(Point point) {
        this->point_uv = point;
        stocker_sommets = true;
        set_point_uv = true;
    }
};


#endif // MYOPENGLWIDGET_H
