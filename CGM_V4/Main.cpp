#include<iostream>

#include "CGM_Log_addon.h"
#include "CGM_Canvas2D.h"

#include "CGM_Shapes2D.h"
#include "CGM_TextBox2D.h"
#include "CGM_Button2D.h"

using namespace std;

int main() {

	CGM::Canvas2D MyCan(128, 48);
	
	CGM::Button MyButton(CGM::Color::Red, CGM::Color::DarkRed, CGM::Vec2i(10, 5), CGM::Vec2i(32, 8));

	MyButton << "I am some cool text!" << "And I even work underwater!";

	while (1) {
		MyCan.Clear();

		if (MyButton.is_left_clicked())
			MyButton.SetSize(40, 20);
		if (MyButton.is_right_clicked())
			break;

		MyCan.Append(&MyButton);

		MyCan.Draw();
	}

	return 0;
}