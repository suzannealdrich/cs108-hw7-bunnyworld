// CResStore.cp// Mar 99 - Hacked for BunnyWorld - sja#include "CResStore.h"#include "DM.h"CResStore::CResStore(ConstStringPtr type)	: Store() {	SetString(TYPE, type);}void CResStore::getType(StringPtr outType) {	Boolean found = FindString(TYPE, outType);}void CResStore::setName(ConstStringPtr name) {	SetString(NAME, name);}void CResStore::getName(StringPtr outName) {	Boolean found = FindString(NAME, outName);}void CResStore::setHandle(Handle resH) {	SetPtr(HANDLE, resH);}void CResStore::getHandle(Handle& outH) {	Boolean found = FindPtr(HANDLE, outH);}