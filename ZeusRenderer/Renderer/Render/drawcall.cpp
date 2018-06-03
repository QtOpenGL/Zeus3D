#include "DrawCall.h"

DrawCall::DrawCall()
{
    // Initial setting
    setSide(false);
    setType(NULL_DC);
    setFullStatic(false);
    objectCount = 0;
    dataBuffer = nullptr;
    simpleBuffer = nullptr;
}

DrawCall::~DrawCall(){}
