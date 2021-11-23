#ifndef GENERAL_DATATYPE_H
#define GENERAL_DATATYPE_H

#include <string>

// определение типа ОГ
enum type_og{GLONASS, GPS, GALILEO, COMPASS};

// определение типа фалов
enum type_file{STATE_TABLE_OG, ALMANAC, RINEX, ZIP, UNKNOWN};

#endif //GENERAL_DATATYPE_H