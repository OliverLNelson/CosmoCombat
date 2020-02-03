
vector<Part> ALLPARTS = vector<Part>();
int numberOfParts;

Part Empty;

Part Bridge;
Part Hallway;
Part FuelReserve;
Part TorpedoBay;
Part QuadHall;
Part TriArmor;
Part ShellArmor;
Part Engine;

UIElement buttonFromPart(int index) {

	UIElement out = Button(0, 0, ICON_DIM, ICON_DIM);
	Part p = part(index);
	out.texture = sprite(p.sprite);
	out.setColors(color(255,255,255), color(230,10,15),color(150,10,15));
	return out;

}
void addPart(Part part) {
	part.num = ALLPARTS.size();
	ALLPARTS.push_back(part);

}


Part part(int index) {

	return ALLPARTS.at(index);

}
GamePart gamePart(int index) {

	Part p = part(index);
	GamePart out;
	out.origin = &p;
	out.sprite = p.sprite;
	out.rot = p.rot;
	return out;

}


void configureParts() {

	Empty.sprite = 0;
	addPart(Empty);


	Bridge.sprite = 1;
	Bridge.price = 0;
	Bridge.weight = 10;
	Bridge.type = BRIDGE;
	addPart(Bridge);


	Hallway.sprite = 10;
	Hallway.price = 50;
	Hallway.weight = 20;
	Hallway.type = HALL;
	addPart(Hallway);

	FuelReserve.price = 200;
	FuelReserve.weight = 25;
	FuelReserve.sprite = 5;
	FuelReserve.capacity = 30;
	FuelReserve.consumtion = 0;
	FuelReserve.type = STORAGE;
	addPart(FuelReserve);

	QuadHall.price = 50;
	QuadHall.weight = 20;
	QuadHall.sprite = 11;
	QuadHall.type = HALL;
	addPart(QuadHall);


	TorpedoBay.price = 200;
	TorpedoBay.weight = 50;
	TorpedoBay.sprite = 4;
	TorpedoBay.type = WEAPON;
	addPart(TorpedoBay);

	ShellArmor.price = 10;
	ShellArmor.weight = 20;
	ShellArmor.sprite = 14;
	ShellArmor.type = ARMOR;
	ShellArmor.defence = 20;
	addPart(ShellArmor);


	TriArmor.price = 50;
	TriArmor.weight = 35;
	TriArmor.sprite = 3;
	TriArmor.defence = 20;
	TriArmor.type = ARMOR;
	addPart(TriArmor);

	Engine.price = 50;
	Engine.weight = 100;
	Engine.sprite = 2;
	Engine.thrust = 1;
	addPart(Engine);

	numberOfParts = ALLPARTS.size();
}
