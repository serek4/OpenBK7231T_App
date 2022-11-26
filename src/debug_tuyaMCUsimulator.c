#ifdef WINDOWS

#include "new_common.h"

const char *dataToSimulate[] =
{
	// dummy entry in order to avoid problems with empty table
	"",
#if 0
#elif 0
	"55AA0307000801020004000000041C",
	"55AA030700130600000F0000000C0000001001C3000077091CAD",
	"55AA0307000509050001001D",
	"55AA03070005100100010121",
	"55AA030700221100001E00000000000000000000006400010E0000AA00000000000A00000000000081",
	"55AA0307001512000011000500640005001E003C0000000000000009",
	"55AA03070008650200040000000480",
	"55AA0307000866020004000000007D",
	"55AA03070008670200040000000C8A",
	"55AA0307000869020004000013881B",
	"55AA030700086D0200040000000387",
	"55AA030700086E0200040000001095",
	"55AA030700086F020004000001BE45",
#elif 1

#else
	"55AA030700130600000F000000BF0000013C01F800064F0930B4",
	"55AA030700130600000F000000BD0000013C01F40006450936AA",
	"55AA030700130600000F000000C10000013C01FD000653092EBD",
	"55AA030700130600000F000000BD0000013B01F6000646092EA4",
	"55AA030700130600000F000000BD0000013B01F5000646092DA2",
#endif
};
int g_totalStrings = sizeof(dataToSimulate) / sizeof(dataToSimulate[0]);

int delay_between_packets = 200;
int curString = 0;
const char *curP = 0;
int current_delay_to_wait_ms = 1000;

void NewTuyaMCUSimulator_RunQuickTick(int deltaMS) {
	byte b;

	if (g_totalStrings <= 0) {
		return;
	}
	if (current_delay_to_wait_ms > 0) {
		current_delay_to_wait_ms -= deltaMS;
		return;
	}
	if (curP == 0) {
		curP = dataToSimulate[curString];
	}

	if (*curP != 0) {
		b = hexbyte(curP);
		UART_AppendByteToCircularBuffer(b);
		curP += 2;
	}
	if (*curP == 0) {
		curString++;
		if (curString >= g_totalStrings)
			curString = 0;
		curP = 0;
		current_delay_to_wait_ms = delay_between_packets;
	}

}


#endif


