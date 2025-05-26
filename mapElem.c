/**
 * @file mapElem.c
 * @brief Implements operations for types MapKey and MapValue.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "mapElem.h"
#include <stdio.h>
#include <string.h>

void mapKeyPrint(MapKey key) {
    printf("%s", key.text);
}

void mapValuePrint(MapValue value) {
    printf("%d", value);
}

int mapKeyCompare(MapKey key1, MapKey key2) {
    return strcmp(key1.text, key2.text);
}
