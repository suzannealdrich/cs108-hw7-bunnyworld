// CResStore.h#pragma once#include "Store.h"class CResStore : public Store {public:	CResStore(ConstStringPtr type);		void getType(StringPtr outType);			void setName(ConstStringPtr name);	void getName(StringPtr outName);		void setHandle(Handle resH);	void getHandle(Handle& outH); };