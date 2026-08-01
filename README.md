# Minimal FreeRTOS blinky for dsPIC33AK128MC

## What's actually in here

- `FreeRTOS/` - the FreeRTOS kernel (`tasks.c`, `queue.c`, `list.c`, headers)
  and the **official Microchip-authored dsPIC33A port**
  (`portable/MPLAB/dsPIC33A/port.c`, `port.S`, `portmacro.h`), taken directly
  from Microchip's `pic24-dspic33-freertos-demo` GitHub repo. That repo's
  dsPIC33A demo targets **dsPIC33AK128MC106** specifically - the exact device
  family you're using - so this port is a real, correct match, not a guess.
- `src/main.c` - trimmed way down from the official demo: one task that
  toggles `RA0` every 500ms, plus the same clock-init code the official demo
  uses (FRC + PLL1 → 50MHz Fosc). No queues, comtest, co-routines, or other
  demo scaffolding.
- `src/FreeRTOSConfig.h` - trimmed version of the official demo's config
  (removed co-routines/trace, since this example doesn't use them).
- `CMakeLists.txt` - **this part is a best-effort reconstruction, not something
  I could verify**, explained below.

## Important honest caveat about the CMake file

I don't have the MPLAB VS Code extension or the XC-DSC compiler available in
my environment, so I can't actually run "MPLAB: Create New Project" and see
the exact `CMakeLists.txt`, toolchain file, and `.vscode/*.json` it generates
for your installed extension version. The `CMakeLists.txt` I included is a
plain, generic reconstruction (right source files, right include paths, right
device name) - but the exact compiler flags and linker script wiring the
extension expects may differ.

**Recommended path** (avoids fighting an unverified CMakeLists.txt):

1. In VS Code, run **MPLAB: Create New Project**, select device
   `dsPIC33AK128MC106` (or your exact part number), toolchain = your XC-DSC
   install, project type = Standard Application. Let it fully generate
   `_build`, `.vscode`, and `cmake` - this gives you a CMakeLists.txt that's
   guaranteed to match your actual toolchain.
2. Delete the placeholder `main.c` it creates.
3. Copy the `FreeRTOS/` folder and `src/main.c` + `src/FreeRTOSConfig.h` from
   this zip into that new project folder.
4. Open the generated `CMakeLists.txt` and add the FreeRTOS sources to its
   `add_executable(...)`/source list, and add `FreeRTOS/include` and
   `FreeRTOS/portable/MPLAB/dsPIC33A` to its include directories - just merge
   these into the existing structure rather than replacing the file.
5. Build. If it complains about a missing `xc.h`/device header, that's just
   the normal "select device pack" step, not a FreeRTOS issue.

If you'd rather just try the included `CMakeLists.txt` directly, it's a
reasonable starting skeleton - you'll likely need to fix the compiler flags
(the `-mcpu=` line is a placeholder) to whatever your XC-DSC actually expects.

## Adjusting the blink pin

`src/main.c` toggles `RA0` via `TRISAbits.TRISA0` / `LATAbits.LATA0`. Change
those two lines to whatever pin has an LED (or a scope probe) on your actual
board. If you've already got pin config from MCC's Pin Grid View, use those
generated macros instead and just keep the `^=` toggle + `vTaskDelay` in
`vBlinkTask`.

## Why FreeRTOS isn't in MCC's Device Resources for this part

MCC Melody's "FreeRTOS Library" GUI component currently only lists AVR
DA/DB/DD as supported devices - it doesn't cover dsPIC33/PIC24 (including
dsPIC33AK) yet. For those parts, Microchip ships FreeRTOS support as source +
a pre-integrated demo project instead, which is what this zip is built from.

## License

FreeRTOS kernel and the dsPIC33A port files are MIT-licensed by Amazon.com,
Inc. (FreeRTOS) / Microchip Technology Inc., unchanged from the official
`pic24-dspic33-freertos-demo` repository.
