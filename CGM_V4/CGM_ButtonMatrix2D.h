#pragma once

#include "CGM_Canvas2D.h"
#include "CGM_Button2D.h"

namespace CGM {

	class ButtonMatrix : public CGM::Ent2i_util {
	public:

		ButtonMatrix() {}
		ButtonMatrix(CGM::Vec2i init_mat_size);
		ButtonMatrix(int x_mat_size, int y_mat_size);

		void SetMatrixElementSize(int x, int y);
		void SetMatrixElementSize(CGM::Vec2i S);

		void SetMatrixColor(uint8_t Color);
		void SetMatrixSelectedColor(uint8_t Color);
		void SetMatrixNotSelectedColor(uint8_t Color);

		void SetElementColor(uint8_t Color, uint32_t el_index);
		void SetElementColor(uint8_t Color, CGM::Vec2i index);
		void SetElementColor(uint8_t Color, uint32_t x_index, uint32_t y_index);

		void SetElementSelectedColor(uint8_t Color, uint32_t el_index);
		void SetElementSelectedColor(uint8_t Color, CGM::Vec2i index);
		void SetElementSelectedColor(uint8_t Color, uint32_t x_index, uint32_t y_index);

		void SetElementNotSelectedColor(uint8_t Color, uint32_t el_index);
		void SetElementNotSelectedColor(uint8_t Color, CGM::Vec2i index);
		void SetElementNotSelectedColor(uint8_t Color, uint32_t x_index, uint32_t y_index);

		void SetSpaceBetweenElements(uint32_t dist);

		CGM::Button& operator[] (uint32_t index);
		CGM::Button& operator[] (CGM::Vec2i index);
		CGM::Button& GetElement(uint32_t index);
		CGM::Button& GetElement(CGM::Vec2i index);
		CGM::Button& GetElement(uint32_t x, uint32_t y);

		uint32_t GetMatrixIndexCount() const;
		uint32_t GetSpaceBetweenElements() const;

		CGM::Vec2i GetMatrixSize() const;
		CGM::Vec2i GetMatrixElementSize() const;

		uint8_t GetMatrixSelectedColor() const;
		uint8_t GetMatrixNotSelectedColor() const;

		uint8_t GetElementSelectedColor(uint32_t el_index) const;
		uint8_t GetElementSelectedColor(CGM::Vec2i index) const;
		uint8_t GetElementSelectedColor(uint32_t x_index, uint32_t y_index) const;

		uint8_t GetElementNotSelectedColor(uint32_t el_index) const;
		uint8_t GetElementNotSelectedColor(CGM::Vec2i index) const;
		uint8_t GetElementNotSelectedColor(uint32_t x_index, uint32_t y_index) const;

		void AddRow(uint32_t RowCount = 1);
		void AddColumn(uint32_t ColumnCount = 1);

		void AddTextToButton(uint32_t index, const char* TextToAdd);
		void AddTextToButton(CGM::Vec2i index, const char* TextToAdd);
		void AddTextToButton(uint32_t x, uint32_t y, const char* TextToAdd);

		bool is_hovered() const;
		bool is_hovered(uint32_t& hovered_index) const;
		bool is_hovered(CGM::Vec2i& hovered_index) const;
		bool is_hovered(uint32_t& x_hovered, uint32_t& y_hovered) const;

		bool is_left_clicked() const;
		bool is_left_clicked(uint32_t& hovered_index) const;
		bool is_left_clicked(CGM::Vec2i& hovered_index) const;
		bool is_left_clicked(uint32_t& x_hovered, uint32_t& y_hovered) const;

		bool is_right_clicked() const;
		bool is_right_clicked(uint32_t& hovered_index) const;
		bool is_right_clicked(CGM::Vec2i& hovered_index) const;
		bool is_right_clicked(uint32_t& x_hovered, uint32_t& y_hovered) const;

		void ResetMatrix();

		void ResetElement(uint32_t index);
		void ResetElement(CGM::Vec2i index);
		void ResetElement(uint32_t x, uint32_t y);

		void AppendToCanvas(CGM::Canvas2D* Can);

	private:

		std::vector<CGM::Button> MyButtonArray;
		CGM::Vec2i MyMatSize = CGM::Vec2i(1, 1);
		CGM::Vec2i MyElementSize;

		uint8_t MySelectedColor = CGM::Color::Black;
		uint8_t MyNotSelectedColor = CGM::Color::Black;

		uint32_t MySpaceBetweenElemenets = 1;

		void resize_array();
		void update_matrix_elements();
		void apply_matrix_coloring();

		int index_of(int index) const;
		int index_of(int x, int y) const;
		int index_of(CGM::Vec2i i) const;

	public:

		void SetSize(int x, int y) = delete;
		void SetSize(CGM::Vec2i S) = delete;
		void SetRegion(CGM::Reg2i R) = delete;

		friend void SaveButtonMatrixToFile(std::ofstream&, const CGM::ButtonMatrix*);

		friend void LoadButtonMatrixFromFile(std::ifstream&, CGM::ButtonMatrix*);

	};

	void SaveButtonMatrixToFile(std::ofstream& out_file, const CGM::ButtonMatrix* butt_mat);

	void LoadButtonMatrixFromFile(std::ifstream& in_file, CGM::ButtonMatrix* butt_mat);

}
