#pragma once

#include "CGM_Canvas2D.h"

namespace CGM {
	
	template<typename T>
	class BaseShape2D : public CGM::Entity2D<T> {
	public:

		void SetFillMode(bool Mode);
		void SetColor(uint8_t Color);

		bool GetFillMode() const;
		uint8_t GetColor() const;

	protected:

		uint8_t MyColor = CGM::Color::Black;
		bool MyFillMode = true;
	};

	typedef BaseShape2D<int> bShape2i_util;
	typedef BaseShape2D<double> bShape2d_util;

	class RectangleShape : public bShape2i_util {
	public:

		RectangleShape() {}
		RectangleShape(uint8_t Color);
		RectangleShape(uint8_t Color, CGM::Vec2i Pos, CGM::Vec2i Size);

		void AppendToCanvas(CGM::Canvas2D* Can);

	};

	class ElipseShape : public bShape2i_util {
	public:

		ElipseShape() {}
		ElipseShape(uint8_t Color);
		ElipseShape(uint8_t Color, CGM::Vec2i Pos, CGM::Vec2i Size);

		void AppendToCanvas(CGM::Canvas2D* Can);

	};

	template<typename T>
	void SaveShapeToFile(std::ofstream& out_file, const CGM::BaseShape2D<T>* Shape);

	template<typename T>
	void LoadShapeFromFile(std::ifstream& in_file, CGM::BaseShape2D<T>* Shape);

	///////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	inline void BaseShape2D<T>::SetFillMode(bool Mode) {
		this->MyFillMode = Mode;
	}

	template<typename T>
	inline void BaseShape2D<T>::SetColor(uint8_t Color) {
		this->MyColor = Color;
	}

	template<typename T>
	inline bool BaseShape2D<T>::GetFillMode() const {
		return this->MyFillMode;
	}

	template<typename T>
	inline uint8_t BaseShape2D<T>::GetColor() const {
		return this->MyColor;
	}

	template<typename T>
	void SaveShapeToFile(std::ofstream& out_file, const CGM::BaseShape2D<T>* Shape) {
		bool tFill = Shape->GetFillMode();
		uint8_t tCol = Shape->GetColor();
		CGM::Region2D<T> tReg = Shape->GetRegion();

		out_file.write((char*)&tFill, sizeof(bool));
		out_file.write((char*)&tCol, sizeof(uint8_t));
		out_file.write((char*)&tReg, sizeof(CGM::Region2D<T>));
	}

	template<typename T>
	void LoadShapeFromFile(std::ifstream& in_file, CGM::BaseShape2D<T>* Shape) {
		bool tFill;
		uint8_t tCol;
		CGM::Region2D<T> tReg;

		in_file.read((char*)&tFill, sizeof(bool));
		in_file.read((char*)&tCol, sizeof(uint8_t));
		in_file.read((char*)&tReg, sizeof(CGM::Region2D<T>));

		Shape->SetFillMode(tFill);
		Shape->SetColor(tCol);
		Shape->SetPosition(tReg.Position);
		Shape->SetSize(tReg.Size);
	}

}