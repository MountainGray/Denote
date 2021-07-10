#ifndef ENUMS_H
#define ENUMS_H

#include <QGraphicsItem>

const int UserType = QGraphicsItem::UserType;

enum graphics {
    TypePage = UserType+1,
    TypePenStroke = UserType+2,
    TypeFillStroke = UserType+3,
    TypeEraser = UserType+4,
    TypeSelectionBox = UserType+5,
    TypeCircleSelect = UserType+6,
    TypeLassoSelect = UserType+7,
    TypeImage = UserType+8
};

#endif // ENUMS_H
