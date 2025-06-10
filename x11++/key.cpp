#include <x11++/key.hpp>

namespace key {
    static KeySym get_keysym_from_event(Event& event) {
        if (event.type == KeyPress || event.type == KeyRelease) {
            return XLookupKeysym(reinterpret_cast<XKeyEvent*>(&event), 0);
        }
        return NoSymbol; // Devuelve un símbolo inválido si no es un evento de teclado
    }

    // --- Implementaciones de funciones para letras (minúsculas y mayúsculas) ---
    bool is_a(Event& event) { return get_keysym_from_event(event) == XK_a; }
    bool is_b(Event& event) { return get_keysym_from_event(event) == XK_b; }
    bool is_c(Event& event) { return get_keysym_from_event(event) == XK_c; }
    bool is_d(Event& event) { return get_keysym_from_event(event) == XK_d; }
    bool is_e(Event& event) { return get_keysym_from_event(event) == XK_e; }
    bool is_f(Event& event) { return get_keysym_from_event(event) == XK_f; }
    bool is_g(Event& event) { return get_keysym_from_event(event) == XK_g; }
    bool is_h(Event& event) { return get_keysym_from_event(event) == XK_h; }
    bool is_i(Event& event) { return get_keysym_from_event(event) == XK_i; }
    bool is_j(Event& event) { return get_keysym_from_event(event) == XK_j; }
    bool is_k(Event& event) { return get_keysym_from_event(event) == XK_k; }
    bool is_l(Event& event) { return get_keysym_from_event(event) == XK_l; }
    bool is_m(Event& event) { return get_keysym_from_event(event) == XK_m; }
    bool is_n(Event& event) { return get_keysym_from_event(event) == XK_n; }
    bool is_o(Event& event) { return get_keysym_from_event(event) == XK_o; }
    bool is_p(Event& event) { return get_keysym_from_event(event) == XK_p; }
    bool is_q(Event& event) { return get_keysym_from_event(event) == XK_q; }
    bool is_r(Event& event) { return get_keysym_from_event(event) == XK_r; }
    bool is_s(Event& event) { return get_keysym_from_event(event) == XK_s; }
    bool is_t(Event& event) { return get_keysym_from_event(event) == XK_t; }
    bool is_u(Event& event) { return get_keysym_from_event(event) == XK_u; }
    bool is_v(Event& event) { return get_keysym_from_event(event) == XK_v; }
    bool is_w(Event& event) { return get_keysym_from_event(event) == XK_w; }
    bool is_x(Event& event) { return get_keysym_from_event(event) == XK_x; }
    bool is_y(Event& event) { return get_keysym_from_event(event) == XK_y; }
    bool is_z(Event& event) { return get_keysym_from_event(event) == XK_z; }

    bool is_A(Event& event) { return get_keysym_from_event(event) == XK_A; }
    bool is_B(Event& event) { return get_keysym_from_event(event) == XK_B; }
    bool is_C(Event& event) { return get_keysym_from_event(event) == XK_C; }
    bool is_D(Event& event) { return get_keysym_from_event(event) == XK_D; }
    bool is_E(Event& event) { return get_keysym_from_event(event) == XK_E; }
    bool is_F(Event& event) { return get_keysym_from_event(event) == XK_F; }
    bool is_G(Event& event) { return get_keysym_from_event(event) == XK_G; }
    bool is_H(Event& event) { return get_keysym_from_event(event) == XK_H; }
    bool is_I(Event& event) { return get_keysym_from_event(event) == XK_I; }
    bool is_J(Event& event) { return get_keysym_from_event(event) == XK_J; }
    bool is_K(Event& event) { return get_keysym_from_event(event) == XK_K; }
    bool is_L(Event& event) { return get_keysym_from_event(event) == XK_L; }
    bool is_M(Event& event) { return get_keysym_from_event(event) == XK_M; }
    bool is_N(Event& event) { return get_keysym_from_event(event) == XK_N; }
    bool is_O(Event& event) { return get_keysym_from_event(event) == XK_O; }
    bool is_P(Event& event) { return get_keysym_from_event(event) == XK_P; }
    bool is_Q(Event& event) { return get_keysym_from_event(event) == XK_Q; }
    bool is_R(Event& event) { return get_keysym_from_event(event) == XK_R; }
    bool is_S(Event& event) { return get_keysym_from_event(event) == XK_S; }
    bool is_T(Event& event) { return get_keysym_from_event(event) == XK_T; }
    bool is_U(Event& event) { return get_keysym_from_event(event) == XK_U; }
    bool is_V(Event& event) { return get_keysym_from_event(event) == XK_V; }
    bool is_W(Event& event) { return get_keysym_from_event(event) == XK_W; }
    bool is_X(Event& event) { return get_keysym_from_event(event) == XK_X; }
    bool is_Y(Event& event) { return get_keysym_from_event(event) == XK_Y; }
    bool is_Z(Event& event) { return get_keysym_from_event(event) == XK_Z; }

    // --- Implementaciones de funciones para números ---
    bool is_0(Event& event) { return get_keysym_from_event(event) == XK_0; }
    bool is_1(Event& event) { return get_keysym_from_event(event) == XK_1; }
    bool is_2(Event& event) { return get_keysym_from_event(event) == XK_2; }
    bool is_3(Event& event) { return get_keysym_from_event(event) == XK_3; }
    bool is_4(Event& event) { return get_keysym_from_event(event) == XK_4; }
    bool is_5(Event& event) { return get_keysym_from_event(event) == XK_5; }
    bool is_6(Event& event) { return get_keysym_from_event(event) == XK_6; }
    bool is_7(Event& event) { return get_keysym_from_event(event) == XK_7; }
    bool is_8(Event& event) { return get_keysym_from_event(event) == XK_8; }
    bool is_9(Event& event) { return get_keysym_from_event(event) == XK_9; }

    // --- Implementaciones de funciones para caracteres especiales y signos de puntuación ---
    bool is_space(Event& event) { return get_keysym_from_event(event) == XK_space; }
    bool is_return(Event& event) { return get_keysym_from_event(event) == XK_Return; }
    bool is_tab(Event& event) { return get_keysym_from_event(event) == XK_Tab; }
    bool is_escape(Event& event) { return get_keysym_from_event(event) == XK_Escape; }
    bool is_backspace(Event& event) { return get_keysym_from_event(event) == XK_BackSpace; }
    bool is_delete(Event& event) { return get_keysym_from_event(event) == XK_Delete; }

    bool is_exclam(Event& event) { return get_keysym_from_event(event) == XK_exclam; }
    bool is_at(Event& event) { return get_keysym_from_event(event) == XK_at; }
    bool is_numbersign(Event& event) { return get_keysym_from_event(event) == XK_numbersign; }
    bool is_dollar(Event& event) { return get_keysym_from_event(event) == XK_dollar; }
    bool is_percent(Event& event) { return get_keysym_from_event(event) == XK_percent; }
    bool is_asciicircum(Event& event) { return get_keysym_from_event(event) == XK_asciicircum; }
    bool is_ampersand(Event& event) { return get_keysym_from_event(event) == XK_ampersand; }
    bool is_asterisk(Event& event) { return get_keysym_from_event(event) == XK_asterisk; }
    bool is_parenleft(Event& event) { return get_keysym_from_event(event) == XK_parenleft; }
    bool is_parenright(Event& event) { return get_keysym_from_event(event) == XK_parenright; }
    bool is_minus(Event& event) { return get_keysym_from_event(event) == XK_minus; }
    bool is_underscore(Event& event) { return get_keysym_from_event(event) == XK_underscore; }
    bool is_equal(Event& event) { return get_keysym_from_event(event) == XK_equal; }
    bool is_plus(Event& event) { return get_keysym_from_event(event) == XK_plus; }
    bool is_bracketleft(Event& event) { return get_keysym_from_event(event) == XK_bracketleft; }
    bool is_bracketright(Event& event) { return get_keysym_from_event(event) == XK_bracketright; }
    bool is_braceleft(Event& event) { return get_keysym_from_event(event) == XK_braceleft; }
    bool is_braceright(Event& event) { return get_keysym_from_event(event) == XK_braceright; }
    bool is_backslash(Event& event) { return get_keysym_from_event(event) == XK_backslash; }
    bool is_bar(Event& event) { return get_keysym_from_event(event) == XK_bar; }
    bool is_semicolon(Event& event) { return get_keysym_from_event(event) == XK_semicolon; }
    bool is_colon(Event& event) { return get_keysym_from_event(event) == XK_colon; }
    bool is_apostrophe(Event& event) { return get_keysym_from_event(event) == XK_apostrophe; }
    bool is_quotedbl(Event& event) { return get_keysym_from_event(event) == XK_quotedbl; }
    bool is_comma(Event& event) { return get_keysym_from_event(event) == XK_comma; }
    bool is_less(Event& event) { return get_keysym_from_event(event) == XK_less; }
    bool is_period(Event& event) { return get_keysym_from_event(event) == XK_period; }
    bool is_greater(Event& event) { return get_keysym_from_event(event) == XK_greater; }
    bool is_slash(Event& event) { return get_keysym_from_event(event) == XK_slash; }
    bool is_question(Event& event) { return get_keysym_from_event(event) == XK_question; }
    bool is_grave(Event& event) { return get_keysym_from_event(event) == XK_grave; }
    bool is_asciitilde(Event& event) { return get_keysym_from_event(event) == XK_asciitilde; }

    // --- Implementaciones de funciones para teclas de función ---
    bool is_F1(Event& event) { return get_keysym_from_event(event) == XK_F1; }
    bool is_F2(Event& event) { return get_keysym_from_event(event) == XK_F2; }
    bool is_F3(Event& event) { return get_keysym_from_event(event) == XK_F3; }
    bool is_F4(Event& event) { return get_keysym_from_event(event) == XK_F4; }
    bool is_F5(Event& event) { return get_keysym_from_event(event) == XK_F5; }
    bool is_F6(Event& event) { return get_keysym_from_event(event) == XK_F6; }
    bool is_F7(Event& event) { return get_keysym_from_event(event) == XK_F7; }
    bool is_F8(Event& event) { return get_keysym_from_event(event) == XK_F8; }
    bool is_F9(Event& event) { return get_keysym_from_event(event) == XK_F9; }
    bool is_F10(Event& event) { return get_keysym_from_event(event) == XK_F10; }
    bool is_F11(Event& event) { return get_keysym_from_event(event) == XK_F11; }
    bool is_F12(Event& event) { return get_keysym_from_event(event) == XK_F12; }

    // --- Implementaciones de funciones para teclas de navegación y edición ---
    bool is_Home(Event& event) { return get_keysym_from_event(event) == XK_Home; }
    bool is_End(Event& event) { return get_keysym_from_event(event) == XK_End; }
    bool is_Prior(Event& event) { return get_keysym_from_event(event) == XK_Prior; }
    bool is_Next(Event& event) { return get_keysym_from_event(event) == XK_Next; }
    bool is_Insert(Event& event) { return get_keysym_from_event(event) == XK_Insert; }
    bool is_Up(Event& event) { return get_keysym_from_event(event) == XK_Up; }
    bool is_Down(Event& event) { return get_keysym_from_event(event) == XK_Down; }
    bool is_Left(Event& event) { return get_keysym_from_event(event) == XK_Left; }
    bool is_Right(Event& event) { return get_keysym_from_event(event) == XK_Right; }

    // --- Implementaciones de funciones para modificadores ---
    bool is_Shift_L(Event& event) { return get_keysym_from_event(event) == XK_Shift_L; }
    bool is_Shift_R(Event& event) { return get_keysym_from_event(event) == XK_Shift_R; }
    bool is_Control_L(Event& event) { return get_keysym_from_event(event) == XK_Control_L; }
    bool is_Control_R(Event& event) { return get_keysym_from_event(event) == XK_Control_R; }
    bool is_Alt_L(Event& event) { return get_keysym_from_event(event) == XK_Alt_L; }
    bool is_Alt_R(Event& event) { return get_keysym_from_event(event) == XK_Alt_R; }
    bool is_Super_L(Event& event) { return get_keysym_from_event(event) == XK_Super_L; } // Tecla de Windows/Comando
    bool is_Super_R(Event& event) { return get_keysym_from_event(event) == XK_Super_R; } // Tecla de Windows/Comando
    bool is_Caps_Lock(Event& event) { return get_keysym_from_event(event) == XK_Caps_Lock; }
    bool is_Num_Lock(Event& event) { return get_keysym_from_event(event) == XK_Num_Lock; }
    bool is_Scroll_Lock(Event& event) { return get_keysym_from_event(event) == XK_Scroll_Lock; }

    // --- Implementaciones de funciones para teclado numérico (Keypad) ---
    bool is_KP_0(Event& event) { return get_keysym_from_event(event) == XK_KP_0; }
    bool is_KP_1(Event& event) { return get_keysym_from_event(event) == XK_KP_1; }
    bool is_KP_2(Event& event) { return get_keysym_from_event(event) == XK_KP_2; }
    bool is_KP_3(Event& event) { return get_keysym_from_event(event) == XK_KP_3; }
    bool is_KP_4(Event& event) { return get_keysym_from_event(event) == XK_KP_4; }
    bool is_KP_5(Event& event) { return get_keysym_from_event(event) == XK_KP_5; }
    bool is_KP_6(Event& event) { return get_keysym_from_event(event) == XK_KP_6; }
    bool is_KP_7(Event& event) { return get_keysym_from_event(event) == XK_KP_7; }
    bool is_KP_8(Event& event) { return get_keysym_from_event(event) == XK_KP_8; }
    bool is_KP_9(Event& event) { return get_keysym_from_event(event) == XK_KP_9; }
    bool is_KP_Add(Event& event) { return get_keysym_from_event(event) == XK_KP_Add; }
    bool is_KP_Subtract(Event& event) { return get_keysym_from_event(event) == XK_KP_Subtract; }
    bool is_KP_Multiply(Event& event) { return get_keysym_from_event(event) == XK_KP_Multiply; }
    bool is_KP_Divide(Event& event) { return get_keysym_from_event(event) == XK_KP_Divide; }
    bool is_KP_Enter(Event& event) { return get_keysym_from_event(event) == XK_KP_Enter; }
    bool is_KP_Decimal(Event& event) { return get_keysym_from_event(event) == XK_KP_Decimal; }
    bool is_KP_Equal(Event& event) { return get_keysym_from_event(event) == XK_KP_Equal; }

} // namespace key