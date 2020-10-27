#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include "point.h"
#include "carreaubezier.h"

using namespace std;

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 * La classe Qt de la fenêtre principale qui affiche tous les éléments
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:


    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /**
     * @brief on_crea_points_clicked : slot appelé lorsqu'on clique sur le bouton
     * de création de carreau de Bézier
     */
    void on_crea_points_clicked();

    /**
     * @brief on_pts_ctrl_clicked : slot appelé lorsqu'on clique sur le bouton
     * d'affichage / masquage des points de contrôle
     */
    void on_pts_ctrl_clicked();

public slots:

    /**
     * @brief onSliderU : slot appelé lorsqu'on déplace le slider U
     * @param value : la valeur entre 0 et 100 de u qui sera divisée par 100 pour
     * rentrer dans la range [0,1]
     */
    void onSliderU(int value);

    /**
     * @brief onSliderV : slot appelé lorsqu'on déplace le slider V
     * @param value : la valeur entre 0 et 100 de v qui sera divisée par 100 pour
     * rentrer dans la range [0,1]
     */
    void onSliderV(int value);

    /**
     * @brief onSliderPtsCtrl1 : slot appelé lorsqu'on déplace le slider contrôlant
     * le nombre de points de contrôle sur le premier axe
     * @param value : le nombre de points de contrôle sur l'un des 2 axes
     */
    void onSliderPtsCtrl1(int value);

    /**
     * @brief onSliderPtsCtrl2 : slot appelé lorsqu'on déplace le slider contrôlant
     * le nombre de points de contrôle sur le deuxième axe
     * @param value : le nombre de points de contrôle sur l'un des 2 axes
     */
    void onSliderPtsCtrl2(int value);

    /**
     * @brief onSliderParamU : slot appelé lorsqu'on déplace le slider U
     * @param value : la qualité du rendu sur l'un des 2 axes. Plus précisément
     * le nombre de points du carreau de Bézier qu'il y aura sur l'un des 2 axes.
     */
    void onSliderParamU(int value);

    /**
     * @brief onSliderParamV : slot appelé lorsqu'on déplace le slider V
     * @param value : la qualité du rendu sur l'un des 2 axes. Plus précisément
     * le nombre de points du carreau de Bézier qu'il y aura sur l'un des 2 axes.
     */
    void onSliderParamV(int value);

private:

    /**
     * @brief ui : pointeur vers l'interface permettant d'accéder aux différents éléments
     */
    Ui::MainWindow *ui;

    /**
     * @brief carreau : pointeur vers le carreau de Bézier actuellement généré
     */
    CarreauBezier* carreau = nullptr;

    /**
     * @brief slider_pt_ctrl_1_value : nombre de points de contrôle sur l'un des 2 axes, à 5 par défaut
     */
    int slider_pt_ctrl_1_value = 5;

    /**
     * @brief slider_pt_ctrl_2_value : nombre de points de contrôle sur l'un des 2 axes, à 5 par défaut
     */
    int slider_pt_ctrl_2_value = 5;

    /**
     * @brief param_u_value : nombre de points du carreau de Bézier qu'il y aura sur l'un des 2 axes, à 10 par défaut.
     */
    int param_u_value = 10;

    /**
     * @brief param_v_value : nombre de points du carreau de Bézier qu'il y aura sur l'un des 2 axes, à 10 par défaut.
     */
    int param_v_value = 10;

    /**
     * @brief slider_u_value : valeur entre 0 et 100 donnant la valeur du paramètre u pour l'affichage d'un point
     * en particulier appartenant au carreau.
     */
    int slider_u_value;

    /**
     * @brief slider_v_value : valeur entre 0 et 100 donnant la valeur du paramètre v pour l'affichage d'un point
     * en particulier appartenant au carreau.
     */
    int slider_v_value;
};

#endif // MAINWINDOW_H
