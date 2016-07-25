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

class CPGModuleTouch : public ModuleTouch {
  public:
	CPGModuleTouch(int b1, int b2, int b3, int b4) : m_b1(b1), m_b2(b2), m_b3(b3), m_b4(b4) {
	}

  protected:
	virtual uint8_t GetState() {
		uint8_t state = 0;

		if (CircuitPlayground.readCap(m_b1) > 100)
			state |= 1;

		if (CircuitPlayground.readCap(m_b2) > 100)
			state |= 2;

		if (CircuitPlayground.readCap(m_b3) > 100)
			state |= 4;

		if (CircuitPlayground.readCap(m_b4) > 100)
			state |= 8;

		return state;
	}

  private:
	int m_b1;
	int m_b2;
	int m_b3;
	int m_b4;
};

class CPGModuleLight : public ModuleLight {
  protected:
	virtual void GetState(uint16_t& visible, uint16_t& ir, uint16_t& lux) {
		visible = CircuitPlayground.lightSensor();
		ir = visible;
		lux = visible;
	}
};

class CPGModuleMotion : public ModuleMotion {
  protected:
	virtual void GetState(Vector<int16_t>& accel, Vector<int16_t>& mag) {
		float x = CircuitPlayground.motionX();
		float y = CircuitPlayground.motionY();
		float z = CircuitPlayground.motionZ();

		accel = Vector<int16_t>{int16_t(x * 4096), int16_t(y * 4096), int16_t(z * 4096)};
		mag = Vector<int16_t>{0, 0, 0};
	}
};

Dock dock;
CPGModuleRainbow rainbow1(0);
CPGModuleRainbow rainbow2(5);
CPGModuleButtons touch1;
CPGModuleLight light;
CPGModuleMotion motion;
CPGModuleTouch touch2(12, 6, 9, 10);

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
	touch2.Init(6);

	dock.AddModule(&rainbow1);
	dock.AddModule(&rainbow2);
	dock.AddModule(&touch1);
	dock.AddModule(&light);
	dock.AddModule(&motion);
	dock.AddModule(&touch2);
}

void loop() {
	dock.Update(&Serial);
	dock.ProcessInput(&Serial);
	delay(100);
}
