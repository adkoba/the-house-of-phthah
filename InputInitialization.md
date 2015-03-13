# When to create input instances? #

For the moment the input is initialized inside the ExampleFrameListener in CHouseOfPhthah.
I suggest that we initialized it directly in CHouseOfPhthah once and for all, so that we can pass the following pointers:
  * OIS::InputManager**mInputManager;
  * OIS::Mouse**		mMouse;
  * OIS::Keyboard**mKeyboard;
  * OIS::JoyStick**	mJoy;
can be passed each time it is needed.

I am not sure whether or not it is a good idea, so tell me what are your feelings about this.

Dis c'est un peu reloud de parler anglais à des heures aussi tardives... ;-)