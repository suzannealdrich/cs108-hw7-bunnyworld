// CPageStore.cp// Mar 99 - Hacked for BunnyWorld - sja#include "CPageStore.h"#include "DM.h"CPageStore::CPageStore() 	: Store() {	SetString(TYPE, PAGE);}void CPageStore::getType(StringPtr outType) {	Boolean found = FindString(TYPE, outType);}void CPageStore::setName(ConstStringPtr name) {	SetString(NAME, name);}void CPageStore::getName(StringPtr outName) {	Boolean found = FindString(NAME, outName);}void CPageStore::setPage(Int32 pageNum) {	SetInt32(PAGENUM, pageNum);}void CPageStore::getPage(Int32& outPageNum) {	Boolean found = FindInt32(PAGENUM, outPageNum);}