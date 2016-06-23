#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>
#include <lib_flotilla.h>

class CPGModuleRainbow : public ModuleRainbow {
  public:
	CPGModuleRainbow(int offset) : m_offset(offset) {
	}

  protected:
	virtual void SetLED(int index, uint8_t r, uint8_t g, uint8_t b) {
		CircuitPlayground.setPixelColor(index + m_offset, r, g, b);
	}

  private:
	int m_offset;
};

class CPGModuleButtons : public ModuleTouch {
  protected:
	virtual uint8_t GetState() {
		uint8_t state = 0;

		if (CircuitPlayground.leftButton())
			state |= 1;

		if (CircuitPlayground.rightButton())
			state |= 2;

		if (CircuitPlayground.slideSwitch())
			state |= 4;

		return state;
	}
};

Dock dock;
CPGModuleRainbow rainbow1(0);
CPGModuleRainbow rainbow2(5);
CPGModuleButtons touch1;

void setup() {
	CircuitPlayground.begin();
	Serial.begin(115200);
	while (!Serial) {
	}

	rainbow1.Init(1);
	rainbow2.Init(2);
	touch1.Init(3);

	dock.AddModule(&rainbow1);
	dock.AddModule(&rainbow2);
	dock.AddModule(&touch1);
}

void loop() {
	dock.Update(&Serial);
	dock.ProcessInput(&Serial);
	delay(10);
}
