#include "pch.h"
#include "CommonFunctions.h"
#include "Settings.h"
#include "ApplicationView.h"


//int CommonFunctions::convX_to_pixels(int pos){
//	return 25+(pos-1)*ApplicationView::FIELD_WIDTH;
//}
//
//int CommonFunctions::convX_to_position(int pix){
//	return (pix-25)/ ApplicationView::FIELD_WIDTH + 1;
//}
//
//int CommonFunctions::convY_to_pixels(int pos){
//	return 25+(pos-1)* ApplicationView::FIELD_HEIGHT;
//}
//
//int CommonFunctions::convY_to_position(int pix){
//	return (pix-25)/ ApplicationView::FIELD_HEIGHT + 1;
//}
//
//bool CommonFunctions::position_inside_board(const Position& pos) {
//	if (pos.col <= 8 && pos.col >= 1) {
//		if (pos.row <= 8 && pos.row >= 1) {
//			return true;
//		}
//	}
//	return false;
//}
//