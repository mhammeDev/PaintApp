#include "drawingcommand.h"

DrawingCommand::DrawingCommand(const QPixmap& prevState, const QPixmap& newState, std::function<void(const QPixmap&)> applyStateFn)
    : prevState(prevState), newState(newState), applyState(applyStateFn) {
}

void DrawingCommand::undo() {
    applyState(prevState);
}

void DrawingCommand::redo() {
    applyState(newState);
}
