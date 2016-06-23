#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>
#include <dock.h>
#include <modulerainbow.h>

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

Dock dock;
CPGModuleRainbow rainbow1(0);
CPGModuleRainbow rainbow2(5);

void setup() {
	CircuitPlayground.begin();
	Serial.begin(115200);
	while (!Serial) {
	}

	rainbow1.Init(1);
	rainbow2.Init(2);
	dock.AddModule(&rainbow1);
	dock.AddModule(&rainbow2);
}

void loop() {
	dock.Update(&Serial);
	dock.ProcessInput(&Serial);
	delay(10);
}
