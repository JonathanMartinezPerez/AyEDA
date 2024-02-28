#include "factorycell.h"

Cell* FactoryCellAce100::createCell(const Position& p,const State& s) const{
    return new CellAce100(p,s);
}

Cell* FactoryCellAce30::createCell(const Position& p,const State& s) const{
    return new CellAce30(p,s);
}

Cell* FactoryCellLife23_3::createCell(const Position& p,const State& s) const{
    return new CellLife23_3(p,s);
}

Cell* FactoryCellLife51_346::createCell(const Position& p,const State& s) const{
    return new CellLife51_346(p,s);
}