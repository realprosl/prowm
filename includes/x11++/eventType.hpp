#pragma once

namespace x {
    enum class EventType {
        keyPress = 2,
        keyRelease,
        buttonPress,
        buttonRelease,
        motionNotify,
        enterNotify,
        leaveNotify,
        focusIn,
        focusOut,
        keymapNotify,
        expose,
        graphicsExpose,
        noExpose,
        circulateRequest,
        configureRequest,
        mapRequest,
        resizeRequest,
        circulateNotify,
        configureNotify,
        createNotify,
        destroyNotify,
        gravityNotify,
        mapNotify,
        mappingNotify,
        reparentNotify,
        unmapNotify,
        visibilityNotify,
        colormapNotify,
        clientMessage,
        propertyNotify,
        selectionClear,
        selectionNotify,
        selectionRequest
};
}