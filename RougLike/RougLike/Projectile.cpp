#include "Projectile.h"

Projectile::Projectile(char d) {
	_dir = d;
	_sym = _arrows[d];
}
void Projectile::Move(Map m) {
	GameObj* Near = this;
	switch (_dir) {
	case 1:
		Near = m.GetSmth(_x, _y+1);
	case 2:
		Near = m.GetSmth(_x + 1, _y);
	case 3:
		Near = m.GetSmth(_x, _y - 1);
	case 4:
		Near = m.GetSmth(_x - 1, _y );
	}
	char N = Near->GetSym();
	if (N == 'K') {
		Near->TakeDmg(_damage);
		m.SetSmth(_x, _y, new Space(_x, _y));
	} else if (N == '#') {
		m.SetSmth(_x,_y,new Space(_x, _y));
	}
};

bool Projectile::TakeDmg(int dmg) {
	return 1;
}