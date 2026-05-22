#ifndef MATRICE_H
#define MATRICE_H

#include <vector>

using namespace std;
class Matrice
{
    public:
        Matrice();
        Matrice(int ligne , int colonne);
        ~Matrice();
        int getNligne();
        int getNcolonne();
        void setNligne(int val);
        void setNcolonne(int val);
        vector<vector<double>> getElement();
        void setElement(vector<vector<double>> tab);
        void redimensionner(int li , int co);
        Matrice operator+(Matrice autre);
        Matrice operator-(Matrice autre);
        Matrice operator*(Matrice autre);
        Matrice operator*(double scalaire);
        double determinant();
        double determinant(int taille , vector<vector<double>> tab);
        Matrice transposer();
        Matrice inverse();

    private:
        int nLigne , nColonne;
        vector<vector<double>> element;
};

#endif // MATRICE_H
