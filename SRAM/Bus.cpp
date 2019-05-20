#include "Bus.hpp"
#include "utility/log.hpp"

void Bus::Init()
{
    SetADPinsToOpenDrain();
    SetADPinsToOutput();
    ALE.SetAsOutput();
    W.SetAsOutput();
    M_IO.SetAsOutput();
    Int.SetAsInput();

    SetValueOfADPins(0);

    ALE.SetLow();
    W.SetHigh();
    M_IO.SetHigh();
}

void Bus::SetADPinsToOpenDrain()
{
    for(uint8_t i = 0; i < num_of_ad_pins; i++)
    {
        ad[i].GetPin().SetAsOpenDrain();
    }
}

void Bus::SetADPinsToOutput()
{
    for(uint8_t i = 0; i < num_of_ad_pins; i++)
    {
        ad[i].SetAsOutput();
    }
}

void Bus::SetADPinsToInput()
{
    for(uint8_t i = 0; i < num_of_ad_pins; i++)
    {
        ad[i].SetAsInput();
    }
}

void Bus::Write(ControlType control, uint8_t address, uint8_t data)
{
    SetADPinsToOutput();
    if(control == ControlType::kMemory)
    {
        LOG_INFO("MEMORY WRITE. address: %i data:%i", address, data);

        ALE.SetHigh();
        W.SetHigh();
        M_IO.SetHigh();

        // Set Control Signals to latch address
        printf("address: ");
        SetValueOfADPins(address);

        // ENABLE CS FOR SRAM
        // A7 = 0: SRAM 0
        // A7 = 1: SRAM 1
        ALE.SetLow();

        // Set Control Signals to send data to SRAM
        printf("data: ");
        SetValueOfADPins(data);

        // SetADPinsToInput();
        W.SetLow();
    }
    else if(control == ControlType::kIO)
    {
        LOG_INFO("IO WRITE. address: %i data:%i", address, data);
    }
}

uint8_t Bus::Read(ControlType control, uint8_t address)
{
    uint8_t data = 0;
    if(control == ControlType::kMemory)
    {
        LOG_INFO("MEMORY READ. address: %i", address);

        ALE.SetHigh();
        W.SetHigh();
        M_IO.SetHigh();

        // Set Control Signals to latch address
        printf("address: ");
        SetValueOfADPins(address);

        ALE.SetLow();
        W.SetLow();

        // Set Control Signals to Read from SRAM
        // data = ReadValueofADPins();
    }
    else if(control == ControlType::kIO)
    {
        LOG_INFO("IO READ. address: %i", address);
    }
    return data;
}

void Bus::SetValueOfADPins(uint8_t val)
{
    for(uint8_t i = num_of_ad_pins; i > 0; i--)
    {
        // LOG_INFO("%X", val & (1 << i));
        if(val & (1 << (i - 1)))
        {
            printf("1");
            ad[i-1].SetHigh();
        }
        else
        {
            printf("0");
            ad[i-1].SetLow();
        }
    }
    printf("\n");
}

uint8_t Bus::ReadValueofADPins()
{
    SetADPinsToInput();
    uint8_t data_read = 0;
    for(uint8_t i = num_of_ad_pins; i > 0; i--)
    {
        // LOG_INFO("%X", data_read & (1 << i));
        if(ad[i-1].Read())
        {
            data_read |= (1 << (i -1));
        }
    }
    printf("\n");
    printf("data read: %i\n", data_read);
    return data_read;
}