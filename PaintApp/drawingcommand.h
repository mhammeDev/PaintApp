#ifndef DRAWINGCOMMAND_H
#define DRAWINGCOMMAND_H

#include <QUndoCommand>
#include <QPixmap>

class DrawingCommand : public QUndoCommand {
public:
    DrawingCommand(const QPixmap& prevState, const QPixmap& newState, std::function<void(const QPixmap&)> applyStateFn);

    void undo() override;
    void redo() override;

private:
    QPixmap prevState;
    QPixmap newState;
    std::function<void(const QPixmap&)> applyState;
};

#endif // DRAWINGCOMMAND_H
