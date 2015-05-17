#include "Entity.h"
#include "../item/Item.h"

class ItemEntity : public Entity {
public:
	ItemEntity(TileSource &,float,float,float,ItemInstance const&);
	ItemEntity(TileSource &);
}
