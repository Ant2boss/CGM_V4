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
	MyText.SetFormatMode_TextBreak(false);
	MyText.SetFormatMode_CenterTopDown(true);
	
	MyText << "Lorem, ipsum dolor sit amet consectetur adipisicing elit. Aperiam id voluptate doloremque vitae voluptatibus quae eaque corrupti, architecto veniam rerum reprehenderit quis quo doloribus libero impedit laboriosam fugit deleniti itaque.";

	MyText.SetPosition(10, 5);

	CGM::TextBox TextLoadingExample;
	std::ifstream in("TestText.bin", ios_base::binary);
	if (!in) {
		cerr << "Error opeing file!";
		return -1;
	}

	CGM::LoadTextBoxFromFile(in, &TextLoadingExample);

	in.close();
	
	while (1) {
		MyCan.Clear();

		//MyText.SetSize(MyCan.GetMousePos() - MyText.GetPosition() + CGM::Vec2i(1, 1));

		MyRect.SetPosition(TextLoadingExample.GetPosition());
		MyRect.SetSize(TextLoadingExample.GetSize());

		MyCan.Append(&MyRect);
		MyCan.Append(&TextLoadingExample);

		if (MyRect.GetRegion().is_over_a_vector(MyCan.GetMousePos()) && GetKeyState(VK_LBUTTON) < 0)
			break;

		MyCan.Draw();

	}

	return 0;
}