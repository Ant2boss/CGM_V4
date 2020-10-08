#include<iostream>

#include "CGM_Log_addon.h"
#include "CGM_Canvas2D.h"

#include "CGM_Shapes2D.h"
#include "CGM_TextBox2D.h"
#include "CGM_Button2D.h"

using namespace std;

int main() {

	CGM::Canvas2D MyCan(128, 48);
	CGM::Butt2_Rect MyButton;

	MyButton.SetPosition(10, 5);
	MyButton.SetSize(31, 11);

	MyButton.SetColorHovered(CGM::Canvas2D::Color::Blue);
	MyButton.SetColorNotHovered(CGM::Canvas2D::Color::DarkBlue);

	//MyButton.SetTextFormatMode_TextBreak(false);

	MyButton.AddTextToButton("Hello world! ");
	MyButton.AddTextToButton("And now I add even more text to see wether the stuff I added actually works!");

	while (1) {
		
		MyCan.Clear();

		if (MyButton.is_left_clicked())
			break;

		MyCan.Append(&MyButton);

		MyCan.Draw();

	}

	return 0;
}