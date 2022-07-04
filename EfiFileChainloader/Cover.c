#include "Main.h"

// based from https://github.com/NekomimiRouter/yahallo/blob/main/TegraFirmwareDump/Console.c
VOID Tegra3ConsoleInputFixup(VOID)
{
	EFI_STATUS                       Status                   = EFI_SUCCESS;
	UINTN                            NumInputProtocolHandles = 0;
	EFI_HANDLE *                     pInputHandles;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL *pScreenEfiInputProtocol;

	Status = gBS->LocateHandleBuffer(
	ByProtocol, &gEfiSimpleTextInProtocolGuid, NULL,
	&NumInputProtocolHandles, &pInputHandles);

	// Some sanity check here.
	if (!EFI_ERROR(Status) && NumInputProtocolHandles >= 3) {
		Status = gBS->HandleProtocol(
			pInputHandles[NumInputProtocolHandles - 1],
			&gEfiSimpleTextInProtocolGuid, (VOID **)&pScreenEfiInputProtocol);

		// Hack: force use the tCover Input for ConIn
		if (!EFI_ERROR(Status)) {
			gST->ConIn           = pScreenEfiInputProtocol;
			gST->ConsoleInHandle = pInputHandles[NumInputProtocolHandles - 1];
		}
	}
}