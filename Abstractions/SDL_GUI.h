//defines UIElement class and functions

#pragma once

using namespace std;
//text

TTF_Font* loadFont(const char* path, Uint32 size);
SDL_Texture* renderText(SDL_Renderer* renderer, const char* text, TTF_Font* font, Color c, TextQuality flags);
//UI Elements:
enum UIElement_Type {

	UNKOWN, BUTTON, ENTRY, SLIDER, PROGRESS_BAR, PAGE, PERIF

};

void defaultCallback(){}

typedef void(*Callback)(void); //Function Pointer typdef

class UIElement {
/*
*single class which can be used to represent each of the UIElement_Types:
			>UNKOWN, BUTTON, ENTRY, SLIDER, PROGRESS_BAR, PAGE
*the type variable will determine its functionality

*/
private:
	UIElement* parent; //used for pages


	Callback callback = defaultCallback; //defines function pointer for callbacks



public:
	vector<UIElement*> elems;
	Color color;
	Color mouseOverColor;
	Color mouseDownColor;
	bool pressed = false;
	string text;
	string hintText;

	bool holdable;
	bool textured;
	bool expander;

	bool perifDir;

	bool visible = true;
	int x, y, w, h;
	Color text_color;
	Sprite* texture = new Sprite();
	Sprite* mouseOverTexture = new Sprite();
	Sprite* mouseDownTexture = new Sprite();
	Sprite* currentTexture = nullptr; // works like currentColor

	Sprite* text_texture = new Sprite();
	UIElement_Type type = UNKOWN;
	Color* currentColor;
	//getters
	Color getColor();
	Color getMouseOverColor();
	Color getMouseDownColor();


	//setters
	void setColor(Color c);
	void setMouseOverColor(Color c);
	void setMouseDownColor(Color c);
	void setColors(Color a, Color b, Color c);
	void setTextures(Sprite * nat, Sprite * mover, Sprite * mdwn);
	void click();
	void release();
	void renderOwnText(SDL_Renderer* renderer, string text, TTF_Font* f, TextQuality q);
	void setCallback(Callback inp);
	Callback getCallback();
	void show();
	void hide();
	void toggle();
	void add(UIElement* adder);
	//client
	void draw(SDL_Renderer* renderer, SDL_Event* event);
	void update(SDL_Renderer* renderer, SDL_Event* event);
	void tick(SDL_Event* event);
	void init();

	void destroy();
	void createBgElements(Sprite* sp);

};
UIElement Button(int x, int y, int w, int h);
UIElement Page(int x, int y, int w, int h);
void SDL_GUI_DISPLAY(SDL_Renderer* renderer, SDL_Event* event);



//masterlist of UIElements
//each instanciated UIElement object is added here so that it can be updated each frame by SDL_GUI_DISPLAY()
//															(see bottom of this document and CosmoCombat.cpp)
vector<UIElement*> master = vector<UIElement*>();

UIElement Perif(int x, int y, int w, int h, bool dir){

	/**
	 *\param dir (Gives Direction) True = Right, False = Left
	 *
	 */
	UIElement *alloc = new UIElement();
	UIElement out = *alloc;
	out.x=x;
	out.y=y;
	out.w=w;
	out.h=h;
	out.type = PERIF;
	out.perifDir=dir;
	return out;
}
void UIElement::createBgElements(Sprite* sp){
	UIElement *p = &Perif(x,y,w,h,true);
	UIElement *p2 = &Perif(x,y,w,h,false);
	p->texture = sp;
	p2->texture=sp;

	parent->add(p);
	parent->add(p2);

}

void drawPerif(UIElement *p, SDL_Renderer* renderer){
	//TODO
	if(p->texture->texture == nullptr){
		cout <<" ERROR periferal texture is null pointer" << endl;
		return;
	}
	int pw = (p->h)*(330/748);
	SDL_Rect sprect = (SDL_Rect){0,0,p->texture->w,p->texture->h};
	if(p->perifDir){
		image(renderer, p->texture->texture, sprect, (SDL_Rect){p->x,p->y,pw,p->h});
	}else{
		image(renderer, p->texture->texture, sprect, (SDL_Rect){p->x+p->w-pw/2,p->y,pw,p->h},0.0,(SDL_Point){sprect.w/2,0},SDL_FLIP_HORIZONTAL);
	}

}

void UIElement::click() {

	pressed = true;

}
void UIElement::release() {
	if (pressed) {
		pressed = false;
		if (callback != nullptr) {
			callback();
		}
	}

}

void tickButton(UIElement* b, SDL_Event* event) {
	int x = b->x;
	int y = b->y;
	int w = b->w;
	int h = b->h;
	int mx;
	int my;
	SDL_GetMouseState(&mx, &my);

	b->currentColor = &b->color;
	b->currentTexture = b->texture;

	if (mx > x&& my > y&& mx < x + w && my < y + h) { //if in bounds
		b->currentTexture = b->mouseOverTexture;
		b->currentColor = &b->mouseOverColor;
		if(event == nullptr)return;
		if (event->button.state == SDL_PRESSED) {
			b->currentColor = &b->mouseDownColor;
			b->currentTexture = b->mouseOverTexture;
			b->click();
		}
		else {
			b->release();
		}
	}
	else {

		b->release();

	}

}
void drawButton(UIElement* b, SDL_Renderer* renderer) {
	if (b->currentTexture == nullptr) {

		quickFillRect(renderer, b->x, b->y, b->w, b->h, *b->currentColor);

	}
	else {
		quickFillRect(renderer, b->x - 1, b->y - 1, b->w + 2, b->h + 2, *b->currentColor);
		int w = 0, h = 0;
		if(SDL_QueryTexture(b->currentTexture->texture, NULL, NULL, &w, &h) < 0)  {
  			cout << "Error on texture query: "<< SDL_GetError() << endl;

		}
		SDL_Rect source = (SDL_Rect){0,0,w,h};
		SDL_Rect dest =(SDL_Rect){b->x,b->y,b->w,b->h};

		image(renderer,b->currentTexture->texture,source,dest);
	}

	if(b->text_texture->texture!=nullptr){

		quickImage(renderer,b->text_texture->texture, b->x+b->w/5,b->y+b->h/2);

	}

}
void drawPage(UIElement* p, SDL_Renderer* renderer, SDL_Event* event) {
	quickFillRect(renderer, p->x, p->y, p->w, p->h, p->color);
	for (int i = 0; i < p->elems.size(); i++) {
		p->elems.at(i)->update(renderer,event); //draw each sub element

	}

}

void UIElement::draw(SDL_Renderer* renderer,SDL_Event* event) {
	if (!visible)return;
	if (type == BUTTON) {
		drawButton(this, renderer);
	}
	else if (type == PAGE) {
		drawPage(this, renderer, event);
	}else if(type==PERIF){
		drawPerif(this, renderer);
	}



}


void UIElement::tick(SDL_Event* event) {

	if (type == BUTTON) {
		tickButton(this, event);
	}


}

void UIElement::update(SDL_Renderer* renderer, SDL_Event* event) {



	tick(event);
	draw(renderer,event);

}


Color UIElement::getColor() {
    return color;
}
Color UIElement::getMouseOverColor() {
    return mouseOverColor;
}
Color UIElement::getMouseDownColor() {
    return mouseDownColor;
}
void UIElement::setColor(Color c) {
    color = c;
}
void UIElement::setMouseOverColor(Color c) {
    mouseOverColor = c;
}
void UIElement::setMouseDownColor(Color c) {
    mouseDownColor = c;
}
void UIElement::setColors(Color normal, Color mouseOver, Color mouseDown) {
	setColor(normal);
	setMouseOverColor(mouseOver);
	setMouseDownColor(mouseDown);
}
void UIElement::setTextures(Sprite * nat, Sprite * mover, Sprite * mdwn){

	texture = nat;
	mouseOverTexture = mover;
	mouseDownTexture = mdwn;
	textured=true;

}

void UIElement::init() {
	master.push_back(this);
}
void UIElement::renderOwnText(SDL_Renderer* renderer, string text, TTF_Font *f, TextQuality q) {

	text_texture->texture = renderText(renderer,text.c_str(),f,text_color,q);
}
void UIElement::show() {
	visible = true;
}
void UIElement::hide() {
	visible = false;
}
void UIElement::toggle() {
	visible = !visible;
}
void UIElement::add(UIElement* adder) {

	if (type != PAGE) {
		cout << "Error: Attempting to add UIElements to something other than a page" << endl;
		return;
	}
	elems.push_back(adder);
	adder->parent = this;
}


//data type Callback is just a function pointer
void UIElement::setCallback(Callback inp) {
	callback = inp;
} //sets the callback function
Callback UIElement::getCallback() {

	return callback;

} //gets it

UIElement Button(int x, int y, int w, int h) {

	UIElement *alloc = new UIElement();
	UIElement out = *alloc;
	out.x = x;
	out.y = y;
	out.w = w;
	out.h = h;
	out.type = BUTTON;
	out.currentColor = &color(255, 0, 255);
	out.text_color = color(0);
	return out;

}
UIElement Page(int x, int y, int w, int h) {

	UIElement out;
	out.x = x;
	out.y = y;
	out.w = w;
	out.h = h;
	out.type = PAGE;
	out.currentColor =&color(255,255,255);
	return out;
}





void SDL_GUI_DISPLAY(SDL_Renderer*renderer,SDL_Event*event) { //root function, called in main
	for (int i = 0; i < master.size(); i++) {
		master.at(i)->update(renderer,event);
	}
	resetRenderColor(renderer);
}
void removeFromVector(vector<UIElement*> *e, UIElement* t) {
	e->erase(remove(e->begin(), e->end(), t));
} //remove from vector by value
void UIElement::destroy() {

	if (parent != nullptr) {
		removeFromVector(&parent->elems, this);
	}
	else {
		removeFromVector(&master, this); //removes element from master
	}

}
