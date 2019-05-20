#include <project_config.hpp>

#include <cstdint>
#include <iterator>

#include "Bus.hpp"
#include "utility/log.hpp"

int main(void)
{
    Bus bus;
    bus.Init();

    int option, user_input, address, data;

    // bus.Write(Bus::ControlType::kMemory, 0xAB, 0xCA);
    // // bus.SetValueOfADPins(0xAB);
    // Delay(2000);

    do
    {
        printf("\n----------------------\nPlease choose an option:\n1. Write to SRAM\n2. Read from SRAM\n3. Quit\n\nChoice: ");
        scanf("%d", &option);
        printf("You chose option %d!\n\n", option);

        if(option == 1)
        {
            printf("Enter address: ");
            scanf("%d", &address);
            printf("address: %d\n", address);
            printf("Enter data: ");
            scanf("%d", &data);
            printf("data: %d\n", data);
    
            printf("address: %d, data: %d\n", address, data);

            printf("address: %d data %d\n", address, data);
            bus.Write(Bus::ControlType::kMemory, address, data);
        }
        else if(option == 2)
        {
            printf("\nEnter an address (0 - 255): ");
            scanf("%d", &address);
            printf("address: %i\n", address);

            printf("%d\n", bus.Read(Bus::ControlType::kMemory, address));
        }
        else if(option == 3)
        {
            printf("\nQuitting\n");
        }
        else
        {
            printf("\nINVALID option. Please try again!\n\n");
        }
    }while(option != 3);


    return 0;
}
