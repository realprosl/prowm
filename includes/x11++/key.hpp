#include<X11/Xlib.h>
#include<X11/X.h>
#include<X11/keysym.h>
#include<X11/Xutil.h>
#include "event.hpp"


#pragma once

namespace key{
    using namespace x;
    bool is_a(Event& event);
    bool is_b(Event& event);
    bool is_c(Event& event);
    bool is_d(Event& event);
    bool is_e(Event& event);
    bool is_f(Event& event);
    bool is_g(Event& event);
    bool is_h(Event& event);
    bool is_i(Event& event);
    bool is_j(Event& event);
    bool is_k(Event& event);
    bool is_l(Event& event);
    bool is_m(Event& event);
    bool is_n(Event& event);
    bool is_o(Event& event);
    bool is_p(Event& event);
    bool is_q(Event& event);
    bool is_r(Event& event);
    bool is_s(Event& event);
    bool is_t(Event& event);
    bool is_u(Event& event);
    bool is_v(Event& event);
    bool is_w(Event& event);
    bool is_x(Event& event);
    bool is_y(Event& event);
    bool is_z(Event& event);

    bool is_A(Event& event);
    bool is_B(Event& event);
    bool is_C(Event& event);
    bool is_D(Event& event);
    bool is_E(Event& event);
    bool is_F(Event& event);
    bool is_G(Event& event);
    bool is_H(Event& event);
    bool is_I(Event& event);
    bool is_J(Event& event);
    bool is_K(Event& event);
    bool is_L(Event& event);
    bool is_M(Event& event);
    bool is_N(Event& event);
    bool is_O(Event& event);
    bool is_P(Event& event);
    bool is_Q(Event& event);
    bool is_R(Event& event);
    bool is_S(Event& event);
    bool is_T(Event& event);
    bool is_U(Event& event);
    bool is_V(Event& event);
    bool is_W(Event& event);
    bool is_X(Event& event);
    bool is_Y(Event& event);
    bool is_Z(Event& event);

    // --- Números ---
    bool is_0(Event& event);
    bool is_1(Event& event);
    bool is_2(Event& event);
    bool is_3(Event& event);
    bool is_4(Event& event);
    bool is_5(Event& event);
    bool is_6(Event& event);
    bool is_7(Event& event);
    bool is_8(Event& event);
    bool is_9(Event& event);

    // --- Caracteres especiales y signos de puntuación ---
    bool is_space(Event& event);
    bool is_return(Event& event); // Enter key
    bool is_tab(Event& event);
    bool is_escape(Event& event);
    bool is_backspace(Event& event);
    bool is_delete(Event& event);

    bool is_exclam(Event& event);       // !
    bool is_at(Event& event);           // @
    bool is_numbersign(Event& event);   // #
    bool is_dollar(Event& event);       // $
    bool is_percent(Event& event);      // %
    bool is_asciicircum(Event& event);  // ^
    bool is_ampersand(Event& event);    // &
    bool is_asterisk(Event& event);     // *
    bool is_parenleft(Event& event);    // (
    bool is_parenright(Event& event);   // )
    bool is_minus(Event& event);        // -
    bool is_underscore(Event& event);   // _
    bool is_equal(Event& event);        // =
    bool is_plus(Event& event);         // +
    bool is_bracketleft(Event& event);  // [
    bool is_bracketright(Event& event); // ]
    bool is_braceleft(Event& event);    // {
    bool is_braceright(Event& event);   // }
    bool is_backslash(Event& event);    // \
    bool is_bar(Event& event);          // |
    bool is_semicolon(Event& event);    // ;
    bool is_colon(Event& event);        // :
    bool is_apostrophe(Event& event);   // '
    bool is_quotedbl(Event& event);     // "
    bool is_comma(Event& event);        // ,
    bool is_less(Event& event);         // <
    bool is_period(Event& event);       // .
    bool is_greater(Event& event);      // >
    bool is_slash(Event& event);        // /
    bool is_question(Event& event);     // ?
    bool is_grave(Event& event);        // `
    bool is_asciitilde(Event& event);   // ~

    // --- Teclas de función ---
    bool is_F1(Event& event);
    bool is_F2(Event& event);
    bool is_F3(Event& event);
    bool is_F4(Event& event);
    bool is_F5(Event& event);
    bool is_F6(Event& event);
    bool is_F7(Event& event);
    bool is_F8(Event& event);
    bool is_F9(Event& event);
    bool is_F10(Event& event);
    bool is_F11(Event& event);
    bool is_F12(Event& event);

    // --- Teclas de navegación y edición ---
    bool is_Home(Event& event);
    bool is_End(Event& event);
    bool is_Prior(Event& event);    // Page Up
    bool is_Next(Event& event);     // Page Down
    bool is_Insert(Event& event);
    bool is_Up(Event& event);
    bool is_Down(Event& event);
    bool is_Left(Event& event);
    bool is_Right(Event& event);

    // --- Modificadores ---
    bool is_Shift_L(Event& event);
    bool is_Shift_R(Event& event);
    bool is_Control_L(Event& event);
    bool is_Control_R(Event& event);
    bool is_Alt_L(Event& event);
    bool is_Alt_R(Event& event);
    bool is_Super_L(Event& event);  // Tecla de Windows/Comando
    bool is_Super_R(Event& event);  // Tecla de Windows/Comando
    bool is_Caps_Lock(Event& event);
    bool is_Num_Lock(Event& event);
    bool is_Scroll_Lock(Event& event);

    // --- Teclado numérico (Keypad) ---
    bool is_KP_0(Event& event);
    bool is_KP_1(Event& event);
    bool is_KP_2(Event& event);
    bool is_KP_3(Event& event);
    bool is_KP_4(Event& event);
    bool is_KP_5(Event& event);
    bool is_KP_6(Event& event);
    bool is_KP_7(Event& event);
    bool is_KP_8(Event& event);
    bool is_KP_9(Event& event);
    bool is_KP_Add(Event& event);        // +
    bool is_KP_Subtract(Event& event);   // -
    bool is_KP_Multiply(Event& event);   // *
    bool is_KP_Divide(Event& event);     // /
    bool is_KP_Enter(Event& event);
    bool is_KP_Decimal(Event& event);    // .
    bool is_KP_Equal(Event& event);      // =
}