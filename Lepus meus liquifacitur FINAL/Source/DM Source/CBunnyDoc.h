// CBunnyDoc.h#pragma once#include <LSingleDoc.h>#include "DM.h"#include "CCanvas.h"#include "CPosessions.h"// class CCanvas;class CBunnyDoc : public LSingleDoc {public:	CBunnyDoc(LCommander *inSuper, FSSpec *inFileSpec);	~CBunnyDoc();		virtual Boolean IsModified();		virtual void DoAESave( FSSpec &inFileSpec, OSType inFileType );		virtual void DoSave();		virtual void DoRevert();void SetCurrentPage(CCanvas* inPage);void HydrateFirstPage();void getCurrentPage(Int32 &pageNum);	protected:	DM* mData;		// CCanvas* mCanvas;	void NameNewDoc();		void OpenFile( FSSpec &inFileSpec );		private:	CCanvas *mCanvas;	CPosessions *mPos;//ajg};