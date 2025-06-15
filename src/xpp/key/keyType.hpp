#include "X11/X.h"
#include<X11/Xlib.h>

namespace key{
    enum {
    // Teclas Modificadoras
    Control = 0, // Generalmente Control_L o Control_R
    Shift,       // Generalmente Shift_L o Shift_R
    Alt,         // Generalmente Alt_L o Alt_R (Mod1Mask en X11)
    Super,       // Tecla Windows/Command (Mod4Mask en X11)
    Meta,        // Tecla Meta (a veces Alt, a veces otra ModMask)
    CapsLock,    // Bloqueo de mayúsculas (LockMask en X11)
    NumLock,     // Bloqueo numérico (NumLockMask en X11)
    // Teclas de Función
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    // Teclas de Edición y Navegación
    Enter,       // O Return
    Backspace,
    Tab,
    Space,
    Escape,
    Delete,      // Tecla Supr
    Insert,
    Home,
    End,
    PageUp,
    PageDown,
    // Teclas de Dirección
    ArrowUp,
    ArrowDown,
    ArrowLeft,
    ArrowRight,
    // Teclas del Teclado Numérico (Keypad)
    Keypad0,
    Keypad1,
    Keypad2,
    Keypad3,
    Keypad4,
    Keypad5,
    Keypad6,
    Keypad7,
    Keypad8,
    Keypad9,
    KeypadPeriod, // .
    KeypadDivide, // /
    KeypadMultiply, // *
    KeypadSubtract, // -
    KeypadAdd,      // +
    KeypadEnter,    // Enter del teclado numérico
    // otras
    PrintScreen, // Impr Pant
    ScrollLock,
    Pause,       // Pausa/Inter
    Menu,        // Tecla de menú contextual
};

}