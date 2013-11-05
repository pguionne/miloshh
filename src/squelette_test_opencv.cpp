//////////////////////////////////////////////////////////////////////////
// Module IRF, 5-iNFO
// Projet, séance 1
// thème : premier pas en OpenCV
// contenu : charge, affiche, réduction, calcul et affichage d'histogramme
// auteur : Luce Morin
// date : 4/10/2010
//////////////////////////////////////////////////////////////////////////

#include "histogram.h"

#include "cv.h"
#include "highgui.h"
using namespace cv;

#include <iostream>
using namespace std;


int main (void) {

	//charge et affiche l'image 
	string imName = "00000.png";
	Mat im = imread(imName);
	if(im.data == NULL){
		cerr << "Image not found: "<< imName << endl;
		exit(0);
	}
	imshow("exemple1", im);

	//charge la croix
	string imNameCroix = "croix.png";
	Mat croix = imread(imNameCroix);
	if(croix.data == NULL){
		cerr << "Image not found: "<< imNameCroix << endl;
		exit(0);
	}

	//applique une reduction de taille d'un facteur 5
	//ici modifier pour ne reduire qu'a l'affichage 
	//comme demande dans l'enonce
	int reduction = 5;
	Size tailleReduite(im.cols/reduction, im.rows/reduction);
	Mat imreduite = Mat(tailleReduite,CV_8UC3); //cree une image à 3 canaux de profondeur 8 bits chacuns
	resize(im,imreduite,tailleReduite);
	imshow("image reduite", imreduite);


	Rect faceRect;
	Mat croppedFaceImage;

	faceRect = Rect(500,500,500,500);
	croppedFaceImage = im(faceRect).clone();

	imshow("zongulus", croppedFaceImage);
	imwrite("image_decoupee.jpg", croppedFaceImage);
	
	//templatematching
	Mat result;
	int method = CV_TM_SQDIFF;

	matchTemplate(im, croix, result, method);
	imwrite("croix_res.jpg", result);


	computeHistogram("histogramme", im);

	//termine le programme lorsqu'une touche est frappee
	waitKey(0);
}
