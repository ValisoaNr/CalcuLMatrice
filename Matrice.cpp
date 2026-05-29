#include "Matrice.h"
#include <iostream>
#include <cmath>

Matrice::Matrice()
{

}
Matrice::Matrice(int ligne , int colonne)
{
    nColonne = colonne;
    nLigne = ligne;
}
Matrice::~Matrice()
{

}
void Matrice::redimensionner(int li , int co)
{
    int i;

    setNligne(li);
    setNcolonne(co);
    element.resize(li , vector<double>(co));

    for(i=0 ; i<li ; i++)
    {
        element[i].resize(co , 0.0);
    }

}
Matrice Matrice::operator+(Matrice autre)
{
    Matrice somme;
    int i , j;
    vector<vector<double>> tab;

    tab.resize(nLigne , vector<double>(nColonne));
    somme.redimensionner(nLigne , nColonne);
    if((nLigne != autre.nLigne) || (nColonne != autre.nColonne))
    {
        cout << "la taille des deux matrices n'est pas compatible pour faire la somme des deux ." << endl;
    }
    else
    {
        for(i=0 ; i<nLigne ; i++)
        {
            for(j=0 ; j<nColonne ; j++)
            {
                tab[i][j] = element[i][j] + autre.getElement()[i][j];
            }
        }
    }
    somme.setElement(tab);

    return (somme);
}
Matrice Matrice::operator-(Matrice autre)
{
    Matrice soustrait;
    int i , j;
    vector<vector<double>> tab;

    tab.resize(nLigne , vector<double>(nColonne));
    soustrait.redimensionner(nLigne , nColonne);
    if((nLigne != autre.nLigne) || (nColonne != autre.nColonne))
    {
        cout << "la taille des deux matrices n'est pas compatible pour faire la soustraction des deux ." << endl;
    }
    else
    {
        for(i=0 ; i<nLigne ; i++)
        {
            for(j=0 ; j<nColonne ; j++)
            {
                tab[i][j] = element[i][j] - autre.getElement()[i][j];
            }
        }
    }
    soustrait.setElement(tab);

    return (soustrait);
}
Matrice Matrice::operator*(double valeur)
{
    Matrice produit;
    int i , j;
    vector<vector<double>> tab;

    tab.resize(nLigne , vector<double>(nColonne));
    produit.redimensionner(nLigne , nColonne);
    for(i=0 ; i<nLigne ; i++)
    {
        for(j=0 ; j<nColonne ; j++)
        {
            tab[i][j] = element[i][j] * valeur;
        }
    }
    produit.setElement(tab);

    return (produit);
}
Matrice Matrice::operator*(Matrice autre)
{
    Matrice produit;
    int i , j , k;
    vector<vector<double>> tab;

    tab.resize(nLigne , vector<double>(autre.getNcolonne()));
    produit.redimensionner(nLigne , autre.getNcolonne());
    if(nColonne != autre.getNligne())
    {
        cout << "la taille des deux matrices n'est pas compatible pour faire le produit des deux ." << endl;
    }
    else
    {
        for(i=0 ; i<nLigne ; i++)
        {
            for(j=0 ; j<autre.getNcolonne() ; j++)
            {
                for(k=0 ; k<nColonne ; k++)
                {
                    tab[i][j] += element[i][k] * autre.getElement()[k][j];
                }
            }
        }
    }
    produit.setElement(tab);
    return (produit);
}
double Matrice::determinant()
{
    double det;

    if(nLigne != nColonne)
    {
        cout << "La matrice n'est pas compatible pour calculer le determinant (il faut une matrice carrée) ." << endl;
    }
    else
    {
        det = determinant(nLigne , element);
    }

    return (det);
}
double Matrice::determinant(int taille , vector<vector<double>> tab)
{
    double det;
    int i , j , iLigne , iTab , signe;
    vector<vector<double>> sousTab;

    if(taille == 1)
    {
        return tab[0][0];
    }

    det = 0;
    if(taille == 2)
    {
        det = (tab[0][0] * tab[1][1]) - (tab[1][0] * tab[0][1]);
    }
    else
    {
        sousTab.resize((taille-1) , vector<double>(taille-1));
        signe = 1;
        for(i=0 ; i<taille ; i++)
        {
            iTab = 0;
            for(iLigne=0 ; iLigne<taille ; iLigne++)
            {
                if(iLigne != i)
                {
                    for(j=1 ; j<taille ; j++)
                    {
                        sousTab[iTab][j-1] = tab[iLigne][j];
                    }
                    iTab++;
                }
            }
            det += signe * tab[i][0] * determinant(taille-1 , sousTab);
            signe *= (-1);
        }
    }

    return (det);
}
Matrice Matrice::transposer()
{
    Matrice transp;
    int i , j;
    vector<vector<double>> tab;

    tab.resize(nLigne , vector<double>(nColonne));
    transp.redimensionner(nLigne , nColonne);
    for(i=0 ; i<nLigne ; i++)
    {
        for(j=0 ; j<nColonne ; j++)
        {
            tab[i][j] = element[j][i];
        }
    }
    transp.setElement(tab);

    return (transp);
}
Matrice Matrice::inverse()
{
    Matrice invers;
    vector<vector<double>> sousMat;
    double det , cofacteur;
    int i , j , k , taille , iLigne , iColonne ;
    double signe;
    vector<vector<double>> tab;


    tab.resize(nLigne , vector<double>(nColonne));
    invers.redimensionner(nLigne , nColonne);

    if(nLigne != nColonne)
    {
        cout << "Il faut une matrice carrée pour l'inverser" << endl;
    }
    else if(fabs(determinant()) < 1e-10) // determinant = 0
    {
        cout << "la matrice n'est pas inversible " << endl;
    }
    else
    {
        sousMat.resize(nLigne-1 , vector<double>(nLigne-1));
        det = determinant();
        for(i=0 ; i<nLigne ; i++)
        {
            for(k=0 ; k<nColonne ; k++)
            {
                taille = 0;
                for(iLigne=0 ; iLigne<nLigne ; iLigne++)
                {
                    if(i != iLigne)
                    {
                        j = 0;
                        for(iColonne=0 ; iColonne<nColonne ; iColonne++)
                        {
                            if(k != iColonne)
                            {
                                sousMat[taille][j] = element[iLigne][iColonne];
                                j++;
                            }
                        }
                        taille++;
                    }
                }
                if(((i+k) % 2) == 0)
                {
                    signe = 1.0;
                }
                else
                {
                    signe = -1.0;
                }
                tab[k][i] = signe * determinant(nLigne-1 , sousMat) / det;
            }
        }
    }

    invers.setElement(tab);

    return (invers);
}
int Matrice::getNligne()
{
    return (nLigne);
}
int Matrice::getNcolonne()
{
    return (nColonne);
}
void Matrice::setNligne(int val)
{
    nLigne = val;
}
void Matrice::setNcolonne(int val)
{
    nColonne = val;
}
vector<vector<double>> Matrice::getElement()
{
    return (element);
}
void Matrice::setElement(vector<vector<double>> tab)
{
    element = tab;
}
