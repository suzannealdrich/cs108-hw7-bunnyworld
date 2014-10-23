// CDrawUtils.cp// Created 31-Oct-95 by Albert C. Lin// A bunch of random utilities for MiniDraw#include "CDrawUtils.h"short CDrawUtils::ShortMin(const short &a, const short &b){	if (a < b) return a;	else return b;}short CDrawUtils::ShortMax(const short &a, const short &b){	if (a > b) return a;	else return b;}// � CDrawUtils::CalcEnclosingRect// Takes two points and returns the rectangle that exactly encloses the two pointsvoid CDrawUtils::CalcEnclosingRect(const Point &a, const Point &b, Rect &outEncl){	outEncl.left = CDrawUtils::ShortMin(a.h, b.h);	outEncl.top = CDrawUtils::ShortMin(a.v, b.v);	outEncl.right = CDrawUtils::ShortMax(a.h, b.h);	outEncl.bottom = CDrawUtils::ShortMax(a.v, b.v);}Boolean CDrawUtils::EqualRGBColor(const RGBColor &c1, const RGBColor &c2){	return ((c1.red == c2.red) && (c1.green == c2.green) && (c1.blue == c2.blue));}// � CDrawUtils::PtOnLine// This code is taken from Graphics Gems (ed. Glassner), p. 49// Given a line through P:(px, py) and Q:(qx, qy), we want to determine whether// T:(tx, ty) is on the line// Returns 0 if T is not on the line through     <--P--Q-->//         1 if T is on the open ray ending at P:   <--P//         2 if T is on the closed interior along:  P--Q//         3 if T is on the open ray ending at Q:      Q-->#define ABS(a)		(((a)<0) ? -(a) : (a))#define MAX(a, b)	(((a)>(b)) ? (a) : (b))int CDrawUtils::PtOnLine(short px, short py, short qx, short qy, short tx, short ty){	if (ABS((qy-py)*(tx-px)-(ty-py)*(qx-px)) >=		(MAX(ABS(qx-px), ABS(qy-py)))) return(0);			if (((qx<px)&&(px<tx)) || ((qy<py)&&(py<ty))) return(1);	if (((tx<px)&&(px<qx)) || ((ty<py)&&(py<qy))) return(1);		if (((px<qx)&&(qx<tx)) || ((py<qy)&&(qy<ty))) return(3);	if (((tx<qx)&&(qx<px)) || ((ty<qy)&&(qy<py))) return(3);	return(2);}