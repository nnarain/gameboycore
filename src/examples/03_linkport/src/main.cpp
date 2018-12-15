#include <gameboycore/gameboycore.h>
#include <gameboycore/link_cable.h>

using namespace gb;

int main(int argc, char * argv[])
{
    // Create two GameboyCore instances
    GameboyCore core1;
    GameboyCore core2;

    // An object representing the link cable used to connect two gameboys
    LinkCable cable;

    // When link 1 is ready to transfer a byte, inform the link cable
    core1.setLinkReadyCallback([&cable](uint8_t byte, Link::Mode mode) {
        cable.link1ReadyCallback(byte, mode);
    });

    // When link 2 is ready to transfer a byte, inform the link cable
    core2.setLinkReadyCallback([&cable](uint8_t byte, Link::Mode mode) {
        cable.link2ReadyCallback(byte, mode);
    });

    // When the link cable has done the transfer it fires a callback for the transfered bytes
    
    // Set callback for core1 recieving a byte
    cable.setLink1RecieveCallback([&core1](uint8_t byte) {
        core1.linkWrite(byte);
    });

    // Set callback for core2 recieving a byte
    cable.setLink2RecieveCallback([&core2](uint8_t byte) {
        core2.linkWrite(byte);
    });
    
    return 0;
}
