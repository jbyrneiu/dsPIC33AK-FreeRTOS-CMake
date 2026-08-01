# ---------------------------------------------------------------------------
# REFERENCE CMakeLists.txt - see README.md before using this directly.
#
# The MPLAB extensions for VS Code generate their own CMakeLists.txt / toolchain
# files / .vscode/*.json when you create a project through the "MPLAB: Create
# New Project" wizard, and those generated files are tied to your installed
# extension + XC-DSC version. This file is a plain, generic reconstruction of
# what that build needs (device, sources, include paths) so you can either:
#   (a) merge these settings into a wizard-generated CMakeLists.txt (recommended), or
#   (b) try building with this file directly, adjusting compiler paths/flags
#       to match what your installed XC-DSC toolchain actually expects.
# ---------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.20)

project(dspic33ak_freertos_blinky C ASM)

set(MCU_DEVICE dsPIC33AK128MC106 CACHE STRING "Target device")

add_executable(${PROJECT_NAME}
    main.c
    FreeRTOS/tasks.c
    FreeRTOS/queue.c
    FreeRTOS/list.c
    FreeRTOS/timers.c
    FreeRTOS/portable/MPLAB/dsPIC33A/port.c
    FreeRTOS/portable/MPLAB/dsPIC33A/port.S
    FreeRTOS/portable/MemMang/heap_4.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    FreeRTOS/include
    FreeRTOS/portable/MPLAB/dsPIC33A
)

# --- Device/toolchain flags -------------------------------------------------
# These are placeholders. Confirm the actual -mcpu / -mprocessor style flag
# and any -x assembler-with-cpp flags your XC-DSC version expects (check a
# wizard-generated project's .vscode/lab0.mplab.json or verbose build log for
# the real invocation), then replace the two lines below accordingly.
target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=${MCU_DEVICE}
    -O0
    -g
)

# A wizard-generated project also sets a device-specific linker script and
# post-build steps (.hex generation, memory usage summary) via its own CMake
# toolchain file - add those here if you're not merging into that project.
