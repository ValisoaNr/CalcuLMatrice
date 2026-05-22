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
        void on_plus_clicked();
        void on_fois_clicked();
        void on_moins_clicked();
        void on_determinant_clicked();
        void on_transpose_clicked();
        void on_inverse_clicked();
        void on_tailleA_clicked();
        void on_tailleB_clicked();
        void on_actioninitialise_triggered();
        void on_actionresultat_vers_A_triggered();
        void on_actionresultat_vers_B_triggered();
        void on_actionechange_A_et_B_triggered();
        void on_actiontranspose_A_triggered();
        void on_actiontranspose_B_triggered();
        void on_actiontranspose_Resultat_triggered();
        void on_actiondeterminant_de_A_triggered();
        void on_actiondeterminant_de_B_triggered();
        void on_actiondeterminant_du_resultat_triggered();
        void on_actionediter_taille_triggered();

        void on_echanger_clicked();

    private:
        Ui::Calcule *ui;
};
#endif // CALCULE_H
