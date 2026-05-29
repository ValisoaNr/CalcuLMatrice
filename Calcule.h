#ifndef CALCULE_H
#define CALCULE_H

#include <QMainWindow>
#include "Matrice.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Calcule;
}
QT_END_NAMESPACE

class Calcule : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Calcule(QWidget *parent = nullptr);
        ~Calcule() override;
        void afficheMatrice(int numCase , Matrice mat);
        Matrice prendMatrice(int numCase);

    private slots:
        void initialise();
        void plus();
        void fois();
        void moins();
        void determinant();
        void transpose();
        void inverse();
        void tailleA();
        void tailleB();
        void resultat_vers_A();
        void resultat_vers_B();
        void echange_A_et_B();
        void transpose_A();
        void transpose_B();
        void transpose_Resultat();
        void determinant_de_A();
        void determinant_de_B();
        void determinant_du_resultat();
        void editer_taille();
        void echanger();

    private:
        Ui::Calcule *ui;
};
#endif // CALCULE_H
