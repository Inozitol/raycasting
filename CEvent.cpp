#include "CEvent.h"
#include <cmath>

CEvent::CEvent(){
}

CEvent::~CEvent(){
}

void CEvent::OnEvent(SDL_Event* Event){
	switch(Event->type){
		case SDL_WINDOWEVENT: {
			switch(Event->window.event){
				case SDL_WINDOWEVENT_ENTER: {
					break;			
				}
				case SDL_WINDOWEVENT_LEAVE: {
					break;
				}
				case SDL_WINDOWEVENT_RESIZED: {
					OnResize(Event->window.data1,Event->window.data2);
					break;			
				}
				case SDL_WINDOWEVENT_EXPOSED: {
					OnExpose();
					break;			
				}
			}
			break;
		}
		
		case SDL_KEYDOWN: {
			OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod);
			break;		
		}
		case SDL_KEYUP: {
			OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod);
			break;
		}
		case SDL_MOUSEMOTION: {
			OnMouseMove(Event->motion.x, Event->motion.y, Event->motion.xrel, Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
			break;		
		}
		case SDL_MOUSEBUTTONDOWN: {
			switch(Event->button.button){
				case SDL_BUTTON_LEFT: {
					OnLButtonDown(Event->button.x,Event->button.y);
					break;			
				}
				case SDL_BUTTON_RIGHT: {
				OnRButtonDown(Event->button.x,Event->button.y);
				break;
			}
			case SDL_BUTTON_MIDDLE: {
				OnMButtonDown(Event->button.x,Event->button.y);
				break;			
			}
		}
	        break;	
		}

		case SDL_MOUSEBUTTONUP: {
			switch(Event->button.button){
				case SDL_BUTTON_LEFT: {
					OnLButtonUp(Event->button.x,Event->button.y);
					break;			
				}
				case SDL_BUTTON_RIGHT: {
					OnRButtonUp(Event->button.x,Event->button.y);
					break;			
				}
				case SDL_BUTTON_MIDDLE: {
					OnMButtonUp(Event->button.x,Event->button.y);
					break;			
				}
			}			
			break;
		}

		case SDL_JOYAXISMOTION: {
			OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
			break;			
		}
		
		case SDL_JOYBALLMOTION: {
			OnJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
			break;			
		}
		
		case SDL_JOYHATMOTION: {
			OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
 			break;			
		}

		case SDL_JOYBUTTONDOWN: {
			OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
			break;			
		}

		case SDL_JOYBUTTONUP: {
			OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
  			break;			
		}

		case SDL_QUIT: {
			OnExit();
	 		break;		
		}

		default: {
			OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
	       		break;		
		}

	}
}




void CEvent::OnInputFocus(){}
void CEvent::OnInputBlur(){}
void CEvent::OnKeyUp(SDL_Keycode sym, Uint16 mod){}
void CEvent::OnKeyDown(SDL_Keycode sym, Uint16 mod){}
void CEvent::OnMouseFocus(){}
void CEvent::OnMouseBlur(){}
void CEvent::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle){}
void CEvent::OnMouseWheel(bool Up, bool Down){}
void CEvent::OnLButtonDown(int mX, int mY){}
void CEvent::OnLButtonUp(int mX, int mY){}
void CEvent::OnRButtonDown(int mX, int mY){}
void CEvent::OnRButtonUp(int mX, int mY){}
void CEvent::OnMButtonDown(int mX, int mY){}
void CEvent::OnMButtonUp(int mX, int mY){}
void CEvent::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value){}
void CEvent::OnJoyButtonDown(Uint8 which, Uint8 button){}
void CEvent::OnJoyButtonUp(Uint8 which, Uint8 button){}
void CEvent::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value){}
void CEvent::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel){}
void CEvent::OnMinimize(){}
void CEvent::OnRestore(){}
void CEvent::OnResize(int w, int h){}
void CEvent::OnExpose(){}
void CEvent::OnExit(){}
void CEvent::OnUser(Uint8 type, int code, void* data1, void* data2){}

KeyboardHandler::KeyboardHandler():
	arrowState {false, false, false, false}
{}

bool KeyboardHandler::keyStatus(SDL_Keycode sym){
	switch(sym){
		case SDLK_UP:
			return arrowState[0];
		break;
		case SDLK_DOWN:
			return arrowState[1];
		break;
		case SDLK_LEFT:
			return arrowState[2];
		break;
		case SDLK_RIGHT:
			return arrowState[3];
		break;
	}

}

void KeyboardHandler::pressKey(SDL_Keycode sym){
	switch(sym){
		case SDLK_UP:
			arrowState[0] = true;
		break;
		case SDLK_DOWN:
			arrowState[1] = true;
		break;
		case SDLK_LEFT:
			arrowState[2] = true;
		break;
		case SDLK_RIGHT:
			arrowState[3] = true;
		break;
	}
}

void KeyboardHandler::releaseKey(SDL_Keycode sym){
	switch(sym){
		case SDLK_UP:
			arrowState[0] = false;
		break;
		case SDLK_DOWN:
			arrowState[1] = false;
		break;
		case SDLK_LEFT:
			arrowState[2] = false;
		break;
		case SDLK_RIGHT:
			arrowState[3] = false;
		break;
	}
}
