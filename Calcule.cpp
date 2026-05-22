#include "Calcule.h"
#include "ui_Calcule.h"
#include <QMessageBox>

Calcule::Calcule(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calcule)
{
    ui->setupUi(this);
    initialise();

}

Calcule::~Calcule()
{
    delete ui;
}
void Calcule::initialise()
{
    Matrice m;
    int i , j;
    vector<vector<double>> tab;


    m.redimensionner(3 , 3);
    tab.resize(3 , vector<double>(3));
    for(i=0 ; i<3 ; i++)
    {
        for(j=0 ; j<3 ; j++)
        {
            if(i == j)
            {
                tab[i][j] = 1;
            }
            else
            {
                tab[i][j] = 0;
            }
        }
    }

    ui->ligne->setValue(3);
    ui->colonne->setValue(3);
    m.setElement(tab);
    afficheMatrice(1 , m);
    afficheMatrice(2 , m*m);
    afficheMatrice(3 , m.inverse());
}
void Calcule::afficheMatrice(int numCase , Matrice mat)
{
    int i , j , nbLigne , nbColonne;
    QTableWidgetItem *valeur;
    QString val;
    QTableWidget *tab;

    nbLigne = mat.getNligne();
    nbColonne = mat.getNcolonne();
    switch(numCase)
    {
        case 1:
        {
            tab = ui->tabMatriceA;
            break;
        }
        case 2:
        {
            tab = ui->tabMatriceB;
            break;
        }
        case 3:
        {
            tab = ui->tabResultat;
            break;
        }
        default :
        {
            QMessageBox::warning(this , "ERREUR" , "numCase invalide pour inserer une matrice");
            exit(0);
        }
    }

    tab->setRowCount(nbLigne);
    tab->setColumnCount(nbColonne);

    for(i=0 ; i<nbColonne ; i++)
    {
        tab->setColumnWidth(i , tab->width()/nbColonne);
    }
    for(i=0 ; i<nbLigne ; i++)
    {
        tab->setRowHeight(i , tab->height()/nbLigne );
    }
    for(i=0 ; i<nbLigne ; i++)
    {
        for(j=0 ; j<nbColonne ; j++)
        {
            val = QString::number(mat.getElement()[i][j]);
            valeur = new QTableWidgetItem();
            valeur->setText(val);
            tab->setItem(i , j , valeur);
        }
    }

}
Matrice Calcule::prendMatrice(int numCase)
{
    QTableWidget *tab;
    QTableWidgetItem *item ;
    Matrice mat;
    QString msg ;
    vector<vector<double>> contenu;
    double val ;
    int lignes ,  colonnes , i , j;
    bool ok;

    tab = nullptr;
    switch(numCase)
    {
    case 1:
    {
        tab = ui->tabMatriceA;
        break;
    }
    case 2:
    {
        tab = ui->tabMatriceB;
        break;
    }
    case 3:
    {
        tab = ui->tabResultat;
        break;
    }
    default:
    {
        return (Matrice());
    }
    }

    lignes = tab->rowCount();
    colonnes = tab->columnCount();
    if((lignes == 0) || (colonnes == 0))
    {
        QMessageBox::warning(this , "Erreur" , "la matrice est vide");
        return Matrice();
    }

    mat.redimensionner(lignes , colonnes);
    contenu.resize(lignes , vector<double>(colonnes));
    for(i=0 ; i<lignes; i++)
    {
        for(j=0 ; j<colonnes ; j++)
        {
            item = tab->item(i, j);
            if(!item)
            {
                contenu[i][j] = 0.0;
                continue;
            }
            val = item->text().toDouble(&ok);
            if(!ok)
            {
                msg = "Erreur de la matrice " + QString::number(numCase) + "(ligne , colonne) = (" + QString::number(i) + "," + QString::number(j) + ")" ;
                QMessageBox::warning(this, "Erreur de saisie", msg);
                contenu[i][j] = 0.0;
            }
            else
            {
                contenu[i][j] = val;
            }
        }
    }

    mat.setElement(contenu);
    return (mat);
}
void Calcule::on_plus_clicked()
{
    Matrice A , B;

    A = prendMatrice(1);
    B = prendMatrice(2);

    if((A.getNcolonne() != B.getNcolonne()) || (A.getNligne() != B.getNligne()))
    {
        QMessageBox::information(this , "ERREUR" , "la taille n'est pas compatible");
    }
    else
    {
        afficheMatrice(1 , A);
        afficheMatrice(2 , B);
        afficheMatrice(3 , A+B);
    }
}
void Calcule::on_fois_clicked()
{
    Matrice A , B;

    A = prendMatrice(1);
    B = prendMatrice(2);

    if(A.getNcolonne() != B.getNligne())
    {
        QMessageBox::information(this , "ERREUR" , "la taille n'est pas compatible");
    }
    else
    {
        afficheMatrice(1 , A);
        afficheMatrice(2 , B);
        afficheMatrice(3 , A*B);
    }
}


void Calcule::on_moins_clicked()
{
    Matrice A , B;

    A = prendMatrice(1);
    B = prendMatrice(2);

    if((A.getNcolonne() != B.getNcolonne()) || (A.getNligne() != B.getNligne()))
    {
        QMessageBox::information(this , "ERREUR" , "la taille n'est pas compatible");
    }
    else
    {
        afficheMatrice(1 , A);
        afficheMatrice(2 , B);
        afficheMatrice(3 , A-B);
    }
}
void Calcule::on_determinant_clicked()
{
    int reponse ;
    Matrice A ;
    double det;

    reponse = QMessageBox::question(this , "Calcule determinant" ,"Veuillez choisir la matrice ." , "matrice A" , "matrice B" , "le resultat");

    A = prendMatrice(reponse+1);
    det = A.determinant();
    ui->reponse->setText("determinant = " + QString::number(det));
}

void Calcule::on_transpose_clicked()
{
    int reponse ;
    Matrice A ;
    double det;

    reponse = QMessageBox::question(this , "Calcule la matrice transposé" ,"Veuillez choisir la matrice ." , "matrice A" , "matrice B" , "le resultat");

    switch(reponse)
    {
        case 0:
        {
            A = prendMatrice(1);
            afficheMatrice(1 , A.transposer());
            break;
        }
        case 1:
        {
            A = prendMatrice(2);
            afficheMatrice(2 , A.transposer());
            break;
        }
        case 3:
        {
            A = prendMatrice(3);
            afficheMatrice(3 , A.transposer());
            break;
        }
    }
}

void Calcule::on_inverse_clicked()
{
    int reponse ;
    Matrice A ;
    double det;

    reponse = QMessageBox::question(this , "Calcule la matrice inverse" ,"Veuillez choisir la matrice ." , "matrice A" , "matrice B" , "le resultat");

    reponse += 1;
    A = prendMatrice(reponse);
    if(A.determinant() != 0)
    {
        afficheMatrice(reponse , A.inverse());
    }
    else
    {
        QMessageBox::information(this , "Erreur" , "La matrice n'est pas inversible !");
    }

}
void Calcule::on_tailleA_clicked()
{
    Matrice A;
    int ligne , colonne;

    ligne = ui->ligne->value();
    colonne = ui->colonne->value();
    A = prendMatrice(1);
    A.redimensionner(ligne , colonne);

    afficheMatrice(1 , A);
}
void Calcule::on_tailleB_clicked()
{
    Matrice A;
    int ligne , colonne;

    ligne = ui->ligne->value();
    colonne = ui->colonne->value();
    A = prendMatrice(2);
    A.redimensionner(ligne , colonne);

    afficheMatrice(2 , A);
}
void Calcule::on_actioninitialise_triggered()
{
    initialise();
}
void Calcule::on_actionresultat_vers_A_triggered()
{
    Matrice A;

    A = prendMatrice(3);
    afficheMatrice(1 , A);
}
void Calcule::on_actionresultat_vers_B_triggered()
{
    Matrice A;

    A = prendMatrice(3);
    afficheMatrice(2 , A);
}
void Calcule::on_actionechange_A_et_B_triggered()
{
    Matrice A , B;

    A = prendMatrice(1);
    B = prendMatrice(2);

    afficheMatrice(1 , B);
    afficheMatrice(2 , A);
}
void Calcule::on_actiontranspose_A_triggered()
{
    Matrice A;

    A = prendMatrice(1);
    A = A.transposer();
    afficheMatrice(1 , A);
}
void Calcule::on_actiontranspose_B_triggered()
{
    Matrice A;

    A = prendMatrice(2);
    A = A.transposer();
    afficheMatrice(2 , A);
}
void Calcule::on_actiontranspose_Resultat_triggered()
{
    Matrice A;

    A = prendMatrice(3);
    A = A.transposer();
    afficheMatrice(3 , A);
}
void Calcule::on_actiondeterminant_de_A_triggered()
{
    Matrice A;
    double det;

    A = prendMatrice(1);
    det = A.determinant();

    ui->reponse->setText("determinant de A : " + QString::number(det));
}
void Calcule::on_actiondeterminant_de_B_triggered()
{
    Matrice A;
    double det;

    A = prendMatrice(2);
    det = A.determinant();

    ui->reponse->setText("determinant de B : " + QString::number(det));
}
void Calcule::on_actiondeterminant_du_resultat_triggered()
{
    Matrice A;
    double det;

    A = prendMatrice(3);
    det = A.determinant();

    ui->reponse->setText("determinant de resultat : " + QString::number(det));
}
void Calcule::on_actionediter_taille_triggered()
{
    ui->ligne->setFocus();
}

void Calcule::on_echanger_clicked()
{
    int indice1 , indice2;
    Matrice A , B;

    indice1 = ui->echange1->currentIndex() + 1;
    indice2 = ui->echange2->currentIndex() + 1;

    A = prendMatrice(indice1);
    B = prendMatrice(indice2);

    afficheMatrice(indice2 , A);
    afficheMatrice(indice1 , B);
}

