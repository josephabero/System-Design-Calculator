#include <stdint.h>
#include <L1_Drivers/gpio.hpp>
class Bus 
{
    public:
        enum class ControlType
        {
          kMemory   = 0,
          kIO       = 1
        };

        typedef union
        {
            uint8_t byte;
            struct 
            {
                uint8_t BIT0: 1;
                uint8_t BIT1: 1;
                uint8_t BIT2: 1;
                uint8_t BIT3: 1;
                uint8_t BIT4: 1;
                uint8_t BIT5: 1;
                uint8_t BIT6: 1;
                uint8_t BIT7: 1;
            } __attribute__((packed));
        } Hex_t;


        void Init();
        void Write(ControlType control, uint8_t address, uint8_t data);
        uint8_t Read(ControlType control, uint8_t address);

        void SetADPinsToOpenDrain();
        void SetADPinsToOutput();
        void SetADPinsToInput();

        void SetValueOfADPins(uint8_t val);
        uint8_t ReadValueofADPins();

    private:
        static const uint8_t num_of_ad_pins = 8;
        Gpio ad[num_of_ad_pins] = {
            Gpio(2, 2),
            Gpio(2, 5),
            Gpio(2, 7),
            Gpio(2, 9),
            Gpio(0, 15),
            Gpio(0, 18),
            Gpio(0, 1),
            Gpio(0, 10)
        };

        Gpio W      = Gpio(0, 17);
        Gpio ALE    = Gpio(0, 22);
        Gpio M_IO   = Gpio(0, 0);
        Gpio Int    = Gpio(0, 11); //This will be used in Lab 4
};
