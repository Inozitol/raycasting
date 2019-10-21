#ifndef _CANIMATION_H_
	#define _CANIMATION_H_

#include <SDL2/SDL.h>

class CAnimation {
	private:
		int CurrentFrame;
		int FrameInc;
		int FrameRate;
		long OldTime;
	public:
		int MaxFrames;
		bool Oscillate;
		CAnimation();
		void OnAnimate();
		void SetFrameRate(int Rate);
		void SetCurrentFrame(int Frame);
		int GetCurrentFrame();
};

#endif
