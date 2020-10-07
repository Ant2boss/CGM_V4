#include<iostream>

#include "CGM_Log_addon.h"
#include "CGM_Canvas2D.h"

#include "CGM_Shapes2D.h"

#include "CGM_TextBox2D.h"

using namespace std;

int main() {

	CGM::Canvas2D MyCan(128, 48);
	
	CGM::TextBox MyText(CGM::Vec2i(24, 5));
	CGM::RectangleShape MyRect(CGM::Canvas2D::Color::Gray);

	MyText.SetFontColor(CGM::Canvas2D::Color::White);
	MyText.SetFormatMode_TextBreak(true);
	
	MyText << "Hello\nI am the Darkness Of the World";
	MyText.SetFontColor(CGM::Canvas2D::Color::Yellow);
	MyText << " And I have The time to ddudd audsdasd duel!" << "This will probably override the start";

	while (1) {
		MyCan.Clear();

		MyText.SetSize(MyCan.GetMousePos());

		MyRect.SetPosition(MyText.GetPosition());
		MyRect.SetSize(MyText.GetSize());

		MyCan.Append(&MyRect);
		MyCan.Append(&MyText);

		MyCan.Draw();

	}

	return 0;
}