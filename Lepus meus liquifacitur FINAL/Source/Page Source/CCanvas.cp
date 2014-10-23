#include "CCanvas.h"#include "MiniConstants.h"//#include "CRect.h"#include "UCursor.h"//BUNNY#include "TArrayIterator.h"//#include "DMAp.h"#include "CBunnyDoc.h"#include "CShapeStore.h"#include "CPageStore.h"#include <typeinfo>	// sja/* CCanvas * -----------------   Nothing special to do in stream constructor */CCanvas::CCanvas(LStream *inStream) : LOffscreenView(inStream) {	//thisPage = new CPageTest();//BUNNY	//int j = getPage();//BUNNY	}CCanvas::~CCanvas() {//Eventually gonna need some kind of delete fn.. .//BUNNY	/*	TArrayIterator<LPane*> iterator(mSubPanes);	CShape*		theSub;	while (iterator.Next(theSub)) {		mSubCommanders.RemoveItemsAt(1, iterator.GetCurrentIndex());		delete ((CShape*) theSub);	}*/	Hide();	PutInside(nil);	SwitchTarget(LCommander::GetTopCommander());	app->GetCPalettePtr()->setTargetShape(NULL);}void CCanvas::DeleteMyself() {	/*TArrayIterator<LPane*> iterator(mSubPanes);	CShape*		theSub;	while (iterator.Next(theSub)) {		mSubCommanders.RemoveItemsAt(1, iterator.GetCurrentIndex());		delete ((CShape*) theSub);	}	Hide();	PutInside(nil);	SwitchTarget(LCommander::GetTopCommander());	app->GetCPalettePtr()->setTargetShape(NULL);*/	delete (this);}/* FinishCreateSelf * -----------------   Just get pointer to the application */void CCanvas::FinishCreateSelf() {	//SetSuperCommander(GetTopCommander());	app = (CDocumentApp *)GetTopCommander();	app->getCatalog()->UpdatePages(); // catalog ejs		//AddAttachment( new LUndoer );	//SetDirty(false);	SwitchTarget(this);}/* TellShapesEnter * -----------------   Tell shapes to execute their enter actions */void CCanvas::TellShapesEnter() {	LPane* sub;	TArrayIterator<LPane*> iterator = GetSubPanes();	// tell them to run their actions after we know everyone's been created...sja	if (app->inPlay()) {		while (iterator.Next(sub)) {			if (typeid(*sub) == typeid(CShape)) {				((CShape*)sub)->RunEnterScript();			}		}	}}/* ClickSelf * -----------------   Defines action to take when canvas is clicked on */void CCanvas::ClickSelf(const SMouseDownEvent &inMouseDown) {	SwitchTarget(this);	int tool = app->GetPalettePtr()->GetToolID();		if (app->inPlay()) tool = kArrow;	// If tool not arrow, ie a drawing tool, then set cursor and	// follow the mouse	if (tool != kArrow) {		//UCursor::SetCross();		if (::StillDown()) {			FollowTheMouse(inMouseDown, tool);		}		//UCursor::SetArrow();	}// else {		// clicked on blank part of canvas, so switch to top commander		//SwitchTarget(this);	//}	}/* FollowTheMouse * -----------------   Handles the series of events when a user clicks on the canvas */bool CCanvas::FollowTheMouse(const SMouseDownEvent &inMouseDown, int tool) {	CShape *newShape;			// make a new shape	newShape = NewShapeByClass(tool);	newShape->SetStartEnd(inMouseDown.whereLocal,inMouseDown.whereLocal);	Assert_(newShape != NULL);		// If it can resize the shape, then switch the target,	// else delete what was just created.	if (newShape->Resize(inMouseDown)) {		SwitchTarget(newShape);		return true;	} else {		newShape->DeleteMyself();	}	return false;}/* NewShapeByClass * -----------------   Creates a new run-time class given shape id. Really comes in handy */CShape *CCanvas::NewShapeByClass(int whichShape) {		// the SPaneInfo struct that the LPane needs		SPaneInfo paneInfo;		paneInfo.paneID = 0;		paneInfo.width = 0;		paneInfo.height = 0;		paneInfo.visible = true;		paneInfo.enabled = true;		paneInfo.bindings.left =			paneInfo.bindings.right =			paneInfo.bindings.top =			paneInfo.bindings.bottom = false;				paneInfo.left = 0;		paneInfo.top = 0;		paneInfo.userCon = 0;		paneInfo.superView = this;		// Fill in details for the CShapeInfo		CShapeInfo shapeInfo;				shapeInfo.start.h = shapeInfo.end.h = 0;		shapeInfo.start.v = shapeInfo.end.v = 0;		shapeInfo.frameC = app->GetPalettePtr()->GetFrameColor();		shapeInfo.fillC = app->GetPalettePtr()->GetForeColor();		shapeInfo.paneInfo = paneInfo;			switch(whichShape) {		case (kBox): // make a new box			CShape *rect = new CShape(shapeInfo);			rect->FinishCreate();			rect->Refresh();			return rect;		break;	}	// Don't know what to create, return null		return NULL;}//Decomped from NewShapeByClass, AJ 3/1//Creates the necessary paneinfo from the stored informationCShapeInfo CCanvas::MakeInfo (CShapeStore* temp) {Point start, end;Boolean tB;	SPaneInfo paneInfo;		paneInfo.paneID = 0;		temp->getStart(start);		temp->getEnd(end);						// account for knob width which changes the width & height		start.h -= kKnobWidth;		start.v -= kKnobHeight;		end.h += kKnobWidth;		end.v += kKnobHeight;				paneInfo.width = end.h - start.h;		if (paneInfo.width < 0) paneInfo.width = 0 - paneInfo.width;		paneInfo.height = end.v - start.v;		if (paneInfo.width < 0) paneInfo.height = 0 - paneInfo.height;		temp->getVisible(tB);//almost surely unecessary, nyet?  AJ 3/8		paneInfo.visible = true;		paneInfo.enabled = true;		paneInfo.bindings.left =			paneInfo.bindings.right =			paneInfo.bindings.top =			paneInfo.bindings.bottom = false;		if (start.h < end.h) {			paneInfo.left = start.h;		} else {			paneInfo.left = end.h;		}		if (start.v < end.v) {			paneInfo.top = start.v;		} else {			paneInfo.top = end.v;		}		paneInfo.userCon = 0;		paneInfo.superView = this;		// Fill in details for the CShapeInfo		CShapeInfo shapeInfo;		// account for knob width which changes the width & height		start.h += kKnobWidth;		start.v += kKnobHeight;		end.h -= kKnobWidth;		end.v -= kKnobHeight;				shapeInfo.start.h = start.h;		shapeInfo.end.h = end.h;		shapeInfo.start.v = start.v;		shapeInfo.end.v = end.v;		shapeInfo.frameC = Color_Black;//testy. . .		shapeInfo.fillC = Color_White;		shapeInfo.paneInfo = paneInfo;		return shapeInfo;}#pragma mark -#pragma mark === Bunny added functions //BUNNY  //This is heavily modified. . .many changes.  Must fix  AJ 3/5//Constructor  //APP needs to pass in all three for correct creation!!  AJ 3/1CCanvas::CCanvas (int num, const SPaneInfo &inPaneInfo,					const SViewInfo &inViewInfo) : LOffscreenView(inPaneInfo, inViewInfo),					LCommander(LWindow::FindWindowByID(kBunnyWindowID)) {	DM* dM;	CShapeStore* temp;	Int32 pageNum;	app = (CDocumentApp*) LCommander::GetTopCommander();	dM = ((CDocumentApp*) LCommander::GetTopCommander())->GetData();	thisPage = dM->getPageStore(num);	if (thisPage != NULL) {//Note: no RT error checking yet!!!		//thisPage->getPage(pageNum);	} else {		thisPage = dM->newPageStore();		thisPage->setPage(num,false); // so it doesn't try to move the shapes to the new page!!!		LStr255 newName;		getNewPageName(newName);		thisPage->setName(newName);	}		FinishCreateSelf();}void CCanvas::getNewPageName(StringPtr outname) {	app = (CDocumentApp *)GetTopCommander();	DM *dM = app->GetData();		LStr255 name(kEmptyString);	Int32 num = dM->getTotalPages() - 1; // don't count me, who was just added!	CPageStore* page;		if (num == 0) { // just me, so must be making the start page!		LString::CopyPStr(kStartPageName,outname);	} else {		do {				num++;						name = kEmptyString;			name += kUntitledPageString;			name += "\p ";			name += static_cast<SInt32>(num);						page = dM->getPageStore((StringPtr)name);		} while (page != NULL);							LString::CopyPStr(name,outname);	}}//sets the shapes from the stream.void CCanvas::SetShapes() {DM* dM = ((CDocumentApp*) LCommander::GetTopCommander())->GetData();CShapeStore* temp;Int32 pageNum;thisPage->getPage(pageNum);TArray <CShapeStore*> shapes = dM->getShapesInPage(pageNum);		TArrayIterator<CShapeStore*> iterator(shapes);		while (iterator.Next(temp)) {			CShape* shape = new CShape(temp, MakeInfo(temp));			shape->FinishCreateSelf();			shape->PutInside(this);//is this necessary?			shape->Refresh();		}		//SetDirty(false);}//Methodsvoid CCanvas::BeTarget() {	CDocumentApp *app = (CDocumentApp *) GetTopCommander();	app->GetCPalettePtr()->setTargetShape(NULL);}void CCanvas::getName(StringPtr outName) {	thisPage->getName(outName);}void CCanvas::getPage(Int32& pageNum) {	thisPage->getPage(pageNum);}void CCanvas::SetName(StringPtr name) {	thisPage->setName(name);}void CCanvas::DrawSelf() {	Rect r;	CalcLocalFrameRect(r);	::FrameRect(&r);}void CCanvas::AddShape(CShape* item) {	Int32 pageNum;	thisPage->getPage(pageNum);		item->PutInside(this);	item->setPage(pageNum);	Refresh();}//removes the shape in question from the data for the CPageStorevoid CCanvas::RemoveShape(CShape* item, bool rFD) {	DM* dM = ((CDocumentApp*) LCommander::GetTopCommander())->GetData();	Str255 pageName;	item->getName(pageName);	if (rFD) dM->removeShapeStore(pageName);}void CCanvas::removeMe() {	delete this;}/*Boolean CCanvas::ObeyCommand(PP_PowerPlant::CommandT inCommand, void *ioParam) {	return (LCommander::GetTopCommander()->ObeyCommand(inCommand, ioParam));}*/void CCanvas::updatePlace(Point curMPt, CShape* dShape) {//What a misonmer. May God have mercy on our souls.	//I WANT THIS CHANGED! AJ 3/8	TArrayIterator<LPane*> iterator(mSubPanes);	CShape*		theSub;	while (iterator.Next(theSub)) {		theSub->onOver(curMPt, dShape);	}}bool CCanvas::drop(Point curMPt, CShape* dShape) {//I know what you think.  Go to hell.bool success = true, oS;TArrayIterator<LPane*> iterator(mSubPanes);	CShape*		theSub;	while (iterator.Next(theSub)) {		oS = theSub->onDrop(curMPt, dShape);		if (!oS) success = false;	}	return success;}//void CCanvas::CreateName () {	/*void CCanvas::FindCommandStatus(	PP_PowerPlant::CommandT	inCommand,	Boolean					&outEnabled,	Boolean					&outUsesMark,	PP_PowerPlant::Char16	&outMark,	Str255					outName){	app = (CDocumentApp *)GetTopCommander();	switch (inCommand) {		case cmd_Close:			outEnabled = ! app->inPlay();					default:			LCommander::FindCommandStatus(inCommand, outEnabled,												outUsesMark, outMark, outName);			break;	}}*/void CCanvas::AdjustCursorSelf(Point inPortPt, const EventRecord& inMacEvent){	CDocumentApp* app = (CDocumentApp *)GetTopCommander();	int tool = kArrow;		if (app->inPlay()) {		UCursor::SetArrow();	} else {		tool = app->GetPalettePtr()->GetToolID();		if (tool != kArrow) {			UCursor::SetCross();		} else {			UCursor::SetArrow();		}		}}void CCanvas::swapMeUp (CShape* shapetoBack) {//before you gogo. . .	SInt32 indexToGo, indexFrom;		indexFrom = mSubPanes.FetchIndexOf(shapetoBack);	indexToGo = mSubPanes.GetCount();		mSubPanes.SwapItems(indexFrom, indexToGo);}