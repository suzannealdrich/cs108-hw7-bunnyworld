#pragma once#include "LPane.h"#include "CShape.h"class CResDraw : public LPane {	public:	enum { class_ID = FOUR_CHAR_CODE('cRES') };		CResDraw(LStream *inStream);		void DrawSelf();		void setShape(CShape *shape);			private:		CShape *shape;};