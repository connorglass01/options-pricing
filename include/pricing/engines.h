#ifndef ENGINES_H
#define ENGINES_H

#include "types.h"

PriceResult vanilla_closed_form(const MarketData&, const Vanilla&);
PriceResult vanilla_mc(const MarketData&, const Vanilla&, const MCSettings&);
PriceResult asian_mc(const MarketData&, const Asian&, const MCSettings&);

#endif