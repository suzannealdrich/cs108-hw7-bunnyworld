#include "CPosessions.h"CPosessions::CPosessions(StringPtr name, const SPaneInfo &inPaneInfo,						const SViewInfo &inViewInfo) : CCanvas (name, inPaneInfo, inViewInfo) {						top = inPaneInfo.top;						highlight = false;												}							bool CPosessions::isInPosessions(Point inpt) {		int x, y;		x = inpt.h; y = inpt.v;		if (highlight) {			top = kCanvasH;		} else {			top = kCanvasH;		}		if (y > top) {		//	HighlightSelf(true);			highlight = true;			Refresh();			UpdatePort();			return true;		}		//HighlightSelf(false);		highlight = false;		Refresh();		UpdatePort();		return false;			}	void CPosessions::addItem(CShape* item) {		item->PutInside(this);			Refresh();	}	void CPosessions::removeItem(CShape* item) {}	void CPosessions::HighlightSelf(bool highlight) {		Rect r;		CalcLocalFrameRect(r);		if (!highlight) RGBForeColor(&Color_White);		::OffsetRect(&r, 0, kCanvasH);//hack  AJ		::PenSize(5, 5);		for (int j = 0; j < 5; j++) {			::InsetRect(&r, 1, 1);			::FrameRect(&r);		UpdatePort();		}		RGBForeColor(&Color_Black);		}		void CPosessions::DrawSelf() {	CCanvas::DrawSelf();	if (highlight) {	Rect r;	CalcLocalFrameRect(r);			//::OffsetRect(&r, 0, kCanvasH);//hack  AJ		for (int j = 0; j < 5; j++) {			::InsetRect(&r, 1, 1);			::FrameRect(&r);		//UpdatePort();		}	}	}