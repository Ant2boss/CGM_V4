#pragma once

#include "CGM_Vector2D.h"
#include "CGM_Region2D.h"

#include <vector>
#include <fstream>
#include <Windows.h>

namespace CGM {

	template<typename T>
	class Entity2D;

	struct Color {
		//Disable making an instance of this class
		Color() = delete;

		static const uint8_t Black = 0;

		static const uint8_t Gray = 1;
		static const uint8_t White = 2;

		static const uint8_t Red = 3;
		static const uint8_t DarkRed = 4;

		static const uint8_t Cyan = 5;
		static const uint8_t Blue = 6;
		static const uint8_t DarkBlue = 7;

		static const uint8_t Green = 8;
		static const uint8_t DarkGreen = 9;

		static const uint8_t Magenta = 10;
		static const uint8_t Indigo = 11;

		static const uint8_t Brown = 12;
		static const uint8_t Bisque = 13;
		static const uint8_t Yellow = 14;
		static const uint8_t Orange = 15;
	};

	class Canvas2D {
	public:

		Canvas2D(size_t x, size_t y);

		~Canvas2D();

		void SetCharAt(char C, int x, int y);
		void SetCharAt(char C, CGM::Vec2i V);

		void SetColorAt(uint8_t Color, int x, int y);
		void SetColorAt(uint8_t Color, CGM::Vec2i V);

		void SetFontColorAt(uint8_t Color, int x, int y);
		void SetFontColorAt(uint8_t Color, CGM::Vec2i V);

		void SetBackColorAt(uint8_t Color, int x, int y);
		void SetBackColorAt(uint8_t Color, CGM::Vec2i V);

		char GetCharAt(int x, int y) const;
		char GetCharAt(CGM::Vec2i V) const;

		uint8_t GetColorAt(int x, int y) const;
		uint8_t GetColorAt(CGM::Vec2i V) const;
		
		CGM::Vec2i GetSize() const;
		CGM::Reg2i GetRegion() const;

		static CGM::Vec2i GetMousePos();

		void AppendLine(uint8_t Color, CGM::Vec2i Start, CGM::Vec2i End);
		void AppendLine(uint8_t Color, int xStart, int yStart, int xEnd, int yEnd);

		template<typename EntityType>
		void Append(CGM::Entity2D<EntityType>* EntityToAdd);

		void Clear(uint8_t ClearColor = 0, char ClearChar = ' ');

		void Draw();

	private:

		std::vector<CHAR_INFO> MyCharInfoArray;
		CGM::Vec2i MySize;

		HANDLE MyInput;
		HANDLE MyOutput;

		CONSOLE_SCREEN_BUFFER_INFOEX MyCSBI;
		CONSOLE_SCREEN_BUFFER_INFOEX MyBackupCSBI;

		COORD MyBuffSize;
		COORD MyBuffCoord;
		SMALL_RECT MySR;

		int index_of(CGM::Vec2i V) const;
		int index_of(int x, int y) const;

	};

	template<typename T>
	class Entity2D {
	public:

		void SetID(uint32_t ID);

		void SetSize(T x, T y);
		void SetSize(CGM::Vector2D<T> Size);

		void SetPosition(T x, T y);
		void SetPosition(CGM::Vector2D<T> Pos);

		void SetRegion(CGM::Region2D<T> Reg);

		void MoveEntity(T x, T y);
		void MoveEntity(CGM::Vector2D<T> Vec);

		uint32_t GetID() const;

		CGM::Vector2D<T> GetSize() const;
		CGM::Vector2D<T> GetPosition() const;

		CGM::Region2D<T> GetRegion() const;
		CGM::Region2D<T> GetLastRegion() const;

		bool IsThisOverEntity(const CGM::Entity2D<T>* Ent) const;
		bool IsThisOverRegion(CGM::Region2D<T> Reg) const;
		bool IsThisOverVector(CGM::Vector2D<T> Vec) const;

		bool CanThisMoveWithoutOverlap(T x, T y, const CGM::Entity2D<T>* Ent) const;
		bool CanThisMoveWithoutOverlap(CGM::Vector2D<T> Vec, const CGM::Entity2D<T>* Ent) const;

		double GetDistanceFromEntity(const CGM::Entity2D<T>* Ent) const;
		double GetDistanceFromEntity_Squared(const CGM::Entity2D<T>* Ent) const;


		virtual void AppendToCanvas(CGM::Canvas2D* Can) = 0;

	protected:
		CGM::Region2D<T> MyRegion;
		CGM::Region2D<T> MyLastRegion;

		uint32_t MyID = 0;
	};
	
	typedef Entity2D<int> Ent2i_util;
	typedef Entity2D<double> Ent2d_util;

	void AppendMessageToCanvas(CGM::Canvas2D* Can, const char* Message, uint8_t Color, int x, int y);
	void AppendMessageToCanvas(CGM::Canvas2D* Can, const char* Message, uint8_t Color, CGM::Vec2i P);

	template<typename T>
	void SaveEntity2DToFile(std::ofstream& file_out, const CGM::Entity2D<T>* Ent);

	template<typename T>
	void LoadEntity2DFromFile(std::ifstream& file_in, CGM::Entity2D<T>* Ent);

	///////////////////////////////////////////////////////////////////////////////////////////////

	template<typename EntityType>
	inline void Canvas2D::Append(CGM::Entity2D<EntityType>* EntityToAdd) {
		EntityToAdd->AppendToCanvas(this);
	}

	template<typename T>
	inline void Entity2D<T>::SetID(uint32_t ID) {
		this->MyID = ID;
	}

	template<typename T>
	inline void Entity2D<T>::SetSize(T x, T y) {
		this->SetSize(CGM::Vector2D<T>(x, y));
	}

	template<typename T>
	inline void Entity2D<T>::SetSize(CGM::Vector2D<T> Size) {
		//this->MyModifiedStatus = true;
		this->MyLastRegion = this->MyRegion;
		this->MyRegion.Size = Size;
	}

	template<typename T>
	inline void Entity2D<T>::SetPosition(T x, T y) {
		this->SetPosition(CGM::Vector2D<T>(x, y));
	}

	template<typename T>
	inline void Entity2D<T>::SetPosition(CGM::Vector2D<T> Pos) {
		//this->MyModifiedStatus = true;
		this->MyLastRegion = this->MyRegion;
		this->MyRegion.Position = Pos;
	}

	template<typename T>
	inline void Entity2D<T>::SetRegion(CGM::Region2D<T> Reg) {
		this->SetPosition(Reg.Position);
		this->SetSize(Reg.Size);
	}

	template<typename T>
	inline void Entity2D<T>::MoveEntity(T x, T y) {
		this->MoveEntity(CGM::Vector2D<T>(x, y));
	}

	template<typename T>
	inline void Entity2D<T>::MoveEntity(CGM::Vector2D<T> Vec) {
		//this->MyModifiedStatus = true;
		this->MyLastRegion = this->MyRegion;
		this->MyRegion.Position += Vec;
	}

	template<typename T>
	inline uint32_t Entity2D<T>::GetID() const {
		return this->MyID;
	}

	template<typename T>
	inline CGM::Vector2D<T> Entity2D<T>::GetSize() const {
		return this->MyRegion.Size;
	}

	template<typename T>
	inline CGM::Vector2D<T> Entity2D<T>::GetPosition() const {
		return this->MyRegion.Position;
	}

	template<typename T>
	inline CGM::Region2D<T> Entity2D<T>::GetRegion() const {
		return this->MyRegion;
	}

	template<typename T>
	inline CGM::Region2D<T> Entity2D<T>::GetLastRegion() const {
		return this->MyLastRegion;
	}

	template<typename T>
	inline bool Entity2D<T>::IsThisOverEntity(const CGM::Entity2D<T>* Ent) const {
		return this->MyRegion.is_over_a_region(Ent->MyRegion);
	}

	template<typename T>
	inline bool Entity2D<T>::IsThisOverRegion(CGM::Region2D<T> Reg) const {
		return this->MyRegion.is_over_a_region(Reg);
	}

	template<typename T>
	inline bool Entity2D<T>::IsThisOverVector(CGM::Vector2D<T> Vec) const {
		return this->MyRegion.is_over_a_vector(Vec);
	}

	template<typename T>
	inline bool Entity2D<T>::CanThisMoveWithoutOverlap(T x, T y, const CGM::Entity2D<T>* Ent) const {
		return this->CanThisMoveWithoutOverlap(CGM::Vector2D<T>(x, y), Ent);
	}

	template<typename T>
	inline bool Entity2D<T>::CanThisMoveWithoutOverlap(CGM::Vector2D<T> Vec, const CGM::Entity2D<T>* Ent) const {
		CGM::Region2D<T> tReg = this->MyRegion;
		tReg.Position += Vec;
		return tReg.is_over_a_region(Ent->MyRegion);
	}

	template<typename T>
	inline double Entity2D<T>::GetDistanceFromEntity(const CGM::Entity2D<T>* Ent) const {
		return this->MyRegion.Position.get_distance(Ent->MyRegion.Position);
	}

	template<typename T>
	inline double Entity2D<T>::GetDistanceFromEntity_Squared(const CGM::Entity2D<T>* Ent) const {
		return this->MyRegion.Position.get_distance_squared(Ent->MyRegion.Position);
	}

	template<typename T>
	void SaveEntity2DToFile(std::ofstream& file_out, const CGM::Entity2D<T>* Ent) {
		CGM::Region2D<T> tReg = Ent->GetRegion();
		file_out.write((char*)&tReg, sizeof(CGM::Region2D<T>));
	}

	template<typename T>
	void LoadEntity2DFromFile(std::ifstream& file_in, CGM::Entity2D<T>* Ent) {
		CGM::Region2D<T> tReg;
		file_in.read((char*)&tReg, sizeof(Region2D<T>));

		Ent->SetPosition(tReg.Position);
		Ent->SetSize(tReg.Size);
	}

}
