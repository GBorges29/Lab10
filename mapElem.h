/**
 * @file mapElem.h
 * @brief Defines the types MapKey and MapValue.
 * 
 * The MapKey is an alias to the type of keys 
 * held by an instance of the ADT Map (PtMap).
 * 
 * The MapValue is an alias to the type of values 
 * held by an instance of the ADT Map (PtMap).
 *  
 * These aliases must be changed according to the use-case.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#pragma once

#include <stdbool.h>
#include "stringWrap.h" // ADICIONADO

/** Key type definition. Alterado para StringWrap */
typedef StringWrap MapKey;

/** Value type definition. Mantém-se como int */
typedef int MapValue;

/**
 * @brief Prints a key.
 * 
 * Must be implemented according to the concrete
 * type of MapKey.
 * 
 * @param key [in] key to print
 */
void mapKeyPrint(MapKey key);

/**
 * @brief Prints a value.
 * 
 * Must be implemented according to the concrete
 * type of MapValue.
 * 
 * @param value [in] value to print
 */
void mapValuePrint(MapValue value);

/**
 * @brief Compares two keys.
 * 
 * This function provides the comparison criteria
 * between two keys.
 * 
 * @param key1 [in] a key
 * @param key2 [in] another key
 * @return 0 if they are equal.
 * @return value less than 0, if 'key1' is less than 'key2' 
 * @return value greater than 0 if 'key1' is greater than 'key2' 
 */
int mapKeyCompare(MapKey key1, MapKey key2);
