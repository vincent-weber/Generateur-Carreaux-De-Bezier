/* R. Raffin
 * M1 Informatique, Aix-Marseille Université
 * Fenêtre principale
 * Au cas où, l'UI contient une barre de menu, une barre de status, une barre d'outils (cf QMainWindow).
 * Une zone est laissée libre à droite du Widget OpenGL pour mettre de futurs contrôles ou informations.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "point.h"
#include "segment.h"
#include "discretisation.h"
#include "carreaubezier.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
    connect(ui->slider_u, SIGNAL(valueChanged(int)), this, SLOT(onSliderU(int)));
    connect(ui->slider_v, SIGNAL(valueChanged(int)), this, SLOT(onSliderV(int)));

    connect(ui->slider_pt_ctrl_1, SIGNAL(valueChanged(int)), this, SLOT(onSliderPtsCtrl1(int)));
    connect(ui->slider_pt_ctrl_2, SIGNAL(valueChanged(int)), this, SLOT(onSliderPtsCtrl2(int)));
    connect(ui->slider_param_u, SIGNAL(valueChanged(int)), this, SLOT(onSliderParamU(int)));
    connect(ui->slider_param_v, SIGNAL(valueChanged(int)), this, SLOT(onSliderParamV(int)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

inline QTextStream& qStdout()
{
    static QTextStream r{stdout};
    return r;
}

void debugAfficherPoints(vector<Point> points) {
    for (int i = 0 ; i < points.size() ; ++i) {
        qDebug() << "[ " << points[i].getX() << " " << points[i].getY() << " " << points[i].getZ() << " ]";
    }
}

vector<Point> convertToUniArray(vector<vector<Point>> points) {
    vector<Point> result;
    for (int i = 0 ; i < points.size() ; ++i) {
        for (int j = 0 ; j < points[0].size() ; ++j) {
            result.push_back(points[i][j]);
        }
    }
    return result;
}

/**
 * @brief genererPointsControle Méthode pour générer des points de contrôle de manière
 * aléatoire en faisant en sorte que le polygône de contrôle formé ne soit pas "emmêlé",
 * pour que le  carreau ne le soit pas non plus.
 * @param n
 * @param m
 * @return
 */
vector<vector<Point>> genererPointsControle(int n, int m) {
    srand (static_cast <unsigned> (time(0)));
    float xOffset = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX));
    float yOffset = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX));
    float yPas = 0.2;
    float xPas = 0.8;
    vector<vector<Point>> result;
    for (int i = 0 ; i < n ; ++i) {
        vector<Point> ligne;
        for (int j = 0 ; j < m ; ++j) {
            float x = -2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(4))) / 20 + xOffset;
            float y = -2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(4))) / 20 + yOffset;
            float z = -1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2))) * 0.5;
            Point p; p.setX(x); p.setY(y); p.setZ(z);
            ligne.push_back(p);
            yOffset += yPas;
        }
        result.push_back(ligne);
        xOffset += xPas;
        yOffset = 0;
    }
    return result;
}

/**
 * @brief MainWindow::on_crea_points_clicked : génère les points de contrôle du
 * carreau de Bézier en fonction des valeurs des sliders et appelle le code de rendu
 * pour l'afficher.
 */
void MainWindow::on_crea_points_clicked()
{
     Discretisation disc;
     vector<vector<Point>> controlPoints;
     controlPoints = genererPointsControle(slider_pt_ctrl_1_value, slider_pt_ctrl_2_value);
     carreau = new CarreauBezier(controlPoints, slider_pt_ctrl_1_value, slider_pt_ctrl_2_value);

     vector<Point> points_surface = disc.discretiser_carreau_bezier(*carreau,param_u_value,param_v_value);

     ui->openGLWidget->setData(param_u_value, param_v_value, points_surface, controlPoints);
     ui->openGLWidget->update();
}

/**
 * @brief MainWindow::on_pts_ctrl_clicked action liée au bouton des points de contôle
 * qui permet d'afficher ou pas les points de contrôle
 */
void MainWindow::on_pts_ctrl_clicked()
{
    ui->openGLWidget->inverserRenduPointsControle();
    ui->openGLWidget->update();
}

/**
 * @brief MainWindow::onSliderU : les sliders ayant une range entre 0 et 100, leur valeur
 * est divisée par 100 pour rentrer entre 0 et 1 pour l'évaluation.
 * @param value
 */
void MainWindow::onSliderU(int value) {
    slider_u_value = value;
    if (carreau != nullptr) {
        Point point = carreau->eval((float)slider_u_value / 100, (float)slider_v_value / 100);
        ui->openGLWidget->setPointUV(point);
        ui->openGLWidget->update();
    }
}



void MainWindow::onSliderV(int value) {
    slider_v_value = value;
    if (carreau != nullptr) {
        Point point = carreau->eval((float)slider_u_value / 100, (float)slider_v_value / 100);
        ui->openGLWidget->setPointUV(point);
        ui->openGLWidget->update();
    }
}

void MainWindow::onSliderPtsCtrl1(int value) {
    slider_pt_ctrl_1_value = value;
    ui->label_pt_ctrl_1->setText(QString::number(value));
}
void MainWindow::onSliderPtsCtrl2(int value){
    slider_pt_ctrl_2_value = value;
    ui->label_pt_ctrl_2->setText(QString::number(value));
}
void MainWindow::onSliderParamU(int value){
    param_u_value = value;
    ui->label_param_u->setText(QString::number(value));
}
void MainWindow::onSliderParamV(int value){
    param_v_value = value;
    ui->label_param_v->setText(QString::number(value));
}

