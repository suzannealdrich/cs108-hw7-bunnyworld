#include "CMultiPanelButton.h"#include "CDocumentApp.h"CMultiPanelButton::CMultiPanelButton(LStream *inStream) : LBevelButton(inStream) {	inStream->ReadData(&mDir,sizeof(int));	LPane *pane = this->GetSuperView()->FindPaneByID(2);	mpv = (LMultiPanelView *)CDocumentApp::FindPaneInMyWindow(this,2);}void CMultiPanelButton::HotSpotResult(SInt16 inHotSpot) {	UInt16 which, total;	which = mpv->GetCurrentIndex();	total = mpv->GetPanelCount();		if (mDir == 1) {		if (which < total) mpv->SwitchToPanel(which + 1);	} else {		if (which > 1) mpv->SwitchToPanel(which - 1);	}}