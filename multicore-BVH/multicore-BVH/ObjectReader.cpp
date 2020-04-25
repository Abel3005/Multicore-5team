#include "ObjectReader.h"
ObjectReader::ObjectReader() {}
void ObjectReader::readTxt(const char* filename)
{
    FILE* infp;
    fopen_s(&infp, filename, "r");
    fscanf_s(infp, "%d", &num);
    objectList = new Object[num];
    for (int i = 0; i < num; i++) {
        fscanf_s(infp, "%d %d %d %d %d %d %d", &objectList[i].points[0].x, &objectList[i].points[0].y, &objectList[i].points[1].x, &objectList[i].points[1].y, &objectList[i].points[2].x, &objectList[i].points[2].y,&objectList[i].scalarValue );
    }
    fclose(infp);
}
ObjectReader::~ObjectReader() {}