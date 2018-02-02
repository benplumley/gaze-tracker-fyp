#ifndef EYEINTERFACE_H
#define EYEINTERFACE_H

struct EYE {
	int x;
	int y;
};

struct EYELIKEDATA {
	int face_width;
	EYE left_eye;
	EYE right_eye;
};

class EyeInterface {
	public:
		EyeInterface();
		// struct EYELIKEDATA {
		// 	int face_width;
		// 	EYE left_eye;
		// 	EYE right_eye;
		// };
		EYELIKEDATA getData();
};

#endif
