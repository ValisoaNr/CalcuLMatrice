#include "Calcule.h"
#include "ui_Calcule.h"
#include <QMessageBox>

Calcule::Calcule(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calcule)
{
    ui->setupUi(this);
    ui->statusbar->addPermanentWidget(new QLabel("Calculatrice Matrice (ma Creation)"));
    initialise();

    connect(ui->actioninitialise , SIGNAL(triggered()) , this , SLOT(initialise()));
    connect(ui->actiondeterminant_de_A , SIGNAL(triggered()) , this , SLOT(determinant_de_A()));
    connect(ui->actiondeterminant_de_B , SIGNAL(triggered()) , this , SLOT(determinant_de_B()));
    connect(ui->actiondeterminant_du_resultat , SIGNAL(triggered()) , this , SLOT(determinant_du_resultat()));

    connect(ui->plus , &QPushButton::clicked , this , &Calcule::plus);
    connect(ui->fois , &QPushButton::clicked , this , &Calcule::fois);
    connect(ui->moins , &QPushButton::clicked , this , &Calcule::moins);

    connect(ui->actionediter_taille , SIGNAL(triggered()) , this , SLOT(editer_taille()));
    connect(ui->actionechange_A_et_B , SIGNAL(triggered()) , this , SLOT(echange_A_et_B()));
    connect(ui->echanger , SIGNAL(clicked()) , this , SLOT(echanger()));

    connect(ui->tailleA , &QPushButton::clicked , this , &Calcule::tailleA);
    connect(ui->tailleB , &QPushButton::clicked , this , &Calcule::tailleB);

    connect(ui->actionresultat_vers_A , SIGNAL(triggered()) , this , SLOT(resultat_vers_A()));
    connect(ui->actionresultat_vers_B , SIGNAL(triggered()) , this , SLOT(resultat_vers_B()));
    connect(ui->determinant , SIGNAL(clicked()) , this , SLOT(determinant()));
    connect(ui->inverse , SIGNAL(clicked()) , this , SLOT(inverse()));

    connect(ui->transpose , SIGNAL(clicked()) , this , SLOT(transpose()));
    connect(ui->actiontranspose_A , SIGNAL(triggered()) , this , SLOT(transpose_A()));
    connect(ui->actiontranspose_B , SIGNAL(triggered()) , this , SLOT(transpose_B()));
    connect(ui->actiontranspose_Resultat , SIGNAL(triggered()) , this , SLOT(transpose_Resultat()));


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
void Calcule::plus()
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
void Calcule::fois()
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


void Calcule::moins()
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
void Calcule::determinant()
{
    int reponse ;
    Matrice A ;
    double det;

    reponse = QMessageBox::question(this , "Calcule determinant" ,"Veuillez choisir la matrice ." , "matrice A" , "matrice B" , "le resultat");

    A = prendMatrice(reponse+1);
    det = A.determinant();
    ui->reponse->setText("determinant = " + QString::number(det));
}

void Calcule::transpose()
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

void Calcule::inverse()
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
void Calcule::tailleA()
{
    Matrice A;
    int ligne , colonne;

    ligne = ui->ligne->value();
    colonne = ui->colonne->value();
    A = prendMatrice(1);
    A.redimensionner(ligne , colonne);

    afficheMatrice(1 , A);
}
void Calcule::tailleB()
{
    Matrice A;
    int ligne , colonne;

    ligne = ui->ligne->value();
    colonne = ui->colonne->value();
    A = prendMatrice(2);
    A.redimensionner(ligne , colonne);

    afficheMatrice(2 , A);
}
void Calcule::resultat_vers_A()
{
    Matrice A;

    A = prendMatrice(3);
    afficheMatrice(1 , A);
}
void Calcule::resultat_vers_B()
{
    Matrice A;

    A = prendMatrice(3);
    afficheMatrice(2 , A);
}
void Calcule::echange_A_et_B()
{
    Matrice A , B;

    A = prendMatrice(1);
    B = prendMatrice(2);

    afficheMatrice(1 , B);
    afficheMatrice(2 , A);
}
void Calcule::transpose_A()
{
    Matrice A;

    A = prendMatrice(1);
    A = A.transposer();
    afficheMatrice(1 , A);
}
void Calcule::transpose_B()
{
    Matrice A;

    A = prendMatrice(2);
    A = A.transposer();
    afficheMatrice(2 , A);
}
void Calcule::transpose_Resultat()
{
    Matrice A;

    A = prendMatrice(3);
    A = A.transposer();
    afficheMatrice(3 , A);
}
void Calcule::determinant_de_A()
{
    Matrice A;
    double det;

    A = prendMatrice(1);
    det = A.determinant();

    ui->reponse->setText("determinant de A : " + QString::number(det));
}
void Calcule::determinant_de_B()
{
    Matrice A;
    double det;

    A = prendMatrice(2);
    det = A.determinant();

    ui->reponse->setText("determinant de B : " + QString::number(det));
}
void Calcule::determinant_du_resultat()
{
    Matrice A;
    double det;

    A = prendMatrice(3);
    det = A.determinant();

    ui->reponse->setText("determinant de resultat : " + QString::number(det));
}
void Calcule::editer_taille()
{
    ui->ligne->setFocus();
}

void Calcule::echanger()
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
