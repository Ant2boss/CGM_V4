#include<iostream>

#include "CGM_Log_addon.h"
#include "CGM_Canvas2D.h"

#include "CGM_Shapes2D.h"
#include "CGM_TextBox2D.h"
#include "CGM_Button2D.h"
#include "CGM_ButtonMatrix2D.h"

using namespace std;

int main() {

	CGM::Canvas2D MyCan(128, 48);
	
	CGM::ButtonMatrix MyMat;

	MyMat.AddColumn(3);
	MyMat.AddRow(3);
	MyMat.SetMatrixSelectedColor(CGM::Color::Blue);
	MyMat.SetMatrixNotSelectedColor(CGM::Color::DarkBlue);

	MyMat.SetPosition(3, 3);
	MyMat.SetMatrixElementSize(15, 5);

	MyMat.SetElementColor(CGM::Color::Brown, 5);
	MyMat.SetElementSelectedColor(CGM::Color::Bisque, 5);

	MyMat[0] << "I am the first";
	MyMat[0].SetFontColor(CGM::Color::Red);
	MyMat[0] << " of many!";

	MyMat[1] << "I am one of the few!";
	MyMat[2] << "I am the third among the crowd";
	MyMat[3] << "I am the final one of many!";

	MyMat.GetElement(1, 3) << "I am a corner :)";

	while (1) {
		MyCan.Clear();

		MyCan.Append(&MyMat);

		if (MyMat.is_left_clicked()) {
			break;
		}

		MyCan.Draw();
	}

	return 0;
}