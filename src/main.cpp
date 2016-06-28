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

class CPGModuleLight : public ModuleLight {
  protected:
	virtual void GetState(uint16_t& visible, uint16_t& ir) {
		visible = CircuitPlayground.lightSensor();
		ir = visible;
	}
};

class CPGModuleMotion : public ModuleMotion {
  protected:
	virtual void GetState(Vector& accel, Vector& mag) {
		float x = CircuitPlayground.motionX();
		float y = CircuitPlayground.motionY();
		float z = CircuitPlayground.motionZ();

		accel = Vector{int16_t(x * 4096), int16_t(y * 4096), int16_t(z * 4096)};
		mag = Vector{0, 0, 0};
	}
};

Dock dock;
CPGModuleRainbow rainbow1(0);
CPGModuleRainbow rainbow2(5);
CPGModuleButtons touch1;
CPGModuleLight light;
CPGModuleMotion motion;

void setup() {
	CircuitPlayground.begin();
	Serial.begin(115200);
	while (!Serial) {
	}

	rainbow1.Init(1);
	rainbow2.Init(2);
	touch1.Init(3);
	light.Init(4);
	motion.Init(5);

	dock.AddModule(&rainbow1);
	dock.AddModule(&rainbow2);
	dock.AddModule(&touch1);
	dock.AddModule(&light);
	dock.AddModule(&motion);
}

void loop() {
	dock.Update(&Serial);
	dock.ProcessInput(&Serial);
	delay(10);
}
